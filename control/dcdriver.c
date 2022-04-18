#include "dcdriver.h"


void motors_init(void){
  // Motor 1
  SYSCTL->RCGCGPIO |= 0x01; 
  GPIOA->DIR |= (1<<3)|(1<<2); //set PA2 and PA3 as digital output pin for motor 1 control
  GPIOA->DEN |= (1<<3)|(1<<2); //set PA2 and PA3 as digital enable
  
  GPIOA->DIR |= (1<<6)|(1<<7); //set PA6 and PA7 as digital output pin for motor 2 control
  GPIOA->DEN |= (1<<6)|(1<<7); //set PA2 and PA3 as digital enable
}
//Spin motor in one direction by giving IN1 and IN2 signals to L298N
void forward(void)
{
    GPIOA->DATA |=(1<<2) | (1<<6);
    GPIOA->DATA &=~((1<<3)|(1<<7));
}

//Spin motor in other direction by giving IN1 and IN2 signals to L298N

void reverse(void)
{
  GPIOA->DATA |=(1<<3) | (1<<7);
  GPIOA->DATA &=~((1<<2) | (1<<7));
}

void stop(void)
{
  GPIOA->DATA &=~((1<<2) | (1<<3) | (1<<6) | (1<<7));
  
}