#ifndef SPEED_H
#define SPEED_H

extern  s8  Steer_error[3];     //舵机偏差
extern  s8  Mechine_error[3];   //电机偏差
extern  u32 D_count;            //编码器
extern  int PID_Kp ,PID_Ki ,PID_Kd; //定义Kp、Ki、Kd 三个参数

void ControlMechine(void);


#endif