#include "main.h"
#include "relay.h"

void Body_MotionStatus(uint8_t status1,uint8_t status2,uint8_t status3)  //SET³öÆø  1    RESETÎüÆø   0   
{
	if(status1 == 1)
	{
		HAL_GPIO_WritePin(PumpMax1_GPIO_Port,PumpMax1_Pin,GPIO_PIN_SET);
	}
	else if(status1 ==0)
	{
		HAL_GPIO_WritePin(PumpMax1_GPIO_Port,PumpMax1_Pin,GPIO_PIN_RESET); 
	}		
	
		if(status2 == 1)
	{
		HAL_GPIO_WritePin(PumpMax2_GPIO_Port,PumpMax2_Pin,GPIO_PIN_SET);
	}
	else if(status2 ==0)
	{
		HAL_GPIO_WritePin(PumpMax2_GPIO_Port,PumpMax2_Pin,GPIO_PIN_RESET);
	}		
	
		if(status3 == 1)
	{
		HAL_GPIO_WritePin(PumpMax3_GPIO_Port,PumpMax3_Pin,GPIO_PIN_SET);		
	}
	else if(status3 ==0)
	{
		HAL_GPIO_WritePin(PumpMax3_GPIO_Port,PumpMax3_Pin,GPIO_PIN_RESET);		
	}		
				
}

void Minipump1_MotionStatus(uint8_t status)     
{
	if(status == 1)
	{
		HAL_GPIO_WritePin(PumpMin1_GPIO_Port,PumpMin1_Pin,GPIO_PIN_SET);
	}
	else if(status ==0)
	{
		HAL_GPIO_WritePin(PumpMin1_GPIO_Port,PumpMin1_Pin,GPIO_PIN_RESET);
	}			
}

void Minipump2_MotionStatus(uint8_t status)     
{
	if(status == 1)
	{
		HAL_GPIO_WritePin(PumpMin2_GPIO_Port,PumpMin2_Pin,GPIO_PIN_SET);
	}
	else if(status ==0)
	{
		HAL_GPIO_WritePin(PumpMin2_GPIO_Port,PumpMin2_Pin,GPIO_PIN_RESET);
	}			
}



