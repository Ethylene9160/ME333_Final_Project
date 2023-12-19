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



/* Private includes ----------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "PID.h"
#include "MyMotor.h"
#include "MyDetector.h"
/* USER CODE END Includes */
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
MyMotor leftforwardMotor, leftbackwardMotor, rightforwardMotor, rightbackwardMotor;
MyMotor *motors[] = {&leftforwardMotor, &leftbackwardMotor, &rightforwardMotor, &rightbackwardMotor};
PIDer leftforwardPider, leftbackwardPider, rightforwardPider, rightbackwardPider;
MyDetector leftleftDetector, leftmiddleDetector, middlemiddleDetector, rightmiddleDetector, rightrightDetector;

extern int flag;
extern int count;
extern int cnt[3];
float RGB_Scale[3];		//储存3个RGB比例因子

/* USER CODE END 0 */

uint8_t isEnd();

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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  // MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  // MX_USART1_UART_Init();
  
  //这里还没init好，为了避免引脚冲突，先注释掉。
  
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim1);	//使能定时器1
	HAL_TIM_Base_Start(&htim2);	//使能定时器2

  //选择2%的输出比例因子
	S0_L;
	S1_H;
	
	LED_ON;		//打开四个白色LED，进行白平衡
	HAL_Delay(3000);		//延时三秒，等待识别
	
	//通过白平衡测试，计算得到白色物的RGB值255与0.5秒内三色光脉冲数的RGB比例因子
	for(int i=0;i<3;i++)
	{
		RGB_Scale[i] = 255.0/cnt[i];
		printf("%5lf  \r\n", RGB_Scale[i]);
	}
	//红绿蓝三色光分别对应的0.5s内TCS3200输出脉冲数，乘以相应的比例因子就是我们所谓的RGB标准值
	//打印被测物体的RGB值
	
	for(int i=0; i<3; i++)
	{
		printf("%d \r\n", (int) (cnt[i]*RGB_Scale[i]));
	}
	printf("White Balance Done!\r\n");
	//白平衡结束

	initAllMotors();
  initAllDetectors();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    
    /*运动功能测试结束*/
    //如果上面的测试没有问题，那么注释掉上面的测试代码。
    //然后，在接好寻线传感器并正确配置引脚的情况下，将下面的注释取消，开始测试寻线。
    
    /* USER CODE BEGIN 3 */

    /* 色彩传感器的测试 */
    flag = 0;
		count = 0;
//		printf("while loop is running!\r\n");
		HAL_Delay(3000);
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
    /* 色彩传感器测试结束 */


    /* 寻线传感器测试 */

    detectMove();
    // Turn_Left();
    // Finally, DO NOT FORGET TO CALL Move() or TimeMove() function to activate the motors.
    Move();
    //TimeMove(500);
		/* 巡线传感器测试结束 */
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
		// HAL_Delay(2000);
		if(isEnd()){
      break;
    }
  }
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint8_t isEnd(){
  // todo: 根据颜色传感器判断是否走到了终点。
  return 0;
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
  //报错也给我跑！！！
  main();
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}


#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
