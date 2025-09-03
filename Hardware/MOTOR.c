#include "MOTOR.h"

void MOTOR_Init(void)
{
  PWM_init();
  // Initialize GPIO pins for motor direction control
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  MOTOR_Stop(); // Ensure motor is stopped at initialization
  
}

void MOTOR_SetSpeed(int16_t speed)
{
  if (speed > 0)
  {
    GPIO_SetBits(GPIOA, GPIO_Pin_0); // Example: Set direction pin high
    GPIO_ResetBits(GPIOA, GPIO_Pin_1); // Ensure backward pin is low
    PWM_SetCompare1((uint16_t)speed);
  }
  else if (speed < 0)                                        
  {
    // Set direction to backward
    GPIO_SetBits(GPIOA, GPIO_Pin_1); // Example: Set direction pin high
    GPIO_ResetBits(GPIOA, GPIO_Pin_0); // Ensure forward pin is low
    PWM_SetCompare1((uint16_t)(-speed));
  }
}

void MOTOR_Stop(void)
{
  PWM_SetCompare1(0);
}
