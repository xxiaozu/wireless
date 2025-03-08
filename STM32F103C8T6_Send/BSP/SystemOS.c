#include "SystemOS.h"




uint16_t _10ms_time = 0, sec = 0;
uint16_t ADC_Value[2];
short GyroRawStaticError[3] = {0};

void SystemOS_Init()
{
	
	MPU_Init();
	
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_Value,2);
	
	HAL_TIM_Base_Start_IT(&htim2);
	
	NRF_Dev_Init();
	
}
/**************************************************************************
*	MouseBuf[0]--
*	|--bit7~bit3: 
*	|--bit2:   1��ʾ�м�����
*	|--bit1:   1��ʾ�Ҽ�����
*	|--bit0:   1��ʾ�������
*
*	MouseBuf[1]-- X����仯����������ʾ�����ƣ����������ơ��ò����ʾ�仯��
*	MouseBuf[2]-- Y����仯����������ʾ�����ƣ����������ơ��ò����ʾ�仯��
*	MouseBuf[3]-- ���ֱ仯,������ʾ���Ϲ�����������ʾ���¹���
***************************************************************************/
short gyrox,gyroy,gyroz;		//������ԭʼ����
void SystemOS_Loop()
{
	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);

	NRF_TX_Buff[1] = -(uint8_t)((ADC_Value[0] - 2048)/128) - gyroz/64;
	NRF_TX_Buff[2] =  (uint8_t)((ADC_Value[1] - 2048)/128) - gyrox/64;

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
	{
		HAL_Delay(15);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
		{
			NRF_TX_Buff[0] |= 0x01;
		}
	}
	else
	{
		NRF_TX_Buff[0] &= 0xFE;
	}
	
	NRF_Send_Packet(NRF_TX_Buff);
		
	if(NRF_TX_Buff[0] || NRF_TX_Buff[1] || NRF_TX_Buff[2] || NRF_TX_Buff[3])
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, GPIO_PIN_SET);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
    if (htim == (&htim2))//10ms
    {
		_10ms_time++;
		if(_10ms_time%100 == 0)
		{
			sec++;
		}
    }
}



