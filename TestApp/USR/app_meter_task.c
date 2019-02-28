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
#define    PORT_RS485_PATH              "/dev/ttyUSB0"
#define    PORT_RS232_PATH              "/dev/ttyUSB1"




/*----------------------ģ�����ඨ��--------------------------*/
typedef enum port_type_t{
	PORT_RS485,
	PORT_RS232,
	PORT_MAX
}PORT_TYPE_T;

typedef union port_cfg_t{
	PORT_RS485_CFG_T rs485_cfg;
	PORT_RS232_CFG_T rs232_cfg;
}PORT_CFG_T;

typedef struct port_t{
	int port_type;
	PORT_CFG_T port_cfg;
	int (*port_write_func)(char *wr_buf,int wr_len);
	int (*port_read_func) (char *rd_buf,int rd_len);
}PORT_T;


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
	
	int i=0;
	int rcv_len=0;
	int	snd_len=0;
	char rcv_buf[512];
	char snd_buf[512];
	
	APP_MeterThreadInit();
	
	for(i=0;i<256;i++)
		snd_buf[i]=i;
	snd_len=256;
	sleep(1);
	while (1)
	{
		//METER_PrintLog("Hello,APP_MeterThread!\r\n");
		snd_len=PORT_Rs485WrTxBuf(snd_buf,256);
		if(snd_len)
		{
			METER_PrintLog("Snd New Dat:%d\r\n",snd_len);
			METER_PrintHex(snd_buf,snd_len);
		}
		rcv_len=PORT_Rs485RdRxBuf(rcv_buf,512);
		if(rcv_len)
		{
			METER_PrintLog("Rcv New Dat:%d\r\n",rcv_len);
			METER_PrintHex(rcv_buf,rcv_len);
		}
	}
	return NULL;
}

#endif//#if __SYS_METER_ENABLE__




