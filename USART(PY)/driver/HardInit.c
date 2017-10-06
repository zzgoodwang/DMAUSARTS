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
	
 	  	/* 复位时钟脉冲，默认为内部时钟 */
	RCC_DeInit();
	/* 配置外部时钟 */	
        RCC_HSEConfig(RCC_HSE_ON);
	/* 等待外部时钟使能完毕 */
	if(RCC_WaitForHSEStartUp()==SUCCESS)
	{   
	    /* 使能FLASH保护单元 */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        /* 等待两个时钟周期 */
    	FLASH_SetLatency(FLASH_Latency_2);
		/* 配置USB时钟 */
		RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
		/* 配置AHB时钟 */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1
							 |RCC_AHBPeriph_DMA2
							 |RCC_AHBPeriph_SRAM
							 |RCC_AHBPeriph_FLITF
							 |RCC_AHBPeriph_CRC
                             |RCC_AHBPeriph_FSMC
                             |RCC_AHBPeriph_SDIO,ENABLE);
		/* 配置HCLK时钟 */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/* 配置PCLK1时钟 */
		RCC_PCLK1Config(RCC_HCLK_Div1);
		/* 配置PCLK2时钟 */
		RCC_PCLK2Config(RCC_HCLK_Div1);
		/* 选择外部时钟作为PLL时钟源 */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);
		/* 配置使能PLL时钟 */
		RCC_PLLCmd(ENABLE);
		/* 等待PLL工作稳定 */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
		/* 选择PLL作为系统的时钟源 */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/* 确认PLL已经成为新的系统时钟沿 */
		while(RCC_GetSYSCLKSource()!=0x08);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_USART1
							  |RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB
                              |RCC_APB2Periph_GPIOF|RCC_APB2Periph_TIM1, ENABLE);
	}
}