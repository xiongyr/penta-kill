#include "dbug.h"
#include "nokia5110.h"

/***
*  具体的测试程序
*/
void test()
{
  // SendImageData(data);
  //printf("%d\n ",D_count );
  D_5110();
}

/***
*  刷新5110
*/
void D_5110()
{
  u8 i=0;
  LCD_clear();  //显示前先对5110清屏
  for(;i<=5;i++)
  {
    LCD_Write_Num(0,i,D5110[i],4);
    LCD_Write_Num(30,i,D5110[i+6],4);
    LCD_Write_Num(60,i,D5110[i+12],4);  
  }  
}

/***
*  初始化拨码开关
*/
void WatchSwitch( void (*PE24)(),void (*PA13)(), void (*PA5)(), void (*PE26)() )
{
  if(PTE24_IN==0 )
   {
     delayms(10);
     if(PTE24_IN==0 )
      {
         (*PE24)();
       }
    }
   if(PTA13_IN==0 )
    {
      delayms(10);
      if(PTA13_IN==0 )
        {
          (*PA13)();
        }
     }

  if( PTA5_IN==0)
   {
     delayms(10);
     if( PTA5_IN==0)
      {
        (*PA5)();
       }
    }
   if( PTE26_IN==0)
    {
      delayms(10);
      if( PTE26_IN==0)
        {
          (*PE26)();
        }
     }
}

/***
*  初始化按键
*/
void WatchCode()
{
  if(PTA16_IN==0)
  {
    D5110[12] = 2;
  }
  if(PTA14_IN==0)
  {
    D5110[13] = 2;
  }
  if(PTA12_IN==0)
  {
    D5110[14] = 2;
  }
}


/***
*  设定按键功能
*/
void addp()
{
   D5110[2]++;
  //Time_Exposure++;
  //PD_Kp++;
  // PD_Kd++;
}

/***
*  设定按键功能
*/
void subp()
{
   D5110[3]++;
  //Time_Exposure--;
  //PD_Kp--;
 //  PD_Kd--;
 //  PD_Kd--;
}

/***
*  设定按键功能
*/
void addd()
{
   D5110[4]++;
  //Time_Exposure++;
  //PD_Kp++;
  // PD_Kd++;
}

/***
*  设定按键功能
*/
void subd()
{
   D5110[5]++;
  //Time_Exposure++;
  //PD_Kp++;
  // PD_Kd++;
}
