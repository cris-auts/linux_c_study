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
* File name: db.c
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
* Description:  database wrapper api defines.
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
/*-----------------------公共头文件---------------------------*/
#include "std_globals.h"
#if __SYS_DBASE_ENABLE__
#if __DBASE_SQLITE3_ENABLE__
#include "db_sqlite3.h"
#endif


/*-----------------------接口头文件---------------------------*/
//#include "xxx_xxx.h"

/*----------------------本模块头文件--------------------------*/
//#include "xxx_xxx.h"

/*----------------------模块内宏定义--------------------------*/
//#define    xxxxxx                (xxxxxxxx)

#if __XXXX_XXXX_DEBUG_ENABLE__
#define XXXX_PrintLog(format,...) \
LOG_Print("XXXX[%s:%d]:"format"\r\n",__FUNCTION__, __LINE__,##__VA_ARGS__)
#else
#define XXXX_PrintLog(format,...)
#endif



/*----------------------模块内类定义--------------------------*/


/*----------------------全局变量常量--------------------------*/


/*----------------------内部静态变量--------------------------*/


/*----------------------内部静态函数--------------------------*/


/*****************************************************************************/
                         /* 函数定义 */
/*****************************************************************************/

/******************************************************************************
* Function:    DB_OpenDataBase
* Input:       db_name:
* Output:      pp_db:返回一个用于其他 SQLite 程序的数据库连接对象
* Return:      xxx
* Description: xxxxx
*db_name:	数据库文件名称
*pp_db:		返回一个用于其他 SQLite 程序的数据库连接对象
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2012-12-15    Cris          1st                    created
*
*
******************************************************************************/
int DB_OpenDataBase(char *db_name, sqlite3 **pp_db)
{
	return SQLITE3_OpenDataBase(db_name,pp_db);
}


/******************************************************************************
* Function:    DB_CloseDataBase
* Input:       
* Output:      
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2012-12-15    Cris          1st                    created
*
*
******************************************************************************/
int DB_CloseDataBase(sqlite3 *p_db)
{
	return SQLITE3_CloseDataBase(p_db);
}




#endif//#if __SYS_DBASE_ENABLE__


