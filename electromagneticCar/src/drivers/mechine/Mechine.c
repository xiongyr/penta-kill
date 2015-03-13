#include "Mechine.h"
#include "FTM.h"

int PWM_given=0; 
int spd_err[3];
int speed_set; //预设定的速度v=0.06*Pai*n*10*如v=150代表速度为1.5m/s*******count_bmq=v*26.5
int diff[4]={0};//,pre_err=0,ppre_err=0
//现在的问题是1、如果通过赛道来选择给电机设定速度 2、鲁棒控制的误差门限的大小
uint8 spd_flag=0;
 
void give_speed()
{
    
//用于速度的设定——用线性设定速度

   uint8 kp,ki,kd;//PID 的参数
 //  uint8 cp1=0,cp2=0;
   
   if(piancha3<0)
   {
     piancha3=-1*piancha3;
   }
   
   diff[2]=diff[1];
   diff[1]=diff[0];
   diff[0]=piancha3;//前三次的偏差值      

  
   if( piancha3>60 )
   {
     speed_set = 2400;
     spd_flag=0;
    
   }
  else if( piancha3>30 && count_bmq>200 )// && (diff[2]-diff[3])>0)
   {
     speed_set=1000;  //( && piancha3<65 )
     if(count_bmq>200)
     {
       spd_flag=1;
     }
     else
     {
       spd_flag=0;
       speed_set=2600;
     }
     
   }
   
   else 
   {
     speed_set=3000;
     spd_flag=0;
   }

        
 

//PID
     spd_err[2]=spd_err[1];   
     spd_err[1]=spd_err[0];
     spd_err[0]=speed_set-10*count_bmq;   
    
    
          
   if(spd_err[0]<250  && spd_err[0]> -250)
     {
       kp=4;
       ki=4;
       kd=5;
     }
   else 
     {
       kp=8;
       kd=5;
     }
     
   
//PID控制
    if(spd_err[0]>-50 && spd_err[0]<50)
    {
      spd_err[0]=0;
    }
   
    
      
      PWM_given=PWM_given+kp*(spd_err[0]-spd_err[1])+ki*spd_err[0]+kd*(spd_err[0]-2*spd_err[1]+spd_err[2]);//若是kd*(1*spd_err[0]-2*spd_err[1]+spd_err[2])未加入微分先行  
      if(PWM_given>20000)
      {
        PWM_given = 20000;
      }
      else if(PWM_given<-8000)
      {
        PWM_given = -8000;
      }
      
      
      if(PWM_given>0)//正转
      { 
        if(PWM_given>PWM1_max)
        {  
          PWM1=PWM1_max;
        }
        else
        {
          PWM1=PWM_given;
        }
        
        PWM2=0;
      }
      else if(PWM_given<0)//反转
      {
        if(PWM_given>-PWM2_max)
        {
          PWM2=-PWM_given;
        }
        else 
        {
          PWM2=PWM2_max;
        }
        
        PWM1=0;
      }
//鲁棒控制    
   if(spd_err[0]>=800)//误差太大，尽快缩小误差
    {       
      PWM1=PWM1_max;//使劲加速，直到spd小于
      PWM2=0;       
    }
   else if(spd_err[0]<=-1100)
   {
     PWM1=0;
     PWM2=PWM2_max;//猛减，直到spd小于
   }
    

   
   if(count_bmq<=10)//碰撞停车
    {
       PWM1=0;
       PWM2=0;
    }
     FTM_PWM_Duty(FTM0, CH2, PWM1);
     FTM_PWM_Duty(FTM0, CH4, PWM2);
    
}


/*
void give_speed()
{
     if(piancha3<0)
   {
     piancha3=-1*piancha3;
   }
 
   diff[3]=diff[2];
   diff[2]=diff[1];
   diff[1]=diff[0];
   diff[0]=piancha3;//前三次的偏差值      
  
  if(diff[0]<20 &&diff[1]<20 &&diff[2]<20 &&diff[3]<20 )
  {
    PWM1=4000;    
  }
  else PWM1=3200;
     FTM_PWM_Duty(FTM0, CH2, PWM1);
     FTM_PWM_Duty(FTM0, CH4, PWM2);
    
}
*/ 