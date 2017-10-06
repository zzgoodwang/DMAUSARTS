/******************** ��Ȩ���� ������ҵ��ѧ�����о��� �˽� ********************
* �ļ���             : main.c
* ����               : �˽�
* �汾               : V1.2
* ����               : 1/12/2010
* ����               : Main program body
* ����               ��������ʾUSART��ƴ�����뷨					   				   	
*******************************************************************************/
#include "stm32f10x.h"
#include "OSQMem.h"	

extern u8 OSUSART1MemQ[OS_MEM_USART1_MAX];  			//�հ��ڴ��

OSMEMTcb* OSQUSART1Index;

const unsigned char Msg0[]="/******************** ��Ȩ���� ������ҵ��ѧ�����о��� �˽� ********************\n\r";
const unsigned char Msg1[]="* �ļ���             : main.c\n\r";
const unsigned char Msg2[]="* ����               : �˽�\n\r";
const unsigned char Msg3[]="* �汾               : V1.2\n\r";
const unsigned char Msg4[]="* ����               : 01/17/2010\n\r";
const unsigned char Msg5[]="* ����               : Main program body\n\r";
const unsigned char Msg6[]="* ����               ��������ʾ��������ƴ�����뷨\n\r";
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
* �ļ���	  	 : main.c
* ����	         : ����PLL��Ϊϵͳ��ʱ��Դ��72MHZ��
* ����           : ��
* ���           : ��
* ����           : ��
*******************************************************************************/
int main(void)
{
  	RCC_Configuration();
	//���ò�����
	USART1_Configuration(115200);
	//�����ڴ����������
	OSQUSART1Index=(OSMEMTcb *)OSMemCreate(OSUSART1MemQ,OS_MEM_USART1_BLK,OS_MEM_USART1_MAX/OS_MEM_USART1_BLK);
	DelayMs(10);
	//��ӭ����
	Welcome();
	DelayMs(100);
	//�������գ���������ֽڣ��������ճ�ʱ�ж�
	USART1RecvData(6,1);

	USART1DispFun("������ƴ��!\n\r");
  	while (1)
  	{
		DelayMs(100);
		

	}
}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/