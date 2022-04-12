#ifndef __SERVO_H__
#define __SERVO_H__

#include "TM4C123GH6PM.h"

#define DUTYCYCLE (20000)
#define MINONDELAY (600)
#define MAXONDELAY (2400)
#define MINANGLE (0)
#define MAXANGLE (180)

void drive(int angle);
void Delay_MicroSecond(int time);
void Servo_90_Degree(void);

#endif