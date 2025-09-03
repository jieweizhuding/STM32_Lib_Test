#ifndef _SERIAL_H
#define _SERIAL_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "misc.h"


// Initialize USART2: TX->PA2, RX->PA3, BaudRate=115200
void Serial_init();
void Serial_SendByte(uint8_t byte);
void Serial_SendString(char* str);
void Serial_SendInt(int32_t num);


#endif