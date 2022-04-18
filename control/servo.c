#include "servo.h"
#include "map.h"

void servo_init(void){
  GPIOA->DIR |= (1<<4);         // set PA4 as output for servo control
  GPIOA->DEN |= (1<<4);         // set PA4 as output for servo control
  Servo_90_Degree();
}

/* This function generate a 3% duty cycle from 20ms PWM signal or 50Hz*/
void drive_servo(int angle)
{
  int delay = map(angle, MINANGLE, MAXANGLE, MINONDELAY, MAXONDELAY);
  int i=0;  	 
  for(i=0; i<50; i++) 
  {
      GPIOA->DATA |= (1<<4); /* make control  pin high */
      Delay_MicroSecond(delay);
      GPIOA->DATA &= ~(1<<4); /* make control  pin low */
      Delay_MicroSecond(DUTYCYCLE - delay);
  }
}
/* This function generate a 7% duty cycle from 20ms PWM signal or 50Hz*/
void Servo_90_Degree(void)
{
   int i=0; 
	 for(i=0; i<50; i++) 
    {	
        /* Given 10us trigger pulse */
          GPIOA->DATA |= (1<<4); /* make control  pin high */
          Delay_MicroSecond(1400); /*1.4ms seconds delay */
          GPIOA->DATA &= ~(1<<4); /* make control  pin low */
          Delay_MicroSecond(18600); /*1.86ms seconds delay */
    }
}

/* Create one microsecond second delay using Timer block 1 and sub timer A */

void Delay_MicroSecond(int time)
{
    int i;
    SYSCTL->RCGCTIMER |= 2;     /* enable clock to Timer Block 1 */
    TIMER1->CTL = 0;            /* disable Timer before initialization */
    TIMER1->CFG = 0x04;         /* 16-bit option */ 
    TIMER1->TAMR = 0x02;        /* periodic mode and down-counter */
    TIMER1->TAILR = 16 - 1;  /* TimerA interval load value reg */
    TIMER1->ICR = 0x1;          /* clear the TimerA timeout flag */
    TIMER1->CTL |= 0x01;        /* enable Timer A after initialization */

    for(i = 0; i < time; i++)
    {
        while ((TIMER1->RIS & 0x1) == 0) ;      /* wait for TimerA timeout flag */
        TIMER1->ICR = 0x1;      /* clear the TimerA timeout flag */
    }
}