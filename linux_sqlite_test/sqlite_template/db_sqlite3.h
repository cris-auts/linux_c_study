/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of CRIS AUTS Inc. (C) 2012.
*
*  Copyright (C), 2010-2012, CRIS AUTS  Tech. Co., Ltd.
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
* 2012-12-15           Cris                1st                            created
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
#ifndef __DB_SQLITE3_H__
#define __DB_SQLITE3_H__
#ifdef __cplusplus
extern "C" {
#endif


/*----------------------公共头文件----------------------------*/
#include "std_globals.h"
#if __DB_SQLITE3_ENABLE__
#include "sqlite3.h"


/*----------------------接口头文件----------------------------*/
//#include "xxx_xxx.h"


/*----------------------公共宏定义----------------------------*/
//#define    xxxxxx                (xxxxxxxx)


/*----------------------公共类定义----------------------------*/


/*-----------------模块对外接口变量声明-----------------------*/
//extern    xxxxx;


/*-----------------模块对外接口函数声明-----------------------*/
//extern    xxxxx;
extern int SQLITE3_OpenDataBase(char *db_name, sqlite3 **pp_db);
extern int SQLITE3_CloseDataBase(sqlite3 *p_db);

#endif//#if __DB_SQLITE3_ENABLE__
#ifdef __cplusplus
}
#endif
#endif //#ifndef __DB_SQLITE3_H__



