
#include "signal.h"
#include "common.h"
#include ""

void get_AD_result(uint8 *p)
{

 	uint8 i,j;
	uint16 AD[SUM_AD]={0,0,0,0,0,0};
	uint8 AD_temp[SUM_AD]={0,0,0,0,0,0};
	uint8 AD_max[SUM_AD]={0,0,0,0,0,0};
	uint8 AD_min[SUM_AD]={255,255,255,255,255,255};
	
	for(i=0;i<10;i++)
	{ 
            AD_temp[0]= (uint8)ad_once(ADC0,SE13,ADC_8bit );
            AD_temp[1]= (uint8)ad_once(ADC0,SE9,ADC_8bit );
            AD_temp[2]= (uint8)ad_once(ADC0,SE18,ADC_8bit );
            AD_temp[3]= (uint8)ad_once(ADC0,SE17,ADC_8bit );
            AD_temp[4]= (uint8)ad_once(ADC0,SE8,ADC_8bit );
            AD_temp[5]= (uint8)ad_once(ADC0,SE12,ADC_8bit );
	    for(j=0;j<6;j++)
            {
              if(AD_temp[j]>=AD_max[j])
              { 
                AD_max[j]=AD_temp[j];
              }
              if(AD_temp[j]<=AD_min[j])
              { 
                AD_min[j]=AD_temp[j];
              }
              AD[j]+=AD_temp[j];
          }	
	}	
	for(j=0;j<6;j++)
	{
	    AD[j]=AD[j]-AD_max[j]-AD_min[j];
            p[j]=(uint8)(AD[j]/8);
	}
}