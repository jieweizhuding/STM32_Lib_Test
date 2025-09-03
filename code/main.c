// OK
// //PA2,PA3
#include "SERIAL.h"

// //PA0,PA1,PA6
// #include "MOTOR.h"

// //PB8,PB9
// #include "OLED.h"

// //PA8,PA9
// #include "ENCODER.h"

//PB6,PB7
// #include "MPU6050.h"

// 无
// #include "TIM.h"
// #include "PID.h"
#include <string.h>


//全局变量定义
char Rec_Data[100];
uint8_t Rec_Flag = 0;

// PID motor_pid;
// int16_t encoder_count = 0;

// MPU6050 mpu;

int main()
{
    // TIM_init();
    // MPU6050_init();
    Serial_init();
    // MOTOR_Init();
    // OLED_Init();
    // ENCODER_Init();
    // PID_Init(&motor_pid, 1.0f, 1.2f, 0.0f, 300.0f, 400.0f);
    // motor_pid.setpoint = 0.0f;

    while (1)
    {
        if (Rec_Flag == 1)
        {
            Rec_Flag = 0;
            if (strcmp(Rec_Data, "ACC") == 0)
            {
                // motor_pid.setpoint += 5.0f;
                Serial_SendString("Target:1\r\n");
            }
            else if (strcmp(Rec_Data, "DEC") == 0)
            {
                // motor_pid.setpoint -= 5.0f;
                Serial_SendString("Target:2\r\n");
            }
            Serial_SendString("Target:\r\n");
            // Serial_SendInt((int32_t)motor_pid.setpoint);
            Serial_SendString("\r\n");
        }
        // MPU_GetRaw(&mpu);
        // OLED_ShowString(0, 0, "Count:", OLED_6X8);
        // OLED_ShowString(0, 16, "AX:", OLED_6X8);
        // OLED_ShowSignedNum(48, 0, mpu.AccX, 6, OLED_6X8);
        // OLED_Update();

        // if (Rec_Flag == 1)
        // {
        //     Rec_Flag = 0;
        //     if (strcmp(Rec_Data, "MPU_RAW") == 0)
        //     {
        //         Serial_SendString("MPU6050 Raw Data:\r\n");
        //         // MPU_GetRaw(&mpu);
        //         // Serial_SendString("AX:");
        //         // Serial_SendInt(mpu.AccX);
        //         // Serial_SendString("\r\n");
        //         // Serial_SendString(" AY:");
        //         // Serial_SendInt(mpu.AccY);
        //         // Serial_SendString("\r\n");
        //         // Serial_SendString(" AZ:");
        //         // Serial_SendInt(mpu.AccZ);
        //         // Serial_SendString("\r\n");
        //         // Serial_SendString(" GX:");
        //         // Serial_SendInt(mpu.GyroX);
        //         // Serial_SendString("\r\n");
        //         // Serial_SendString(" GY:");
        //         // Serial_SendInt(mpu.GyroY);
        //         // Serial_SendString("\r\n");
        //         // Serial_SendString(" GZ:");
        //         // Serial_SendInt(mpu.GyroZ);
        //         // Serial_SendString("\r\n----------------\r\n");
        //     }
        // }
    }
}

// void TIM2_IRQHandler()
// {
//     if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//     {

//         encoder_count = ENCODER_GetCount();
//         PID_Compute(&motor_pid, encoder_count);
//         MOTOR_SetSpeed((int16_t)(motor_pid.output));

//         TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//     }
// }

void USART2_IRQHandler()
{
    static uint8_t RX_State = 0;
    static uint8_t RX_Num = 0;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
    {
        char RX_DATA = USART_ReceiveData(USART2);
        if (RX_State == 0)
        {
            if (RX_DATA == '@')
            {
                RX_State = 1;
                RX_Num = 0;
            }
        }
        else if (RX_State == 1)
        {
            if (RX_DATA == '\r')
            {
                RX_State = 2;
            }
            else
            {
                Rec_Data[RX_Num] = RX_DATA;
                RX_Num++;
            }
        }
        else if (RX_State == 2)
        {
            if (RX_DATA == '\n')
            {
                RX_State = 0;
                Rec_Data[RX_Num] = '\0';
                Rec_Flag = 1;
            }
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}