#include "common.h"
#include "FTM.h"
#include "steer.h"


void ControlSteering()
{
    PWM0=4350+PD_Kp*(Steer_error[0]) + PD_Kd*(Steer_error[0]-Steer_error[1]);
    LimitRange(PWM0,6100,2300);
    FTM_PWM_Duty(FTM0, CH0, (int)PWM0);//PTA9����300hz��ռ�ձ�43% ���ת�����
    
}

