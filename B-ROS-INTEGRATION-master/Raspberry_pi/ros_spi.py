#!/usr/bin/env python 

#import modules
import spidev
import time
import rospy
import struct
from std_msgs.msg import String
from geometry_msgs.msg import Twist

#initialise SPIDev
spi=spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz = 500000
spi.mode=0
time.sleep(0.0005)

# ROS subscriber rostopic
def twist(msg):
	move = msg
	linearx = move.linear.x
	angularz = move.angular.z
	
	oldrange=(10+10)
	newrange=(2000-1000)
	
	linx = (((int(linearx)+10)*newrange)/oldrange)+1000
	angz = (((int(angularz)+10)*newrange)/oldrange)+1000
	endcap = 255
	print(linx)
	print(angz)
		
	spi.xfer([(linx & 0xFF00) >> 8])
	spi.xfer([(linx & 0xFF)])
	#spi.xfer([angz])
	spi.xfer([(angz & 0xFF00) >> 8])
	spi.xfer([(angz & 0xFF)])
	#spi.xfer([endcap])


def listener():
	#twist = Twist()
	rospy.init_node('pi_spi', anonymous=True) #node name
	print("start node")
	#rospy.Subscriber('cmd_vel', Twist, twist) #Topic name TBD
	#rospy.spin()
        #print("ros spun")

#main loop
print("Starting")
listener()
while 1 : # rospy.is_shutdown():
	sub = rospy.Subscriber('cmd_vel', Twist, twist) #Topic name TBD
	#spi.xfer(angularz)
	time.sleep(0.1)

	rospy.spin()

