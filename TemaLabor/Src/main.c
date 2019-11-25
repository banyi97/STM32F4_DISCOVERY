/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stm32f4xx.h>

#include "display.h"
#include "vcp.h"
#include "Common.h"
#include "drawing.h"
#include "touch.h"
#include "gyroscope.h"

#include "UartFifo.h"
#include "MessageHandler.h"
#include "CommHandler.h"

#include "WindowManager.h"
#include "MenuWindow.h"

#include <stdio.h>
#include <math.h>

static void SystemClock_Config(void);
char buff[20];
uint32_t frameTime;

int main(void)
{
	gyro_t gyroVal;

	SystemClock_Config();
	HAL_Init();
	DRV_InitLed(LED3);
	DRV_InitLed(LED4);
	DRV_InitDrawTimer();
	DRV_Display_Init();
	DRV_Display_Clear();

	UartFifoInit();

	InitWindowManager();

	DRV_VCP_Init();
	DRV_TS_Init();
	DRV_Gyro_Init();
	DRV_Gyro_Reset();
	DRV_Gyro_Calibration();

	DRV_VCP_WriteString("TemaLabor Hello.\r\n");

	SetActiveWindow(GetMenuWindow());

	uint8_t fifobyte;
	pMessage_t pMessage;
	uint8_t generateSignal=1;

	while(1)
	{

		if(DRV_TS_IsTouchDetected())
			HandleTouch(DRV_TS_GetX(), DRV_TS_GetY());

		//gyroVal = DRV_Gyro_GetXYZ();

		while(UartFifoPop(&fifobyte)){
			pMessage=CommByteReceived(fifobyte);
			if (pMessage!=NULL){
				HandleMessage(pMessage);
				InitMessage(pMessage);
				generateSignal=0;
			}
		}

		if (generateSignal){
			float dftTestSignal = 1000 * sin(2 * M_PI * 1 * HAL_GetTick()/1000.0f) + 1000 * sin(2 * M_PI * 8 * HAL_GetTick()/1000.0f);
			DataPacket d;
			d.Data = dftTestSignal; //gyroVal.omega_z;
			HandleSpectrum(dftTestSignal);
			gyroVal=DRV_Gyro_GetXYZ();
			HandleChart(gyroVal.omega_z);
			HandleCompass(gyroVal.omega_z);
			HandleHistogram(gyroVal.omega_z);
			HandleGame(gyroVal);
		}

		//DataPacket d;
		//d.Data = dftTestSignal; //gyroVal.omega_z;
		//HandleNewData(&d);
		HAL_Delay(10);

	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (HandleDraw())
		DRV_Display_SwitchBuffer();
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the Over-Drive mode */
  HAL_PWREx_EnableOverDrive();

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	DRV_ErrorLoop();

}
#endif
