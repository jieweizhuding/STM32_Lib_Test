#include "ENCODER.h"

void ENCODER_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  // GPIO 配置 PA8, PA9 作为编码器输入
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // 定时器时基配置
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  // 输入捕获配置
    TIM_ICInitTypeDef TIM_ICstructure;
    TIM_ICStructInit(&TIM_ICstructure);
    TIM_ICstructure.TIM_Channel=TIM_Channel_1;
    TIM_ICstructure.TIM_ICFilter=0xF;
    TIM_ICInit(TIM1,&TIM_ICstructure);
    TIM_ICstructure.TIM_Channel=TIM_Channel_2;
    TIM_ICstructure.TIM_ICFilter=0xF;
    TIM_ICInit(TIM1,&TIM_ICstructure);

  // 编码器接口配置
  TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Falling, TIM_ICPolarity_Rising);

  TIM_SetCounter(TIM1, 0);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  TIM_Cmd(TIM1, ENABLE);

}


int16_t ENCODER_GetCount(void)
{
  int16_t count = (int16_t)TIM_GetCounter(TIM1);
  TIM_SetCounter(TIM1, 0);
  return count;
}