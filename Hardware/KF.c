#include "KF.h"

void KF_init(KF *kf)
{
  kf->ax_offset = 0.0f;
  kf->ay_offset = 0.0f;
  kf->gx_offset = 0.0f;
  kf->gy_offset = 0.0f;
  kf->roll_v = 0.0f;
  kf->pitch_v = 0.0f;
  kf->dt = 0.0f;
  kf->gyro_roll = 0.0f;
  kf->gyro_pitch = 0.0f;
  kf->acc_roll = 0.0f;
  kf->acc_pitch = 0.0f;
  kf->k_roll = 0.0f;
  kf->k_pitch = 0.0f;
  kf->e_P[0][0] = 1.0f; kf->e_P[0][1] = 0.0f;
  kf->e_P[1][0] = 0.0f; kf->e_P[1][1] = 1.0f;
  kf->k_K[0][0] = 0.0f; kf->k_K[0][1] = 0.0f;
  kf->k_K[1][0] = 0.0f; kf->k_K[1][1] = 0.0f;

}

void KF_setup(KF *kf,MPU6050 *mpu, MPU_Conv *conv)
{
  for(int i=0; i<2000; i++)
  {
    MPU_GetConv(mpu, conv);
    kf->ax_offset += conv->AccX_g;
    kf->ay_offset += conv->AccY_g;
    kf->gx_offset += conv->GyroX_dps;
    kf->gy_offset += conv->GyroY_dps;
  }
  kf->ax_offset /= 2000.0f;
  kf->ay_offset /= 2000.0f;
  kf->gx_offset /= 2000.0f;
  kf->gy_offset /= 2000.0f;
}

void KF_update(KF *kf,MPU6050 *mpu, MPU_Conv *conv)
{
  MPU_GetConv(mpu, conv);

  kf->roll_v = (conv->GyroX_dps - kf->gx_offset) +((sin(kf->k_pitch)*sin(kf->k_roll))/cos(kf->k_pitch))*(conv->GyroY_dps - kf->gy_offset) + ((sin(kf->k_pitch))*(cos(kf->k_roll))/cos(kf->k_pitch))*(conv->GyroZ_dps);

  kf->pitch_v = (cos(kf->k_roll))*(conv->GyroY_dps - kf->gy_offset) - (sin(kf->k_roll))*(conv->GyroZ_dps);

  kf->gyro_roll = kf->k_roll+kf->roll_v * kf->dt;
  kf->gyro_pitch = kf->k_pitch+kf->pitch_v * kf->dt;


  kf->e_P[0][0] += 0.0025f;
  kf->e_P[0][1] += 0;
  kf->e_P[1][0] += 0;
  kf->e_P[1][1] += 0.0025f;


  kf->k_K[0][0] = kf->e_P[0][0] / (kf->e_P[0][0] + 0.3f);
  kf->k_K[0][1] = 0;
  kf->k_K[1][0] = 0;
  kf->k_K[1][1] = kf->e_P[1][1] / (kf->e_P[1][1] + 0.3f);

  kf->acc_roll = atan((conv->AccY_g - kf->ay_offset)/conv->AccZ_g) * 57.29578f;
  kf->acc_pitch = -1*atan((conv->AccX_g - kf->ax_offset)/sqrt((conv->AccY_g - kf->ay_offset)*(conv->AccY_g - kf->ay_offset) + conv->AccZ_g*conv->AccZ_g)) * 57.29578f;

  kf->k_roll = kf->gyro_roll + kf->k_K[0][0] * (kf->acc_roll - kf->gyro_roll);
  kf->k_pitch = kf->gyro_pitch + kf->k_K[1][1] * (kf->acc_pitch - kf->gyro_pitch);


  kf->e_P[0][0] = (1 - kf->k_K[0][0]) * kf->e_P[0][0];
  kf->e_P[0][1] = 0;
  kf->e_P[1][0] = 0;
  kf->e_P[1][1] = (1 - kf->k_K[1][1]) * kf->e_P[1][1];

}

void KF_setDt(KF *kf, float dt)
{
  kf->dt = dt;
}
