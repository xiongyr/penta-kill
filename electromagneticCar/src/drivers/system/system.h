#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include "common.h"

//����ȫ�ֱ���
//ִ�л���
extern int PD_Kp,PD_Kd;  //���PDֵ
extern int PID_Kp,PID_Kd,PID_Ki;  //���PIDֵ
 
extern int PWM0,PWM1,PWM2;    //����PWM��
extern s8 Steer_error[3];     //���ƫ������
extern s8 Mechine_error[3];   //���ƫ������
extern  u32 D_count;          //������
extern int D5110[18];        //5110��ʾ����
extern u8 ADresult[6];        //�洢ADֵ����

//��������
void system_Init(void);
void SetInitValue();
int GetSpeedValue();
void ADCInit();
void KeyInit();
void DIPInit();
#endif