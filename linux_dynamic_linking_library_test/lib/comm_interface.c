/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of WAN XING Tech. Co., Ltd.(C) 2020.
*
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
*********************************************************************************************************
*
* File name: comm_interface.c
* -------------------------------------
*
* Module: xxx
* -------------------------------------
*
* Project: xxx
* -------------------------------------
*
* Version: V1.0
* -------------------------------------
*
* Description:  xxxxxxxxxxxxxxxxxxxxxxxx
*
* ------------------------------------------------------------------------
*
* History:
*
* Date                   Author             Change Id             Release Description Of Change
* ------------------------------------------------------------------------------------------------------
*
*
* ------------------------------------------------------------------------------------------------------
*
*
* ------------------------------------------------------------------------------------------------------
*
* Others:
*
********************************************************************************************************/
/*------------------------------------------------------------------*/
#include "std_globals.h"
#if 1//__XXX_xxx__
//#include "xxx_xxx.h"
//#include "xxx_xxx.h"



/*-----------------------ģ���ں궨��-------------------------*/
#define    COMM_ID_INFO_MAP_SIZE              (8)




/*----------------------ģ�����ඨ��--------------------------*/

typedef struct comm_id_info_map_t
{
	INT32_T	if_id;
	INT8_T* pif_info;
}COMM_ID_INFO_MAP_T;

/*----------------------������������--------------------------*/


COMM_ID_INFO_MAP_T comm_id_info_map[COMM_ID_INFO_MAP_SIZE]={0};
/*
1.����Ҫ����һ��ӳ����,��IF_ID��IF_INFO�Ĺ�ϵ
2.ͨ�Ž��������Ժ���Ҫ����Ҫ�����ӳ������г�ʼ��
3.��Ҫ�����ݿ��м�������˿ڵľ�����Ϣ��
4.���������˿��߳�
*/
/*****************************************************************************/
                         /* �������� */
/*****************************************************************************/

/******************************************************************************
* Function:    COMM_InterfaceRegister
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceRegister(void *p_if,INT32_T len)
{
/*
	1.��ӳ�������в�ѯ��p_if�Ƿ��Ѿ����ڣ�����Ѿ�����ֱ�Ӷ�Ӧ��id
	2.�������в����ڣ�����Ҫ��������˿���Ϣ����ѯ�Ƿ��ж�Ӧ�Ķ˿��߳�
	3.����ж˿��̣߳����������У���������Ӧ��ID������¼��ӳ�����С����سɹ���Ϣ
	4.�������˿��̲߳����ڣ��򷵻ش�����Ϣ��
*/

	printf("%s:%d\r\n",__func__,__LINE__);
	return 1;

}

/******************************************************************************
* Function:    COMM_InterfaceUnRegister
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceUnRegister(INT32_T if_id)
{
	printf("%s:%d\r\n",__func__,__LINE__);
	return 1;

}

/******************************************************************************
* Function:    COMM_InterfaceReadDat
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceReadDat(INT32_T if_id,void *pbuf,INT32_T rlen)
{
	printf("%s:%d\r\n",__func__,__LINE__);
	return 1;
}


/******************************************************************************
* Function:    COMM_InterfaceWriteDat
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T  COMM_InterfaceWriteDat(INT32_T if_id,void *pbuf,INT32_T wlen)
{
	printf("%s:%d\r\n",__func__,__LINE__);
	return 1;
}


#endif//#if __XXX_xxx__





