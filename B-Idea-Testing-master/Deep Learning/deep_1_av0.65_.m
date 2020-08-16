imds = imageDatastore('Training', ...
    'IncludeSubfolders',true, ...
    'LabelSource','foldernames');
numTrainFiles = 200;
[imdsTrain,imdsValidation] = splitEachLabel(imds,numTrainFiles,'randomize');


layers = [
    imageInputLayer([384 512 3],"Name","imageinput")
    convolution2dLayer([5 3],3,"Name","conv_1","Padding","same")
    reluLayer("Name","relu_1")
    batchNormalizationLayer("Name","batchnorm_1")
    maxPooling2dLayer([5 5],"Name","maxpool_2","Padding","same")
    convolution2dLayer([5 3],3,"Name","conv_2","Padding","same")
    reluLayer("Name","relu_2")
    batchNormalizationLayer("Name","batchnorm_2")
    maxPooling2dLayer([5 5],"Name","maxpool_1","Padding","same")
    fullyConnectedLayer(3,"Name","fc","BiasLearnRateFactor",10,"WeightLearnRateFactor",10)
    softmaxLayer("Name","softmax")
    classificationLayer("Name","classoutput")];

options = trainingOptions('sgdm', ...
    'MaxEpochs',10, ...
    'InitialLearnRate',1e-4, ...
    'ValidationData',imdsValidation, ...
    'ValidationFrequency',30, ...
    'Verbose',false, ...
    'Plots','training-progress');

net = trainNetwork(imdsTrain,layers,options);

YPred = classify(net,imdsValidation);
YValidation = imdsValidation.Labels;
accuracy = mean(YPred == YValidation)

 rubbish_net = net;
 save rubbish_net
