/*******************************************************************************
* 文件名	  	 : USARTConfig.c 
* 描述	         : USART的底层配置函数
* 移植步骤		 :（1）配置函数（管脚，时钟等）
				  （2）控制的参数（极性，波特率，位数，校验位等）
				  （3）中断函数	
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
#include "stm32f10x.h"
#include "USART.h"

void USART1DMAConfiguration(u8 TxBuffer1,u16 num);
/*******************************************************************************
* 文件名	  	 : ADC1GPIOC_Configuration
* 描述	         : 配置 USART1 Tx Rx
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1PinConfiguration(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;	
	/* 配置 USART1 Tx (PA.09) as alternate function push-pull */
  	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA,&GPIO_InitStructure);

	/* 配置 USART1 Rx (PA.10) as input floating */
  	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

/*******************************************************************************
* 文件名	  	 : TIM2NVIC_Configuration
* 描述	         : TIM2中断通道4配置
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void TIM2NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* 配置 DMA通道4的中断，中断优先级别为1，响应级别为2 */
//	NVIC_StructInit(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=10;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* 文件名	  	 : USART1ClearCounter
* 描述	         : USART1ClearCounter
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1ClearCounter(void)
{
	TIM_SetCounter(TIM2,0x0000);
}

/*******************************************************************************
* 文件名	  	 : USART1StartCounter
* 描述	         : USART1StartCounter
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1StartCounter(void)
{
	USART1ClearCounter();
	TIM_Cmd(TIM2, ENABLE);
}

/*******************************************************************************
* 文件名	  	 : USART1StopCounter
* 描述	         : USART1StopCounter
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1StopCounter(void)
{
	TIM_Cmd(TIM2, DISABLE); 
}

/*******************************************************************************
* 文件名	  	 : TIM2_IRQHandler
* 描述	         : TIM2_IRQHandler
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		TIM_ClearFlag(TIM2,TIM_IT_Update);
		USART1RecvResetBufferIndex();
	}
}


unsigned int USART1RecvByte(void)
{
	return(USART_ReceiveData(USART1));
}


/*******************************************************************************
* 文件名	  	 : TIM2_Configuration
* 描述	         : TIM2_Configuration
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStruct;

	TIM_DeInit(TIM2);
	TIM2NVIC_Configuration();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure); 
	TIM_TimeBaseInitStructure.TIM_Period=9999;
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;	 
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);


	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_Timing;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High; 
	TIM_OCInitStruct.TIM_Pulse=4999;
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
		
	
	TIM_SelectInputTrigger(TIM2,TIM_TS_ITR1);
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	
	TIM_Cmd(TIM2, ENABLE); 
	USART1StopCounter();
}

/*******************************************************************************
* 文件名	  	 : USART1NVIC_Configuration
* 描述	         : USART1DMA中断通道4配置
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* 配置 DMA通道4的中断，中断优先级别为1，响应级别为2 */
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*******************************************************************************
* 文件名	  	 : USART1配置
* 描述	         : baud:USART1波特率
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1_Configuration(unsigned long baud)
{	
	USART_InitTypeDef USART_InitStructure;
	USART1PinConfiguration();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
	/* 配置 USART1 参数：115200波特率，一位停止位，八位数据位，无硬件控制 */
	USART_DeInit(USART1);
	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate=baud;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; 
	USART_Init(USART1,&USART_InitStructure);
#if	DMA_MODE
#else
	USART_ITConfig(USART1,USART_IT_TC,ENABLE);	 
	
#endif
	USART1NVIC_Configuration();
	USART_Cmd(USART1,ENABLE);
	TIM2_Configuration();
}

/*******************************************************************************
* 文件名	  	 : USART1SendByte配置
* 描述	         : temp:USART1发送的数据
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1SendByte(unsigned char temp)
{
	USART_SendData(USART1,temp);
}


/*******************************************************************************
* 文件名	  	 : USART1_IRQHandler
* 描述	         : USART1_IRQHandler（USART1发送）中断函数通道
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1_IRQHandler(void)
{
	static u8 Flag=0;
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
	{
	    USART_ClearFlag(USART1,USART_FLAG_RXNE);//TCIE,TE,RE
		if(Flag)
		{			
			USART1RecvUpdate();
		}
	}
	if(USART_GetFlagStatus(USART1,USART_FLAG_TC)==SET)
	{
	    USART_ClearFlag(USART1,USART_FLAG_TC);//TCIE,TE,RE
	//如果不是DMA发送，采用中断发送		
#if	  	DMA_MODE
		;
#else
		if(Flag)
		{
			USART1SendUpdate();
		}
#endif
	
	}
	Flag=1;
}
/*******************************************************************************
* 文件名	  	 : USART1StopSendISR
* 描述	         : 停止发送中断
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1StopSendISR(void)
{
	USART_ITConfig(USART1,USART_IT_TC,DISABLE);	  	
}
/*******************************************************************************
* 文件名	  	 : USART1StartSendISR
* 描述	         : 开启发送中断
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1StartSendISR(void)
{
	USART_ITConfig(USART1,USART_IT_TC,ENABLE);		 
}
/*******************************************************************************
* 文件名	  	 : USART1StopRecvISR
* 描述	         : 停止接收中断
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1StopRecvISR(void)
{
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
}
/*******************************************************************************
* 文件名	  	 : USART1StartRecvISR
* 描述	         : 开启接收中断
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void USART1StartRecvISR(void)
{
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}
/*******************************************************************************
* 文件名	  	 : USART1DMAConfiguration
* 描述	         : 开启接收中断
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/

#define USART1_DR_Base  0x40013804

void USART1DMAConfig(u8 TxBuffer1,u16 num)
{
    DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
    /* DMA1 Channel4 (triggered by USART1 Tx event) Config */
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)TxBuffer1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = num;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_Cmd(DMA1_Channel4, ENABLE);
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	USART_Cmd(USART1,ENABLE);
}

/*******************************************************************************
* 文件名	  	 : DMA1_Channel4_IRQHandler
* 描述	         : DMA1_Channel4_IRQHandler（USART1发送）DMA函数通道
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC4)==SET)
	{
	    DMA_ClearFlag(DMA1_IT_TC4);//TCIE,TE,RE			
		USART1DMAUpdate();
	}
}




	 


