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
#include "usart.h"
#include "gpio.h"

#include "PID.h"
#include "MyMotor.h"
#include "MyDetector.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "Controller.hpp"

MyMotor leftforwardMotor, leftbackwardMotor, rightforwardMotor, rightbackwardMotor;
MyMotor *motors[] = {&leftforwardMotor, &leftbackwardMotor, &rightforwardMotor, &rightbackwardMotor};
PIDer leftforwardPider, leftbackwardPider, rightforwardPider, rightbackwardPider;
MyDetector leftleftDetector, leftmiddleDetector, middlemiddleDetector, rightmiddleDetector, rightrightDetector;
void initAllMotors();

void initAllDetectors(){
    initDetector(&leftleftDetector, LEFT_LEFT);
    initDetector(&leftmiddleDetector, LEFT_MIDDLE);
    initDetector(&middlemiddleDetector, MIDDLE_MIDDLE);
    initDetector(&rightmiddleDetector, RIGHT_MIDDLE);
    initDetector(&rightrightDetector, RIGHT_RIGHT);
}

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int v2pwm(float v);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void Base_Motor_Rotate(MyMotor* const motor);

void My_Motor_Rotate(MyMotor* const motor, int pwm, int time);

//注意，下面的四个函数，只会修改电机的速度，不会马上转动电机。
void Turn_Left();

void Turn_Right();

void Turn_Back();

void Forward();

//需要调用下面的函数，才会真正转动电机。
void Move();

void detectMove();

u8 isEnd();

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
  //check: whether init successfully or not.
  initAllMotors();
  initAllDetectors();
  /* USER CODE BEGIN 2 */
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  static int counter = 0;
  while (1)
  {
    /* USER CODE END WHILE */
		//1号ID的电机，逆时针转，2号ID的电机，顺时针转

    /*测试运动功能*/
    switch(counter){
      case 0:
        Forward();
        break;
      case 1:
        Turn_Left();
        break;
      case 2:
        Turn_Right();
        break;
      case 3:
        Turn_Back();
        break;
    }
    ++coounter;
    /*运动功能测试结束*/
    //如果上面的测试没有问题，那么注释掉上面的测试代码。然后，将下面的注释取消，开始测试寻线。
    //detectMove();
    Move();
		
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
		HAL_Delay(2000);
		if(isEnd()){
      break;
    }
    /* USER CODE BEGIN 3 */
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

void Base_Motor_Rotate(MyMotor*const motor){
  //todo: 把v映射到pwm
  //int pwm = (int)motor->vx*100;
  My_Motor_Rotate(motor, v2pwm(motor->vx), 500);
}

void My_Motor_Rotate(MyMotor*const motor, int pwm, int time){
  Motor_Rotate(motor->MotorID, pwm, time);
}

void initAllMotors(){
    //todo: adjust pid
    initPID(&leftforwardPider, 0.0, 0.0, 0.0);
    initPID(&leftbackwardPider, 0.0, 0.0, 0.0);
    initPID(&rightforwardPider, 0.0, 0.0, 0.0);
    initPID(&rightbackwardPider, 0.0, 0.0, 0.0);

    initMotor(&leftforwardMotor, LEFT_FORWARD, &leftforwardPider);
    initMotor(&leftbackwardMotor, LEFT_BACKWARD, &leftbackwardPider);
    initMotor(&rightforwardMotor, RIGHT_FORWARD, &rightforwardPider);
    initMotor(&rightbackwardMotor, RIGHT_BACKWARD, &rightbackwardPider);
}

void Forward(){
  leftforwardMotor.vx = 1.0;
  leftbackwardMotor.vx = 1.0;
  rightforwardMotor.vx = 1.0;
  rightbackwardMotor.vx = 1.0;
}

void Turn_Back(){
  leftforwardMotor.vx = -1.0;
  leftbackwardMotor.vx = -1.0;
  rightforwardMotor.vx = -1.0;
  rightbackwardMotor.vx = -1.0;
}

void Turn_Left(){
  leftforwardMotor.vx = -1.0;
  leftbackwardMotor.vx = -1.0;
  rightforwardMotor.vx = 1.0;
  rightbackwardMotor.vx = 1.0;
}

void Move(){
  int i;
  for(i = 0; i < 4; i++){
    Base_Motor_Rotate(*(motors+i));
  }
}

int v2pwm(float v){
  //todo: override this function.
  return (int)(100*v);
}

//先读内侧，再往外读取。
void detectMove(){
  if (digitalRead(&middlemiddleDetector) == 1){
    //前进
    Forward();
  }else if (digitalRead(&leftmiddleDetector) == 1){
    //左转
    Turn_Left();
  }else if (digitalRead(&rightmiddleDetector) == 1){
    //右转
    Turn_Right();
  }else if (digitalRead(&leftleftDetector) == 1){
    //左转
    Turn_Left();
  }else if (digitalRead(&rightrightDetector) == 1){
    //右转
    Turn_Right();
  }else{
    //直走
    Forward();
  }

}

u8 isEnd(){
  // todo: 根据颜色传感器判断是否走到了终点。
  return 0;
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
