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
#if 1//__XXX_xxx__
#include "port.h"
//#include "xxx_xxx.h"



/*-----------------------模块内宏定义-------------------------*/
//#define    xxxxxx              (xxxxxxxx)



/*----------------------模块内类定义--------------------------*/



/*----------------------变量常量定义--------------------------*/




/*****************************************************************************/
                         /* 函数定义 */
/*****************************************************************************/
/******************************************************************************
* Function:    PORT_InitPortInfo
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T PORT_InitPortInfo(PORT_T *p_port,UINT32_T ch_id,PORT_DEV_CFG_T *p_dev_cfg,PORT_USR_CFG_T *p_usr_cfg)
{
	INT32_T err=0;
	//INT32_T ret=0;

	switch (p_usr_cfg->comm_prm.comm_port)
		{
			case COMM_RS485_1:
				p_port->port_id=PORT_ID_RS485_1;
				p_port->port_type=PORT_TYPE_RS485;
				memcpy(&(p_port->port_cfg.dev_cfg),p_dev_cfg,sizeof(PORT_DEV_CFG_T));
				memcpy(&(p_port->port_cfg.usr_cfg),p_usr_cfg,sizeof(PORT_USR_CFG_T));
				memset(p_port->prtc_tab,0,PORT_MULTI_CH_MAX);
				p_port->prtc_tab[0].ch_id=ch_id;
				p_port->prtc_tab[0].prtc=p_usr_cfg->comm_prm.prtc_type;
				p_port->prtc_tab[0].valid_flg=VALID_FLG;
		
				p_port->p_port_rx_buf = malloc(PORT_RS485_BUF_SIZE);
				if(p_port->p_port_rx_buf == NULL)
				{
					err=-1;
					p_port->port_rx_bufsize=0;
				}
				else
					p_port->port_rx_bufsize=PORT_RS485_BUF_SIZE;
				
				p_port->p_port_tx_buf = malloc(PORT_RS485_BUF_SIZE);
				if(p_port->p_port_tx_buf == NULL)
				{
					err=-1;
					p_port->port_tx_bufsize=0;
				}
				else
					p_port->port_tx_bufsize=PORT_RS485_BUF_SIZE;
				break;

			
			case COMM_RS485_2:

				break;
				
			case COMM_RS232_1:

				break;
				
			case COMM_RS232_2:

				break;

			case COMM_ETH_1:

				break;
				
			case COMM_ETH_2:

				break;
				
			case COMM_WIFI_1:
				break;

			
			case COMM_GPRS_1:

				break;

			default:
				err=-1;
				break;
		}

	return err;
}

/******************************************************************************
* Function:    PORT_CreatePortThread
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
INT32_T PORT_CreatePortThread(PORT_T *p_port)
{
#if 0
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
	printf("%s:%ld\r\n",__func__,__LINE__);

	rc=pthread_create(&thread_port_rs485,&pthread_port_rs485_attr,PORT_Rs485Thread,&(port_rs485.port_cfg.rs485_cfg));
	if(rc != 0)
	{
		pthread_detach(thread_port_rs485);
		p_tid=thread_port_rs485;
		METER_PrintLog("create port RS485 thread failed!\r\n");
	}
	else
		METER_PrintLog("Create port RS485 thread successfully\r\n");
#endif
	return 0;
}

INT32_T PORT_DestroyPortThread(PORT_T *p_port)
{
	return 0;
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
INT32_T PORT_GetPortThreadStatus(PORT_T *p_port)
{
	SINT_T err = pthread_kill(p_port->thread,0);
	
	if(err == ESRCH){
		printf("the specified thread did not exists or already quit/n");
		return 0;
	}
	else if(err == EINVAL)
	{
		printf("signal is invalid/n");
		return 0;

	}
	else
		printf("threadis alive/n");
	
	return 1;
}

#endif//#if __XXX_xxx__




