#ifndef SPEED_H
#define SPEED_H

extern  s8  Steer_error[3];     //���ƫ��
extern  s8  Mechine_error[3];   //���ƫ��
extern  u32 D_count;            //������
extern  int PID_Kp ,PID_Ki ,PID_Kd; //����Kp��Ki��Kd ��������

void ControlMechine(void);


#endif