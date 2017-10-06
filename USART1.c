/*******************************************************************************
* �ļ���	  	 : USART1.c
* ����	         : USART����������
* ��ֲ����		 : �м�㺯��
* ����           : ��
* ���           : ��
* ����           : ��
*******************************************************************************/
#include "stm32f10x.h"
#include "OSQMem.h"
#include "USART.h"

#define USART1_SEND_MAX_Q	  	(OS_MEM_USART1_BLK-4)	//�����ڴ���ڵ����ռ�
#define USART1_SEND_MAX_BOX		20	   					//�����ڴ����������

unsigned char USART1SendQBoxHost=0;						//�ڴ��ͷָ��							
unsigned char USART1SendQBoxTail=0;						//�ڴ��βָ��
unsigned int  USART1SendQFree=USART1_SEND_MAX_BOX;   
unsigned char USART1SendOVF=0; 							//USART1��������������־
unsigned char USART1RunningFlag=0;
typedef struct{
unsigned char Num;
unsigned char *Index;
}USART1SendTcb;
USART1SendTcb USART1SendTCB[USART1_SEND_MAX_BOX];

#define USART1_RECV_MAX_Q	  	32						//�ڴ���ڵ����ռ�
unsigned char USART1QRecvBuffer[USART1_RECV_MAX_Q];		//�����ڴ��	
unsigned char USART1RecvOVF=0; 							//USART2��������������־  
unsigned int Recv1Index=0x00;
unsigned int Recv1Count=0x00;
unsigned char USART1RecvFlag=0;

extern u8 OSUSART1MemQ[OS_MEM_USART1_MAX];  			//�հ��ڴ��
extern OSMEMTcb* OSQUSART1Index;

void USART1DMAUpdate(void);
//������
#define ERR_NO_SPACE	0xff

/*******************************************************************************
* �ļ���	  	 : USART1SendUpdate
* ����	         : ���ṹ��������û�����ݻ�δ������ϣ���û�з��ͣ���������ͣ�
				   ��������ϣ��˳�
* ����           : ��
* ���           : ��
* ����           : ��
*******************************************************************************/
void USART1SendUpdate(void)
{
	static unsigned char count=0;
	
	if(USART1SendQFree==USART1_SEND_MAX_BOX){return;}
	USART1StopSendISR();
	//������ڵ��ڴ������ݻ�û�з�����ϣ��������ͣ�Num��һ
	if((USART1SendTCB[USART1SendQBoxTail].Num)&&(USART1SendQBoxTail!=USART1SendQBoxHost))
	{
		USART1SendTCB[USART1SendQBoxTail].Num--;
		USART1SendByte(*(USART1SendTCB[USART1SendQBoxTail].Index+count));
		count++;
	}
	//һ�����Ϳ��Ѿ���������� ��USART1SendQFree++,βָ���һ��ָ����һ�����Ϳ�
	else if(USART1SendQBoxTail!=USART1SendQBoxHost)
	{		
		OSMemDelete(OSQUSART1Index,USART1SendTCB[USART1SendQBoxTail].Index);
		if(++USART1SendQBoxTail>=USART1_SEND_MAX_BOX)USART1SendQBoxTail=0;
		if(++USART1SendQFree>=USART1_SEND_MAX_BOX)USART1SendQFree=USART1_SEND_MAX_BOX;
		count=0;
		//USART1SendQBoxTail����USART1SendQBoxTail��ʱ��ͱ�־�ⷢ�ͽ����ˣ�����ֱ���˳�
		if((USART1SendQBoxTail!=USART1SendQBoxHost))
//		if((USART1SendTCB[USART1SendQBoxTail].Num)&&(USART1SendQBoxTail!=USART1SendQBoxHost))
		{
			USART1SendTCB[USART1SendQBoxTail].Num--;
			USART1SendByte(*(USART1SendTCB[USART1SendQBoxTail].Index+count));
			count++;
		}
		else
		{	
		//USART1SendQBoxTail����USART1SendQBoxTail��ʱ��ͱ�־�ⷢ�ͽ����ˣ�����ֱ���˳�
			USART1RunningFlag=0;
			USART1SendQFree=USART1_SEND_MAX_BOX;
			count=0;
		}	
	}
	//����ͷָ��һֱ��ָ��յķ��Ϳ�ģ�����USART1SendQBoxTail����USART1SendQBoxTail
	//��ʱ��ͱ�־�ⷢ�ͽ����ˣ�����ֱ���˳�
	else
	{
		USART1RunningFlag=0;
		USART1SendQFree=USART1_SEND_MAX_BOX;
		count=0;
	}
	USART1StartSendISR();	
}
/*******************************************************************************
* �ļ���	  	 : USART1WriteDataToBuffer
* ����	         : ��鷢�ͻ������Ĵ�С�����ռ��㹻���������͵����ݷ��뵽���ͻ���
				   ����ȥ,������������
* ����           : buffer�����͵����ݵ�ָ�룬count�����͵����ݵ�����
* ���           : ��
* ����           : ����ȷ���뵽���ͻ�������ȥ�ˣ��ͷ���0x00	 �����򷵻�0x01
*******************************************************************************/
unsigned char USART1WriteDataToBuffer(unsigned char *buffer,unsigned char count)
{
	unsigned char i=count;
	u8 err;
	/*�˴����Լ����źŵƻ��߹ر��ж�*/
	if(count==0)return;
	USART1StopSendISR();
	/*�������count��������Ҫ���ٸ��ڴ��*/
	if(count%USART1_SEND_MAX_Q)count=count/USART1_SEND_MAX_Q+1;
	else count=count/USART1_SEND_MAX_Q;
	/*��Ҫcount�����ݿ�*/
	/*����ڴ治�㣬ֱ�ӷ���*/		 
	if(USART1SendQFree<count){USART1StartSendISR();return ERR_NO_SPACE;}
	//���������ڴ�飬USART1SendQBoxHost����һ���ڴ������ż�һ
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
			//��Ҫһ���µ��ڴ���Ž����������ݣ����Ը���USART1SendQBoxHost
			if(++USART1SendQBoxHost>=USART1_SEND_MAX_BOX)USART1SendQBoxHost=0;
			//��Ҫһ���µ��ڴ���Ž�����������	
			USART1SendTCB[USART1SendQBoxHost].Index=(u8 *)OSMemGet(OSQUSART1Index,&err);
			//�յķ���������һ 			
			USART1SendQFree--;
			count=0;
		}
		buffer++;
		i--;
	}
	//�˴�����δ�����������ݣ�����ҲҪ�����һ���µ��ڴ����
	if(count!=0)
	{
		USART1SendTCB[USART1SendQBoxHost].Num=count; 
		USART1SendQFree--;
		if(++USART1SendQBoxHost>=USART1_SEND_MAX_BOX)USART1SendQBoxHost=0;
	}
	//����ǵ�һ�Σ����������ͣ�������Ѿ�������û�������Ҫ��
	if(USART1RunningFlag==0)
	{
#if	  	DMA_MODE
		USART1DMAConfig(USART1SendTCB[USART1SendQBoxTail].Index,USART1SendTCB[USART1SendQBoxTail].Num);
#else	
		USART1SendUpdate();
#endif		
		USART1RunningFlag=1;
	}
	/*�˴����Կ����źŵƻ��ߴ��ж�*/
	USART1StartSendISR();
	return 0x00;
}
/*******************************************************************************
* �ļ���	  	 : USART1DispFun
* ����	         : ��鷢�ͻ������Ĵ�С�����ռ��㹻���������͵����ݷ��뵽���ͻ���
				   ����ȥ,������������,��USART1WriteDataToBuffer��ͬ���ǣ���������
				   ����������Ҫָ���ļ���С�ģ���͸������ṩ�˷���.
* ����           : buffer�����͵����ݵ�ָ��
* ���           : ��
* ����           : ����ȷ���뵽���ͻ�������ȥ�ˣ��ͷ���0x00	 �����򷵻�0x01
*******************************************************************************/
unsigned char USART1DispFun(unsigned char *buffer)
{
	unsigned long count=0;
	while(buffer[count]!='\0')count++;
	return(USART1WriteDataToBuffer(buffer,count));
}


/*******************************************************************************
* �ļ���	  	 : USART1RecvResetBufferIndex
* ����	         : ��������ʱ�жϵ�ʱ�򣬽����յ�ָ����㣬���ҹرռ�鳬ʱ��ʱ��
* ����           : ��
* ���           : ��
* ����           : ��
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
		USART1DispFun("\n\r�����ƴ�����룬����������!\n\r");
		while(Count!=0)PinYinIndex[Count--]=0;	
	}		
	
	
}
//unsigned char test1;	
/*******************************************************************************
* �ļ���	  	 : USART1RecvFun
* ����	         : �����յ�������һ֡�����Ժ�Ĵ�����
* ����           : ptr���յ�������֡��ͷָ�룬���յ�������֡�����ݸ���
* ���           : ��
* ����           : ��
*******************************************************************************/
void USART1RecvFun(unsigned char *ptr,unsigned int count)
{
	USART1WriteDataToBuffer(ptr,8);
}
/*******************************************************************************
* �ļ���	  	 : USART1RecvUpdate
* ����	         : ������յ�һ������
* ����           : ��
* ���           : ��
* ����           : ��
*******************************************************************************/	
void USART1RecvUpdate(void)
{
	if(Recv1Index<Recv1Count)
	{
		USART1QRecvBuffer[Recv1Index++]=(unsigned char)USART1RecvByte();
		//֪�����յ�ָ������������
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
* �ļ���	  	 : USART1RecvData
* ����	         : �����յ�������һ֡�����Ժ�Ĵ�����
* ����           : count��Ҫ���յ���һ֡�������ݵĸ�����flag��1������ʱ�ж�
				   0�رճ�ʱ�ж�
* ���           : ��
* ����           : ��
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
* �ļ���	  	 : USART1DMAUpdate.c
* ����	         : USART_DMA����������
* ��ֲ����		 : �м�㺯��
* ����           : ��
* ���           : ��
* ����           : ��
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