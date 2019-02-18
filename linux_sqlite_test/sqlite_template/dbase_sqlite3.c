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
* File name: db_sqlite3.c
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
#if __DBASE_SQLITE3_ENABLE__

/*-----------------------接口头文件---------------------------*/
//#include "xxx_xxx.h"

/*----------------------本模块头文件--------------------------*/
#include "dbase_sqlite3.h"

/*----------------------模块内宏定义--------------------------*/
//#define    xxxxxx                (xxxxxxxx)




/*----------------------模块内类定义--------------------------*/


/*----------------------全局变量常量--------------------------*/


/*----------------------内部静态变量--------------------------*/


/*----------------------内部静态函数--------------------------*/


/*****************************************************************************/
                         /* 函数定义 */
/*****************************************************************************/

/******************************************************************************
* Function:    XXX_XxxXxx
* Input:       xxx
* Output:      xxx
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
/******************************************************************************
* Function:    SQLITE3_OpenDataBase
* Input:	   db_name:
* Output:	   pp_db:返回一个用于其他 SQLite 程序的数据库连接对象
* Return:	   xxx
* Description: xxxxx
*db_name:	数据库文件名称
*pp_db: 	返回一个用于其他 SQLite 程序的数据库连接对象
* Others:
*
* -------------------------------------------------------------------
* History:
*	  Date		   Author	  Change Id 	Release Description Of Change
* 2012-12-15	Cris		  1st					 created
*
*
******************************************************************************/
int SQLITE3_OpenDataBase(char *db_name, sqlite3 **pp_db)
{
	int rc = sqlite3_open(db_name,pp_db); //打开数据库
	if(rc != SQLITE_OK)
	{
		printf("sqlite3_open failed!\r\n");
		return 1;
	}
	else
		return 0;
}



/******************************************************************************
* Function:    SQLITE3_CloseDataBase
* Input:	   
* Output:	  
* Return:	   xxx
* Description: xxxxx
* 
* Others:
*
* -------------------------------------------------------------------
* History:
*	  Date		   Author	  Change Id 	Release Description Of Change
* 2012-12-15	Cris		  1st					 created
*
*
******************************************************************************/
int SQLITE3_CloseDataBase(sqlite3 *p_db)
{
	int rc = sqlite3_close(p_db); //打开数据库
	if(rc != SQLITE_OK)
	{
		printf("sqlite3_close failed!\r\n");
		return 1;
	}
	else
		return 0;
}



#endif//#if __DBASE_SQLITE3_ENABLE__

