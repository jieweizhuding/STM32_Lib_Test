#ifndef _TIM_H
#define _TIM_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"

//100Hz->10ms 定时器中断
void TIM_init();

#endif