/**************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of WAN XING Tech. Co., Ltd.(C) 2020.
* 
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
***************************************************************************************************
*
* File name: std_globals.h
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
* Description:  This file defines most customer 's  global variables for 
*                    the project.
* -----------------------------------------------------------------------------
*
* History:
*
* Date                Author             Change Id             Release Description Of Change 
* ---------------------------------------------------------------------------------------
* 2012-12-15           Cris                1st                            created
* ---------------------------------------------------------------------------------------
*
* ---------------------------------------------------------------------------------------
*
**************************************************************************************************/

#ifndef __STD_GLOBALS_H__
#define __STD_GLOBALS_H__


/*-------------------ϵͳͷ�ļ�----------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>      /*�ļ����ƶ���*/  
#include <termios.h>    /*PPSIX �ն˿��ƶ���*/  
#include <errno.h>      /*����Ŷ���*/  
#include <sys/types.h>   
#include <sys/stat.h>     


/*-------------------����ͷ�ļ�----------------*/
#include "std_config.h"
#include "std_macros.h"
#include "std_types.h"
#include "std_funcs.h"
#include "std_debug.h"

/*--------------�Զ��幫��ͷ�ļ�-------------*/


/*------------------- �ӿ�ͷ�ļ�----------------*/


/*----------------------�����궨��----------------------------*/
#define SYS_HANDLE_OK					(0x00)
#define SYS_VERIFY_ERR					(0x01)
#define SYS_INVAILD_ERR					(0x02)
#define SYS_OVERTIME_ERR				(0x03)
#define SYS_UNKNOWN_ERR					(0x04)

/*----------------------�����ඨ��----------------------------*/

typedef struct dev_prm_nvram_t
{
    UINT16_T cs;
	DEBUG_LOG_ST_T debug_log_st;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}DEV_PRM_NVRAM_T;
typedef struct dev_prm_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}DEV_PRM_GPRAM_T;
typedef struct dev_dat_nvram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}DEV_DAT_NVRAM_T;
typedef struct dev_dat_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}DEV_DAT_GPRAM_T;


typedef struct usr_prm_nvram_t
{
    UINT16_T cs;
	
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}USR_PRM_NVRAM_T;
typedef struct usr_prm_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}USR_PRM_GPRAM_T;

typedef struct usr_dat_nvram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}USR_DAT_NVRAM_T;
typedef struct usr_dat_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}USR_DAT_GPRAM_T;


typedef struct run_prm_nvram_t
{
    UINT16_T cs;
	
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}RUN_PRM_NVRAM_T;
typedef struct run_prm_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}RUN_PRM_GPRAM_T;
typedef struct run_dat_nvram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}RUN_DAT_NVRAM_T;
typedef struct run_dat_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//У��洢��Ԥ���������ֽ���
}RUN_DAT_GPRAM_T;

//----------------------------------------------------
typedef struct dev_prm_t
{
    DEV_PRM_NVRAM_T nvram;
    DEV_PRM_GPRAM_T gpram;
}DEV_PRM_T;
typedef struct dev_dat_t
{
    DEV_DAT_NVRAM_T nvram;
    DEV_DAT_GPRAM_T gpram;
}DEV_DAT_T;


typedef struct usr_prm_t
{
    USR_PRM_NVRAM_T nvram;
    USR_PRM_GPRAM_T gpram;
}USR_PRM_T;
typedef struct usr_dat_t
{
    USR_DAT_NVRAM_T nvram;
    USR_DAT_GPRAM_T gpram;
}USR_DAT_T;

typedef struct run_prm_t
{
    RUN_PRM_NVRAM_T nvram;
    RUN_PRM_GPRAM_T gpram;
}RUN_PRM_T;
typedef struct run_dat_t
{
    RUN_DAT_NVRAM_T nvram;
    RUN_DAT_GPRAM_T gpram;
}RUN_DAT_T;


/*------------------ģ�����ӿڱ�������-----------------------*/
//extern    xxxxx;
extern DEV_PRM_T g_dev_prm;
extern DEV_DAT_T g_dev_dat;
extern USR_PRM_T g_usr_prm;
extern USR_DAT_T g_usr_dat;
extern RUN_PRM_T g_run_prm;
extern RUN_DAT_T g_run_dat;

/*------------------ģ�����ӿں�������-----------------------*/
//extern    xxxxx;





#endif//#ifndef __STD_GLOBALS_H__

