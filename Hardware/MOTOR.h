#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "PWM.h"

//PA1控制前进，PA2控制后退
void MOTOR_Init(void);
void MOTOR_SetSpeed(int16_t speed);
void MOTOR_Stop(void);

#endif