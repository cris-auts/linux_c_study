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


/*----------------------公共头文件----------------------------*/
#include "std_globals.h"
#if 1//__XXX_xxx__
#include "port_rs485_func.h"
#include "port_rs232_func.h"
#include "msg.h"


/*----------------------公共宏定义----------------------------*/
#define PORT_RS232_1_PATH              "/dev/ttyUSB2"
#define PORT_RS232_2_PATH              "/dev/ttyUSB3"

#define	PORT_MULTI_CH_MAX              (8)


#define PORT_RS485_BUF_SIZE				(512)
#define PORT_RS232_BUF_SIZE				(512)
#define PORT_ETH_BUF_SIZE				(1024*2)
#define PORT_WIFI_BUF_SIZE				(1024*2)
#define PORT_GPRS_BUF_SIZE				(1024*1)
#define PORT_4GLTE_BUF_SIZE				(1024*2)


/*----------------------公共类定义----------------------------*/
typedef enum port_id_t{
	PORT_ID_RS485_1,
	PORT_ID_RS485_2,
	PORT_ID_RS232_1,
	PORT_ID_RS232_2,
	PORT_ID_ETH_1,
	PORT_ID_ETH_2,
	PORT_ID_WIFI_1,
	PORT_ID_WIFI_2,
	PORT_ID_GPRS_1,
	PORT_ID_GPRS_2,
	PORT_ID_4GLTE_1,
	PORT_ID_4GLTE_2,
	PORT_ID_MAX
}PORT_ID_T;


typedef enum port_type_t{
	PORT_TYPE_RS485,
	PORT_TYPE_RS232,
	PORT_TYPE_ETH,
	PORT_TYPE_WIFI,
	PORT_TYPE_GPRS,
	PORT_TYPE_4GLTE,
	PORT_TYPE_MAX
}PORT_TYPE_T;

#if 0
typedef struct port_dev_cfg_t{
	
}PORT_DEV_CFG_T;

typedef struct port_usr_cfg_t{
	TABLE_COMM_PRM_T comm_prm;  
}PORT_USR_CFG_T;
#else
typedef TABLE_COMM_CFG_T PORT_DEV_CFG_T;
typedef PRM_MAIN_T 		 PORT_USR_CFG_T;
#endif

typedef struct port_cfg_t{
	PORT_DEV_CFG_T dev_cfg;
	PORT_USR_CFG_T usr_cfg;
}PORT_CFG_T;

typedef struct prtc_tab_t{
	UINT8_T  valid_flg;
	UINT32_T prtc;
	UINT32_T ch_id; 
}PRTC_TAB_T;

typedef struct port_t{
	PORT_ID_T 	port_id;
	PORT_TYPE_T port_type;
	PORT_CFG_T 	port_cfg;
	PRTC_TAB_T  prtc_tab[PORT_MULTI_CH_MAX];
	UINT8_T*	p_port_rx_buf;
	UINT8_T*	p_port_tx_buf;
	UINT32_T	port_rx_bufsize;
	UINT32_T	port_tx_bufsize;
	UINT32_T 	(*port_write_func)(UINT8_T *p_buf, UINT32_T w_len);
	UINT32_T 	(*port_read_func) (UINT8_T *p_buf, UINT32_T r_len);
	pthread_t 	thread;
	pthread_attr_t 	thread_attr;
}PORT_T;


/*-----------------模块对外接口变量声明-----------------------*/
//extern    xxxxx;


/*-----------------模块对外接口函数声明-----------------------*/
//extern    xxxxx;
extern INT32_T PORT_InitPortInfo(PORT_T *p_port,UINT32_T ch_id,PORT_DEV_CFG_T *p_dev_cfg,PORT_USR_CFG_T *p_usr_cfg);
extern INT32_T PORT_CreatePortThread(PORT_T *p_port);

extern INT32_T PORT_CreatePortThread(PORT_T *p_port);
extern INT32_T PORT_DestroyPortThread(PORT_T *p_port);
extern INT32_T PORT_GetPortThreadStatus(PORT_T *p_port);

#endif//#if __XXX_xxxx__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __PORT_H__





/*-----------------------模块内宏定义-------------------------*/




/*----------------------模块内类定义--------------------------*/

