/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of  WAN XING Tech. Co., Ltd.(C) 2012.
*
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
*********************************************************************************************************
*
* File name: app_modbus_task.c
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
#if __SYS_MODBUS_ENABLE__
//#include "xxx_xxx.h"
//#include "xxx_xxx.h"



/*-----------------------ģ���ں궨��-------------------------*/
//#define    xxxxxx              (xxxxxxxx)



/*----------------------ģ�����ඨ��--------------------------*/



/*----------------------������������--------------------------*/




/*****************************************************************************/
                         /* �������� */
/*****************************************************************************/

/******************************************************************************
* Function:    XXX_XxxXxx
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
void* APP_ModbusTask(void *p_arg)
{
	while (1)
	{
		MODBUS_PrintLog("Hello,APP_ModbusTask!\r\n");
		sleep(1);
	}
	return NULL;
}

#endif//#if __SYS_MODBUS_ENABLE__



