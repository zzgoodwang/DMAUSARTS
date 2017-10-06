#include "stm32f10x.h"

void DelayMs(unsigned long N)
{
	long count=14200;
	while(N)
	{
		count=14200;
		while(count--);
		N--;
	}
}

void DelayUs(unsigned long N)
{
	long count=14;
	while(N)
	{
		count=14;
		while(count--);
		N--;
	}
}

void RCC_Configuration(void)
{
	
 	  	/* ��λʱ�����壬Ĭ��Ϊ�ڲ�ʱ�� */
	RCC_DeInit();
	/* �����ⲿʱ�� */	
        RCC_HSEConfig(RCC_HSE_ON);
	/* �ȴ��ⲿʱ��ʹ����� */
	if(RCC_WaitForHSEStartUp()==SUCCESS)
	{   
	    /* ʹ��FLASH������Ԫ */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        /* �ȴ�����ʱ������ */
    	FLASH_SetLatency(FLASH_Latency_2);
		/* ����USBʱ�� */
		RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
		/* ����AHBʱ�� */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1
							 |RCC_AHBPeriph_DMA2
							 |RCC_AHBPeriph_SRAM
							 |RCC_AHBPeriph_FLITF
							 |RCC_AHBPeriph_CRC
                             |RCC_AHBPeriph_FSMC
                             |RCC_AHBPeriph_SDIO,ENABLE);
		/* ����HCLKʱ�� */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/* ����PCLK1ʱ�� */
		RCC_PCLK1Config(RCC_HCLK_Div1);
		/* ����PCLK2ʱ�� */
		RCC_PCLK2Config(RCC_HCLK_Div1);
		/* ѡ���ⲿʱ����ΪPLLʱ��Դ */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		/* ����ʹ��PLLʱ�� */
		RCC_PLLCmd(ENABLE);
		/* �ȴ�PLL�����ȶ� */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
		/* ѡ��PLL��Ϊϵͳ��ʱ��Դ */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/* ȷ��PLL�Ѿ���Ϊ�µ�ϵͳʱ���� */
		while(RCC_GetSYSCLKSource()!=0x08);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_USART1
							  |RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB
                              |RCC_APB2Periph_GPIOF|RCC_APB2Periph_TIM1, ENABLE);
	}
}