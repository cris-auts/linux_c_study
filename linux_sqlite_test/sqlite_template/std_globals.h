/**************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of  CRIS Technologies, Inc.
* 
*  Copyright (C), 2010-2015 CRIS Technologies, Inc.
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


/*-------------------系统头文件----------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

/*-------------------公共头文件----------------*/
#include "std_config.h"
#include "std_macros.h"
#include "std_types.h"
#include "std_debug.h"
#include "std_funcs.h"

/*--------------自定义公共头文件-------------*/


/*------------------- 接口头文件----------------*/


/*----------------------公共宏定义----------------------------*/
#define SYS_HANDLE_OK					(0x00)
#define SYS_VERIFY_ERR					(0x01)
#define SYS_INVAILD_ERR					(0x02)
#define SYS_OVERTIME_ERR				(0x03)
#define SYS_UNKNOWN_ERR					(0x04)

/*----------------------公共类定义----------------------------*/


//----------------------------------------------------
typedef struct dev_prm_t
{
	DEBUG_LOG_ST_T debug_log_st;
}DEV_PRM_T;
typedef struct dev_dat_t
{
}DEV_DAT_T;
typedef struct usr_prm_t
{
}USR_PRM_T;
typedef struct usr_dat_t
{
}USR_DAT_T;

typedef struct run_prm_t
{
}RUN_PRM_T;
typedef struct run_dat_t
{
}RUN_DAT_T;


/*------------------模块对外接口变量声明-----------------------*/
//extern    xxxxx;
extern DEV_PRM_T g_dev_prm;
extern DEV_DAT_T g_dev_dat;
extern USR_PRM_T g_usr_prm;
extern USR_DAT_T g_usr_dat;
extern RUN_PRM_T g_run_prm;
extern RUN_DAT_T g_run_dat;

/*------------------模块对外接口函数声明-----------------------*/
//extern    xxxxx;





#endif//#ifndef __STD_GLOBALS_H__

