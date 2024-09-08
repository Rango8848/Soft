#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#include "motor.h"

void Body_Status(uint8_t status1,int duty1,uint8_t status2,int duty2,uint8_t status3,int duty3);
void Minipump1_Status(uint8_t status,int duty);
void Minipump2_Status(uint8_t status,int duty);

#endif
