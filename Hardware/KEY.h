#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"

//有时间可以改为定时器实现，用外部中断实现弊端过大
void Key_init();

#endif