#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include "common.h"

//声明全局变量
//执行机构
extern int PD_Kp,PD_Kd;  //舵机PD值
extern int PID_Kp,PID_Kd,PID_Ki;  //电机PID值
 
extern int PWM0,PWM1,PWM2;    //定义PWM波
extern s8 Steer_error[3];     //舵机偏差数组
extern s8 Mechine_error[3];   //电机偏差数组
extern  u32 D_count;          //编码器
extern int D5110[18];        //5110显示数组
extern u8 ADresult[6];        //存储AD值数组

//声明函数
void system_Init(void);
void SetInitValue();
int GetSpeedValue();
void ADCInit();
void KeyInit();
void DIPInit();
#endif