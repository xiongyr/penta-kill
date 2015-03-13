#include "common.h"
#include "ccd.h"
#include "gpio.h"
#include "adc.h"
#include "uart.h"

#define TargetPixelAverageValueAllowError  10
#define TargetPixelAverageValue           130

//ccd初始化

#define left_line 34//24//35//21 //17 //21
#define right_line 83//100//99 //102 //107
#define Center_line 64

s8 abs(signed char a)
{
   if(a<0)
   {
      return -a;
   }
   else
   {
      return a;
   }
}

u8 getJump(void)
{
  switch(Time_Exposure)
  {         //白天开灯c105
    case 7:
      return 18;
    case 6:
      return 21;
                
    case 5:
      return 18;       
    case 4:
      return 24;  
    case 3:
      return 30;
    case 2:
      return 20;
    default:
      return 24;
  }
}


void ccd_init(void){
   gpio_init(PORTE,24,GPO,LOW);
    
   gpio_init(PORTC,7,GPO,HIGH);
   gpio_init(PORTC,5,GPO,HIGH);
   adc_init(ADC1,AD5b);
   
}
//开始积分函数
void StartIntegration(void) {

    unsigned char i;

    SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */
}
//采集函数
void ImageCapture(unsigned char * ImageData) {

    unsigned char i;
    SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 250; i++) {
      SamplingDelay() ;  //200ns
    }

    //Sampling Pixel 1

    *ImageData =  ad_once(ADC1, AD5b, ADC_8bit);
    ImageData ++ ;
    CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128
        u16 a=0;
       a = ad_once(ADC1, AD5b, ADC_8bit);
       *ImageData=a;
        ImageData ++ ;
        CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendHex
*  功能说明：采集发数程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
    uart_putchar(UART0,temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
   uart_putchar(UART0,temp - 10 + 'A');
  }
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendImageData
*  功能说明：
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    uart_putchar(UART0,'*');
    uart_putchar(UART0,'L');
    uart_putchar(UART0,'D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    uart_putchar(UART0,'#');
}
//普通延时函数
void SamplingDelay(void){
   volatile u8 i ;
   for(i=0;i<1;i++) {
    asm("nop");
    asm("nop");}
 }
//计算数组的平均值
u8 PixelAverage(u8 len, u8 *data) {
  unsigned char i;
  unsigned int sum = 0;
  for(i = 0; i<len; i++) {
    sum = sum + *data++;
  }
  return ((unsigned char)(sum/len));
}
//自适应调整曝光时间
s16 PixelAverageValueError=0;
u8 PixelAverageValue=0;

void CalculateIntegrationTime(void)   //自调整曝光时间
{
    PixelAverageValue = PixelAverage(128,data);/* 计算128个像素点的平均AD值 */
    
   // PixelAverageVoltage = (unsigned char)((int)PixelAverageValue * 25 / 128);/* 计算128个像素点的平均电压值,实际值的10倍 */

    PixelAverageValueError = TargetPixelAverageValue - PixelAverageValue;
    D5110[14] = PixelAverageValue;
    //Time_Exposure=14;
    if(PixelAverageValueError < -TargetPixelAverageValueAllowError)
       Time_Exposure++;    //积分时间减少
    if(PixelAverageValueError > TargetPixelAverageValueAllowError)
      Time_Exposure--;
    if(Time_Exposure <= 1)
        Time_Exposure = 1;
    if(Time_Exposure >= 10)
        Time_Exposure = 10;
}

void  CalcuBackline(u8 *a,u8 Repeted,signed char  offset)
{
    
    u8 i=0;  //循环变量
    u8 jump=40+offset;//getJump() +offset;
     D5110[13]=jump;
     k1=0;
     k2=0;
    //查找左线
     for(i=0;i<8;i++)
     {
        cord[0][i]=255;
     }
    for(i=4;i<80;i++)
    {
        if( a[i+4]-a[i]>jump )
        {
          //lvbobc
          if( a[i+10]-a[i]>jump-5)
          {
            //if(a[i+10]>130)
        //   if((abs(BlackLine[0][0]-i)<25))
            {
              cord[0][k1]=i;
              i=i+6; //保证接下去的6个点不会是黑线
              k1++;
              if(k1>3)
              {
                  break;
              }
            }
          }
        }
    }
    //查找右线
    for(i=125;i>30;i--)
    {
        if( a[i-4]-a[i]>jump )
        {
          if(a[i-10]-a[i]>jump-5)  //滤波
          {
            {          
              cord[0][4+k2]=i;
              i=i-6; //保证接下去的6个点不会是黑线
              k2++;
              if(k2>3)
              {
                  break;
              }
              }
          }
        }
    }
//    for(i=0;i<k1;i++)
//    {
//     
//        if(abs(cord[0][0]-cord[0][4]) < 20 )
//        {
//           for(j=0;j<k1;j++)
//           {
//             cord[0][j] = cord[0][j+1];     
//           } 
//           
//        }
//    
//    }
    //如果程序从主函数入内，则判断是否需要二次扫线
    if(Repeted==0)
    {
      if(k1>=3||k2>=3)
      {
        //增加jump扫
        CalcuBackline(data,1,+5);
      }
      if(k1==0||k2==0)
      {
        //减少jump扫
         CalcuBackline(data,1,-5);
      }
    }
}
//返回的值是偏差

//计算出偏差是多少;此外在对BLACKline 操作
s8 GetPositionError(u8 left,u8 right,u8 _case)
{
  switch(_case) 
  {
    case 0x01:     //0x0001
       return 127;  //返回上一次的偏差;
     break;
    case 0x02: //0x0010;
      BlackLine[0][0]=cord[0][0];
      BlackLine[0][1]=255;
      return left_line-left;
     break;
    case 0x04: //x0x0100;
      BlackLine[0][1]=cord[0][4];
      BlackLine[0][0]=255;
      return  right_line - right;
     break;
    case 0x08 :
      BlackLine[0][0]=cord[0][0];
      BlackLine[0][1]=cord[0][4];
      return 64-(left+right)/2;
    default:
      return 127    ;
  }
  
}
//比较获取位置
u8 GetAccurateBlackline(u8 isRight)
{
  if(BlackLine[isRight][1]!=255)
  {
    if(isRight)      
    {
      return abs(cord[0][4]-BlackLine[isRight][1])< abs(cord[0][5]-BlackLine[isRight][1])?cord[0][4]:cord[0][5] ;
    }
    else
    {
      return abs(cord[0][0]-BlackLine[isRight][1])< abs(cord[0][1]-BlackLine[isRight][1])?cord[0][0]:cord[0][1] ;
    }
  }
  else
  {
    return 255;
  }
}
//对K值得种类判断
s8 DealBlackLine(u8 k1,u8 k2)
{
   u8 j=0;
    for( ;j<3;j++)
    {
      BlackLine[j+1][0] = BlackLine[j][0];
      BlackLine[j+1][1] = BlackLine[j][1];
    }
  
  if((k1>=3||k1==0)&&(k2>=3||k2==0))
    {
      PSW=0x11;   
      return GetPositionError(255,255,1); 
    }
   if(k1==1&&k2==1)
   {
      PSW=0x22;
      if((s8)(cord[0][4]-cord[0][0])>50)
      {
        return GetPositionError(cord[0][0],cord[0][4],8);
      }
      else
      {
         return GetPositionError(255,255,1); 
      }
      
   }
   if(k1==1)
   {
      PSW=0x12;
      return GetPositionError(cord[0][0],255,2);
   }
   if(k2==1)
   {
      PSW=0x21;
      return GetPositionError(255,cord[0][4],4);
   }
   if(k1==2||k2==2)
   {
        //这里还可以改进
      u8 tempBlackleft=255;
      u8 tempBlackRight=255;
      PSW=00;
      if(k1==2)
      {
        tempBlackleft=GetAccurateBlackline(0);
        PSW+=0x04;
      }
      else
      {
        PSW+=0x01;
      }
      if(k2==2)
      {
         tempBlackRight=GetAccurateBlackline(1);
         PSW+=0x40;
      }
      else
      {
        PSW+=0x10;
      }
    
      
        if(tempBlackleft!=255&&tempBlackRight!=255)
        {
          PSW=PSW<<1; // PSW=0x88
          return GetPositionError(tempBlackleft,tempBlackRight,8);
        }
        else if(tempBlackleft!=255)
        {
          PSW=PSW+0x02;  //PSW=0x46;PSW=16 
          return GetPositionError(tempBlackleft,tempBlackRight,2);
        }
        else if(tempBlackRight!=255)
        {
          PSW=PSW+0x20; //PSW=0x64; 0x61
          return GetPositionError(tempBlackleft,tempBlackRight,4);
        }
        else
        {
           PSW=PSW+0x11; //PSW=0x55  0x15 0x51 
           return GetPositionError(tempBlackleft,tempBlackRight,1);
        }
      
   }
    else
    {
      PSW=0xEE;
      return 0xFF;
    }
}





//void  CalcuBackline(u8 *a)
//{
//    u8 i=0;
//    u8 jump=25;
//    u8 k=0;
//   
//    for(i=0;i<=100;i++)
//    {
//        if(a[i+5]-a[i]>jump)
//        {
//            cord[k]=i;
//            k++
//            i=i+5; //如果找到，则默认后面5个也为黑线
//            if(k>3)
//            {
//              break;
//            }
//        }
//
//        if(k==1)
//            {
//                PSW=16;        //0b00010000;
//            }
//        if(k==2)
//            {
//                PSW=32;       //0b00100000;
//            }
//        if(k==3)
//            {
//                PSW=64;       //0b01000000;
//            }        
//    }
//    if(k==0)
//    {
//      PSW=0;
//      //尝试寻找右线
//      for(i=120;i>=20;i--)
//      {
//        if(a[i-5]-a[i]>jump)
//        {
//            cord[k]=i;
//            k++;
//            i=i+5; //如果找到，则默认后面5个也为黑线
//            if(k>=3)
//            {
//              break;
//            }
//        }
//      }
//     if(k==1)
//     {      
//       PSW=129;              //0b10000001;
//     }
//     if(k==2)
//     {
//       PSW=130;              //0b10000010; 
//     }
//     if(k==3)
//     {
//       PSW=132;              //0b10000100; 
//     }
//     
//    }
//    if(k==0)
//    {
//       PSW=136;             //0b10001000;
//    }
//    
