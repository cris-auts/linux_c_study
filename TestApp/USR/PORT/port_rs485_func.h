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
* File name: port_rs485_func.h
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
#ifndef __PORT_RS485_H__
#define __PORT_RS485_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------公共头文件----------------------------*/
#include "std_globals.h"
#if __SYS_RS485_ENABLE__

//#include "xxx_xxx.h"


/*----------------------公共宏定义----------------------------*/
//#define    xxxxxx                (xxxxxxxx)

/*----------------------公共类定义----------------------------*/
typedef struct port_rs485_cfg_t{
	char dev_path[32];
	int band_rate;
	int flow_ctrl;
	int data_bits;
	int stop_bits;
	int parity;
}PORT_RS485_CFG_T;



/*-----------------模块对外接口变量声明-----------------------*/
//extern    xxxxx;


/*-----------------模块对外接口函数声明-----------------------*/
extern UINT32_T PORT_Rs485WrTxBuf(UINT8_T *pbuf, UINT32_T wlen);
extern UINT32_T PORT_Rs485RdRxBuf(UINT8_T *pbuf, UINT32_T rlen);
extern void* PORT_Rs485Thread(void *p_arg);

#endif//#if __SYS_RS485_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __PORT_RS485_H__





