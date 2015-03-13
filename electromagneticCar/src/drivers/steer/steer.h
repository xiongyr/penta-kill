#ifndef _STEER_H_
#define _STEER_H_

extern int  PD_Kp,PD_Kd;
extern int PWM0;
extern s8 Steer_error[3];

void ControlSteering();

#endif