#include "main.h"
#include "relay.h"


/**
 * @brief  身体气泵吸放气状态(电磁阀)
 * @param  status1 SET出气  1    RESET吸气   0   
 * @param  status2 SET出气  1    RESET吸气   0   
 * @param  status3 SET出气  1    RESET吸气   0   
 */
void Body_MotionStatus(uint8_t status1,uint8_t status2,uint8_t status3)  //SET出气  1    RESET吸气   0   
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

/**
 * @brief  头部气泵吸放气状态
 * @param  status SET出气  1    RESET吸气   0   
 */
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

/**
 * @brief  尾部气泵吸放气状态
 * @param  status SET出气  1    RESET吸气   0   
 */
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



