#ifndef __ccd_H__
#define __ccd_H__
  #include "gpio.h"

//�������ź�
#define SI_SetVal()   PTC7_OUT = 1
#define SI_ClrVal()   PTC7_OUT = 0
#define CLK_ClrVal()  PTC5_OUT = 0
#define CLK_SetVal()  PTC5_OUT = 1

//ccd��ʼ��
void ccd_init(void);
//ccd�ع⺯��
void StartIntegration(void);
//��ʱ����
void SamplingDelay(void);
//�ɼ�����
void ImageCapture(unsigned char * ImageData);

void SendImageData(unsigned char * ImageData);

void CalculateIntegrationTime();
void  CalcuBackline(u8 *a,u8 Repeted,signed char  );

s8 DealBlackLine (u8 k1,u8 k2);
u8 getJump(void);
s8 abs(signed char a);

extern u8 cord[3][8];
extern u8 PSW;
extern u8 data[148];
extern u8 Time_Exposure;
extern u8 BlackLine[3][2];
extern u8 k1,k2;
extern int D5110[18];
#endif