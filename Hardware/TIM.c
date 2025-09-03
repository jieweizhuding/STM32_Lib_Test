#include "TIM.h"

void TIM_init()
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

  TIM_InternalClockConfig(TIM2);

  TIM_TimeBaseInitTypeDef TIM_structure;
  TIM_structure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_structure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_structure.TIM_Period=7200-1;
  TIM_structure.TIM_Prescaler=10000-1;
  TIM_structure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(TIM2,&TIM_structure);

  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitTypeDef NVIC_structure;
  NVIC_structure.NVIC_IRQChannel=TIM2_IRQn;
  NVIC_structure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_structure.NVIC_IRQChannelPreemptionPriority=1;
  NVIC_structure.NVIC_IRQChannelSubPriority=1;
  NVIC_Init(&NVIC_structure);

  TIM_Cmd(TIM2,ENABLE);
}