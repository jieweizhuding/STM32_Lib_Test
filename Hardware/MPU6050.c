#include "MPU6050.h"

// MPU6050 器件 I2C 地址（写操作时最低位为0）
// 实际地址为 0x68 << 1 = 0xD0
#define MPU_ADDR 0xD0


// 向 MPU6050 某寄存器写入 1 字节数据
void MPU_writeReg(uint8_t Addr, uint8_t Data)
{
  I2C_GenerateSTART(I2C1, ENABLE); // 产生起始信号
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS); // 等待进入主模式

  I2C_Send7bitAddress(I2C1, MPU_ADDR, I2C_Direction_Transmitter); // 发送器件地址+写位
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

  I2C_SendData(I2C1, Addr); // 发送寄存器地址
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);

  I2C_SendData(I2C1, Data); // 发送数据
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);

  I2C_GenerateSTOP(I2C1, ENABLE); // 产生停止信号
}

// 从 MPU6050 某寄存器读取 1 字节数据
uint8_t MPU_readReg(uint8_t Addr)
{
  uint8_t Data;

  I2C_GenerateSTART(I2C1, ENABLE); // 产生起始信号
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

  I2C_Send7bitAddress(I2C1, MPU_ADDR, I2C_Direction_Transmitter); // 发送器件地址+写位
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

  I2C_SendData(I2C1, Addr); // 发送寄存器地址
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);

  // 重新启动 I2C（Repeated START）进行读操作
  I2C_GenerateSTART(I2C1, ENABLE);
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

  I2C_Send7bitAddress(I2C1, MPU_ADDR, I2C_Direction_Receiver); // 发送器件地址+读位
  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);

  I2C_AcknowledgeConfig(I2C1, DISABLE); // 关闭应答，准备接收最后一个字节
  I2C_GenerateSTOP(I2C1, ENABLE);       // 产生停止信号

  while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
  Data = I2C_ReceiveData(I2C1); // 读取数据

  I2C_AcknowledgeConfig(I2C1, ENABLE); // 恢复 ACK

  return Data;
}

// MPU6050 初始化，使用 I2C1 (PB6=SCL, PB7=SDA)
void MPU6050_init()
{
  // 1. 开启 I2C1 和 GPIOB 时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  // 2. 配置 PB6, PB7 为开漏复用 (I2C SCL, SDA)
  GPIO_InitTypeDef GPIO_structure;
  GPIO_structure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_structure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_structure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_structure);

  // 3. 配置 I2C1
  I2C_InitTypeDef I2C_structure;
  I2C_structure.I2C_Ack = I2C_Ack_Enable;                     // 允许应答
  I2C_structure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // 7位地址
  I2C_structure.I2C_ClockSpeed = 50000;                       // SCL 时钟频率 50kHz
  I2C_structure.I2C_DutyCycle = I2C_DutyCycle_2;              // 占空比
  I2C_structure.I2C_Mode = I2C_Mode_I2C;                      // I2C 模式
  I2C_structure.I2C_OwnAddress1 = 0x00;                       // 主机，不需要自身地址
  I2C_Init(I2C1, &I2C_structure);

  I2C_Cmd(I2C1, ENABLE); // 使能 I2C1

  // // 4. MPU6050 芯片配置
  MPU_writeReg(MPU6050_PWR_MGMT_1, 0x01);  // 选择时钟源
  MPU_writeReg(MPU6050_PWR_MGMT_2, 0x00); // 开启所有传感器

  MPU_writeReg(MPU6050_SMPLRT_DIV, 0x09);     // 采样率：1kHz/(1+9)=100Hz
  MPU_writeReg(MPU6050_CONFIG, 0x03);         // 配置低通滤波器
  MPU_writeReg(MPU6050_GYRO_CONFIG, 0x00);    // 陀螺仪量程 ±250°/s
  MPU_writeReg(MPU6050_ACCEL_CONFIG, 0x00);   // 加速度计量程 ±2g
}

// 读取 MPU6050 的加速度计与陀螺仪数据
void MPU_GetRaw(MPU6050 *mpu)
{
  uint8_t Data_H, Data_L;

  // --- 加速度计 ---
  Data_H = MPU_readReg(MPU6050_ACCEL_XOUT_H);
  Data_L = MPU_readReg(MPU6050_ACCEL_XOUT_L);
  mpu->AccX = (Data_H << 8) | Data_L;

  Data_H = MPU_readReg(MPU6050_ACCEL_YOUT_H);
  Data_L = MPU_readReg(MPU6050_ACCEL_YOUT_L);
  mpu->AccY = (Data_H << 8) | Data_L;

  Data_H = MPU_readReg(MPU6050_ACCEL_ZOUT_H);
  Data_L = MPU_readReg(MPU6050_ACCEL_ZOUT_L);
  mpu->AccZ = (Data_H << 8) | Data_L;

  // --- 陀螺仪 ---
  Data_H = MPU_readReg(MPU6050_GYRO_XOUT_H);
  Data_L = MPU_readReg(MPU6050_GYRO_XOUT_L);
  mpu->GyroX = (Data_H << 8) | Data_L;

  Data_H = MPU_readReg(MPU6050_GYRO_YOUT_H);
  Data_L = MPU_readReg(MPU6050_GYRO_YOUT_L);
  mpu->GyroY = (Data_H << 8) | Data_L;

  Data_H = MPU_readReg(MPU6050_GYRO_ZOUT_H);
  Data_L = MPU_readReg(MPU6050_GYRO_ZOUT_L);
  mpu->GyroZ = (Data_H << 8) | Data_L;
}

void MPU_GetConv(MPU6050 *mpu, MPU_Conv *conv)
{
  MPU_GetRaw(mpu);
  conv->AccX_g = mpu->AccX / 16384.0f;   // 转换为 g 单位
  conv->AccY_g = mpu->AccY / 16384.0f;
  conv->AccZ_g = mpu->AccZ / 16384.0f;

  conv->GyroX_dps = mpu->GyroX / 131.0f; // 转换为 °/s 单位
  conv->GyroY_dps = mpu->GyroY / 131.0f;
  conv->GyroZ_dps = mpu->GyroZ / 131.0f;
}

float MPU_GetOffset_z(){

  MPU6050 mpu;
  MPU_Conv conv;
  float offset = 0;
  for(int i=0;i<100;i++){
    MPU_GetConv(&mpu, &conv);
    offset += conv.GyroZ_dps;
    for(int j=0;j<10000;j++);
  }
  offset /= 100.0f;
  return offset;
}
