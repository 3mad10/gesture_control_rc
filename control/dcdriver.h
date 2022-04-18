#ifndef __DCDRIVER_H__
#define __DCDRIVER_H__

#include "TM4C123GH6PM.h"

void motors_init(void);
void forward(void);
void reverse(void);
void stop(void);
static void Delay_ms(int time_ms);

#endif