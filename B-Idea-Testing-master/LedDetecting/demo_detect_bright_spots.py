# USAGE
# python detect_bright_spots.py --image images/lights_01.png

# import the necessary packages
from imutils import contours
from skimage import measure
import numpy as np
import imutils
import cv2
import colorsys
import time
import operator
#from time import sleep
colorthresh = 120
colorvalthresh = 80
colorinnerbound = -6
colorouterbound = -4
colorerrorthresh = 1000
colorsatthresh = 60

binA = ["red","","blue","","green","","green",""]
binB = [
"green",
"green",
"green",
"green",
"green",
"green",
"green",
"green",
"",
"",
"",
"",
"",
"",
"",
"",
"red",
"red",
"red",
"red",
"red",
"red",
"red",
"red",
"",
"",
"",
"",
"",
"",
"",
"",
"blue",
"blue",
"blue",
"blue",
"blue",
"blue",
"blue",
"blue",
"",
"",
"",
"",
"",
"",
"",
"",
]

#binC = 


def hsv2rgb(h,s,v):
    return tuple(round(i * 255) for i in colorsys.hsv_to_rgb(h,s,v))

def rgb2hsv(r,g,b):
    return tuple(i for i in colorsys.rgb_to_hsv(r/255,g/255,b/255))

def colorchek(pixel): #@@ use hsv range for color detection ie between red band green band blue band
        hsvcol = rgb2hsv(pixel[2],pixel[1],pixel[0]) # opencv uses bgr color
        hsvcoltest = hsvcol[0] *360
        if(hsvcol[1]*100>colorsatthresh):
            if(60<hsvcoltest<60+120):
                    return "green"
            if(180<hsvcoltest<180+120):
                    return "blue"
            if(hsvcoltest<60 or hsvcoltest>300):
                    return "red"
        return "unknown"
    
def colorcomparer(colarray):
        err = 0
        okpoint = 0
        for i in range(len(colarray)):
            for k in range(len(colarray)):
                        if colarray[i] != colarray[k]:
                                err += 1
                        else:
                                okpoint=k
        #print(err)
        if err>colorerrorthresh:
                return "unknown"
        else:
                return colarray[okpoint]
def patterncomparer(lightpattern,binpattern):
    for i in range(0,len(lightpattern)):
        if(lightpattern[i] == binpattern[i]):
            return "True"
        else:
            lightpattern.insert(0,lightpattern.pop)
    return "False"

def condense(lightpattern):
    newpattern = []
    for i in range(0,len(lightpattern),8):
        redcount = 0
        greencount = 0
        bluecount = 0
        nonecount = 0
        for j in range(0,8):
            col = lightpattern[i+j]
            if(col == "red"):
                redcount+=1
            elif(col == "green"):
                greencount+=1
            elif(col == "blue"):
                bluecount+=1
            else:
                nonecount+=1
            nonecount = nonecount/2
            stats = {"red":redcount, "green":greencount, "blue":bluecount, "none":nonecount}
            newpattern.append(max(stats.items(), key=operator.itemgetter(1))[0])
    return newpattern



# load the image, convert it to grayscale, and blur it
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output2.avi',fourcc, 20.0, (640,480))
cap = cv2.VideoCapture(0)
pattern = []
for frames in range(108):
    ret, image = cap.read()
    if ret==True:
         out.write(image)
cap.release()
out.release()

cap = cv2.VideoCapture('output2.avi')
out = cv2.VideoWriter('modified output.avi',fourcc, 20.0, (640,480))
#@@ capture 108 frames
for frames in range(108):
    ret, image = cap.read()
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (11, 11), 0)

    # threshold the image to reveal light regions in the
    # blurred image
    thresh = cv2.threshold(blurred, 190, 255, cv2.THRESH_BINARY)[1]

    # perform a series of erosions and dilations to remove
    # any small blobs of noise from the thresholded image
    thresh = cv2.erode(thresh, None, iterations=2)
    thresh = cv2.dilate(thresh, None, iterations=4)

    # perform a connected component analysis on the thresholded
    # image, then initialize a mask to store only the "large"
    # components
    labels = measure.label(thresh, connectivity=2, background=0)
    mask = np.zeros(thresh.shape, dtype="uint8")

    # loop over the unique components
    for label in np.unique(labels):
        # if this is the background label, ignore it
        if label == 0:
                continue

        # otherwise, construct the label mask and count the
        # number of pixels 
        labelMask = np.zeros(thresh.shape, dtype="uint8")
        labelMask[labels == label] = 255
        numPixels = cv2.countNonZero(labelMask)

        # if the number of pixels in the component is sufficiently
        # large, then add it to our mask of "large blobs"
        if numPixels > 300:
                mask = cv2.add(mask, labelMask)

    # find the contours in the mask, then sort them from left to
    # right
    cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
        cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)
    if(len(cnts)>1):
            cnts = contours.sort_contours(cnts)[0]

            lightsarray = []
            #@@ loop over the contours
            for (i, c) in enumerate(cnts):
                    #@@ find and draw the bright spot on the image
                    colorarray = []
                    (x, y, w, h) = cv2.boundingRect(c)
                    height, width, channels = image.shape

                    ((cX, cY), radius) = cv2.minEnclosingCircle(c)
                    cX=int(cX)
                    cY=int(cY)
                    oldrad = int(radius)+colorinnerbound
                    radius=int(radius)+colorouterbound
                    for k in range(cX-radius, cX+radius):
                            for j in range(cY-radius, cY+radius):
                                    if((k>cX+oldrad or k<cX-oldrad) and (j>cY+oldrad or j<cY-oldrad)):
                                            if(k<width and j<height):
                                                     
                                                    test = colorchek(image[j,k,:])
                                                    if (test != 0):
                                                            colorarray.append(test)
                                                    image[j,k,:] = (0,255,0)
                                            #else:
                                                    #print(j,k,cX,cY,i)
                    colcomp = colorcomparer(colorarray)
                    if(colcomp!='unknown'):
                        cv2.circle(image, (int(cX), int(cY)), int(radius),
                                (0, 0, 255), 3)
                        cv2.putText(image, "#{}".format(i + 1), (x, y - 15),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 0, 255), 2)
                        lightsarray.append(colcomp)
                        
            
            #finalcolor = []
            #for light in range(len(lightsarray)):
            #       finalcolor.append(colorcomparer(lightsarray[light]))
                    

            #@@ show the output image and display colour
            print(lightsarray)
            pattern.append(lightsarray)
            out.write(image)

            #@@ Display first 5 frames live
            ##if(frames<5):
            #cv2.imwrite('./imagesout.png',image)
                ##cv2.imshow("Image", image)
                ##cv2.waitKey(0)
out.release()


print("condensed") #, condense(pattern))


#@@ Final comparison
string = "False" # patterncomparer(condense(pattern),binA) 

print("is binA?",string)
