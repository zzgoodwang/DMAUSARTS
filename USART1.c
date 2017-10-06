/*******************************************************************************
* 文件名	  	 : USART1.c
* 描述	         : USART的驱动函数
* 移植步骤		 : 中间层函数
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
#include "stm32f10x.h"
#include "OSQMem.h"
#include "USART.h"

#define USART1_SEND_MAX_Q	  	(OS_MEM_USART1_BLK-4)	//发送内存块内的最大空间
#define USART1_SEND_MAX_BOX		20	   					//发送内存块的最大数量

unsigned char USART1SendQBoxHost=0;						//内存块头指针							
unsigned char USART1SendQBoxTail=0;						//内存块尾指针
unsigned int  USART1SendQFree=USART1_SEND_MAX_BOX;   
unsigned char USART1SendOVF=0; 							//USART1发送任务块溢出标志
unsigned char USART1RunningFlag=0;
typedef struct{
unsigned char Num;
unsigned char *Index;
}USART1SendTcb;
USART1SendTcb USART1SendTCB[USART1_SEND_MAX_BOX];

#define USART1_RECV_MAX_Q	  	32						//内存块内的最大空间
unsigned char USART1QRecvBuffer[USART1_RECV_MAX_Q];		//接收内存块	
unsigned char USART1RecvOVF=0; 							//USART2接收任务块溢出标志  
unsigned int Recv1Index=0x00;
unsigned int Recv1Count=0x00;
unsigned char USART1RecvFlag=0;

extern u8 OSUSART1MemQ[OS_MEM_USART1_MAX];  			//空白内存块
extern OSMEMTcb* OSQUSART1Index;

void USART1DMAUpdate(void);
//错误定义
#define ERR_NO_SPACE	0xff

/*******************************************************************************
* 文件名	  	 : USART1SendUpdate
* 描述	         : 检查结构体里面有没有数据还未发送完毕，若没有发送，则继续发送，
				   若发送完毕，退出
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1SendUpdate(void)
{
	static unsigned char count=0;
	
	if(USART1SendQFree==USART1_SEND_MAX_BOX){return;}
	USART1StopSendISR();
	//如果现在的内存块的数据还没有发送完毕，启动发送，Num减一
	if((USART1SendTCB[USART1SendQBoxTail].Num)&&(USART1SendQBoxTail!=USART1SendQBoxHost))
	{
		USART1SendTCB[USART1SendQBoxTail].Num--;
		USART1SendByte(*(USART1SendTCB[USART1SendQBoxTail].Index+count));
		count++;
	}
	//一个发送块已经发送完毕了 ，USART1SendQFree++,尾指针加一。指向下一个发送块
	else if(USART1SendQBoxTail!=USART1SendQBoxHost)
	{		
		OSMemDelete(OSQUSART1Index,USART1SendTCB[USART1SendQBoxTail].Index);
		if(++USART1SendQBoxTail>=USART1_SEND_MAX_BOX)USART1SendQBoxTail=0;
		if(++USART1SendQFree>=USART1_SEND_MAX_BOX)USART1SendQFree=USART1_SEND_MAX_BOX;
		count=0;
		//USART1SendQBoxTail等于USART1SendQBoxTail的时候就标志这发送结束了，可以直接退出
		if((USART1SendQBoxTail!=USART1SendQBoxHost))
//		if((USART1SendTCB[USART1SendQBoxTail].Num)&&(USART1SendQBoxTail!=USART1SendQBoxHost))
		{
			USART1SendTCB[USART1SendQBoxTail].Num--;
			USART1SendByte(*(USART1SendTCB[USART1SendQBoxTail].Index+count));
			count++;
		}
		else
		{	
		//USART1SendQBoxTail等于USART1SendQBoxTail的时候就标志这发送结束了，可以直接退出
			USART1RunningFlag=0;
			USART1SendQFree=USART1_SEND_MAX_BOX;
			count=0;
		}	
	}
	//由于头指针一直是指向空的发送块的，所以USART1SendQBoxTail等于USART1SendQBoxTail
	//的时候就标志这发送结束了，可以直接退出
	else
	{
		USART1RunningFlag=0;
		USART1SendQFree=USART1_SEND_MAX_BOX;
		count=0;
	}
	USART1StartSendISR();	
}
/*******************************************************************************
* 文件名	  	 : USART1WriteDataToBuffer
* 描述	         : 检查发送缓冲区的大小，若空间足够，将待发送的数据放入到发送缓冲
				   区中去,并且启动发送
* 输入           : buffer待发送的数据的指针，count待发送的数据的数量
* 输出           : 无
* 返回           : 若正确放入到发送缓冲区中去了，就返回0x00	 ，否则返回0x01
*******************************************************************************/
unsigned char USART1WriteDataToBuffer(unsigned char *buffer,unsigned char count)
{
	unsigned char i=count;
	u8 err;
	/*此处可以加入信号灯或者关闭中断*/
	if(count==0)return;
	USART1StopSendISR();
	/*计算放入count个数据需要多少个内存块*/
	if(count%USART1_SEND_MAX_Q)count=count/USART1_SEND_MAX_Q+1;
	else count=count/USART1_SEND_MAX_Q;
	/*需要count个数据块*/
	/*如果内存不足，直接返回*/		 
	if(USART1SendQFree<count){USART1StartSendISR();return ERR_NO_SPACE;}
	//首先申请内存块，USART1SendQBoxHost在下一个内存申请后才加一
	USART1SendTCB[USART1SendQBoxHost].Index=(u8 *)OSMemGet(OSQUSART1Index,&err);
	if(USART1SendQBoxHost>=USART1_SEND_MAX_BOX)USART1SendQBoxHost=0;	
	count=0;
	while(i!='\0')										 
	{
		*(USART1SendTCB[USART1SendQBoxHost].Index+count)=*buffer;
		count++;
		if(count>=USART1_SEND_MAX_Q)
		{
			USART1SendTCB[USART1SendQBoxHost].Num=USART1_SEND_MAX_Q;
			//需要一个新的内存块存放接下来的数据，所以更新USART1SendQBoxHost
			if(++USART1SendQBoxHost>=USART1_SEND_MAX_BOX)USART1SendQBoxHost=0;
			//需要一个新的内存块存放接下来的数据	
			USART1SendTCB[USART1SendQBoxHost].Index=(u8 *)OSMemGet(OSQUSART1Index,&err);
			//空的发送任务块减一 			
			USART1SendQFree--;
			count=0;
		}
		buffer++;
		i--;
	}
	//此处是尚未整块存完的数据，它们也要存放在一个新的内存块里
	if(count!=0)
	{
		USART1SendTCB[USART1SendQBoxHost].Num=count; 
		USART1SendQFree--;
		if(++USART1SendQBoxHost>=USART1_SEND_MAX_BOX)USART1SendQBoxHost=0;
	}
	//如果是第一次，就启动发送，如果是已经启动就没有这个必要了
	if(USART1RunningFlag==0)
	{
#if	  	DMA_MODE
		USART1DMAConfig(USART1SendTCB[USART1SendQBoxTail].Index,USART1SendTCB[USART1SendQBoxTail].Num);
#else	
		USART1SendUpdate();
#endif		
		USART1RunningFlag=1;
	}
	/*此处可以开启信号灯或者打开中断*/
	USART1StartSendISR();
	return 0x00;
}
/*******************************************************************************
* 文件名	  	 : USART1DispFun
* 描述	         : 检查发送缓冲区的大小，若空间足够，将待发送的数据放入到发送缓冲
				   区中去,并且启动发送,与USART1WriteDataToBuffer不同的是，启动发送
				   函数世不需要指定文件大小的，这就给调用提供了方便.
* 输入           : buffer待发送的数据的指针
* 输出           : 无
* 返回           : 若正确放入到发送缓冲区中去了，就返回0x00	 ，否则返回0x01
*******************************************************************************/
unsigned char USART1DispFun(unsigned char *buffer)
{
	unsigned long count=0;
	while(buffer[count]!='\0')count++;
	return(USART1WriteDataToBuffer(buffer,count));
}


/*******************************************************************************
* 文件名	  	 : USART1RecvResetBufferIndex
* 描述	         : 当发生超时中断的时候，将接收的指针归零，并且关闭检查超时的时钟
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1RecvResetBufferIndex(void)
{	
	static u8 PinYinIndex[6];
	static u8 Count=0xff;

	USART1WriteDataToBuffer(USART1QRecvBuffer,Recv1Index);
	USART1StopCounter();
	Recv1Index=0;
	if(Count==0xff){Count=0;return;}

	if(((*USART1QRecvBuffer>='a')&&(*USART1QRecvBuffer<='z'))||((*USART1QRecvBuffer>='A')&&(*USART1QRecvBuffer<='Z')))
	{
		if(Count<6)
		{
			PinYinIndex[Count++]=*USART1QRecvBuffer;
		}
		else 
		{
			USART1DispFun("\n\r");
			USART1DispFun((char *)PYSearch(PinYinIndex));
			USART1DispFun("\n\r");
			while(Count!=0)PinYinIndex[Count--]=0;
			
		}		  
	}	
	else if(*USART1QRecvBuffer=='\r')
	{
		if(Count!=0)
		{
			USART1DispFun("\n\r");
			USART1DispFun((char *)PYSearch(PinYinIndex));
			USART1DispFun("\n\r");
			while(Count!=0)PinYinIndex[Count--]=0;
		}
	}
	else 
	{
		USART1DispFun("\n\r错误的拼音代码，请重新输入!\n\r");
		while(Count!=0)PinYinIndex[Count--]=0;	
	}		
	
	
}
//unsigned char test1;	
/*******************************************************************************
* 文件名	  	 : USART1RecvFun
* 描述	         : 当接收到完整的一帧数据以后的处理函数
* 输入           : ptr接收到的数据帧的头指针，接收到的数据帧的数据个数
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1RecvFun(unsigned char *ptr,unsigned int count)
{
	USART1WriteDataToBuffer(ptr,8);
}
/*******************************************************************************
* 文件名	  	 : USART1RecvUpdate
* 描述	         : 处理接收到一个数据
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/	
void USART1RecvUpdate(void)
{
	if(Recv1Index<Recv1Count)
	{
		USART1QRecvBuffer[Recv1Index++]=(unsigned char)USART1RecvByte();
		//知道接收到指定数量的数据
		if(Recv1Index>=Recv1Count)
		{
			Recv1Index=0;
			USART1StopCounter();
			USART1RecvFun(USART1QRecvBuffer,Recv1Count);
		}
		if(USART1RecvFlag==1)USART1StartCounter();	
		else USART1StopCounter();	
	}	
}
/*******************************************************************************
* 文件名	  	 : USART1RecvData
* 描述	         : 当接收到完整的一帧数据以后的处理函数
* 输入           : count：要接收到的一帧数据数据的个数，flag：1开启超时中断
				   0关闭超时中断
* 输出           : 无
* 返回           : 无
*******************************************************************************/	
unsigned char USART1RecvData(unsigned int count,unsigned char flag)
{
	if(count!=0)
	{
		Recv1Count=count;
		USART1RecvFlag=flag;
		if(flag==1)USART1StartRecvISR();
	}
	else if(count>USART1_RECV_MAX_Q) return ERR_NO_SPACE;
	return 0x00;
}
/*******************************************************************************
* 文件名	  	 : USART1DMAUpdate.c
* 描述	         : USART_DMA的驱动函数
* 移植步骤		 : 中间层函数
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1DMAUpdate(void)
{
	if(USART1SendQBoxTail!=USART1SendQBoxHost)
	{
		OSMemDelete(OSQUSART1Index,USART1SendTCB[USART1SendQBoxTail].Index);
		if(++USART1SendQBoxTail>=USART1_SEND_MAX_BOX)USART1SendQBoxTail=0;
		if(++USART1SendQFree>=USART1_SEND_MAX_BOX)USART1SendQFree=USART1_SEND_MAX_BOX;
		if(USART1SendQBoxTail!=USART1SendQBoxHost)
		{
			USART1DMAConfig(USART1SendTCB[USART1SendQBoxTail].Index,USART1SendTCB[USART1SendQBoxTail].Num);	
		}
		else USART1RunningFlag=0;	
	}
	else 
	{		
		OSMemDelete(OSQUSART1Index,USART1SendTCB[USART1SendQBoxTail].Index);
		if(++USART1SendQBoxTail>=USART1_SEND_MAX_BOX)USART1SendQBoxTail=0;
		if(++USART1SendQFree>=USART1_SEND_MAX_BOX)USART1SendQFree=USART1_SEND_MAX_BOX;
		USART1RunningFlag=0;
	}	
}