clear

camera = webcam;
neural = load('rubbish_net.mat');
%nnet.neural_net=neural.net;
while true
    w=waitforbuttonpress;
if w==1
    
%img = snapshot(camera);
%img = imresize(img,[384 512]);
%label = classify(neural.rubbish_net,img);
%imshow(img);
%title(char(label));
%drawnow;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ROI + MULTIPLE OBJECTS
img=imread('close crabs img.PNG');
imgI=rgb2gray(img);

normalizedThresholdValue = 0.8; % In range 0 to 1.
thresholdValue = normalizedThresholdValue * max(max(imgI)); % Gray Levels.
binaryImage = im2bw(imgI, normalizedThresholdValue);       % One way to threshold to binary
binaryImage = imfill(binaryImage, 'holes');

labeledImage = bwlabel(binaryImage, 8);
boundaries = bwboundaries(binaryImage);
blobMeasurements = regionprops(labeledImage, imgI, 'all');
numberOfBlobs = size(blobMeasurements, 1);

allBlobCentroids = [blobMeasurements.Centroid];
centroidsX = allBlobCentroids(1:2:end-1);
centroidsY = allBlobCentroids(2:2:end);

centroidsX = centroidsX';
centroidsY = centroidsY';

t=table(centroidsX,centroidsY);

writetable(t, 'interestingCoordinates.txt')
imshow(binaryImage);


%imgres=imresize(img,[384 512]);%Resizes to analyse areas
%bbox = classify(neural.rubbish_net,img);
%annotatedImage = insertShape(I,'Rectangle',bbox);
%annotatedImage = imresize(annotatedImage,2);




end
end