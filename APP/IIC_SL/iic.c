#include "iic.h"

/*******************************************************************************
*@FunctionName 	  : I2C_INIT()
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : 初始化GPIO.
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void I2C_INIT()
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

	GPIO_InitStructure.GPIO_Pin=I2C_SCL|I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);

	I2C_SCL_H;
	I2C_SDA_H;
}
/*******************************************************************************
*@FunctionName 	  : I2C_SDA_OUT()
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : SDA输出配置
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void I2C_SDA_OUT()
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}
/*******************************************************************************
*@FunctionName 	  : I2C_SDA_IN()
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : SDA输入配置
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

/*******************************************************************************
*@FunctionName 	  : I2C_Start
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : 产生起始信号
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void I2C_Start(void)
{
  I2C_SDA_OUT();
	
	I2C_SDA_H;
	I2C_SCL_H;
	delay_us(5);
	I2C_SDA_L;
	delay_us(6);
	I2C_SCL_L;
}
/*******************************************************************************
*@FunctionName 	  : I2C_Stop
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : 产生停止信号
*@Input  :			
*@Output :
*@Return :
********************************************************************************/

void I2C_Stop(void)
{
   I2C_SDA_OUT();

   I2C_SCL_L;
   I2C_SDA_L;
   I2C_SCL_H;
   delay_us(6);
   I2C_SDA_H;
   delay_us(6);
}
/*******************************************************************************
*@FunctionName 	  : I2C_Ack
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : 主机产生应答信号ACK
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void I2C_Ack(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_L;
   delay_us(4);
   I2C_SCL_H;
   delay_us(4);
   I2C_SCL_L;
}

/*******************************************************************************
*@FunctionName 	  : I2C_NAck
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : 主机不产生应答信号NACK
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void I2C_NAck(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_H;
   delay_us(4);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}
/*******************************************************************************
*@FunctionName 	  : I2C_Wait_Ack
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : 等待从机应答信号
*@Input  :			
*@Output :
*@Return :				1 接收应答失败
									0 接收应答成功
********************************************************************************/
u8 I2C_Wait_Ack(void)
{
	u8 tempTime=0;

	I2C_SDA_IN();

	I2C_SDA_H;
	delay_us(4);
	I2C_SCL_H;
	delay_us(4);

	while(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			I2C_Stop();
			return 1;
		}	 
	}

	I2C_SCL_L;
	return 0;
}
/*******************************************************************************
*@FunctionName 	  : I2C_Send_Byte
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : I2C 发送一个字节
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;

	I2C_SDA_OUT();
	I2C_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delay_us(4); //发送数据
		I2C_SCL_L;
		delay_us(4);
	}
}
/*******************************************************************************
*@FunctionName 	  : I2C_Read_Byte
*@Auther        	:	帅比
*@Vertion       	: V1.0
*@Date						:	20150730
*@Description 	  : I2C 读取一个字节
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
u8 I2C_Read_Byte(u8 ack)
{
   u8 i=0,receive=0;

   I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		I2C_SCL_L;
		delay_us(4);
		I2C_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
		   receive++;
		delay_us(4);	
   }

   	if(ack==0)
	   	I2C_NAck();
	else
		I2C_Ack();

	return receive;
}



