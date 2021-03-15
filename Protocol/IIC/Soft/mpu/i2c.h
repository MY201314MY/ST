#ifndef _I2C_H_
#define _I2C_H_

#include "gpio.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_ll_system.h"

#define IIC_SCL(x) x==1?HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)
#define IIC_SDA(x)  x==1?HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)
#define READ_SDA  HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)


void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte_NAK(unsigned char ack);
uint8_t IIC_Read_Byte(unsigned char ack);

#endif
