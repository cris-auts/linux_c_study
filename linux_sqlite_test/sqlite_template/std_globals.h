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
#if __SYS_OS_POS__
#include "pos_core.h"
#endif
#if __SYS_NVRAM_SUPPORT__
#include "mdw_nvram.h"
#endif


/*------------------- 接口头文件----------------*/




/*----------------------公共宏定义----------------------------*/
#define SPI_FLASH_START_ADDR	(0x00000000UL)

#define SPI_FLASH_NVRAM_START_ADDR		(SPI_FLASH_START_ADDR)
#define SPI_FLASH_NVRAM_SIZE			(0x01000000UL)
#define SPI_FLASH_NVRAM_END_ADDR		(SPI_FLASH_NVRAM_START_ADDR+SPI_FLASH_NVRAM_SIZE)

#define SPI_FLASH_FATFS_START_ADDR		(SPI_FLASH_NVRAM_END_ADDR)
#define SPI_FLASH_FATFS_SIZE			(0x001000000UL)
#define SPI_FLASH_FATFS_END_ADDR		(SPI_FLASH_FATFS_START_ADDR+SPI_FLASH_FATFS_SIZE)


#define NV_RAM_RSV_SIZE			(32)
#define GP_RAM_RSV_SIZE			(32)

/*----------------------公共类定义----------------------------*/

typedef struct usr_run_prm_nvram_t
{
    UINT16_T cs;
	UINT32_T lpm_rprt_cyc;		//低功耗模式上报周期（单位：ms）
	UINT32_T nrm_rprt_cyc;		//正常模式上报周期（单位：ms）
    UINT16_T rprt_times;		//上报重发次数
	UINT16_T led_on_time;		//告警LED灯点亮时间(ms)
	UINT16_T led_on_cyc;		//告警LED灯点亮周期(ms)
	INT16U	RunLpModeDelay;		//低功耗与取电切换延时窗口时间(ms)
	INT16U	LpmRfWakeCyc;		//低功耗模式无线唤醒周期(ms)
	INT16U	LbStaUpTime;		//录波起始时间(ms)
	INT16U	LbWaveNum;			//录波周期数目
	INT16U	LbAdFreq;			//录波采样频率
	INT16U	PowOnFgTime;		//上电复归时间
}USR_RUN_PRM_NVRAM_T;






//----------------------------------------------------
typedef struct dev_prm_nvram_t
{
	DEV_CALIB_PRM_NVRAM_T calib_prm;
	DEV_COMM_PRM_NVRAM_T  comm_prm;
}DEV_PRM_NVRAM_T;
typedef struct dev_prm_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//校验存储区预留变量总字节数
}DEV_PRM_GPRAM_T;


typedef struct dev_dat_nvram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//校验存储区预留变量总字节数
}DEV_DAT_NVRAM_T;
typedef struct dev_dat_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//校验存储区预留变量总字节数
}DEV_DAT_GPRAM_T;


typedef struct usr_prm_nvram_t
{
    UINT16_T cs;
	
    UINT8_T  rsv[8];		//校验存储区预留变量总字节数
}USR_PRM_NVRAM_T;
typedef struct usr_prm_gpram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//校验存储区预留变量总字节数
}USR_PRM_GPRAM_T;

typedef struct usr_dat_nvram_t
{
    UINT16_T cs;
    UINT8_T  rsv[8];		//校验存储区预留变量总字节数
}USR_DAT_NVRAM_T;
typedef struct usr_dat_gpram_t
{
    UINT16_T cs;
	USR_DAT_GP_EVT_T evt;
    UINT8_T  rsv[8];		//校验存储区预留变量总字节数
}USR_DAT_GPRAM_T;
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
    //USR_PRM_NVRAM_T nvram;
   // USR_PRM_GPRAM_T gpram;
}RUN_PRM_T;
typedef struct run_dat_t
{
   // USR_DAT_NVRAM_T nvram;
    //USR_DAT_GPRAM_T gpram;
}RUN_DAT_T;


/*------------------模块对外接口变量声明-----------------------*/
//extern    xxxxx;
#if __DRV_PRINT_ENABLE__
extern int drv_print_enable;
#endif

#if __APP_PRINT_ENABLE__
extern int app_print_enable;
#endif
extern DEV_PRM_T dev_prm;
extern DEV_DAT_T dev_dat;
extern USR_PRM_T usr_prm;
extern USR_DAT_T usr_dat;

/*------------------模块对外接口函数声明-----------------------*/
//extern    xxxxx;
extern UINT16_T GetDatCheckSum(UINT8_T* pdat,UINT16_T len);
extern UINT16_T GetDatKeyCheckSum(UINT16_T cs_key,UINT8_T* pdat,UINT16_T len);





#endif//#ifndef __STD_GLOBALS_H__

