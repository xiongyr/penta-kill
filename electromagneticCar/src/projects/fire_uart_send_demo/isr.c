/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.c
 * ����         ���жϴ�������
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


void PIT0_IRQHandler(void)
{
    PIT_Flag_Clear(PIT0);   //����ϱ��
    GetAdc();
   
}

void USART0_IRQHandler(void)
{
     DisableInterrupts;          //�����ж�   
  
      EnableInterrupts;            //�����ж�   
}
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****Ӳ���Ϸô���!!!*****\r\n\n");
    }
}