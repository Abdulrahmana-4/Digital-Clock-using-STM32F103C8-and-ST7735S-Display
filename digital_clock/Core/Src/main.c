/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @author  		: Abdulahman Ahmed Saeed
  * @file           : main.c
  * @brief          : Digital Clock
  ******************************************************************************
  */
/* CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "ST7735.h"
#include "fonts.h"
/* CODE END Includes */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

/* CODE BEGIN PV */
RTC_TimeTypeDef time;
RTC_DateTypeDef date;
char newTime[30];
char newDate[30];
/* CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_SPI1_Init(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	  HAL_Init();

	  /* Configure the system clock */
	  SystemClock_Config();

	  /* Initialize all configured peripherals */
	  /* SPI*/
	  MX_GPIO_Init();
	  MX_RTC_Init();
	  MX_SPI1_Init();
	  /* TFT Display*/
	  ST7735_Init();



	  /** RTC backup data register*/
	  time.Hours   = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
	  time.Minutes = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
	  time.Seconds = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
	  HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);


	  date.Year    = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
	  date.Month   = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5);
	  date.Date    = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR6);
	  date.WeekDay = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR7);
	  HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);




	  char date_arr[3], year_arr[5], month_arr[4], day_arr[10];


	  ST7735_FillScreenFast(ST7735_BLUE);
	  ST7735_WriteString(20, 10, "Digital Clock", Font_7x10, ST7735_YELLOW, ST7735_BLUE);

	  /* Infinite loop */
	  /* BEGIN WHILE */


	  uint8_t day   = date.WeekDay;
	  uint8_t month = date.Month;

	  switch(date.Month){
	  		case RTC_MONTH_JANUARY:   strcpy(month_arr, "Jan\0"); break;
	  		case RTC_MONTH_FEBRUARY:  strcpy(month_arr, "Feb\0"); break;
	  		case RTC_MONTH_MARCH:     strcpy(month_arr, "Mar\0"); break;
	  		case RTC_MONTH_APRIL:     strcpy(month_arr, "Apr\0"); break;
	  		case RTC_MONTH_MAY:       strcpy(month_arr, "May\0"); break;
	  		case RTC_MONTH_JUNE:      strcpy(month_arr, "Jun\0"); break;
	  		case RTC_MONTH_JULY:      strcpy(month_arr, "Jul\0"); break;
	  		case RTC_MONTH_AUGUST:    strcpy(month_arr, "Aug\0"); break;
	  		case RTC_MONTH_SEPTEMBER: strcpy(month_arr, "Sep\0"); break;
	  		case RTC_MONTH_OCTOBER:   strcpy(month_arr, "Oct\0"); break;
	  		case RTC_MONTH_NOVEMBER:  strcpy(month_arr, "Nov\0"); break;
	  		case RTC_MONTH_DECEMBER:  strcpy(month_arr, "Dec\0"); break;
	  	}
	  switch(day){
	  		case RTC_WEEKDAY_FRIDAY:    strcpy(day_arr, "Friday\0"); break;
	  		case RTC_WEEKDAY_SATURDAY:  strcpy(day_arr, "Saturday\0"); break;
	  		case RTC_WEEKDAY_SUNDAY:    strcpy(day_arr, "Sunday\0"); break;
	  		case RTC_WEEKDAY_MONDAY:    strcpy(day_arr, "Monday\0"); break;
	  		case RTC_WEEKDAY_TUESDAY:   strcpy(day_arr, "Tuesday\0"); break;
	  		case RTC_WEEKDAY_WEDNESDAY: strcpy(day_arr, "Wednesday\0"); break;
	  		case RTC_WEEKDAY_THURSDAY:  strcpy(day_arr, "Thursday\0"); break;
	  }


	  while (1)
	  {

		  HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
		  HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);


		  /** Month*/
		  if(month != date.Month){
			  month = date.Month;
			  switch(date.Month){
			  	  case RTC_MONTH_JANUARY:   strcpy(month_arr, "Jan\0"); break;
			  	  case RTC_MONTH_FEBRUARY:  strcpy(month_arr, "Feb\0"); break;
			  	  case RTC_MONTH_MARCH:     strcpy(month_arr, "Mar\0"); break;
			  	  case RTC_MONTH_APRIL:     strcpy(month_arr, "Apr\0"); break;
			  	  case RTC_MONTH_MAY:       strcpy(month_arr, "May\0"); break;
			  	  case RTC_MONTH_JUNE:      strcpy(month_arr, "Jun\0"); break;
			  	  case RTC_MONTH_JULY:      strcpy(month_arr, "Jul\0"); break;
			  	  case RTC_MONTH_AUGUST:    strcpy(month_arr, "Aug\0"); break;
			  	  case RTC_MONTH_SEPTEMBER: strcpy(month_arr, "Sep\0"); break;
			  	  case RTC_MONTH_OCTOBER:   strcpy(month_arr, "Oct\0"); break;
			  	  case RTC_MONTH_NOVEMBER:  strcpy(month_arr, "Nov\0"); break;
			  	  case RTC_MONTH_DECEMBER:  strcpy(month_arr, "Dec\0"); break;
			  }

		  }
		  /** Day*/
		  if(day != date.WeekDay){
			  day = date.WeekDay;
			  switch(day){
			  	  case RTC_WEEKDAY_FRIDAY:    strcpy(day_arr, "Friday\0"); break;
			  	  case RTC_WEEKDAY_SATURDAY:  strcpy(day_arr, "Saturday\0"); break;
			  	  case RTC_WEEKDAY_SUNDAY:    strcpy(day_arr, "Sunday\0"); break;
			  	  case RTC_WEEKDAY_MONDAY:    strcpy(day_arr, "Mon\0"); break;
			  	  case RTC_WEEKDAY_TUESDAY:   strcpy(day_arr, "Tuesday\0"); break;
			  	  case RTC_WEEKDAY_WEDNESDAY: strcpy(day_arr, "Wednesday\0"); break;
			  	  case RTC_WEEKDAY_THURSDAY:  strcpy(day_arr, "Thursday\0"); break;
			  }
		  }

		  date_arr[0]='0'+(date.Date/10);
		  date_arr[1]='0'+(date.Date%10);
		  date_arr[2]='\0';
		  year_arr[0]='2';
		  year_arr[1]='0';
		  year_arr[2]='0'+(date.Year/10);
		  year_arr[3]='0'+(date.Year%10);
		  year_arr[4]='\0';


		  ST7735_WriteString(5, 40, date_arr, Font_11x18, ST7735_CYAN, ST7735_BLUE);
		  ST7735_WriteString(35, 40, month_arr, Font_11x18, ST7735_CYAN, ST7735_BLUE);
		  ST7735_WriteString(75, 40, year_arr, Font_11x18, ST7735_CYAN, ST7735_BLUE);
		  ST7735_WriteString(15, 70, day_arr,Font_11x18 , ST7735_GREEN, ST7735_BLUE);


		  sprintf(newTime, "%02d:%02d:%02d", time.Hours, time.Minutes, time.Seconds);
		  ST7735_WriteString(20,110,newTime,Font_11x18,ST7735_WHITE,ST7735_BLUE);

		  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, time.Hours);
		  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, time.Minutes);
		  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, time.Seconds);
		  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, date.Year);
		  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, date.Month);
		  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR6, date.Date);
		  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR7, date.WeekDay);
	  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 5;
  sTime.Minutes = 50;
  sTime.Seconds = 10;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_THURSDAY;
  DateToUpdate.Month = RTC_MONTH_JULY;
  DateToUpdate.Date = 11;
  DateToUpdate.Year = 24;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{


  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB6 PB7 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }

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

}
#endif /* USE_FULL_ASSERT */
