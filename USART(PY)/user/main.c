/******************** 版权所有 北京工业大学焊接研究所 潘健 ********************
* 文件名             : main.c
* 作者               : 潘健
* 版本               : V1.2
* 日期               : 1/12/2010
* 描述               : Main program body
* 功能               ：用于演示USART与拼音输入法					   				   	
*******************************************************************************/
#include "stm32f10x.h"
#include "OSQMem.h"	

extern u8 OSUSART1MemQ[OS_MEM_USART1_MAX];  			//空白内存块

OSMEMTcb* OSQUSART1Index;

const unsigned char Msg0[]="/******************** 版权所有 北京工业大学焊接研究所 潘健 ********************\n\r";
const unsigned char Msg1[]="* 文件名             : main.c\n\r";
const unsigned char Msg2[]="* 作者               : 潘健\n\r";
const unsigned char Msg3[]="* 版本               : V1.2\n\r";
const unsigned char Msg4[]="* 日期               : 01/17/2010\n\r";
const unsigned char Msg5[]="* 描述               : Main program body\n\r";
const unsigned char Msg6[]="* 功能               ：用于演示串口驱与拼音输入法\n\r";
const unsigned char Msg7[]="*******************************************************************************/\n\r";
void Welcome(void)
{
	USART1DispFun((unsigned char *)Msg0); 
	USART1DispFun((unsigned char *)Msg1); 
	USART1DispFun((unsigned char *)Msg2);
	USART1DispFun((unsigned char *)Msg3);
	USART1DispFun((unsigned char *)Msg4);
	USART1DispFun((unsigned char *)Msg5);
	USART1DispFun((unsigned char *)Msg6);
	USART1DispFun((unsigned char *)Msg7); 
}
/*******************************************************************************			 
* 文件名	  	 : main.c
* 描述	         : 采用PLL作为系统的时钟源（72MHZ）
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
int main(void)
{
  	RCC_Configuration();
	//配置波特率
	USART1_Configuration(115200);
	//申请内存管理管理块
	OSQUSART1Index=(OSMEMTcb *)OSMemCreate(OSUSART1MemQ,OS_MEM_USART1_BLK,OS_MEM_USART1_MAX/OS_MEM_USART1_BLK);
	DelayMs(10);
	//欢迎界面
	Welcome();
	DelayMs(100);
	//允许接收，最多六个字节，开启接收超时中断
	USART1RecvData(6,1);

	USART1DispFun("请输入拼音!\n\r");
  	while (1)
  	{
		DelayMs(100);
		

	}
}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
