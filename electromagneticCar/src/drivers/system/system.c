#include "system.h"
#include "include.h"

 // 4 3  2 1 5 6
 // R1 L1 L3 R3 L2 R2   

void system_Init(void)
{
    //������ģ��
    ADCInit();                                                //ģ��ת����ʼ�����ɼ����ݣ�B0 B1 B2 B3 A8 A9
    DMA_count_Init(DMA_CH4, PTE0 , 0x7FFF, DMA_falling_up);   //DMA��ʼ��  //�ٶȴ�����
    
    //����ģ�� 
    LCD_Init();                //5110��ʼ��
    uart_init(UART1, 57600);   //����ģ��
    KeyInit();                 //��ʼ����������
    DIPInit();                 //��ʼ�����뿪��
    

    //pit�жϣ��������ģ��
    pit_init_ms(PIT0,1000); 
    //ִ�л���ģ������ģ��
    FTM_PWM_init(FTM1, CH1, 10000, PWM1); //��ʼ��FTM0_CH0���Ƶ��Ϊ20KHZ,ռ�ձ�Ϊ50%��PWM ��FTM1_CH1��ӦPTA9��
    FTM_PWM_init(FTM2, CH1, 10000, PWM2); //��ʼ��FTM2_CH1���Ƶ��Ϊ20KHZ,ռ�ձ�Ϊ50%��PWM ��FTM2_CH1��ӦPTC11��
    //�ŷ����ģ��
    FTM_PWM_init(FTM0, CH1, 300, 10000);  //��ʼ��FTM0_CH1���Ƶ��Ϊ300HZ,ռ�ձ�Ϊ50%��PWM ��FTM0_CH1��ӦPTC2��
}
    
/***
*  ��ʼ������
*/
void KeyInit()
{
    gpio_init(PORTA,13,GPI_UP,LOW);
    gpio_init(PORTE,24,GPI_UP,LOW);
    gpio_init(PORTA,5,GPI_UP,LOW);
    gpio_init(PORTE,26,GPI_UP,LOW);     
}

/***
*  ��ʼ�����뿪�� 
*/
void DIPInit()
{
    gpio_init(PORTA,16,GPI,LOW);
    gpio_init(PORTA,14,GPI,LOW);
    gpio_init(PORTA,12,GPI,LOW); 
}

/***
*  ��ʼ�������� 
*/
void ADCInit()
{
    adc_init(ADC0,SE8);     //ģ��ת����ʼ�����ɼ����ݣ�B0 
    adc_init(ADC0,SE9);     //ģ��ת����ʼ�����ɼ����ݣ�B1 
    adc_init(ADC0,SE12);     //ģ��ת����ʼ�����ɼ����ݣ�B2 
    adc_init(ADC0,SE13);     //ģ��ת����ʼ�����ɼ����ݣ�B3 
    adc_init(ADC0,SE10);     //ģ��ת����ʼ�����ɼ����ݣ�A7 
    adc_init(ADC0,SE11);     //ģ��ת����ʼ�����ɼ����ݣ�B8 
}


/***
*  ϵͳ������ʼ��
*/
void SetInitValue()
{
   PWM1 = 0;
   PWM2 =4500;
   PD_Kp=37,PD_Kd=101;           //�ŷ����
   PID_Kp=40,PID_Kd=4,PID_Ki=4;  //���
}

/***
*  �����������
*/
int GetSpeedValue()
{
   D_count = DMA_count_get(DMA_CH4);
   DMA_count_reset(DMA_CH4);
   return D_count;
}

