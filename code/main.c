//PB8连接SCL,PB9连接SDA
#include "OLED.h"
//PB6连接SCL,PB7连接SDA
#include "MPU6050.h"

MPU6050 mpu;

int main()
{
    MPU6050_init();
    OLED_Init();

    while (1)
    {
        MPU_GetRaw(&mpu);
        OLED_ShowString(0, 0, "AX:", OLED_6X8);
        OLED_ShowSignedNum(30, 0, mpu.AccX, 6, OLED_6X8);
        OLED_ShowString(0, 10, "AY:", OLED_6X8);
        OLED_ShowSignedNum(30, 10, mpu.AccY, 6, OLED_6X8);
        OLED_ShowString(0, 20, "AZ:", OLED_6X8);
        OLED_ShowSignedNum(30, 20, mpu.AccZ, 6, OLED_6X8);
        OLED_ShowString(0, 30, "GX:", OLED_6X8);
        OLED_ShowSignedNum(30, 30, mpu.GyroX, 6, OLED_6X8);
        OLED_ShowString(0, 40, "GY:", OLED_6X8);
        OLED_ShowSignedNum(30, 40, mpu.GyroY, 6, OLED_6X8);
        OLED_ShowString(0, 50, "GZ:", OLED_6X8);
        OLED_ShowSignedNum(30, 50, mpu.GyroZ, 6, OLED_6X8);
        OLED_Update();
    }
}
