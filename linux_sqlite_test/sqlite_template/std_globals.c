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
* File name: std_globals.c
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
#include "std_globals.h"
/*---------------------------------接口头文件--------------------------------*/
//#include "xxx_xxx.h"



/*--------------------------------模块内宏定义-------------------------------*/
//#define    xxxxxx                (xxxxxxxx)



/*--------------------------------模块内类定义-------------------------------*/



/*--------------------------------变量常量定义-------------------------------*/
#if __SYS_PRINT_ENABLE__
#if __DRV_PRINT_ENABLE__
int drv_print_enable = TRUE;
#endif

#if __APP_PRINT_ENABLE__
int app_print_enable = TRUE;
#endif
#endif

DEV_PRM_T dev_prm;
DEV_DAT_T dev_dat;
USR_PRM_T usr_prm;
USR_DAT_T usr_dat;
RUN_PRM_T run_prm;
RUN_DAT_T run_dat;

/*--------------------------------静态函数声明--------------------------------*/




/*************************************************************************************************/
                                   /* 函数定义 */
/*************************************************************************************************/

/******************************************************************************
* Function:    GetDatCheckSum
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2012-12-15    Cris          1st                    created
*
*
******************************************************************************/
UINT16_T GetDatCheckSum(UINT8_T* pdat,UINT16_T len)
{
	UINT16_T i;
	UINT16_T cs=0;

	for(i=0; i<len; i++)
	{
		cs += pdat[i];
	}
	return(cs);
}

/******************************************************************************
* Function:    GetDatKeyCheckSum
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2012-12-15    Cris          1st                    created
*
*
******************************************************************************/
UINT16_T GetDatKeyCheckSum(UINT16_T cs_key,UINT8_T* pdat,UINT16_T len)
{
	UINT16_T i;

	for(i=0; i<len; i++)
	{
		cs_key += pdat[i];
	}
	return(cs_key);
}








































