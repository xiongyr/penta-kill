#include "system.h"
#include "include.h"

 // 4 3  2 1 5 6
 // R1 L1 L3 R3 L2 R2   

void system_Init(void)
{
    //传感器模块
    ADCInit();                                                //模数转化初始化，采集数据，B0 B1 B2 B3 A8 A9
    DMA_count_Init(DMA_CH4, PTE0 , 0x7FFF, DMA_falling_up);   //DMA初始化  //速度传感器
    
    //调试模块 
    LCD_Init();                //5110初始化
    uart_init(UART1, 57600);   //串口模块
    KeyInit();                 //初始化按键程序
    DIPInit();                 //初始化拨码开关
    

    //pit中断；程序控制模块
    pit_init_ms(PIT0,1000); 
    //执行机构模电机电机模块
    FTM_PWM_init(FTM1, CH1, 10000, PWM1); //初始化FTM0_CH0输出频率为20KHZ,占空比为50%的PWM ：FTM1_CH1对应PTA9口
    FTM_PWM_init(FTM2, CH1, 10000, PWM2); //初始化FTM2_CH1输出频率为20KHZ,占空比为50%的PWM ：FTM2_CH1对应PTC11口
    //伺服电机模块
    FTM_PWM_init(FTM0, CH1, 300, 10000);  //初始化FTM0_CH1输出频率为300HZ,占空比为50%的PWM ：FTM0_CH1对应PTC2口
}
    
/***
*  初始化按键
*/
void KeyInit()
{
    gpio_init(PORTA,13,GPI_UP,LOW);
    gpio_init(PORTE,24,GPI_UP,LOW);
    gpio_init(PORTA,5,GPI_UP,LOW);
    gpio_init(PORTE,26,GPI_UP,LOW);     
}

/***
*  初始化拨码开关 
*/
void DIPInit()
{
    gpio_init(PORTA,16,GPI,LOW);
    gpio_init(PORTA,14,GPI,LOW);
    gpio_init(PORTA,12,GPI,LOW); 
}

/***
*  初始化传感器 
*/
void ADCInit()
{
    adc_init(ADC0,SE8);     //模数转化初始化，采集数据，B0 
    adc_init(ADC0,SE9);     //模数转化初始化，采集数据，B1 
    adc_init(ADC0,SE12);     //模数转化初始化，采集数据，B2 
    adc_init(ADC0,SE13);     //模数转化初始化，采集数据，B3 
    adc_init(ADC0,SE10);     //模数转化初始化，采集数据，A7 
    adc_init(ADC0,SE11);     //模数转化初始化，采集数据，B8 
}


/***
*  系统变量初始化
*/
void SetInitValue()
{
   PWM1 = 0;
   PWM2 =4500;
   PD_Kp=37,PD_Kd=101;           //伺服电机
   PID_Kp=40,PID_Kd=4,PID_Ki=4;  //电机
}

/***
*  返回脉冲个数
*/
int GetSpeedValue()
{
   D_count = DMA_count_get(DMA_CH4);
   DMA_count_reset(DMA_CH4);
   return D_count;
}

