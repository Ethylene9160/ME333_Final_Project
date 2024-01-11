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

#include "MyMotor.h"
#include "MyDetector.h"
#include "PID.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
MyMotor leftforwardMotor, leftbackwardMotor, rightforwardMotor, rightbackwardMotor;
MyDetector leftleftDetector, leftmiddleDetector, middlemiddleDetector ,rightmiddleDetector, rightrightDetector;
PIDer leftforwardPider, leftbackwardPider, rightforwardPider, rightbackwardPider;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// #define Move();
// #define detectMove();
// #define initAllDetectors();
// #define initAllMotors();
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern int flag;
extern int count;
extern int cnt[3];
float RGB_Scale[3];		//å‚¨å­˜3ä¸ªRGBæ¯”ä¾‹å› å­

uint8_t Is_end(int* cnt,float* RGB_Scale);

uint8_t isEnd();
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int is_end=0;

int RGB_abs_min[]={210,150,80};

int RGB_abs_max[]={1000,300,160};
int count_RGB=0;
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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

	HAL_TIM_Base_Start_IT(&htim1);	//ä½¿èƒ½å®šæ—¶å™?1
	HAL_TIM_Base_Start(&htim2);	//ä½¿èƒ½å®šæ—¶å™?2
	
	//é€‰æ‹©2%çš„è¾“å‡ºæ¯”ä¾‹å› å­?
	S0_L;
	S1_H;
	
	LED_ON;		//æ‰“å¼€å››ä¸ªç™½è‰²LEDï¼Œè¿›è¡Œç™½å¹³è¡¡
	HAL_Delay(3000);		//å»¶æ—¶ä¸‰ç§’ï¼Œç­‰å¾…è¯†åˆ?
	
	//é€šè¿‡ç™½å¹³è¡¡æµ‹è¯•ï¼Œè®¡ç®—å¾—åˆ°ç™½è‰²ç‰©çš„RGBå€?255ä¸?0.5ç§’å†…ä¸‰è‰²å…‰è„‰å†²æ•°çš„RGBæ¯”ä¾‹å› å­
	for(int i=0;i<3;i++)
	{
		RGB_Scale[i] = 255.0/cnt[i];
		printf("%5lf  \r\n", RGB_Scale[i]);
	}
	//çº¢ç»¿è“ä¸‰è‰²å…‰åˆ†åˆ«å¯¹åº”çš?0.5så†…TCS3200è¾“å‡ºè„‰å†²æ•°ï¼Œä¹˜ä»¥ç›¸åº”çš„æ¯”ä¾‹å› å­å°±æ˜¯æˆ‘ä»¬æ‰€è°“çš„RGBæ ‡å‡†å€?
	//æ‰“å°è¢«æµ‹ç‰©ä½“çš„RGBå€?
	
	for(int i=0; i<3; i++)
	{
		printf("%d \r\n", (int) (cnt[i]*RGB_Scale[i]));
	}
	printf("White Balance Done!\r\n");
	//ç™½å¹³è¡¡ç»“æ?

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

		count = 0;
//	printf("while loop is running!\r\n");
		// HAL_Delay(3000);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
		initAllDetectors();
    initAllMotors();
		for(int i=0; i<3; i++)
		{
			if(i==0)
				printf("RGB = (");
			if(i==2)
				printf("%d)\r\n",(int) (cnt[i]*RGB_Scale[i]));
			else
				printf("%d, ", (int) (cnt[i]*RGB_Scale[i]));
		}
    /* USER CODE BEGIN 3 */
		// Motor_Rotate(1,1800,1000);
		// Motor_Rotate(2,1150,1000);
		// if(Is_end(cnt,RGB_Scale)){
    //   printf("end\r\n");
    //   break;
    // }
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
    detectMove();
    // leftbackwardMotor.targetV = 0.0;
    // Turn_Right(2.0);
    //Move();

    TimeMove(20);//16

    // Motor_Rotate(1,1                                                                                                                                           aA150,200);
		//HAL_Delay(2000);
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
  RCC_OscInitStruct.PLL.PLLR = 2;
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
}

/* USER CODE BEGIN 4 */
uint8_t Is_end(int* cnt, float* RGB_Scale){
  static int counter = 0;//è®°å½•æ£€æµ‹åˆ°é»„è‰²çš„æ¬¡æ•°ã€‚å¦‚æžœåˆ°è¾¾äº†å·´æ‹‰å·´æ‹‰æ¬¡ï¼Œå†è¿”å›žçœŸï¼Œä»¥æŽ’é™¤è¯¯å·®ã€?
	is_end=0;
	count_RGB=0;
	for(int i=0;i<3;i++){
		if(RGB_abs_min[i] < (int)(cnt[i]*RGB_Scale[i]) && RGB_abs_max[i]>(int)(cnt[i]*RGB_Scale[i]))
			count_RGB++;
		else
			break;
	}
	if(count_RGB==3){
    counter += 1;
    if(counter == 3){
		  is_end=1;
    } 
  }else{
    counter = 0;
  }
	return is_end;
}

//æˆ–è€…ä½¿ç”¨è¿™ä¸ªå‡½æ•°ï¼Œè¿™ä¸ªå‡½æ•°å¯¹æŒ‡é’ˆç›´æŽ¥å–å€¼ï¼Œå¹¶é‡‡ç”¨å¾ªçŽ¯å±•å¼€ï¼Œå¯¹å•ç‰‡æœºæœ‰æ›´é«˜çš„æ•ˆçŽ‡ã€?
uint8_t isEnd(){
  static int counter = 0;
  if(*(RGB_abs_min)   < (int)((*(cnt))*(*(RGB_Scale)))      && *(RGB_abs_max)   >(int)((*(cnt))*(*(RGB_Scale))) &&
    *(RGB_abs_min+1)  < (int)((*(cnt+1))*(*(RGB_Scale+1)))  && *(RGB_abs_max+1) >(int)((*(cnt+1))*(*(RGB_Scale+1))) &&
    *(RGB_abs_min+2)  < (int)((*(cnt+2))*(*(RGB_Scale+2)))  && *(RGB_abs_max+2) >(int)((*(cnt+2))*(*(RGB_Scale+2)))){
      counter += 1;
      if(counter == 3){
        return 1;
      }
    }else{
      counter = 0;
    }
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
