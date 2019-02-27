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
* File name: app_meter_task.c
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
#if __SYS_METER_ENABLE__
#include "app_meter_task.h"
#include "port_rs485_func.h"
#include "port_rs232_func.h"


/*-----------------------ģ���ں궨��-------------------------*/
#define    PORT_RS485_PATH              "/dev/ttyUSB1"
#define    PORT_RS232_PATH              "/dev/ttyUSB0"




/*----------------------ģ�����ඨ��--------------------------*/
typedef enum port_type_t{
	PORT_RS485,
	PORT_RS232,
	PORT_MAX
}PORT_TYPE_T;


typedef struct port_cfg_t{
	int port_type;
	union
	{
		PORT_RS485_CFG_T rs485_cfg;
		PORT_RS232_CFG_T rs232_cfg;
	};
}PORT_CFG_T;


/*----------------------������������--------------------------*/

METER_T meter;



/*****************************************************************************/
                         /* �������� */
/*****************************************************************************/
/******************************************************************************
* Function:    APP_MeterThreadInit
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
void APP_MeterThreadInit(void)
{
	/*
		1.�����ݿ��ж������������¹ҵĶ˿ںͱ���
		2.��ʼ�������˿ڣ������������˿ڵ��߳�
		3.���ݱ������Ͷ�Ӧ�Ķ˿ڣ�������Ӧ��
	*/
	static pthread_t thread_port_rs485;
	static pthread_attr_t pthread_port_rs485_attr;
	static PORT_CFG_T port_rs485_cfg;

	
	static pthread_t thread_port_rs232;
	static pthread_attr_t pthread_port_rs232_attr;
	static PORT_CFG_T port_rs232_cfg;
	
	int rc = 0;

	port_rs485_cfg.port_type = PORT_RS485;
	port_rs485_cfg.rs485_cfg.band_rate = 9600;
	port_rs485_cfg.rs485_cfg.flow_ctrl = 0;
	port_rs485_cfg.rs485_cfg.data_bits = 8;
	port_rs485_cfg.rs485_cfg.stop_bits = 1;
	port_rs485_cfg.rs485_cfg.parity = 'N';
	memcpy(port_rs485_cfg.rs485_cfg.dev_path,PORT_RS485_PATH,sizeof(PORT_RS485_PATH));
	rc=pthread_create(&thread_port_rs485,&pthread_port_rs485_attr,PORT_Rs485Thread,&(port_rs485_cfg.rs485_cfg));
	if(rc != 0)
	{
		pthread_detach(thread_port_rs485);
		METER_PrintLog("create port RS485 thread failed!\r\n");
	}
	else
		METER_PrintLog("Create port RS485 thread successfully\r\n");


	port_rs232_cfg.port_type = PORT_RS232;
	port_rs232_cfg.rs232_cfg.band_rate = 115200;
	port_rs232_cfg.rs232_cfg.flow_ctrl = 0;
	port_rs232_cfg.rs232_cfg.data_bits = 8;
	port_rs232_cfg.rs232_cfg.stop_bits = 1;
	port_rs232_cfg.rs232_cfg.parity = 'N';
	memcpy(port_rs232_cfg.rs232_cfg.dev_path,PORT_RS232_PATH,sizeof(PORT_RS232_PATH));
	rc=pthread_create(&thread_port_rs232,&pthread_port_rs232_attr,PORT_Rs232Thread,&port_rs232_cfg.rs232_cfg);
	if(rc != 0)
	{
		pthread_detach(thread_port_rs232);
		METER_PrintLog("create port RS232 thread failed!\r\n");
	}
	else
		METER_PrintLog("Create port RS232 thread successfully\r\n");


	
}



/******************************************************************************
* Function:    APP_MeterThread
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
void* APP_MeterThread(void *p_arg)
{
	APP_MeterThreadInit();
	while (1)
	{
		METER_PrintLog("Hello,APP_MeterThread!\r\n");
		sleep(1);
	}
	return NULL;
}

#endif//#if __SYS_METER_ENABLE__




