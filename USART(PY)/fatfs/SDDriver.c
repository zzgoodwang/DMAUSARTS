#include "stm32f10x.h"
#include "sdcard.h"
#include "stdio.h"
#include "integer.h"
#include "ff.h"
#include "diskio.h"

#define 	die(res)		(res)=0	
FATFS fs;            	// Work area (file system object) for logical drive
FIL fsrc, fdst;      	// file objects
BYTE buffer[512]; 		// file copy buffer
FRESULT res;         	// FatFs function common result code
UINT br, bw;         	// File R/W count
u8 FATBuffer[512];
u8 FontBuffer[256];
u8 FontData[32];

/* 字码是从1410处开始显示
/*"啊",1410*
{0x00,0x00,0xF7,0x7E,0x95,0x04,0x95,0x04,0x96,0x74,0x96,0x54,0x95,0x54,0x95,0x54},
{0x95,0x54,0xF5,0x54,0x97,0x74,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x14,0x04,0x08},
*/
/*"齄",8177*/
/* 字码是从8177处结束
{0x20,0x20,0x7C,0x20,0x55,0xFE,0x6C,0x20,0x54,0x70,0xFE,0xAE,0x93,0x24,0xFE,0xF8},
{0x92,0x88,0xFE,0xF8,0x00,0x88,0xFE,0x88,0x24,0xF8,0x24,0x00,0x25,0xFE,0x44,0x00},
*/
/*共计6768个汉字，对应的数据为0，,6767*/


SD_CardInfo SDCardInfo;

SD_Error Status = SD_OK;

void OutPutFile(void)
{
	unsigned int a;
    FRESULT res;
    FILINFO finfo;
    DIR dirs;
    int i;
    char *fn;
    char path[50]={""};    
    char name[]={"WVO.TXT"};
        
    USART1DispFun("\n    file system(Tini-FatFa0.07C) starting! \n");
    
    disk_initialize(0);
        
    f_mount(0, &fs);

 	if(f_opendir(&dirs, path) == FR_OK) 
    {
        while (f_readdir(&dirs, &finfo) == FR_OK)    
        {
            if (finfo.fattrib & AM_ARC) 
            {
                if(!finfo.fname[0])break;                 
                USART1DispFun("\r\n file name is:\n\r");
				USART1DispFun(finfo.fname);
                res = f_open(&fsrc, finfo.fname, FA_OPEN_EXISTING | FA_READ);
                br=1;
				a=0;
				for (;;)
				{
					for(a=0; a<512; a++) buffer[a]=0; 
		        	res = f_read(&fsrc, buffer, sizeof(buffer), &br);
					USART1DispFun(buffer);	
		        	if (res || br == 0) break;
		        }
				f_close(&fsrc);	                                            
        	}
        } 
       
    }
}
void SDInit(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;

  	/* Configure the NVIC Preemption Priority Bits */
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	/*-------------------------- SD Init ----------------------------- */
    Status = SD_Init();
    if (Status == SD_OK)
    {
        /*----------------- Read CSD/CID MSD registers ------------------*/
        Status = SD_GetCardInfo(&SDCardInfo);
    } 
    if (Status == SD_OK)
    {
        /*----------------- Select Card --------------------------------*/
        Status = SD_SelectDeselect((u32) (SDCardInfo.RCA << 16));
    }
    /* Set Device Transfer Mode to DMA */
    if (Status == SD_OK)
    {        
        Status = SD_SetDeviceMode(SD_INTERRUPT_MODE);
    }
}
			
/*******************************************************************************
* 文件名	  	 : FontRead
* 描述	         : LCDRST
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
const u8 CHARNUMTAB[6]={10,11,12,13,14,15};
void FontRead(u8 *hazi)
{
	u16 i=0,j=0;
	u32 offset=0;
	u16 index1,index2;
	u8 *ptr;
	
	index1=(unsigned int)*hazi++;
	index1-=0xa0;
	index2=(unsigned int)*hazi++;
	index2-=0xa0;
	index1=index1*100+index2;
	index1-=1601;
	index2=index1/100;
	index1=index1-index2*6;

	offset=754+index1*395;

	// Register a work area for logical drive 0
    f_mount(0, &fs);

    // Open source file
    res = f_open(&fsrc, "CN16X16.txt", FA_OPEN_EXISTING | FA_READ);
    if (res) die(res);

	res = f_lseek(&fsrc, offset);
	if (res) die(res);

    // Copy source to destination
    res = f_read(&fsrc, FontBuffer, 256, &br);
    if (res || br == 0) die(res);   // error or eof
	ptr=FontBuffer;

    // Close all files
    f_close(&fsrc);

    // Unregister a work area before discard it
    f_mount(0, NULL);

	while(j<32)
	{
		if(*ptr=='x')
		{
			ptr++;
			i++;
			if(((*ptr)>=0x30)&&((*ptr)<=0x39))FontData[j]=*ptr-0x30;
			else if(((*ptr)>='A')&&((*ptr)<='F'))FontData[j]=CHARNUMTAB[*ptr-'A']; 
			FontData[j]<<=4;
			ptr++;
			i++;
			if(((*ptr)>=0x30)&&((*ptr)<=0x39))FontData[j]+=(*ptr-0x30);
			else if(((*ptr)>='A')&&((*ptr)<='F'))FontData[j]+=CHARNUMTAB[*ptr-'A']; 
			j++;
		}
		ptr++;
		i++;
	}
//	USART1WriteDataToBuffer(FontBuffer,166);
//	USART1DispFun("\n\r");
}

