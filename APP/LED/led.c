#include "led.h"

/*******************************************************************************
*@FunctionName 		: delay()
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:20171031
*@Description 	  : 延时函数，delay(6000000)延时约1s
*@Input  :			i
*@Output :
*@Return :
********************************************************************************/
void delay(u32 i)	  
{
	while(i--);
}
/*******************************************************************************
*@FunctionName 	 : LED_Init
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:
*@Description 	  : LED初始化函数
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void LED_Init()	  //端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure; //声明一个结构体变量，用来初始化GPIO

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=LED;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	   /* 初始化GPIO */
}

