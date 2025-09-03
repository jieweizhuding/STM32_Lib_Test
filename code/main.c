//PB8连接SCL,PB9连接SDA
#include "OLED.h"
//PB6连接SCL,PB7连接SDA
#include "MPU6050.h"


// #include "SERIAL.h"

#include "TIM.h"
#include "KF.h"

MPU6050 mpu;
MPU_Conv conv;
KF kf;

int i=0;

// char Rec_Data[100];
// uint8_t Rec_Flag = 0;

int main()
{
    MPU6050_init();
    TIM_init();
    OLED_Init();

    KF_setDt(&kf,1.0f);
    KF_init(&kf);
    KF_setup(&kf,&mpu, &conv);
    // Serial_init();


    while (1)
    {

        MPU_GetConv(&mpu, &conv);
        OLED_ShowString(0, 0, "AX:", OLED_6X8);
        OLED_ShowFloatNum(30, 0, conv.AccX_g,3,3, OLED_6X8);
        OLED_ShowString(0, 10, "AY:", OLED_6X8);
        OLED_ShowFloatNum(30, 10, conv.AccY_g,3,3, OLED_6X8);
        OLED_ShowString(0, 20, "AZ:", OLED_6X8);
        OLED_ShowFloatNum(30, 20, conv.AccZ_g, 3,3, OLED_6X8);
        OLED_ShowString(0, 30, "GX:", OLED_6X8);
        OLED_ShowFloatNum(30, 30, conv.GyroX_dps, 3,3, OLED_6X8);
        OLED_ShowString(0, 40, "GY:", OLED_6X8);
        OLED_ShowFloatNum(30, 40, conv.GyroY_dps, 3,3, OLED_6X8);
        OLED_ShowString(0, 50, "GZ:", OLED_6X8);
        OLED_ShowFloatNum(30, 50, conv.GyroZ_dps, 3,3, OLED_6X8);
        OLED_ShowNum(0, 60, i, 5, OLED_6X8);
        OLED_Update();


        // OLED_ShowString(0, 0, "ROLL:", OLED_6X8);
        // OLED_ShowFloatNum(50, 0, kf.k_roll, 3,3, OLED_6X8);
        // OLED_ShowString(0, 10, "PITCH:", OLED_6X8);
        // OLED_ShowFloatNum(50, 10, kf.k_pitch, 3,3, OLED_6X8);
        // OLED_ShowString(0, 20, "YAW:", OLED_6X8);
        // OLED_ShowFloatNum(50, 20, kf.k_yaw, 3,3, OLED_6X8);
        // OLED_Update();

        // Serial_SendInt((int16_t)(conv.GyroX_dps*100));
        // Serial_SendByte(',');
        // Serial_SendInt((int16_t)(conv.GyroY_dps*100));
        // Serial_SendByte(',');
        // Serial_SendInt((int16_t)(conv.GyroZ_dps*100));
        // Serial_SendByte('\n');

        // Serial_SendInt((int16_t)(conv.AccX_g*1000));
        // Serial_SendByte(',');
        // Serial_SendInt((int16_t)(conv.AccY_g*1000));
        // Serial_SendByte(',');
        // Serial_SendInt((int16_t)(conv.AccZ_g*1000));
        // Serial_SendByte('\n');
        // KF_update(&kf);
    }
}



void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        KF_update(&kf,&mpu, &conv);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

// void USART3_IRQHandler()
// {
//     static uint8_t RX_State = 0;
//     static uint8_t RX_Num = 0;
//     if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
//     {
//         char RX_DATA = USART_ReceiveData(USART3);
//         if (RX_State == 0)
//         {
//             if (RX_DATA == '@')
//             {
//                 RX_State = 1;
//                 RX_Num = 0;
//             }
//         }
//         else if (RX_State == 1)
//         {
//             if (RX_DATA == '\r')
//             {
//                 RX_State = 2;
//             }
//             else
//             {
//                 Rec_Data[RX_Num] = RX_DATA;
//                 RX_Num++;
//             }
//         }
//         else if (RX_State == 2)
//         {
//             if (RX_DATA == '\n')
//             {
//                 RX_State = 0;
//                 Rec_Data[RX_Num] = '\0';
//                 Rec_Flag = 1;
//             }
//         }
//         USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//     }
// }