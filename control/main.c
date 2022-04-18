#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdlib.h>
#include "bluetooth.h"
#include "servo.h"
#include "dcdriver.h"

#define TWOSECONDS 1000000 // two second delay from micro second delay function 

int main(void)
{
  motors_init(); // initialize DC motors
  servo_init(); // initialize servo motor
  HC05_init(); // call HC05_init() to initialze UART5 of TM4C123GH6P
  SYSCTL->RCGCGPIO |= 0x20;   // enable clock to GPIOF
  GPIOF->DIR |= 0x0E;         //set PF1, PF2 and PF3 as digital output pin
  GPIOF->DEN |= 0x0E;         // CON PF1, PF2 and PF3 as digital GPIO pins
  Delay_MicroSecond(TWOSECONDS / 2);
  
  while(1)
  {
    /*int angle = 0;
    char c = Bluetooth_Read();          // get a character from UART5
    switch(c){
    case 'A':
      {
      char encoded_angle;
      encoded_angle = Bluetooth_Read();
      angle = encoded_angle - '0';
      drive_servo(angle * 2 * 10);
      break;
      }
    case 'M':
      {
      char state;
      state = Bluetooth_Read();
      switch(state){
      case 'D':
        {
        forward();
        break;
        }
      case 'R':
        {
          reverse();
          break;
        }
      } 
      break;
      }
    default:
      {
      stop();
      break;
      }
    }*/
    forward();
    Delay_MicroSecond(TWOSECONDS / 2);
    stop();
    Delay_MicroSecond((TWOSECONDS * 3) / 2);
  }
}


/* This function is called by the startup assembly code to perform system specific initialization tasks. */
void SystemInit(void)
{
    __disable_irq();    /* disable all IRQs */
    
    /* Grant coprocessor access */
    /* This is required since TM4C123G has a floating point coprocessor */
    SCB->CPACR |= 0x00F00000;
}