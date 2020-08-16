#include <SPI.h>
#include <Servo.h>

byte buf [100];
volatile byte pos;
volatile boolean process;

int servodrive = 2; //Forward
int servodrive2 = 3; //Reverse

Servo fwd;
Servo rev;

void setup (void)
{
  Serial.begin (9600);   // debugging00

  pinMode(servodrive, OUTPUT);
  pinMode(servodrive2, OUTPUT);

  fwd.attach(servodrive);
  rev.attach(servodrive2);

  // Have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // Turn on SPI in slave mode
  SPCR |= _BV(SPE);
  // Enable Interrupts
  SPCR |= _BV(SPIE);

  pos = 0;
  process = false;

}  // end of setup


//Interrupt to read data into a buffered array
ISR (SPI_STC_vect)
{
  byte c = SPDR;

  if (pos < sizeof buf) {
    buf [pos++] = c;

    //This if defines the number that is being looked for in the sequence to say that one data set has been retrieved
    //eg. LinX AngZ $YOURNUMBER$ LinX AngZ $YOURNUMBER$ etc
    if (pos == 4) {
      process = true;
    }
  }
}


// Main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process) {

    uint16_t finalvalx = (uint16_t) buf[0] * 256 + (uint16_t) buf[1];
    uint16_t finalvalz = (uint16_t) buf[2] * 256 + (uint16_t) buf[3];

    //Serial.println (finalvalx);
    //Serial.println (finalvalz);
    //Serial.println ("\n");

    dcmovement(finalvalx, finalvalz);

    pos = 0;
    process = false;
  }
  stopmotion();
  delay(1000);
}  // end of loop


void dcmovement(uint16_t u, uint16_t j) {

  if (u > 1500) {
    //Forward
    fwd.writeMicroseconds(1000); //Right hand wheel
    rev.writeMicroseconds(1000); //Left Hand Wheel
    //fwd.writeMicroseconds(u);
    delay(50);

  }
  if (u < 1500) {
    //Reverse
    fwd.writeMicroseconds(2000);//right wheel
    rev.writeMicroseconds(2000);//left wheel
    //fwd.writeMicroseconds(u);
    delay(50);
  }
  if (j > 1500) {
    //Turn Right
    fwd.writeMicroseconds(2000);
    rev.writeMicroseconds(1000);
    //rev.writeMicroseconds(j);
  }
  if (j < 1500) {
    //Turn Left
    fwd.writeMicroseconds(1000);
    rev.writeMicroseconds(2000);
    //rev.writeMicroseconds(j);
  }
}

void stopmotion() {
  fwd.writeMicroseconds(1500);
  rev.writeMicroseconds(1500);
}
