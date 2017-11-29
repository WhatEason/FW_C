/*******************************************************************************
*                 									帅比
*                 		       
--------------------------------------------------------------------------------
* 实 验 名		 		: 	基于UCOS-II的固定翼飞控
* 实验说明				: 
* 连接方式 			: 
* 注    意		 	: 	
*******************************************************************************/
#include "public.h"	  //公共函数头文件

/*******************************************************************************
*@FunctionName 	: 启动时任务任务配置
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:	20171031
*@Description 	  : 
********************************************************************************/
//设置任务优先级
#define START_TASK_PRIO 10//应该将开始任务优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE 64
//任务堆栈
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *padta);

/*******************************************************************************
*@FunctionName 	: LED任务配置
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:	20171031
*@Description 	  :启动时启动查看程序是否在运行
********************************************************************************/
//设置任务优先级
#define LED_TASK_PRIO 7
//设置任务堆栈大小
#define LED_STK_SIZE 64
//任务堆栈
OS_STK LED_TASK_STK[LED_STK_SIZE];
//任务函数
void led_task(void *padta);

/*******************************************************************************
*@FunctionName 	: printf输出任务配置
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:	20171110
*@Description 	  :测试printf使用
********************************************************************************/
//设置任务优先级
#define PRINTF_TASK_PRIO 9
//设置任务堆栈大小
#define PRINTF_STK_SIZE 64
//任务堆栈
OS_STK PRINTF_TASK_STK[PRINTF_STK_SIZE];
//任务函数
void printf_task(void *padta);

/*******************************************************************************
*@FunctionName 	: OSTick_Init
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:20171029
*@Description 	  : 操作系统滴答时钟初始化
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
void OSTick_Init(void)
{
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC);
}

/*******************************************************************************
*@FunctionName 		: main()
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:2071029
*@Description 	  : 主函数
*@Input  :			
*@Output :
*@Return :
********************************************************************************/
int main()
{
	OSInit();
	OSTaskCreate(start_task,(void *) 0,(OS_STK *)&START_TASK_STK[START_STK_SIZE - 1],START_TASK_PRIO);
	OSStart();
}

/*******************************************************************************
*@FunctionName 		: start_task(void *pdata)
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:20171031
*@Description 	  : 初始任务
*@Input  :				*pdata
*@Output :
*@Return :
********************************************************************************/
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr = 0;
	pdata = pdata;//防止报错
	
	OSTick_Init();//systick时钟初始化
	
	OS_ENTER_CRITICAL();//进入临界区
	OSTaskCreate(led_task,(void *) 0,(OS_STK *)&LED_TASK_STK[LED_STK_SIZE - 1],LED_TASK_PRIO);
	OSTaskCreate(printf_task,(void *) 0,(OS_STK *)&PRINTF_TASK_STK[PRINTF_STK_SIZE - 1],PRINTF_TASK_PRIO);
	OSTaskSuspend(START_TASK_PRIO);//挂起起始任务
	OS_EXIT_CRITICAL();//退出临界区（可以被中断打断）
}

/*******************************************************************************
*@FunctionName 	: led_task(void *padta)
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:	20171031
*@Description 	  : 启动时启动查看程序是否在运行
*@Input  :			*padta
*@Output :
*@Return :
********************************************************************************/
void led_task(void *padta)
{
	LED_Init();	
	while(1){
		GPIO_SetBits(GPIOA,LED);
		OSTimeDlyHMSM(0, 0,1,0);
		GPIO_ResetBits(GPIOA,LED);
		OSTimeDlyHMSM(0, 0,1,0);
	}
}

/*******************************************************************************
*@FunctionName 	: printf_task(void *padta)
*@Auther        	: 帅比
*@Vertion       	: v1.0
*@Date						:	20171110
*@Description 	  : 勾选USE MicroLIB（printf为安全线程）
*@Input  :			*padta
*@Output :
*@Return :
********************************************************************************/
void printf_task(void *padta)
{
	printf_init();	
	while(1){
		printf("%d OJBK\n",1000);
		OSTimeDlyHMSM(0, 0,1,0);		
	}
}











