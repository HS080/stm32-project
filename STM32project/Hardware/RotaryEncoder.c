#include "stm32f10x.h"                  // Device header

uint16_t RotaryEncoder_Count;            //全局变量，用于计数
uint8_t last_a_state;             //上次A相状态
uint8_t encoder_button_state;     //编码器按钮状态
uint8_t last_button_state;        //上次按钮状态

/**
  * 函    数：旋转编码器初始化
  * 参    数：无
  * 返 回 值：无
  */
void RotaryEncoder_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*AFIO选择中断引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	/*EXTI初始化*/
	EXTI_InitTypeDef EXTI_InitStructure;
	
	// 初始化A相中断（PB12）
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	// 初始化按钮中断（PB14）
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// 配置A相中断
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	/*初始化变量*/
	RotaryEncoder_Count = 500; // 初始速度为50%
	last_a_state = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
	last_button_state = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
	encoder_button_state = 0;
}

/**
  * 函    数：获取旋转编码器的计数值
  * 参    数：无
  * 返 回 值：计数值，范围：0~1000
  */
uint16_t RotaryEncoder_Get(void)
{
	return RotaryEncoder_Count;
}

/**
  * 函    数：获取旋转编码器按钮状态
  * 参    数：无
  * 返 回 值：按钮状态，1表示按下，0表示未按下
  */
uint8_t RotaryEncoder_GetButton(void)
{
	uint8_t button_state = encoder_button_state;
	encoder_button_state = 0; // 复位按钮状态
	return button_state;
}




