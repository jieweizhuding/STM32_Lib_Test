#ifndef _SERIAL_H
#define _SERIAL_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "misc.h"

//经过测试，发现USART2默认连接在STLINK上，所以无法使用PA2、PA3连接USART2
// Initialize USART3: TX->PB10, RX->PB11, BaudRate=115200
void Serial_init();
void Serial_SendByte(uint8_t byte);
void Serial_SendString(char* str);
void Serial_SendInt(int32_t num);


#endif