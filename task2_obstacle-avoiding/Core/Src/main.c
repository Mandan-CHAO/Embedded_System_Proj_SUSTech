/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Turn_left(int);
void Turn_right(int);
void Forward(int);
void Color_stop(int,int,int);
void Decide_dir(int,int,int,int,int,int,int,int,int,int);
int Forward_adjust(int,int);
int Forward_adjust2(int,int);
void back(int);
void Left_move();
void Right_move();

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern int flag;
extern int count;
extern int cnt[3];
float RGB_Scale[3];
int motor_flag=1;
int stop_signal=0;
int double_check=0;
int Count_turn=0;
int test_mode=0;
int First_time=1;
int color_start=1;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

 //ѡ�����Ƶ��
	//2%
	HAL_TIM_Base_Start_IT(&htim1);//ʹ�ܶ�ʱ��1
	HAL_TIM_Base_Start(&htim2);//ʹ�ܶ�ʱ��2
	
	//ѡ��2%�������������
	S0_L;
	S1_H;
	LED_ON;//���ĸ���ɫLED�����а�ƽ��
//	HAL_Delay(3000);
	if (!test_mode){
	HAL_Delay(1000);
	}
	//ͨ����ƽ����ԣ�����õ���ɫ���RGBֵ255��0.5������ɫ����������RGB��������
	for(int i = 0; i < 3; i++){
		RGB_Scale[i] = 255.0/cnt[i];
		printf("RGB Scaler %f \r\n",RGB_Scale[i]); 
	}
	
	//��������ɫ��ֱ��Ӧ��0.5s��TCS3200�����������������Ӧ�ı������Ӿ���������ν��RGB��׼ֵ
	//��ӡ���������RGBֵ
	for(int i = 0; i < 3; i++){
		printf("RGB = %d \r\n",(int)(cnt[i]*RGB_Scale[i])); 
	}
	printf("White Balance Done!\r\n");
//	HAL_Delay(3000);
//	if (!test_mode){
//	HAL_Delay(3000);
//	}
	
	//��ƽ�����
    /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	unsigned int dta=10;
	unsigned int dta2=50;
	unsigned int dta_last;
	unsigned int dta_last2;
	unsigned int dta2_last5=50;
	unsigned int dta2_last4=50;
	unsigned int dta2_last3=50;
	unsigned int dta2_last2=50;
	unsigned int dta2_last1=50;
	unsigned int dta3=60;
	if (!test_mode){
	Forward(0);
	HAL_Delay(800);
	}
	
  while (1)
  {
		printf("\n====================================\n");
		// 右超声波
		StartModule();               //����������ģ��
    while(!GetStatus());        //��ECHO����0���ȴ�          
    start();
    while(GetStatus());		  //��ECHOΪ1�������ȴ�		
		dta_last2=dta_last;
		dta_last= dta;
    dta = get_num();
		int diff01=dta-dta_last;
		int diff12=dta_last-dta_last2;
    printf("Distance_right:%d cm\r\n",dta);	
		
		//左超声波
		StartModule2();               //����������ģ��
		while(!GetStatus2()){};        //��ECHO����0���ȴ�          
    start();
    while(GetStatus2());		  //��ECHOΪ1�������ȴ�   
		dta2_last5=dta2_last4;
		dta2_last4=dta2_last3;
		dta2_last3=dta2_last2;
		dta2_last2=dta2_last1;
		dta2_last1=dta2;    
    dta2 = get_num();
    printf("Distance_left:%d cm\r\n",dta2);
//		printf("last1:%d cm\r\n",dta2_last1);
//		printf("last2:%d cm\r\n",dta2_last2);
//		printf("last3:%d cm\r\n",dta2_last3);
//		printf("last4:%d cm\r\n",dta2_last4);
//		printf("last5:%d cm\r\n\n",dta2_last5);
		
		//前超声波	
		StartModule3();               //����������ģ��
    while(!GetStatus3());        //��ECHO����0���ȴ�          
    start();
    while(GetStatus3());		  //��ECHOΪ1�������ȴ�		
//		dta3_last2=dta3_last;
//		dta3_last= dta3;
    dta3 = get_num();
    printf("Distance_forward:%d cm\r\n",dta3);	
    
		if(Count_turn>=22) //至少两次左转，两次右转后，才会开启颜色识别，增加380ms delay，每个循环的延迟会显著增高
			{
				flag = 0;
				count = 0;
				HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
				for(int i=0; i<3; i++)
				{
					if(i==0)
						printf("RGB = (");
					if(i==2)
						printf("%d)\r\n",(int) (cnt[i]*RGB_Scale[i]));
					else
						printf("%d, ", (int) (cnt[i]*RGB_Scale[i]));
				}
				int red=(int) cnt[0]*RGB_Scale[0];
				int green=(int) cnt[1]*RGB_Scale[1];
				int blue=(int) cnt[2]*RGB_Scale[2];
				HAL_Delay(380);
				printf("red:%d,green:%d,blue:%d",cnt[0],cnt[1],cnt[2]);
				if(First_time){
				Left_move(400);
				HAL_Delay(400);
				First_time=0;
				}
				if(dta2>=20&& First_time==0 && color_start){
				Right_move(300);
				HAL_Delay(300);
				back(500);
				HAL_Delay(600);
				color_start=0;
				}
				Color_stop(red,green,blue);//积累红色信号
		//		Color_stop(cnt[0],cnt[1],cnt[2]);//积累红色信号
			}else{
		if (!test_mode){
    Decide_dir(dta,dta2,dta3,diff01,diff12,dta2_last5,dta2_last4,dta2_last3,dta2_last2,dta2_last1);
		}
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			}
		HAL_Delay(20);

    
	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */



void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1|RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1|RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1|RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1|RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Decide_dir(int dta,int dta2,int dta3, int diff01,int diff12,int dta2_last5,int dta2_last4,int dta2_last3,int dta2_last2,int dta2_last1)
{
//	if(dta2>10 &&dta2<17)
//{
//	double_check++;
//}
//else 
//{
//	double_check=0;
//}
//	if(double_check>=2){
//		Turn_left();
//		HAL_Delay(550);
//		double_check=0;
//	}
	
	
//	int yes=0;
//	if(dta2_last5<50 && dta2_last4<50 &&dta2_last3<40 && dta2_last2<40 && dta2_last1<30)
//		{
//			yes=1;
//	}
//	else{yes=0;}
//	if(dta2>0 && dta2<30 && yes && Count_turn<=1)
//{
//Turn_left();
//HAL_Delay(600);
//printf("Count_turn= %d\n",Count_turn);
//Count_turn++;
//}
//	else if(dta2>0 && dta2<28 && Count_turn>=2)
//{
//Turn_right();
//HAL_Delay(600);
//}



if (Count_turn==2){
	Forward(0);
	HAL_Delay(200);
}
// dta是右超声波，dta2是左超声波，dta3是前置超声波
if(dta > 30 && Count_turn>=2 && dta3 <= 22 && dta2<=22) //右转部分。Count_turn加到2，才能开启右转功能
{
//	back();
//	HAL_Delay(500);
	Left_move(200);//左平移
	HAL_Delay(200);
	if(dta2<8){
	Right_move(400);//右平移
	HAL_Delay(400);
	}
	Turn_right(460);//右转
	HAL_Delay(460);
	Count_turn+=10;
}
else if(((dta2>=18 && dta>=20)||dta2 > 30) && dta3 <= 20)//左转部分
{
	back(200); // 加段后退，是为了解决抵着墙动不了的情况。让下一个循环就有机会转动
	HAL_Delay(200);
	Right_move(200);//右平移
	HAL_Delay(200);
	if(dta<8){
	Left_move(200);//左平移
	HAL_Delay(200);
	}
	if (Count_turn==1){
	Turn_left(460);//左转
	HAL_Delay(460);
	}else{
	Turn_left(460);//左转
	HAL_Delay(460);
	}
	Count_turn++;
}
else
{
	if(dta<18&& dta2 <18)//判断在直道里
		{
//		int coff=Forward_adjust(diff01,diff12);//算直线矫正补偿
		int coff=Forward_adjust2(dta,dta2);//算直线矫正补偿
		Forward(coff);//加直线矫正补偿的直行
	}else{Forward(0);}//不在直道里，就不加直线矫正补偿的直行
}
}

void Color_stop(int red,int green, int blue)
{
if(red>=green+blue)
{
	stop_signal++;
	printf("Red++\n");
}
//else{
//	if(stop_signal>0)
//{
//  stop_signal--;
//	printf("Set Zero\n");
//}
//}
if (stop_signal>=1)
{
//	printf("Stop!!!!!!!!!!\n");
//	back(200);
//	HAL_Delay(200);
	Motor_Rotate(1,1500,5000);
	Motor_Rotate(2,1500,5000);
	Motor_Rotate(3,1500,5000);
	Motor_Rotate(4,1500,5000);
	HAL_Delay(5000);
}else{
	Motor_Rotate(1,1190,1000);
	Motor_Rotate(2,1190,1000);
	Motor_Rotate(3,1750,1000);
	Motor_Rotate(4,1750,1000);
}
}

void Turn_right(int time)
{
	/*ID: 1-RightFront 2-RightRear 3-LeftRear 4-LeftFront*/
	/*Velocity: 1500-2500_clockwise 500-1500_counterclocwist*/
	Motor_Rotate(1,1900,time);
	Motor_Rotate(2,1900,time);
	Motor_Rotate(3,1900,time);
	Motor_Rotate(4,1900,time);
	printf("right!!!!!!!!!!!\n");
}

void Turn_left(int time)
{
	/*ID: 1-RightFront 2-RightRear 3-LeftRear 4-LeftFront*/
	/*Velocity: 1500-2500_clockwise 500-1500_counterclocwist*/
  Motor_Rotate(1,800,time);
	Motor_Rotate(2,800,time);
	Motor_Rotate(3,800,time);
	Motor_Rotate(4,800,time);
	printf("left!!!!!!!!!!!\n");
}
//void Forward(int coff){
//	/*ID: 1-RightFront 2-RightRear 3-LeftRear 4-LeftFront*/	
//	/*Velocity: 1500-2500_clockwise 500-1500_counterclocwist*/
//	Motor_Rotate(1,1176+coff,2000);
//	Motor_Rotate(2,1176+coff,2000);
//	Motor_Rotate(3,1750+coff,2000);
//	Motor_Rotate(4,1750+coff,2000);
//	printf("forward!!!!!!!!!!!\n");
//}

void Forward(int coff){
	/*ID: 1-RightFront 2-RightRear 3-LeftRear 4-LeftFront*/	
	/*Velocity: 1500-2500_clockwise 500-1500_counterclocwist*/
	Motor_Rotate(1,1010+coff,2000);
	Motor_Rotate(2,1010+coff,2000);
	Motor_Rotate(3,2000+coff,2000);
	Motor_Rotate(4,2000+coff,2000);
	printf("forward!!!!!!!!!!!\n");
}

void Left_move(int time){
	/*ID: 1-RightFront 2-RightRear 3-LeftRear 4-LeftFront*/	
	/*Velocity: 1500-2500_clockwise 500-1500_counterclocwist*/
	Motor_Rotate(1,1050,time);
	Motor_Rotate(2,1750,time);
	Motor_Rotate(3,1750,time);
	Motor_Rotate(4,1050,time);
	printf("left_move!!!!!!!!!!!\n");
}

void Right_move(int time){
	/*ID: 1-RightFront 2-RightRear 3-LeftRear 4-LeftFront*/	
	/*Velocity: 1500-2500_clockwise 500-1500_counterclocwist*/
	Motor_Rotate(1,1750,time);
	Motor_Rotate(2,1050,time);
	Motor_Rotate(3,1050,time);
	Motor_Rotate(4,1750,time);
	printf("right_move!!!!!!!!!!!\n");
}

void back(time){
	/*ID: 1-RightFront 2-RightRear 3-LeftRear 4-LeftFront*/	
	/*Velocity: 1500-2500_clockwise 500-1500_counterclocwist*/
	Motor_Rotate(1,1750,time);
	Motor_Rotate(2,1750,time);
	Motor_Rotate(3,1150,time);
	Motor_Rotate(4,1150,time);
	printf("back!!!!!!!!!!!\n");
}

//int Forward_adjust(int diff01,int diff12)
//{
//int coff=0;
//if(diff01>=1&&diff12>=1)
//{
//coff=100;
//printf("adjust to right\n");
//}
//else if(diff01<=-1&&diff12<=-1)
//{
//coff=-100;
//printf("adjust to left\n");
//}
//return coff;
//}

int Forward_adjust2(int dta,int dta2)
{
int coff=0;
if(dta2<=5||dta>=12)
{
coff=30;
//Right_move(200);
//HAL_Delay(200);

//printf("adjust to right\n");
}
else if(dta<=6||dta2>=10)
{
coff=-30;
//Left_move(200);
//HAL_Delay(200);
//printf("adjust to left\n");
}
return coff;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
