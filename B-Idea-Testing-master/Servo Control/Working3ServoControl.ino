#include <XBOXRECV.h>
#include <Servo.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

USB Usb;
XBOXRECV Xbox(&Usb);

int servoup = 3;
int servolr = 4;
int servoturn = 5;

Servo grip;
Servo wrist;
Servo wristlr;

void setup() {
  Serial.begin(115200);
  pinMode( 7, OUTPUT); //vital to set pin 7 HIGH in order to work!
  //pinMode(servoup, OUTPUT);
  //pinMode(servolr, OUTPUT);

  //digitalWrite( 7, HIGH);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  grip.attach(servoup);
  wrist.attach(servolr);
  wristlr.attach(servoturn);
}

void loop() {
  while(1){
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        

       int x = (Xbox.getAnalogHat(LeftHatX, i));
       int y = (Xbox.getAnalogHat(LeftHatY, i));
       int z = (Xbox.getAnalogHat(RightHatX, i));
       movement(x,y,z);
 
        
      /*int z = (Xbox.getAnalogHat(RightHatX, i));
      int v = (Xbox.getAnalogHat(RightHatY, i));
       
       
       
        if (z > 7500 || z < -7500 || v > 7500 || v < -7500) {
          
          if(v > 7500) {
            Serial.print("i"); //down
            delay(20);
          }
          if(v < -7500) {
            Serial.print("k"); //up
            delay(20);
          }
          if(z < -7500) {
            Serial.print("h"); //right 
            delay(20);
          }
          if(z > 7500) {
            Serial.print("j"); //left
            delay(20);
          }
          Serial.println();
        }*/
      }
    }
  }
  else{
    //digitalWrite( 7, HIGH);
    //digitalWrite(7, LOW);
    //digitalWrite(7, HIGH);
    while (!Serial);
  }
 }
}


void movement(int l, int k, int u){
       if (l > 7500 || l < -7500 || k > 7500 || k < -7500 || u > 7500 || u < -7500) {
          
          if(k > 7500) {
            //Serial.print("u"); //up
            //digitalWrite(servoup, HIGH);
            wrist.write(120);
            delay(20);
          }
          if(k < -7500) {
            //Serial.print("d"); //down
            //digitalWrite(servoup, LOW);
            wrist.write(60);
            delay(20);
          }
          if(l < -7500) {
            //Serial.print("l"); //left
            //digitalWrite(servolr, HIGH);
            grip.write(120); 
            delay(20);
          }
          if(l > 7500) {
            //Serial.print("r"); //right
            //digitalWrite(servolr, LOW);
            grip.write(60);
            delay(20);
          }
          if(u < -7500) {
            //Serial.print("l"); //left
            //digitalWrite(servolr, HIGH);
            wristlr.write(120); 
            delay(20);
          }
          if(u > 7500) {
            //Serial.print("r"); //right
            //digitalWrite(servolr, LOW);
            wristlr.write(60);
            delay(20);
          }
          //Serial.println();
        }
        
        else if ( l < 7500 && l > -7500 && k < 7500 && k > -7500 && u < 7500 && u > -7500) {
          //Serial.print("s"); //stationary
          //Serial.println();
          grip.write(90);
          wrist.write(90);
          wristlr.write(90);
        }
  }
