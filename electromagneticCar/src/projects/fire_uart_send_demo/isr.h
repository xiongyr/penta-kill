/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.h
 * ����         �����º궨���жϺţ���ӳ���ж�����������жϺ�����ַ��
 *                ʹ��ָ��������������жϷ������������жϷ�����
 *                ���棺ֻ����"vectors.c"���������ұ�����"vectors.h"�����ĺ��棡����
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/



#ifndef __ISR_H
#define __ISR_H 1

#include  "include.h"

/*                          ���¶����ж�������
 *  ��ȡ��Ĭ�ϵ��ж�����Ԫ�غ궨��       #undef  VECTOR_xxx
 *  �����¶��嵽�Լ���д���жϺ���       #define VECTOR_xxx    xxx_IRQHandler
 *  ���磺
 *       #undef  VECTOR_003
 *       #define VECTOR_003    HardFault_Handler    ���¶���Ӳ���Ϸ��жϷ�����
 */


#endif  //__ISR_H
extern void PIT0_IRQHandler(void);
/* End of "isr.h" */
    #undef VECTOR_084
    #define VECTOR_084  PIT0_IRQHandler

//extern void PIT1_IRQHandler(void);
//#undef  VECTOR_085
//#define VECTOR_085    PIT1_IRQHandler

extern void USART0_IRQHandler(void);
    #undef VECTOR_061
    #define VECTOR_061   USART0_IRQHandler

extern void HardFault_Handler(void);
    #undef VECTOR_003
    #define VECTOR_003   HardFault_Handler

//extern void DMA_CH4_Handler(void);
//#undef  VECTOR_020
//#define VECTOR_020    DMA_CH4_Handler