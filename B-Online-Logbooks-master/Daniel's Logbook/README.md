# DANS LOGBOOK

This will include anything that is too long or can only be accessed online.

# 21/10/2019 | Simulink Machine Vision

- [Optical Flow, Moving Object Tracking](https://youtu.be/3YoWCa4jGAI)

This is a short video depicting an initial test performed to assess the capabilities of simulink for machine vision. This                 is using an Optical Flow method which determines the change between two frames and masks the area which has changed.                       The program currently checks every frame to the last which could be slow/inefficient when used on a raspberry pi, but that                 can be adapted. There is also a variable value which determines the minimum size of each bounding box to be displayed,                     this prevents every possible change being displayed. This also uses blob analysis to determine where to draw the boxes based off the intensity image, which depicts what areas have moved.

# 24/10/2019 | Tracked Robot and Arm Testing

- [Robot Testing Compilation](https://www.youtube.com/watch?v=stPPC0m9og8)

This video depicts the outcomes of some tests that were performed to create an easy to use program that could be integrated with a wireless device in the future. This would allow the robot to connect to ROS quickly and easily allowing for better integration in the future.
In this video the robot is shown to be able to be controlled fully along with a 3 servo motor robotic arm, all using the same control board (Botboarduino), USB Host Shield and an Xbox controller. 

**Limitations:**

The whole system was powered through a National Instruments VirtualBench, supplying ``6V 1A and 7.5V 0.5A``. This was done due to the number of servo motors being used was drawing far too much current, causing the USB Host shield to not function correctly. The other downside of this setup is that only 4 motors can run concurrently. The solution to this is to use the SSC-32 Servo Motor control board, which will allow all of the motors to be powered on a separate board, thus increasing the reliability of the system. The robot also requires a system to transform the input from a 12V battery to roughly the same inputs as used from the Virtual Bench.

**Links To Components To Test**

- https://www.amazon.co.uk/Valefod-Efficiency-Voltage-Regulator-Converter-8-Pack/dp/B07DYP6L35/ref=pd_bxgy_23_3/260-3998133-8310120?_encoding=UTF8&pd_rd_i=B07DYP6L35&pd_rd_r=84bc9c07-7ac6-4a84-a82d-b573e9ee1a88&pd_rd_w=aiwYc&pd_rd_wg=FAjCH&pf_rd_p=ef559a91-574d-47a2-9928-86e4dd75e7e9&pf_rd_r=PS5B2B3VVGN3KG5RGHJ0&psc=1&refRID=PS5B2B3VVGN3KG5RGHJ0

*This is a buck converter to allow the use of the 12V battery with the botboarduino*

- [ ] Owned

-https://www.sparkfun.com/products/13678

*This is a wireless adapter. Connects via SPI and has built in TCP/IP protocols which allows it to work with the arduino platform*

- [ ] Owned

https://www.selectsolar.co.uk/prod/269/powerfilm-pt72150-200ma-72v-mini-solar-panel

*Flexible/Durable small solar panel for use atop a robot to increase its activity time whilst cleaning a beach*

- [ ] Owned

# 07/03/2020 | RTAB MAP Stereo Mapping+Navigation

Replacing orb-slam with Stereo slam using RTab map.

- https://github.com/introlab/rtabmap/wiki/Stereo-mapping

- http://wiki.ros.org/rtabmap_ros/Tutorials/SetupOnYourRobot#Stereo_A

- http://wiki.ros.org/viso2_ros

- http://wiki.ros.org/vision_opencv

# 09/03/2020 | RTAB MAP Stereo Mapping+Navigation: PART 2

- https://answers.ros.org/question/274701/rtabmapstereo-cameratwo-web-cam/

- https://answers.ros.org/question/267915/rtabmap-non-overlapping-3d-cloud/
