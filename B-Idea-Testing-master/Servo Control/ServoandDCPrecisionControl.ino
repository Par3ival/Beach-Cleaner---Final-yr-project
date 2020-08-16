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
//int servoturn = 5;
int servodrive = 2;
int servodrive2 = 5;

Servo grip;
Servo wrist;
//Servo wristlr;
Servo fwd;
Servo fwd2;

void setup() {
  Serial.begin(115200);
  pinMode( 7, OUTPUT); //vital to set pin 7 HIGH in order to work!
  pinMode(servodrive, OUTPUT);
  pinMode(servodrive2, OUTPUT);

  //digitalWrite( 7, HIGH);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  grip.attach(servoup);
  wrist.attach(servolr);
  //wristlr.attach(servoturn);
  fwd.attach(servodrive);
  fwd2.attach(servodrive2);
}

void loop() {
  while(1){
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        

       int x = (Xbox.getAnalogHat(LeftHatX, i));
       int y = (Xbox.getAnalogHat(LeftHatY, i));
       int z = (Xbox.getAnalogHat(RightHatY, i));
       int r = (Xbox.getAnalogHat(RightHatX, i));

       //Serial.print(z, DEC);
       //Serial.print("\n");
       //Serial.print(r, DEC);
       //Serial.print("\n");
       
       x = map(x, -32768, 32768, 1000, 2000);
       y = map(y, -32768, 32768, 1000, 2000);
       z = map(z, -32768, 32768, 1000, 2000);
       r = map(r, -32768, 32768, 1000, 2000);

       if(x > 1600 || x < 1400 || y > 1600 || y < 1400){
       smovement(x,y);
       }
       else{
       dcmovement(z,r);
       }
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


void smovement(int l, int k){
       if (l > 1000 || l < 2000 || k > 1000 || k < 2000) {
          
          if(k > 1500) {
            //Serial.print("u"); //up
            //digitalWrite(servoup, HIGH);
            wrist.writeMicroseconds(k);
            delay(15);
          }
          if(k < 1500) {
            //Serial.print("d"); //down
            //digitalWrite(servoup, LOW);
            wrist.writeMicroseconds(k);
            delay(15);
          }

          if(l > 1500) {
            //Serial.print("l"); //left
            //digitalWrite(servolr, HIGH);
            //wristlr.writeMicroseconds(l); 
            delay(15);
          }
          if(l < 1500) {
            //Serial.print("r"); //right
            //digitalWrite(servolr, LOW);
            //wristlr.writeMicroseconds(l);
            delay(15);
          }
          if(Xbox.getButtonPress(A)){

            if(grip.read()>90){
            grip.write(0);
            delay(15);
            }
            else{
               grip.write(180);
              }
            }
            delay(15);
          }
        
        

} 

void dcmovement(int u, int j){

    if (u > 1000 || u < 2000 || j > 1000 || j < 2000) {
          if(Xbox.getButtonPress(X)) {
            //Forward
            fwd.writeMicroseconds(1000); //Right hand wheel
            fwd2.writeMicroseconds(1000); //Left Hand Wheel
            delay(50);
            
          }
          if(Xbox.getButtonPress(B)) {
            //Reverse
            fwd.writeMicroseconds(2000);//right wheel
            fwd2.writeMicroseconds(2000);//left wheel
            delay(50);
          }
          if(j > 1500) {
            //Turn Right
            fwd.writeMicroseconds(2000);
            fwd2.writeMicroseconds(1000);
          }
          if(j < 1500) {
            //Turn Left
            fwd.writeMicroseconds(1000);
            fwd2.writeMicroseconds(2000);
          }
          if ( u < 1700 && u > 1300 && j < 1700 && j > 1300) {
          fwd.writeMicroseconds(1500);
          fwd2.writeMicroseconds(1500);
        }
    }  }
    
