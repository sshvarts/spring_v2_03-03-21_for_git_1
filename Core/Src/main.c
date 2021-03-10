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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_sockets.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

//#include "stm32f4xx_hal_usart.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern BaseType_t FreeRTOS_IPInit( const uint8_t ucIPAddress[],
        const uint8_t ucNetMask[],
        const uint8_t ucGatewayAddress[],
        const uint8_t ucDNSServerAddress[],
        const uint8_t ucMACAddress[] );

//extern HAL_StatusTypeDef HAL_USART_Transmit(USART_HandleTypeDef *husart, uint8_t *pTxData, uint16_t Size, uint32_t Timeout);


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TRUE	1
#define FALSE	0
#define AVAILABLE TRUE
#define NOT_AVAILABLE FALSE

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ETH_HandleTypeDef heth;

USART_HandleTypeDef husart6;

osThreadId defaultTaskHandle;

TaskHandle_t xTaskHandle1 = NULL;
TaskHandle_t xTaskHandle2 = NULL;



char usr_msg[250];
uint8_t UART_ACCESS_KEY = AVAILABLE;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART6_UART_Init(void);
void StartDefaultTask(void const * argument);

static void USART6_Init(void);

void vStartTCPEchoClientTasks_SingleTasks( uint16_t usTaskStackSize, UBaseType_t uxTaskPriority );

void vTask1_handler(void *params);
void vTask2_handler(void *params);
//void printmsg(char *msg);

//static void prvSetupHardware(void);
////static void prvSetupUart(void);


/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static uint8_t ucMACAddress[ 6 ] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };

static const uint8_t ucIPAddress[ 4 ] = { 192, 168, 92, 18 };
static const uint8_t ucNetMask[ 4 ] = { 255, 255, 255, 0 };
static const uint8_t ucGatewayAddress[ 4 ] = { 192, 168, 92, 1 };

static const uint8_t ucDNSServerAddress[ 4 ] = { 208, 67, 222, 222 };

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
  MX_ETH_Init();
  USART6_Init();
  MX_USART6_UART_Init();


  /* USER CODE BEGIN 2 */
  sprintf(usr_msg,"Hello World Starting\r\n");
  HAL_USART_Transmit(&husart6, (uint8_t*)usr_msg, strlen(usr_msg), 1000);

  FreeRTOS_IPInit( ucIPAddress,
                   ucNetMask,
                   ucGatewayAddress,
                   ucDNSServerAddress,
                   ucMACAddress );

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
//  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
//  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

	xTaskCreate( vTask1_handler,
				 "Task-1",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 2,
				&xTaskHandle1 );

	xTaskCreate( vTask2_handler,
				 "Task-2",
				 configMINIMAL_STACK_SIZE,
				 NULL,
				 2,
				&xTaskHandle2 );

  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

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
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  heth.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
  heth.Init.Speed = ETH_SPEED_100M;
  heth.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
  heth.Init.PhyAddress = DP83848_PHY_ADDRESS;
  heth.Init.MACAddr[0] =   0x00;
  heth.Init.MACAddr[1] =   0x80;
  heth.Init.MACAddr[2] =   0xE1;
  heth.Init.MACAddr[3] =   0x00;
  heth.Init.MACAddr[4] =   0x00;
  heth.Init.MACAddr[5] =   0x00;
  heth.Init.RxMode = ETH_RXPOLLING_MODE;
  heth.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
  heth.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

}

void USART6_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */
	__HAL_RCC_USART6_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  husart6.Instance = USART6;
  husart6.Init.BaudRate = 115200;
  husart6.Init.WordLength = USART_WORDLENGTH_8B;
  husart6.Init.StopBits = USART_STOPBITS_1;
  husart6.Init.Parity = USART_PARITY_NONE;
  husart6.Init.Mode = USART_MODE_TX_RX;
//  husart6.Init.HwFlowCtl = USART_HWCONTROL_NONE;
//  husart6.Init.OverSampling = USART_OVERSAMPLING_16;
  if (HAL_USART_Init(&husart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/* USER CODE BEGIN 4 */
/* Called by FreeRTOS+TCP when the network connects or disconnects.  Disconnect
events are only received if implemented in the MAC driver. */
void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
{
uint32_t ulIPAddress, ulNetMask, ulGatewayAddress, ulDNSServerAddress;
char cBuffer[ 16 ];
static BaseType_t xTasksAlreadyCreated = pdFALSE;

FreeRTOS_printf( ( "vApplicationIPNetworkEventHook: event %ld\n", eNetworkEvent ) );

//	showMemories();  //stsh
	/* If the network has just come up...*/
	if( eNetworkEvent == eNetworkUp )
	{
		/* Create the tasks that use the IP stack if they have not already been
		created. */
		if( xTasksAlreadyCreated == pdFALSE )
		{
			/* Tasks that use the TCP/IP stack can be created here. */

			#if( mainCREATE_TCP_ECHO_TASKS_SINGLE == 1 )
			{
				/* See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Clients.html */
				vStartTCPEchoClientTasks_SingleTasks( configMINIMAL_STACK_SIZE * 4, tskIDLE_PRIORITY + 1 );
			}
			#endif

			#if( mainCREATE_SIMPLE_TCP_ECHO_SERVER == 1 )
			{
				/* See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Server.html */
				vStartSimpleTCPServerTasks( configMINIMAL_STACK_SIZE * 4, tskIDLE_PRIORITY + 1 );
			}
			#endif


			#if( ( mainCREATE_FTP_SERVER == 1 ) || ( mainCREATE_HTTP_SERVER == 1 ) )
			{
				/* See TBD.
				Let the server work task now it can now create the servers. */
				xTaskNotifyGive( xServerWorkTaskHandle );
				xTaskNotifyGive( xCommandTaskHandle );
			}
			#endif

			/* Start a new task to fetch logging lines and send them out. */
//			vUDPLoggingTaskCreate();	//stsh

			xTasksAlreadyCreated = pdTRUE;
		}

		/* Print out the network configuration, which may have come from a DHCP
		server. */
		FreeRTOS_GetAddressConfiguration( &ulIPAddress, &ulNetMask, &ulGatewayAddress, &ulDNSServerAddress );
		FreeRTOS_inet_ntoa( ulIPAddress, cBuffer );
		FreeRTOS_printf( ( "IP Address: %s\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulNetMask, cBuffer );
		FreeRTOS_printf( ( "Subnet Mask: %s\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulGatewayAddress, cBuffer );
		FreeRTOS_printf( ( "Gateway Address: %s\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulDNSServerAddress, cBuffer );
		FreeRTOS_printf( ( "DNS Server Address: %s\n", cBuffer ) );
	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
}

  void vTask1_handler(void *params)
  {
  	while(1)
  	{
  		if (UART_ACCESS_KEY == AVAILABLE)
  		{
  			UART_ACCESS_KEY = NOT_AVAILABLE;
//  			printmsg("Hello Task-1----------****\r\n");

			sprintf(usr_msg,"Hello Task-1----------****\r\n");
			HAL_USART_Transmit(&husart6, (uint8_t*)usr_msg, strlen(usr_msg), 1000);

  			UART_ACCESS_KEY = AVAILABLE;

  //			SEGGER_SYSVIEW_Print("Task1 is yielding");
  //			traceISR_EXIT_TO_SCHEDULER();

  			taskYIELD();
  		}
  	}
  }

  void vTask2_handler(void *params)
  {
  	while(1)
  	{
  		if (UART_ACCESS_KEY == AVAILABLE)
  		{
  			UART_ACCESS_KEY = NOT_AVAILABLE;
//  			printmsg("Hello Task-2=====================\r\n");
			sprintf(usr_msg,"Hello Task-2=====================\r\n");
			HAL_USART_Transmit(&husart6, (uint8_t*)usr_msg, strlen(usr_msg), 1000);

  			UART_ACCESS_KEY = AVAILABLE;

  //			SEGGER_SYSVIEW_Print("Task2 is yielding");
  //			traceISR_EXIT_TO_SCHEDULER();

  			taskYIELD();
  		}
  	}
  }

  /* USER CODE END 5 */


//static void prvSetupUart(void)
//{
////	GPIO_InitTypeDef gpio_uart_pins;
////	USART_InitTypeDef usart6_init;
////	USART_HandleTypeDef husart_6;
//
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	//1. Enable UART peripheral clock
////	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
////	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//
//	__HAL_RCC_USART6_CLK_ENABLE();
//	__HAL_RCC_GPIOC_CLK_ENABLE();
//
//	//PA2 is UART2_TX, PA3 is UART_RX
//
//	//2. Alternate functions of pins PC6 and PC7
//	//Zero each element of the structure
////	memset(&gpio_uart_pins,0, sizeof(gpio_uart_pins));
////
////	gpio_uart_pins.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7;
////	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
////	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
////	GPIO_Init(GPIOC, &gpio_uart_pins);
//
//	  /* Configure PA1, PA2 and PA7 */
//	  GPIO_InitStructure.Pin 		= GPIO_PIN_6 | GPIO_PIN_7;
//
//	  GPIO_InitStructure.Speed 		= GPIO_SPEED_FREQ_HIGH;
//	  GPIO_InitStructure.Mode 		= GPIO_MODE_AF_PP;
//	  GPIO_InitStructure.Pull 		= GPIO_MODE_OUTPUT_PP;
//	  GPIO_InitStructure.Alternate 	= GPIO_AF8_USART6;
//	  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//
//	//3. AF mode settings for pins
////	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6); // PC6
////	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6); // PC7
//
//	//4. UART parameter initialization
//
//	//Zero each element of the structure
//	memset(&husart6.Init, 0, sizeof(husart6.Init));
//
////	husart_6.Instance = USART6;
//	husart6.Instance = USART6;
//
//
//	husart6.Init.BaudRate = 115200;
////	usart6_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	husart6.Init.Mode = USART_MODE_TX | USART_MODE_RX;
//	husart6.Init.Parity = USART_PARITY_NONE;
//	husart6.Init.StopBits = USART_STOPBITS_1;
//	husart6.Init.WordLength = USART_WORDLENGTH_9B;   //USART_WORDLENGTH_8B;  stsh
//
////	USART_SetConfig(&husart_6);
//
//	HAL_USART_Init(&husart6);
//
//
//	//5. Enable the UART peripheral
////	USART_Cmd(USART6, ENABLE);
//}



//void prvSetupHardware(void)
//{
//	// Setup UART2
////	prvSetupUart();
//}

//void printmsg(char *msg)
//{
//	for(uint32_t i = 0; i < strlen(msg); i++)
//	{
////		while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) != SET);
//		__HAL_USART_GET_FLAG(USART6, USART_FLAG_TXE);
//		USART_SendData(USART6, msg[i]);
//	}
//}


//void printmsg(char *msg)
//{
//	for(uint32_t i = 0; i < strlen(msg); i++)
//	{
//		while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) != SET);
//		USART_SendData(USART6, msg[i]);
//	}
//}


 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
  /* USER CODE BEGIN Callback 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  /* USER CODE END Callback 1 */
}

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
