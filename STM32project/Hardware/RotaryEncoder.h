#ifndef __ROTARY_ENCODER_H
#define __ROTARY_ENCODER_H

#include "stm32f10x.h"

extern uint16_t RotaryEncoder_Count;            //全局变量，用于计数
extern uint8_t last_a_state;             //上次A相状态
extern uint8_t encoder_button_state;     //编码器按钮状态

void RotaryEncoder_Init(void);
uint16_t RotaryEncoder_Get(void);
uint8_t RotaryEncoder_GetButton(void);

#endif
