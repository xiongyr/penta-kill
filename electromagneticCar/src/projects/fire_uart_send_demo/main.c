/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：main.c
 * 描述         ：UART串口发送实验
 *
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：野火嵌入式开发工作室
 * 淘宝店       ：http://firestm32.taobao.com
 * 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/


#include "common.h"
#include "include.h"


/*************************************************************************
*                             野火嵌入式开发工作室
*                               串口发送实验测试
*
*  实验说明：野火串口发送实验
*            野火串口默认为： UART1，TX接PTC4，RX接PTC3
*            k60_fire.h里定义了 printf 函数的输出设置：
*                #define FIRE_PORT           UART1
*                #define FIRE_BAUD           19200
*            这里的串口发送实验也使用 UART1 ，这样方便显示。
*
*  实验操作：打开串口助手 ，设置波特率为 19200 。
*            串口线（经过MAX3232电平转换）：TX接PTC4，RX接PTC3
*
*  实验效果：在串口助手里，可以看到输出如下信息：
*
*                        野火kinetis核心板测试程序
*                内核频率：200MHz	总线频率 ：66MHz
*                flex频率：66MHz 	flash频率：28MHz
*
*                Software Reset
*
*                K60-144pin      Silicon rev 1.2
*                Flash parameter version 0.0.7.0
*                Flash version ID 3.2.7.0
*                512 kBytes of P-flash	P-flash only
*                128 kBytes of RAM
*
*                串口发送实验
*
*                                ——野火kinetis开发板
*
*                Fuart_sendNuart_str函数发送数据
*                -------------野火kinetis开发板-------------
*
*
*  实验目的：测试串口发送的各个函数：printf、uart_putchar、uart_sendN、uart_sendStr
*
*  修改时间：2012-2-29     已测试
*
*  备    注：printf函数的底层是调用 uart_putchar 来发送。
*************************************************************************/

u32 D_count;           //编码器读数
u8  ADresult[6];       //存储采集到的AD值
s8  Steer_error[3];    //舵机
s8  Mechine_error[3];  //电机

int PWM0,PWM1,PWM2;
int  D5110[18];

int PD_Kp=50,PD_Kd=4;             //伺服电机
int PID_Kp=40,PID_Ki=4,PID_Kd=4;  //电机

void  main(void)
{
   DisableInterrupts;                    //关闭总中断    
   SetInitValue();
   system_Init();
   EnableInterrupts;                     //开启总中断
    
    while(1)
    {
         //信号采集
         GetAdc();
          
         //信号处理
         DealAdc();
          
         //舵机控制
         ControlSteering();
         
         //电机控制
         ControlMechine();
         //调试 
         WatchSwitch(addp,subd,addd,subp);    //监测按键
         WatchCode();                         //监测拨码开关
         printf("%d  %d  %d \n",1,2,3 );      //串口
         test();                              //刷新5110  测试代码
    }



}
