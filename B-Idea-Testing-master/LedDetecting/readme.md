# LED detecting code

inital light detecting code found at

https://www.pyimagesearch.com/2016/10/31/detecting-multiple-bright-spots-in-an-image-with-python-and-opencv/
http://t.dripemail2.com/c/eyJhY2NvdW50X2lkIjoiNDc2ODQyOSIsImRlbGl2ZXJ5X2lkIjoiODY2NzI2MDMyOCIsInVybCI6Imh0dHA6Ly9weWltZy5jby81cmRtaz9fX3M9cWV0eTIxY3NxZjFpNTd6emlyeXMifQ

After detecting lights it will cycle through the lights and take point around the light(labeled in green in the output image) and test for their color if the color is within a band on an hsv curve for hue (currently set to max band) it will be determined to be red, green or blue this will then be compared for each point to reach a consensus on color and add that to a list of numbered lights from left to right and their color.
The next step is to apply this to video and then determine flashing patterns

# How to run

1. install opencv, numpy and skimage for python 3
2. edit line 48 ( currently reading image = cv2.imread("/home/leo/Downloads/multiple-bright-spots/images/lights_02.png") ) to point to input image path
3. run in python 3
4. an image will be output in the directory you run the file in or in the directory the file is stored if using idle
