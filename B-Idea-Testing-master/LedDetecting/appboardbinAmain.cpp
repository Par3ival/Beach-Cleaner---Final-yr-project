#include "mbed.h"

DigitalOut r(p23);
DigitalOut g(p24);
DigitalOut b(p25);

//PwmOut r (p23);
//PwmOut g (p24);
//PwmOut b (p25);
float period = 500;
int main()
{
    r=1;
    g=1;
    b=1;
    //r.period(0.001);
    while(1) {
                
                wait_ms(period);
                r=0;
                wait_ms(period);
                r=1;
                wait_ms(period);
                b=0;
                wait_ms(period);
                b=1;
                wait_ms(period);
                g=0;
                wait_ms(period);
                g=1;
                wait_ms(period);
                g=0;
                wait_ms(period);
                g=1;
    }
}
