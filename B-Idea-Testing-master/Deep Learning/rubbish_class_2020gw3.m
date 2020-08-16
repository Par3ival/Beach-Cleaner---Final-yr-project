clear

rosinit('192.168.0.100:22')

camera = rossubscriber('/usb_cam/image_raw');
rubbishpub = rospublisher('/rubbish_label', 'std_msgs/String');
rubbishmsg = rosmessage(rubbishpub);

neural = load('rubbish_net2020.mat');
%nnet.neural_net2020=neural.net;

while true
    
    
img = readImage(camera);
img = imresize(img,[384 512]);
label = classify(neural.rubbish_net,img);


rubbishmsg.Data = label
imshow(img);
title(char(label));
drawnow;
end
