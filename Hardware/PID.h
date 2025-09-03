#ifndef _PID_H
#define _PID_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "misc.h"

typedef struct {
  float kp;
  float ki;
  float kd;

  float pre_error;
  float cur_error;
  float integral;

  float setpoint;
  float output;
  float actual;

  float integral_limit;
  float output_limit;
}PID;

//单环PID
void PID_Init(PID* pid, float kp, float ki, float kd, float integral_limit, float output_limit);
float PID_Compute(PID* pid, float actual);

//PID调参：使用USART修改三个参数，并观察数据波形

//双环PID


#endif