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



/*-----------------------模块内宏定义-------------------------*/
#define    COMM_ID_INFO_MAP_SIZE              (8)




/*----------------------模块内类定义--------------------------*/

typedef struct comm_id_info_map_t
{
	INT32_T	if_id;
	INT8_T* pif_info;
}COMM_ID_INFO_MAP_T;

/*----------------------变量常量定义--------------------------*/


COMM_ID_INFO_MAP_T comm_id_info_map[COMM_ID_INFO_MAP_SIZE]={0};
/*
1.首先要建立一个映射表格,绑定IF_ID和IF_INFO的关系
2.通信进程启动以后，需要，需要对这个映射表格进行初始化
3.需要从数据库中加载物理端口的具体信息。
4.启动各个端口线程
*/
/*****************************************************************************/
                         /* 函数定义 */
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
	1.从映射表格表格中查询，p_if是否已经存在，如果已经存在直接对应的id
	2.如果表格中不存在，则需要按照这个端口信息，查询是否有对应的端口线程
	3.如果有端口线程，并在在运行，，则分配对应的ID，并记录到映射表格中。返回成功信息
	4.如果如果端口线程不存在，则返回错误信息。
*/

	printf("%s:%d",__func__,__LINE__);
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
	printf("%s:%d",__func__,__LINE__);
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

	printf("%s:%d",__func__,__LINE__);
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
	printf("%s:%d",__func__,__LINE__);
	return 1;

}


void Hello_Word(void)
{
	printf ("Hello,World!\r\n");
}
#endif//#if __XXX_xxx__





