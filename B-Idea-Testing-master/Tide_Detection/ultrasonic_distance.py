# https://thepihut.com/blogs/raspberry-pi-tutorials/hc-sr04-ultrasonic-range-sensor-on-the-raspberry-pi
# https://tutorials-raspberrypi.com/raspberry-pi-ultrasonic-sensor-hc-sr04/
# https://github.com/engcang/HC-SR04-UltraSonicSensor-ROS-RaspberryPi/blob/master/ROS_sonar_sensor.py

#!/usr/bin/python

#Libraries
import RPi.GPIO as GPIO
import time
import rospy
from std_msgs.msg import Float32

# Create publisher class
class Ultrasonic():
    def __init_node(self):
	rospy.init_node('sea_level', anonymous=True)
        self.distance_publisher = rospy.Publisher('/sea_level_dist',Float32, queue_size=1)
        self.r = rospy.Rate(15)  # How long it takes to send message
    def dist_sender(self,dist):
        data = Float32()
        data.data=dist
        self.distance_publisher.publish(data)

#GPIO Mode (BOARD / BCM)
GPIO.setmode(GPIO.BCM)
 
#set GPIO Pins
GPIO_TRIGGER = 23 # pin 16
GPIO_ECHO = 24    # pin 24
 
#set GPIO direction (IN / OUT)
GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
GPIO.setup(GPIO_ECHO, GPIO.IN)
 
def distance():
    # set Trigger to HIGH
    GPIO.output(GPIO_TRIGGER, True)
 
    # set Trigger after 0.01ms to LOW
    time.sleep(0.00001)
    GPIO.output(GPIO_TRIGGER, False)
 
    StartTime = time.time()
    StopTime = time.time()
 
    # save StartTime
    while GPIO.input(GPIO_ECHO) == 0:
        StartTime = time.time()
 
    # save time of arrival
    while GPIO.input(GPIO_ECHO) == 1:
        StopTime = time.time()
 
    # time difference between start and arrival
    TimeElapsed = StopTime - StartTime
    # multiply with the sonic speed (34300 cm/s)
    # and divide by 2, because there and back
    distance = (TimeElapsed * 34300) / 2
 
    return distance
print ('-----------------------------------------------------------------Ultrasound  start') 

if __name__ == '__main__':
    try:
        while True:
            dist = distance()
            print ("Measured Distance = %.1f cm" % dist)
            time.sleep(1)
 
        # Reset by pressing CTRL + C
    except KeyboardInterrupt:
        print("Measurement stopped by User")
        GPIO.cleanup()

