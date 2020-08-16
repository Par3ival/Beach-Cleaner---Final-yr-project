# Information on coding a Rapberry Pi will go here

## Downloading libraries
Downloading pip: `$ sudo apt install python-pip`

Downlaoding packages: `$ pip install [library name]` 

Check the package is available [here](https://pypi.org/)

## GPIO pinout
https://www.raspberrypi.org/documentation/usage/gpio/

## ROS_SPI and bb_SPI

These two programs were created in conjunction with oneanother to allow for the communication between a raspberry Pi and botboarduino/arduino. This has allowed for full remote control through ROS by subscribing to a topic on the PI, mapping the data and then transmitting over SPI for the aruduino (SPI slave) to recieve and then interpret to turn into movement commands.
