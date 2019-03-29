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
* File name: app_monitor_master_station.h
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


#ifndef __MAIN_H__
#define __MAIN_H__




/*----------------------����ͷ�ļ�----------------------------*/

#include "std_globals.h"
#include "dbase.h"



/*----------------------�����궨��----------------------------*/

#define ID_NUM_MAX 20

#define UVAL_USELESS 0XFFFF
#define SVAL_USELESS (-1)


#define DL698_BUFF_SIZE 4096
#define MAINT_BUFF_SIZE 1024

#define PRTC_BUFF_SIZE_MIN 500





/*-----------------ģ�����ӿڱ�������-----------------------*/
extern UINT32_T comm_prm_num;                      //ͨ�Ų�����Ŀ

//���̴߳��ݲ���
typedef struct prm_main
{
	UINT8_T   slaver_run_mode;       //�ֽ������ģʽ
	UINT8_T   slaver_run_ip_index;   //�ֽ������ip����
	TABLE_COMM_PRM_T comm_prm;
}PRM_MAIN_T,*pM_MAIN_T;


typedef struct user_comm_prm_t
{
	PRM_MAIN_T comm_prm_info;
	UINT8_T * commdata_space;    //ͨ�����ݿռ�
	UINT8_T * prtc_buff_space;   //��Լ����ռ�
	pthread_t thread_sever;      //��ģʽʹ��/���ģʽ�·�����ģʽ
}USER_COMM_PRM_T,*pUSER_COMM_PRM_T;


//����ӳ���
typedef struct map_list_prm
{
	INT32_T   comm_id;               //ͨ��id
	UINT8_T   status;
	UINT32_T  buff_size;
	UINT8_T * buff_rx;
	UINT32_T  buff_rx_len;
	UINT8_T * buff_tx;
	UINT32_T  buff_tx_len;
	USER_COMM_PRM_T user_comm_prm;
}MAP_LIST_PRM_T,*pMAP_LIST_PRM_T;



//����ӳ��������
typedef struct map_list_ctrl
{
	INT32_T   prm_master_id;         //������id
	UINT32_T  prm_map_list_num;      //����������Ŀ
	MAP_LIST_PRM_T * prm_map_list;   //ӳ����ַ
}MAP_LIST_CTRL_T,*pMAP_LIST_CTRL_T;



/*-----------------ģ�����ӿں�������-----------------------*/


extern MAP_LIST_PRM_T g_prm_map_list[ID_NUM_MAX];	
extern UINT32_T Main_FindID_Map(unsigned int s_id);


#endif


