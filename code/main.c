//PB8连接SCL,PB9连接SDA
#include "OLED.h"
//PB6连接SCL,PB7连接SDA
#include "MPU6050.h"

#include "TIM.h"


#include "KF.h"

MPU6050 mpu;
MPU_Conv conv;
KF kf;

int main()
{
    MPU6050_init();
    OLED_Init();
    KF_init(&kf);
    KF_setup(&kf,&mpu, &conv);


    while (1)
    {
        MPU_GetConv(&mpu, &conv);
        OLED_ShowString(0, 0, "AX:", OLED_6X8);
        OLED_ShowSignedNum(30, 0, conv.AccX_g, 6, OLED_6X8);
        OLED_ShowString(0, 10, "AY:", OLED_6X8);
        OLED_ShowSignedNum(30, 10, conv.AccY_g, 6, OLED_6X8);
        OLED_ShowString(0, 20, "AZ:", OLED_6X8);
        OLED_ShowSignedNum(30, 20, conv.AccZ_g, 6, OLED_6X8);
        OLED_ShowString(0, 30, "GX:", OLED_6X8);
        OLED_ShowSignedNum(30, 30, conv.GyroX_dps, 6, OLED_6X8);
        OLED_ShowString(0, 40, "GY:", OLED_6X8);
        OLED_ShowSignedNum(30, 40, conv.GyroY_dps, 6, OLED_6X8);
        OLED_ShowString(0, 50, "GZ:", OLED_6X8);
        OLED_ShowSignedNum(30, 50, conv.GyroZ_dps, 6, OLED_6X8);
        OLED_Update();
    }
}
