#include "mpu.h"
#include <stdio.h>
uint8_t BUF[8];

void Single_Write_MMA8452(uint8_t REG_Address,uint8_t REG_data)
{
	IIC_Start();
	IIC_Send_Byte(0x38);
	IIC_Send_Byte(REG_Address);
	IIC_Send_Byte(REG_data);
	IIC_Stop(); 
}

unsigned char ReadByte(unsigned char addr)
{
	unsigned char dat;
	

	IIC_Start();
	IIC_Send_Byte(0x38);
	IIC_Send_Byte(addr);
	IIC_Start();
	IIC_Send_Byte(0x39);
	dat=IIC_Read_Byte(1);
	IIC_Stop(); 
	
	if(dat == 0x2A){
		puts("checked MMA8452 MPU");
	}else{
		puts("NO MPU Found!");
	}
	
	return dat;
}
void Init_MMA8452()
{
    Single_Write_MMA8452(0x2A,0x01);   
    Single_Write_MMA8452(0x2B,0x02); 
	
	ReadByte(0x0D);
}

void Multiple_Read_MMA8452(void)
{
	uint8_t i;
	IIC_Start();
	IIC_Send_Byte(0x38);
	IIC_Send_Byte(0x01);
	
	IIC_Start();
	IIC_Send_Byte(0x39);
	
	for(i=0;i<6;i++)
	{
		BUF[i]=IIC_Read_Byte(1);
	}
	IIC_Stop(); 
}
short acc_x, acc_y, acc_z;

void parse(){
	short temp;
	
	Multiple_Read_MMA8452();
	
	
	temp = BUF[0];
	temp<<=4;
	temp |= BUF[1]; 
	if(BUF[0]&0x80){
		temp |= 0xF000;
	}
	acc_x = temp;
	
	temp = BUF[2];
	temp<<=4;
	temp |= BUF[3]; 
	if(BUF[2]&0x80){
		temp |= 0xF000;
	}
	acc_y = temp;
	
	temp = BUF[4];
	temp<<=4;
	temp |= BUF[5]; 
	if(BUF[4]&0x80){
		temp |= 0xF000;
	}
	acc_z = temp;
	
	printf("x:%d y:%d z:0x%d\r\n", acc_x, acc_y, acc_z);
}
