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
* File name: std_funcs.c
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
* Description:  This file defines cstd debug functions.
* 
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
#if __STD_FUNCS_ENABLE__

/*-----------------------接口头文件---------------------------*/
//#include "xxx_xxx.h"

/*----------------------本模块头文件--------------------------*/
//#include "xxx_xxx.h"

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






#endif//#if __STD_FUNCS_ENABLE__

