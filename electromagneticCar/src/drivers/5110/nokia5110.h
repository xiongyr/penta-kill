#ifndef __NOKIA5110_H__
#define __NOKIA5110_H__

//#include <hidef.h>      /* common defines and macros */
//#include "derivative.h"      /* derivative-specific definitions */

#include "common.h"
#include "gpio.h"



struct typHZ_GB12	/*12*12 汉字字模显示数据结构,一个汉字分为上下两层*/
{
   char Index[2];//一个汉字占两个字节
   char Msk[24];//一个汉字的编码由24个十六进制数组成
};

#define uchar unsigned char  //自己加的
#define uint unsigned int   //自己加的

//位操作定义
#define LCD_RST  PTD4_OUT 
#define LCD_CE   PTD2_OUT 
#define LCD_DC   PTD0_OUT 
#define SDIN     PTC17_OUT 
#define SCLK     PTC15_OUT 

//函数声明
void Delay_us(uint ut);
void LCD_Init(void);
void LCD_clear(void);
void LCD_write_byte(uchar, uchar);
void LCD_set_XY(uchar , uchar );      
void LCD_write_char(uchar );
void LCD_Write_Char(uchar ,uchar ,uchar);
void LCD_Write_Num(uchar ,uchar ,uint,uchar);
void LCD_write_english_string(uchar ,uchar ,char *); 
void LCD_write_chinese(uchar , uchar , char *);
void LCD_write_chinese_string(uchar , uchar ,char *);
void LCD_Write_String(uchar , uchar ,char *);
void LCD_draw_bmp_pixel(uchar ,uchar ,uchar *, uchar ,uchar );
void LCD_Write_NumChar(uchar X,uchar Y,uchar N);


#endif