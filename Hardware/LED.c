#include "LED.h"

void LED_init(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

  GPIO_InitTypeDef GPIO_structure;
  GPIO_structure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_structure.GPIO_Pin=GPIO_Pin_0;
  GPIO_structure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_structure);
}

void LED_Turn()
{
  if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)==1){
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);
  }else{
    GPIO_SetBits(GPIOA,GPIO_Pin_0);
  }
}
