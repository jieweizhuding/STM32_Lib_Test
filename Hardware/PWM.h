#ifndef _PWM_H
#define _PWM_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

//PA6 - TIM3_CH10
void PWM_init(void);
void PWM_SetCompare1(uint16_t Compare);

#endif