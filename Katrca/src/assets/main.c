/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include "stm32f411.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
	USART_TypeDef *USARTx; //npr. USART1 ali USART2...
	uint32_t COM_SPEED; //npr. 115200 ali 9600,...
	GPIO_TypeDef *TX_PORT; //npr. GPIOA ali GPIOB, ...
	uint8_t TX_PIN; //npr. pin 0 ali pin 1, ....
	GPIO_TypeDef *RX_PORT; //npr. GPIOA ali GPIOB, ...
	uint8_t RX_PIN; //npr. pin 0 ali pin 1, ....
} myUart_TypeDdef;

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t tx_buf[]= "Test funkcije za pošiljanje\n";
uint8_t rx_buf[100]; //Polje za sprejem zankov

void myUART_Init(myUart_TypeDdef *uart_x) {

	if (uart_x->USARTx == USART1) {
		RCC->APB1ENR |= 4;

		if ((uart_x->TX_PORT == GPIOA && uart_x->TX_PIN == 9) || (uart_x->TX_PORT == GPIOA && uart_x->TX_PIN == 15) || (uart_x->TX_PORT == GPIOB && uart_x->TX_PIN == 6)) {
			if (uart_x->TX_PORT == GPIOA) {
				// Enable GPIOA Clock
				RCC->AHB1ENR |= 1 << 0;
				// Init TX Pin
				GPIOA->MODER |= 1 << (uart_x->TX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->TX_PIN * 2;
			} else {
				RCC->AHB1ENR |= 1 << 1;

				GPIOB->MODER |= 1 << (uart_x->TX_PIN * 2 + 1);
				GPIOB->AFR[0] = 7 << uart_x->TX_PIN * 2;
			}
		}
		if ((uart_x->RX_PORT == GPIOA && uart_x->RX_PIN == 10) || (uart_x->RX_PORT == GPIOA && uart_x->RX_PIN == 16) || (uart_x->RX_PORT == GPIOB && uart_x->RX_PIN == 7)) {
			if (uart_x->RX_PORT == GPIOA) {
				// Enable GPIOA Clock
				RCC->AHB1ENR |= 1 << 0;

				GPIOA->MODER |= 1 << (uart_x->RX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->RX_PIN * 2;
			} else {
				RCC->AHB1ENR |= 1 << 1;

				GPIOB->MODER |= 1 << (uart_x->RX_PIN * 2 + 1);
				GPIOB->AFR[0] = 7 << uart_x->RX_PIN * 2;
			}
		}

		// Enable Rx
		USART1->CR1 |= 1<<2;
		// Enable Tx
		USART1->CR1 |= 1<<3;

		USART1->BRR = SystemCoreClock / uart_x->COM_SPEED;
		USART1->CR1 |= 1<<13;
		// Enable RXNE interrupts
		USART1->CR1 |= USART_CR1_RXNEIE;
		NVIC_EnableIRQ(USART1_IRQn);

	} else if (uart_x->USARTx == USART2) {
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		USART2->CR1 &= ~USART_CR1_UE;

		if ((uart_x->TX_PORT == GPIOA && uart_x->TX_PIN == 2) || (uart_x->TX_PORT == GPIOD && uart_x->TX_PIN == 5)) {
			if (uart_x->TX_PORT == GPIOA) {
				// Enable GPIOA Clock
				RCC->AHB1ENR |= 1 << 0;

				GPIOA->MODER |= 1 << (uart_x->TX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->TX_PIN * 2;
			} else {
				RCC->AHB1ENR |= 1 << 3;

				GPIOA->MODER |= 1 << (uart_x->TX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->TX_PIN * 2;
			}
		}
		if ((uart_x->RX_PORT == GPIOA && uart_x->RX_PIN == 3) || (uart_x->RX_PORT == GPIOD && uart_x->RX_PIN == 6)) {
			if (uart_x->RX_PORT == GPIOA) {
				// Enable GPIOA Clock
				RCC->AHB1ENR |= 1 << 0;

				GPIOA->MODER |= 1 << (uart_x->RX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->RX_PIN * 2;
			} else {
				RCC->AHB1ENR |= 1 << 3;

				GPIOA->MODER |= 1 << (uart_x->RX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->RX_PIN * 2;
			}
		}

		// Enable Rx
		USART2->CR1 |= 1<<2;
		// Enable Tx
		USART2->CR1 |= 1<<3;

		USART2->BRR = SystemCoreClock / uart_x->COM_SPEED;
		USART2->CR1 |= 1<<13;
		// Enable RXNE interrupts
		USART2->CR1 |= USART_CR1_UE;
		USART2->CR1 |= USART_CR1_RXNEIE;
		NVIC_EnableIRQ(USART1_IRQn);

	} else if (uart_x->USARTx == USART6) {
		RCC->APB2ENR |= 5;

		if ((uart_x->TX_PORT == GPIOA && uart_x->TX_PIN == 11) || (uart_x->TX_PORT == GPIOC && uart_x->TX_PIN == 6)) {
			if (uart_x->TX_PORT == GPIOA) {
				// Enable GPIOA Clock
				RCC->AHB1ENR |= 1 << 0;

				GPIOA->MODER |= 1 << (uart_x->TX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->TX_PIN * 2;
			} else {
				RCC->AHB1ENR |= 1 << 2;

				GPIOA->MODER |= 1 << (uart_x->TX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->TX_PIN * 2;
			}
		}
		if ((uart_x->RX_PORT == GPIOA && uart_x->RX_PIN == 12) || (uart_x->RX_PORT == GPIOC && uart_x->RX_PIN == 7)) {
			if (uart_x->TX_PORT == GPIOA) {
				// Enable GPIOA Clock
				RCC->AHB1ENR |= 1 << 0;

				GPIOA->MODER |= 1 << (uart_x->RX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->RX_PIN * 2;
			} else {
				RCC->AHB1ENR |= 1 << 2;

				GPIOA->MODER |= 1 << (uart_x->RX_PIN * 2 + 1);
				GPIOA->AFR[0] = 7 << uart_x->RX_PIN * 2;
			}
		}

		// Enable Rx
		USART6->CR1 |= 1<<2;
		// Enable Tx
		USART6->CR1 |= 1<<3;

		USART6->BRR = SystemCoreClock / uart_x->COM_SPEED;
		USART6->CR1 |= 1<<13;
		// Enable RXNE interrupts
		USART6->CR1 |= USART_CR1_RXNEIE;
		NVIC_EnableIRQ(USART1_IRQn);

	}

}

void myUART_Tx(USART_TypeDef *USARTx, uint8_t* tx_buff, uint32_t tx_len) {
	uint8_t i = 0;

		while (1) {
		// while (((USART1_SR) & 1 << 7) == 0);
		while (!(USARTx->SR & USART_SR_TXE)) ;

		if (tx_buff[i] == 0) break;

		USARTx->DR = tx_buff[i];
		i++;
	}
}

void myUART_Rx(USART_TypeDef *USARTx, uint8_t* rx_buff, uint32_t rx_len, uint8_t end_char) {
	uint32_t i = 0;

	while (USARTx->SR & USART_SR_RXNE) {
		uint32_t r = USARTx->DR;
		rx_buff[i] = (uint8_t)r;
		i = (i + 1) % 100;
	}

	myUART_Tx(USARTx,rx_buff,strlen((char*)rx_buff));
}

void USART1_IRQHandler(void) {
    myUART_Rx(USART1, rx_buf, 0, '\n');
}

void USART2_IRQHandler(void) {
    myUART_Rx(USART2, rx_buf, 0, '\n');
}

void USART6_IRQHandler(void) {
    myUART_Rx(USART6, rx_buf, 0, '\n');
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	myUart_TypeDdef myUsart2;
	myUsart2.USARTx = USART2;
	myUsart2.COM_SPEED = 115200U;
	myUsart2.TX_PORT = GPIOA;
	myUsart2.TX_PIN = 2;
	myUsart2.RX_PORT = GPIOA;
	myUsart2.RX_PIN = 3;
	myUART_Init(&myUsart2);
	myUART_Tx(USART2,tx_buf,strlen((char*)tx_buf)); //Pošlje niz tx_buff
	myUART_Rx(USART2, rx_buf, 0, '\n'); //Sprejem znakov se zaključi z znakom ‘\n’
	//myUART_Rx(USART2, rx_buf, 5, ‘\n’); //Sprejem znakov se zaključi po 5 znakih
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
