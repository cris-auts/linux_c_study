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
* File name: std_funcs.h
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
* Description:  This file declares cstd debug interfaces.
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

#ifndef __STD_FUNCS_H__
#define __STD_FUNCS_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "std_globals.h"
#if __STD_FUNCS_ENABLE__
/*---------------------------------接口头文件--------------------------------*/
//#include "xxx_xxx.h"



/*---------------------------------模块宏定义--------------------------------*/
#if __SYS_PRINT_ENABLE__
#define MyPrintLog(format,args...) \
DEBUG_Print("[cris-log][%s:%d]:"format"\r\n",__FUNCTION__, __LINE__,##args)
#else
#define MyPrintLog(format,...)
#endif

#if __SYS_PRINT_ENABLE__
#define PrintLog(format,args...) \
DEBUG_Print(format,##args)
#else
#define PrintLog(format,...)
#endif


#if __SYS_PRINT_ENABLE__
#define PrintHex(pdat,len) \
DEBUG_PrintHex(pdat,len)
#else
#define PrintHex(pdat,len)
#endif


#if __SYS_PRINT_ENABLE__
#define PrintChar(pdat,len) \
DEBUG_PrintChar(pdat,Len)
#else
#define PrintChar(pdat,len)
#endif


#if __SYS_PRINT_ENABLE__
#if __DRV_PRINT_ENABLE__
#define DRV_Printlog(fmt,arg...)          do{\
	if(drv_print_enable)\
	PrintLog("[DRV][%s:%d]"fmt"\n",__func__, __LINE__, ##arg);\
}while(0)
#else
#define DRV_DEBUG(fmt,arg...)
#endif

#if __APP_PRINT_ENABLE__
#define APP_Printlog(fmt,arg...)          do{\
	if(drv_print_enable)\
	PrintLog("[APP][%s:%d]"fmt"\n",__func__, __LINE__, ##arg);\
}while(0)
#else
#define DRV_DEBUG(fmt,arg...)
#endif
#endif


/*---------------------------------模块类定义--------------------------------*/



/*-------------------------------变量常量声明-------------------------------*/
//extern    xxxxx;



/*-------------------------------函数接口声明-------------------------------*/
extern void DEBUG_Print(char * format,...);
extern void DEBUG_PrintHex(unsigned char *pdat,unsigned int dat_len);
extern void DEBUG_PrintChar(unsigned char *pdat,unsigned int dat_len);



#endif//#if __STD_FUNCS_ENABLE__


#ifdef __cplusplus
}
#endif
#endif //#ifndef __STD_FUNCS_H__






