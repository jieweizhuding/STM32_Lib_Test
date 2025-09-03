#ifndef _KF_H
#define _KF_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "MPU6050.h"
#include <math.h>

typedef struct{
  float ax_offset;
  float ay_offset;

  float gx_offset;
  float gy_offset;

  float roll_v;
  float pitch_v;

  float dt;

  float gyro_roll;
  float gyro_pitch;

  float acc_roll;
  float acc_pitch;

  float k_roll;
  float k_pitch;

  float e_P[2][2];

  float k_K[2][2];
}KF;


void KF_init(KF *kf);
void KF_setup(KF *kf,MPU6050 *mpu, MPU_Conv *conv);
void KF_update(KF *kf,MPU6050 *mpu, MPU_Conv *conv);
void KF_setDt(KF *kf,float dt);

#endif
