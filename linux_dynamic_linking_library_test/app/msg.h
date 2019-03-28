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




/*----------------------公共头文件----------------------------*/

#include "std_globals.h"
#include "dbase.h"



/*----------------------公共宏定义----------------------------*/

#define ID_NUM_MAX 20

#define UVAL_USELESS 0XFFFF
#define SVAL_USELESS (-1)


#define DL698_BUFF_SIZE 4096
#define MAINT_BUFF_SIZE 1024

#define PRTC_BUFF_SIZE_MIN 500





/*-----------------模块对外接口变量声明-----------------------*/
extern UINT32_T comm_prm_num;                      //通信参数条目

//主线程传递参数
typedef struct prm_main
{
	TABLE_COMM_PRM_T comm_prm;
	UINT8_T * commdata_space;    //通信数据空间
	UINT8_T * prtc_buff_space;   //规约缓存空间
	pthread_t thread_sever;      //单模式使用/混合模式下服务器模式
}PRM_MAIN_T,*pM_MAIN_T;


typedef struct user_comm_prm_t
{
	UINT8_T   slaver_run_mode;       //分解后运行模式
	UINT8_T   slaver_run_ip_index;   //分解后运行ip索引
	PRM_MAIN_T comm_prm_info;
}USER_COMM_PRM_T,*pUSER_COMM_PRM_T;


//参数映射表
typedef struct map_list_prm
{
	INT32_T   comm_id;               //通信id
	UINT8_T   status;
	UINT32_T  buff_size;
	UINT8_T * buff_rx;
	UINT32_T  buff_rx_len;
	UINT8_T * buff_tx;
	UINT32_T  buff_tx_len;
	USER_COMM_PRM_T user_comm_prm;
}MAP_LIST_PRM_T,*pMAP_LIST_PRM_T;



//参数映射表控制器
typedef struct map_list_ctrl
{
	INT32_T   prm_master_id;         //参数主id
	UINT32_T  prm_map_list_num;      //引射表参数数目
	MAP_LIST_PRM_T * prm_map_list;   //映射表地址
}MAP_LIST_CTRL_T,*pMAP_LIST_CTRL_T;



/*-----------------模块对外接口函数声明-----------------------*/


extern MAP_LIST_PRM_T g_prm_map_list[ID_NUM_MAX];	
extern UINT32_T Main_FindID_Map(unsigned int s_id);


#endif


