#include "TM4C123GH6PM.h"
#include <stdint.h>
#include <stdlib.h>
#include "bluetooth.h"
#include "servo.h"

#define TWOSECONDS 1000000 // two second delay from micro second delay function 

int main(void)
{
  HC05_init(); // call HC05_init() to initialze UART5 of TM4C123GH6P
  SYSCTL->RCGCGPIO |= 0x21;   // enable clock to GPIOF and GPIOA
  GPIOF->DIR |= 0x0E;         //set PF1, PF2 and PF3 as digital output pin
  GPIOF->DEN |= 0x0E;         // CON PF1, PF2 and PF3 as digital GPIO pins
  GPIOA->DIR |=(1<<4);         /* set PA4 as a digial output pin */
  GPIOA->DEN |=(1<<4);         /* make PA4 as digital pin */
  Delay_MicroSecond(TWOSECONDS / 2);
  
  while(1)
  {
    char c = Bluetooth_Read();          // get a character from UART5
    int angle = c - '0';
    drive(angle * 2 * 10);
    Delay_MicroSecond(TWOSECONDS);
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