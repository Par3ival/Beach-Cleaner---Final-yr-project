
#include <Servo.h>  //include the correct library need for this code

Servo motor1;
Servo motor2;

int servopos = 0;        // initialises the servoposition so it starts at 0

void setup() {

  motor1.attach(9);  //this attaches each motor on the rover to a digital pin on the ardino
  motor2.attach(6);
   
}

void loop() {

  for(servopos = 0; servopos < 180; servopos++)    // creates a for loop so that both motors move from 0 position to 180. once the posion is > 180 it can leave the for loop
  {
    motor1.write(servopos);
    motor2.write(servopos);
    delay(100);
  }

  for(servopos = 180; servopos > 0; servopos--)  // this then moves the motors in the oppposite direction from 180n back to 0 
  {
    motor1.write(servopos);
    motor2.write(servopos);
    delay(100);
  }
  
  

}
