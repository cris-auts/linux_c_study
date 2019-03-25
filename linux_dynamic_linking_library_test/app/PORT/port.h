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
* File name: xxx_xxx.h
* -------------------------------------
*
* Module: all
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
* Date                Author             Change Id             Release Description Of Change
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
#ifndef __PORT_H__
#define __PORT_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------����ͷ�ļ�----------------------------*/
#include "std_globals.h"
#if 1//__XXX_xxx__

#include "port_rs485_func.h"
#include "port_rs232_func.h"


/*----------------------�����궨��----------------------------*/
#define    PORT_RS485_PATH              "/dev/ttyUSB0"
#define    PORT_RS232_PATH              "/dev/ttyUSB1"


/*----------------------�����ඨ��----------------------------*/
typedef enum port_id_t{
	PORT_RS485_1,
	PORT_RS485_2,
	PORT_RS232_1,
	PORT_RS232_2,
	PORT_ETH_1,
	PORT_ETH_2,
	PORT_GPRS_1,
	PORT_GPRS_2,
	PORT_4GLTE_1,
	PORT_4GLTE_2,
	PORT_ID_MAX
}PORT_ID_T;


typedef enum port_type_t{
	PORT_RS485,
	PORT_RS232,
	PORT_TYPE_MAX
}PORT_TYPE_T;

typedef union port_cfg_t{
	PORT_RS485_CFG_T rs485_cfg;
	PORT_RS232_CFG_T rs232_cfg;
}PORT_CFG_T;

typedef struct port_t{
	PORT_ID_T 	port_id;
	PORT_TYPE_T port_type;
	PORT_CFG_T 	port_cfg;
	UINT32_T 	(*port_write_func)(UINT8_T *pbuf, UINT32_T wlen);
	UINT32_T 	(*port_read_func) (UINT8_T *pbuf, UINT32_T rlen);
}PORT_T;


/*-----------------ģ�����ӿڱ�������-----------------------*/
//extern    xxxxx;


/*-----------------ģ�����ӿں�������-----------------------*/
//extern    xxxxx;
INT32_T PORT_CreatePortThread(PORT_ID_T port_id,PORT_TYPE_T port_type,PORT_CFG_T *p_port_cfg);
INT32_T PORT_GetPortThreadStatus(PORT_ID_T port_id);
INT32_T PORT_GetPortCfg(PORT_ID_T port_id,PORT_CFG_T *p_port_cfg);
INT32_T PORT_SetPortCfg(PORT_ID_T port_id,PORT_CFG_T *p_port_cfg);

#endif//#if __XXX_xxxx__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __PORT_H__





/*-----------------------ģ���ں궨��-------------------------*/




/*----------------------ģ�����ඨ��--------------------------*/

