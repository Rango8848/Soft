#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "main.h"
#include "system.h"

void Run_on_off(uint8_t mode);
void Run(uint8_t mode);
long map(long x, long in_min, long in_max, long out_min, long out_max);
void BEND_Value_Conversion(void);
uint16_t Get_Adc_Average(ADC_HandleTypeDef *hadc,uint8_t times);
void Test(uint8_t mode);

#endif
