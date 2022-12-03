/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "stdio.h"
#include "string.h"
/* USER CODE BEGIN 0 */
//����2�����ڷ��͵��ָ��
//���һ��дһ�����ͺ���������HAL�⺯������
void UART2_Send(uint8_t *Data, uint16_t Size)
{
	uint16_t i = 0;
	for(i = 0;i<Size; i++){
		HAL_UART_Transmit(&huart2, &Data[i], 1, 1000);
		while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TXE)!=SET);
	}
}



//����1�����ڷ��͵�����Ϣ��PC��
//�ض��� fputc ����������HAL�⺯�����͡�
int fputc(int ch,FILE *f)
{
	uint8_t temp = ch;
	HAL_UART_Transmit(&huart1,&temp,1,1000);
	while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TXE)!=SET);
	return ch;
}
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  } 
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */


//����������ٶȿ��ƣ������ٶȺ�PWM������Ӧ��ϵ�������е��Ի�궨��
//			input�����ID��(1-999)�������������İ��������֣������ڲ����Զ���'0'���ַ���
//			input��PWM������500-2500�������������İ��������֣������ڲ����Զ���'0'���ַ���
//			input��ת��ʱ�䣬1-9999�������������İ��������֣������ڲ����Զ���'0'���ַ���
//			output: NULL

 void Motor_Rotate(int id, int pwm, int time)
{
		char ID_str[10] = {};
		char PWM_str[10] = {};
		char TIME_str[10] = {};
			
		char data[50] = {"#"};		//data���飬���ڷ��Ϳ���ָ��,����Э�飬��ͷ��"#"
		
		//����������ID��ת��Ϊ�ַ���
		myitoa(id, ID_str, 10);	
		
		//��ID�ŵ��ַ�����ǰ�����㣬����б�Ҫ�Ļ�
		if( (3 - strlen(ID_str)) == 2) {
			strcat(data,"00");
		}
		else if( (3 - strlen(ID_str)) == 1) {
			strcat(data,"0");
		}
		//�ַ���ƴ��
		strcat(data, ID_str);
		//����������PWM����ֵת��Ϊ�ַ���
		myitoa(pwm,PWM_str,10);
		
		//��PWM�������ַ�����ǰ�����㣬����б�Ҫ�Ļ�
		if( (4 - strlen(PWM_str)) == 1) {
			strcat(data,"P0");
		}
		else if( (4 - strlen(PWM_str)) == 0) {
			strcat(data,"P");
		}
		//�ַ���ƴ��
		strcat(data, PWM_str);
		//����������ת��ʱ��ת��Ϊ�ַ���
		myitoa(time, TIME_str, 10);

		//��ת��ʱ����ַ�����ǰ�����㣬����б�Ҫ�Ļ�
		if( (4 - strlen(TIME_str)) == 2) {
			strcat(data,"T00");
		}
		else if( (4 - strlen(TIME_str)) == 1) {
			strcat(data,"T0");
		}
		else if( (4 - strlen(TIME_str)) == 0) {
			strcat(data,"T");
		}
		
		//�ַ���ƴ��
		strcat(data, TIME_str);
		strcat(data,"!\r\n");		//ĩ������"\r\n"��ʹ��ָ�������PC��ʱ��ÿһ��ָ���ռ1�У�����Ϊ�˷���۲�͵��ԡ�
		
		
		//����2���͵������ָ��
		UART2_Send((uint8_t *)data, sizeof(data));
		//��ͬ���Ŀ���ָ��ͨ������1�������PC�ˣ��Ա����
//		printf("%s", data); 
	
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);

}	 



//�������ܣ�������ת�ַ���
//stm32��֧�ֱ�׼��itoa,�����Լ�ʵ��
//�����ָ�����Ϥ�������Լ��ж�����һ�δ��롣

char *myitoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
        if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */
/* USART2 init function */
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
