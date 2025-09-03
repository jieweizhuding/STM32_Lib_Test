#ifndef _ENCODER_H
#define _ENCODER_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

//PA8 -> TIM1_CH1, PA9 -> TIM1_CH2
void ENCODER_Init(void);
int16_t ENCODER_GetCount(void);


#endif