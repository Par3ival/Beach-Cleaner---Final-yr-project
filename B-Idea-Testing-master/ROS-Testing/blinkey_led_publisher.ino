/*#include <util.h>
#include <EthernetClient.h>
#include <Dhcp.h>
#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <Dns.h>

#include <SPI.h>

#include <ros.h>
//#include <ArduinoTcpHardware.h>
//#include <ArduinoHardware.h>*/

/*
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

// Arduino – ROS headers
#include <ros.h>
#include <std_msgs/Empty.h>

//Creating a Nodehandle object
ros::NodeHandle nh;

// Creating a callback for the topic toggle_led, whenever a value come through this topic, this callback will execute
// The callback will toggle the state of LED which is on PIN 13

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13)); // blink the led
}

//Creating a subscriber with a name toggle_led, and its callback
ros::Subscriber<std_msgs::Empty> sub(“toggle_led”, &messageCb);

//Setting PIN 13 as output and initializing ROS node and subscriber object
void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

// Spining the node each times to listen from the topic
void loop()
{
  nh.spinOnce();
  delay(1);
}
