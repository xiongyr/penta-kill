#ifndef _DBUG_H_
#define _DBUG_H_

//����ȫ�ֱ���
extern int D5110[18];
//��������
void D_5110();
void WatchSwitch( void (*)(),void (*)(),void (*)(),void (*)() );
void WatchCode();
void addp();
void subp();
void addd();
void subd();
void test();
#endif