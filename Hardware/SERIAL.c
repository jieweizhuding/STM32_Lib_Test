#include "SERIAL.h"

void Serial_init()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  GPIO_InitTypeDef GPIO_structure;
  GPIO_structure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_structure.GPIO_Pin = GPIO_Pin_2;
  GPIO_structure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_structure);
  GPIO_structure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_structure.GPIO_Pin = GPIO_Pin_3;
  GPIO_structure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_structure);

  USART_InitTypeDef USART_structure;
  USART_structure.USART_BaudRate = 115200;
  USART_structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_structure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_structure.USART_Parity = USART_Parity_No;
  USART_structure.USART_StopBits = USART_StopBits_1;
  USART_structure.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART2, &USART_structure);

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  NVIC_InitTypeDef NVIC_structure;
  NVIC_structure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_structure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_structure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_structure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_structure);
  USART_Cmd(USART2, ENABLE);
}


void Serial_SendByte(uint8_t Byte){
    USART_SendData(USART2,Byte);
    while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}

void Serial_SendInt(int32_t num){
  char buffer[12];
  int i=0;
  if(num<0){
    Serial_SendByte('-');
    num=-num;
  }
  if(num==0){
    Serial_SendByte('0');
    return;
  } 
  while(num>0){
    buffer[i++]=(num%10)+'0';
    num/=10;
  }
  for(int j=i-1;j>=0;j--){
    Serial_SendByte(buffer[j]);
  }
}

void Serial_SendString(char* s){
  while(*s!=0){
    Serial_SendByte(*s);
    s++;
  }
}