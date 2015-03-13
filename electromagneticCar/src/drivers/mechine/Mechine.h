#ifndef _Mechine_H_
#define _Mechine_H_
#include "common.h"
//变量
extern u16 PWM1;//正转
extern u16 PWM2;//反转
extern u16 PWM1_max,PWM2_max;
extern u8 count_bmq;//返回即时实际速度count_bmq=10*n/s
extern int piancha3;
//函数
void ChangeSpeed();

#endif  //_CAMERA_H_