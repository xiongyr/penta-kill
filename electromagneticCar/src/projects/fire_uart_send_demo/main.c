/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��main.c
 * ����         ��UART���ڷ���ʵ��
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/


#include "common.h"
#include "include.h"


/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*                               ���ڷ���ʵ�����
*
*  ʵ��˵����Ұ�𴮿ڷ���ʵ��
*            Ұ�𴮿�Ĭ��Ϊ�� UART1��TX��PTC4��RX��PTC3
*            k60_fire.h�ﶨ���� printf ������������ã�
*                #define FIRE_PORT           UART1
*                #define FIRE_BAUD           19200
*            ����Ĵ��ڷ���ʵ��Ҳʹ�� UART1 ������������ʾ��
*
*  ʵ��������򿪴������� �����ò�����Ϊ 19200 ��
*            �����ߣ�����MAX3232��ƽת������TX��PTC4��RX��PTC3
*
*  ʵ��Ч�����ڴ�����������Կ������������Ϣ��
*
*                        Ұ��kinetis���İ���Գ���
*                �ں�Ƶ�ʣ�200MHz	����Ƶ�� ��66MHz
*                flexƵ�ʣ�66MHz 	flashƵ�ʣ�28MHz
*
*                Software Reset
*
*                K60-144pin      Silicon rev 1.2
*                Flash parameter version 0.0.7.0
*                Flash version ID 3.2.7.0
*                512 kBytes of P-flash	P-flash only
*                128 kBytes of RAM
*
*                ���ڷ���ʵ��
*
*                                ����Ұ��kinetis������
*
*                Fuart_sendNuart_str������������
*                -------------Ұ��kinetis������-------------
*
*
*  ʵ��Ŀ�ģ����Դ��ڷ��͵ĸ���������printf��uart_putchar��uart_sendN��uart_sendStr
*
*  �޸�ʱ�䣺2012-2-29     �Ѳ���
*
*  ��    ע��printf�����ĵײ��ǵ��� uart_putchar �����͡�
*************************************************************************/

u32 D_count;           //����������
u8  ADresult[6];       //�洢�ɼ�����ADֵ
s8  Steer_error[3];    //���
s8  Mechine_error[3];  //���

int PWM0,PWM1,PWM2;
int  D5110[18];

int PD_Kp=50,PD_Kd=4;             //�ŷ����
int PID_Kp=40,PID_Ki=4,PID_Kd=4;  //���

void  main(void)
{
   DisableInterrupts;                    //�ر����ж�    
   SetInitValue();
   system_Init();
   EnableInterrupts;                     //�������ж�
    
    while(1)
    {
         //�źŲɼ�
         GetAdc();
          
         //�źŴ���
         DealAdc();
          
         //�������
         ControlSteering();
         
         //�������
         ControlMechine();
         //���� 
         WatchSwitch(addp,subd,addd,subp);    //��ⰴ��
         WatchCode();                         //��Ⲧ�뿪��
         printf("%d  %d  %d \n",1,2,3 );      //����
         test();                              //ˢ��5110  ���Դ���
    }



}
