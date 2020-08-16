clear

camera = webcam;
neural = load('rubbish_net.mat');
%nnet.neural_net=neural.net;

while true
    
img = snapshot(camera);
img = imresize(img,[384 512]);

label = classify(neural.rubbish_net,img);

imshow(img);
title(char(label));
drawnow;

end
