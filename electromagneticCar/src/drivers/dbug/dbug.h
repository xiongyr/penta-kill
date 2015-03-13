#ifndef _DBUG_H_
#define _DBUG_H_

//声明全局变量
extern int D5110[18];
//声明函数
void D_5110();
void WatchSwitch( void (*)(),void (*)(),void (*)(),void (*)() );
void WatchCode();
void addp();
void subp();
void addd();
void subd();
void test();
#endif