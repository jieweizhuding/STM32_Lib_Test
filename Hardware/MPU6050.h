#ifndef _MPU6050_H
#define _MPU6050_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "MPU_Reg.h"


typedef struct 
{
  float pitch;
  float roll;
  float yaw;

  int16_t AccX;
  int16_t AccY;
  int16_t AccZ;

  int16_t GyroX;
  int16_t GyroY;
  int16_t GyroZ;
}MPU6050;

typedef struct{
  float AccX_g;
  float AccY_g;
  float AccZ_g;

  float GyroX_dps;
  float GyroY_dps;
  float GyroZ_dps;

}MPU_Conv;

void MPU6050_init();
void MPU_writeReg(uint8_t Addr, uint8_t Data);
uint8_t MPU_readReg(uint8_t Addr);
void MPU_GetRaw(MPU6050 *mpu);
void MPU_GetConv(MPU6050 *mpu, MPU_Conv *conv);
void MPU_GetAng(MPU6050 *mpu);

#endif
