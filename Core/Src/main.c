#include "stm32f1xx.h"
void SystemClock_Config(void);

void SW_Init(void)
{
	GPIO_InitTypeDef SW;
	SW.Mode=GPIO_MODE_INPUT;
	SW.Pin=GPIO_PIN_0;
	SW.Pull=GPIO_PULLDOWN;
	SW.Speed=GPIO_SPEED_FREQ_MEDIUM;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA,&SW);
}
void GPIO_Init(void)
{
	GPIO_InitTypeDef zhanglele;
	zhanglele.Mode=GPIO_MODE_OUTPUT_PP;
	zhanglele.Pin=GPIO_PIN_8|GPIO_PIN_12;
	zhanglele.Pull=GPIO_NOPULL;
	zhanglele.Speed=GPIO_SPEED_FREQ_MEDIUM;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA,&zhanglele);
}

int main(void)
{
	uint8_t flag=1;
	HAL_Init();
	SystemClock_Config();
	GPIO_Init();
	SW_Init();
	
	// 初始状态设置PA12为低电平（熄灭）
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
	
   while(1)
	 {
//		 if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1)
//		{
//			// 等待按键松开
//			while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1);
//			// 切换PA12状态
//			HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_12);
//			// 短暂延时，避免抖动
//			for(int i=0;i<10000;i++);
//		}
		if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1)&&(flag==1))
		 {
			 HAL_Delay(10);
			 if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1)
			 {
				 HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_12);
				 flag=0;
			 }
			 
		
		 }
		 else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0)
		 {
			 flag=1;
		 }

	}

}
void Error_Handler(void)
{
  
  __disable_irq();
  while (1)
  {
  }
 
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
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
}
