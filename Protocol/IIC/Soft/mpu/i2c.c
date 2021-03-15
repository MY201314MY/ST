#include "i2c.h"
#include <stdio.h>

GPIO_InitTypeDef GPIO_InitStruct = {0};


void SDA_IN(){
	GPIO_InitStruct.Pin = GPIO_PIN_7;	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;	
	GPIO_InitStruct.Pull = GPIO_PULLUP;	
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

void SDA_OUT() {
	GPIO_InitStruct.Pin = GPIO_PIN_7;	
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	
	GPIO_InitStruct.Pull = GPIO_PULLUP;	
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	
}
 

void IIC_Start(void)
{
	SDA_OUT();  
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	HAL_Delay(1);
 	IIC_SDA(0);
	HAL_Delay(1);
	IIC_SCL(0);
}

void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL(0);
	IIC_SDA(0);
 	HAL_Delay(1);
	IIC_SCL(1); 
	HAL_Delay(1);
	IIC_SDA(1);
	HAL_Delay(1);							   	
}
		  
uint8_t IIC_Send_Byte(uint8_t txd)
{                                      
    uint8_t t, ack;   
	SDA_OUT(); 	    
    
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)
			IIC_SDA(1);
		else
			IIC_SDA(0);

		txd<<=1; 	  
		HAL_Delay(1);  
		IIC_SCL(1);
		HAL_Delay(1); 
		IIC_SCL(0);	
		HAL_Delay(1);
    }
	SDA_IN();
	
	HAL_Delay(1);
	IIC_SCL(1);
	ack = READ_SDA;
	HAL_Delay(1);
	IIC_SCL(0);
	
	return ack;
	
} 	    

  
uint8_t IIC_Read_Byte_NAK(unsigned char ack)
{
	unsigned char mask, dat;

	SDA_IN();
	for(mask=0x80;mask!=0;mask>>=1)
	{
		HAL_Delay(1);
		IIC_SCL(1);
		if(READ_SDA==0)
			dat&=~mask;
		else
			dat|=mask;
		HAL_Delay(1);
		IIC_SCL(0);
	}
	
	SDA_OUT();
	IIC_SDA(1);
    HAL_Delay(1);
	IIC_SCL(1);
	HAL_Delay(1);
	IIC_SCL(0);
	
    return dat;
}

uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char mask, dat=0;

	SDA_IN();
	for(mask=0x80;mask!=0;mask>>=1)
	{
		HAL_Delay(1);
		IIC_SCL(1);
		if(READ_SDA==0)
			dat&=~mask;
		else
			dat|=mask;
		HAL_Delay(1);
		IIC_SCL(0);
	}
	SDA_OUT();
	IIC_SDA(0);
    HAL_Delay(1);
	IIC_SCL(1);
	HAL_Delay(1);
	IIC_SCL(0);
	
    return dat;
}

