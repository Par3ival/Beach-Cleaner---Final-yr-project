# B-ROS-INTEGRATION

https://github.com/tue-robotics/cb_base_navigation
`--- Example for nav stack use ---`

https://github.com/abhineet123/ORB_SLAM2 
`--- Example for 2D map for ORBSLAM ---`
# SETTING UP NEW CAMERAS FOR STEREO
This includes if cameras arent changed but their separation is

``rosrun camera_calibration cameracalibrator.py --approximate 1 --size 6x4 --square 0.12 right:=/cam_R/usb_camR/image_raw left:=/cam_L/usb_camL/image_raw left_camera:=/cam_L/usb_camL right_camera:=/cam_R/usb_camR``
