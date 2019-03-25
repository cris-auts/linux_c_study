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
* File name: xxx_xxx.c
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
#if __XXX_xxx__
//#include "xxx_xxx.h"
//#include "xxx_xxx.h"



/*-----------------------模块内宏定义-------------------------*/
//#define    xxxxxx              (xxxxxxxx)



/*----------------------模块内类定义--------------------------*/



/*----------------------变量常量定义--------------------------*/




/*****************************************************************************/
                         /* 函数定义 */
/*****************************************************************************/

/******************************************************************************
* Function:    PORT_CreatePortThread
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
SINT32_T PORT_CreatePortThread(PORT_ID_T port_id,PORT_TYPE_T port_type,PORT_CFG_T *p_port_cfg)
{
	static pthread_t thread_port_rs485;
	static pthread_attr_t pthread_port_rs485_attr;
	static PORT_T port_rs485;

	
	static pthread_t thread_port_rs232;
	static pthread_attr_t pthread_port_rs232_attr;
	static PORT_T port_rs232;
	
	int rc = 0;

	port_rs485.port_type = PORT_RS485;
	port_rs485.port_cfg.rs485_cfg.band_rate = 9600;
	port_rs485.port_cfg.rs485_cfg.flow_ctrl = 0;
	port_rs485.port_cfg.rs485_cfg.data_bits = 8;
	port_rs485.port_cfg.rs485_cfg.stop_bits = 1;
	port_rs485.port_cfg.rs485_cfg.parity = 'N';
	memcpy(port_rs485.port_cfg.rs485_cfg.dev_path,PORT_RS485_PATH,sizeof(PORT_RS485_PATH));
	port_rs485.port_write_func = PORT_Rs485WrTxBuf;
	port_rs485.port_read_func  = PORT_Rs485RdRxBuf;

	rc=pthread_create(&thread_port_rs485,&pthread_port_rs485_attr,PORT_Rs485Thread,&(port_rs485.port_cfg.rs485_cfg));
	if(rc != 0)
	{
		pthread_detach(thread_port_rs485);
		METER_PrintLog("create port RS485 thread failed!\r\n");
	}
	else
		METER_PrintLog("Create port RS485 thread successfully\r\n");

	port_rs232.port_type = PORT_RS232;
	port_rs232.port_cfg.rs232_cfg.band_rate = 115200;
	port_rs232.port_cfg.rs232_cfg.flow_ctrl = 0;
	port_rs232.port_cfg.rs232_cfg.data_bits = 8;
	port_rs232.port_cfg.rs232_cfg.stop_bits = 1;
	port_rs232.port_cfg.rs232_cfg.parity = 'N';
	memcpy(port_rs232.port_cfg.rs232_cfg.dev_path,PORT_RS232_PATH,sizeof(PORT_RS232_PATH));
	port_rs232.port_write_func = PORT_Rs232WrTxBuf;
	port_rs232.port_read_func  = PORT_Rs232RdRxBuf;
	rc=pthread_create(&thread_port_rs232,&pthread_port_rs232_attr,PORT_Rs232Thread,&port_rs232.port_cfg.rs232_cfg);
	if(rc != 0)
	{
		pthread_detach(thread_port_rs232);
		METER_PrintLog("create port RS232 thread failed!\r\n");
	}
	else
		METER_PrintLog("Create port RS232 thread successfully\r\n");

}




/******************************************************************************
* Function:    PORT_GetPortThreadStatus
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
SINT32_T PORT_GetPortThreadStatus(PORT_ID_T port_id)
{


}


/******************************************************************************
* Function:    PORT_GetPortCfg
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
SINT32_T PORT_GetPortCfg(PORT_ID_T port_id,PORT_CFG_T *p_port_cfg)
{


}

/******************************************************************************
* Function:    PORT_SetPortCfg
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
SINT32_T PORT_SetPortCfg(PORT_ID_T port_id,PORT_CFG_T *p_port_cfg)
{


}

#endif//#if __XXX_xxx__




