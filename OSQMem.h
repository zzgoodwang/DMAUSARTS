
/******************** ��Ȩ���� ������ҵ��ѧ�����о��� �˽� ********************
* �ļ���             : OSQMem.h
* ����               : �˽�
* �汾               : V1.2
* ����               : 1/13/2010
* ����               : �ڴ�Ĺ�����
* ����               ���ڴ�Ĺ�����				   				   	
*******************************************************************************/
#ifndef _OSQMEM_H
#define _OSQMEM_H

#include "stm32f10x.h"
#define 	OS_MEM_MAX 				8	   			//���������ڴ�������
#define 	OS_MEM_USART1_MAX 		1024			//���ͻ��������ڴ��С
#define 	OS_MEM_USART1_BLK 		32				//ÿһ����ĳ���

typedef struct OSMEMTCB{
	void 		*OSMemFreeList;
	u8 			OSMemBlkSize;
	u8 			OSMemNBlks;
	u8 			OSMemFreeNBlks;
}OSMEMTcb;


#endif