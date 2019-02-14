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
* File name: std_debug.h
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

#ifndef __STD_DEBUG_H__
#define __STD_DEBUG_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "std_globals.h"
#if __SYS_DEBUG_SUPPORT__
/*---------------------------------接口头文件--------------------------------*/
//#include "xxx_xxx.h"

#define SYS_HANDLE_OK					(0x00)
#define SYS_VERIFY_ERR					(0x01)
#define SYS_INVAILD_ERR					(0x02)
#define SYS_OVERTIME_ERR				(0x03)
#define SYS_UNKNOWN_ERR					(0x04)


/*---------------------------------模块宏定义--------------------------------*/
#if __SYS_PRINT_ENABLE__
#define MyPrintLog(format,args...) 	DEBUG_Print("[cris-log][%s:%d]:"format"\r\n",__FUNCTION__, __LINE__,##args)
#define PrintLog(format,args...)	DEBUG_Print(format,##args)
#define PrintHex(pdat,len)			DEBUG_PrintHex(pdat,len)
#define PrintChar(pdat,len)			DEBUG_PrintChar(pdat,len)
#define DRV_PrintLog(fmt,arg...)          do{\
	if(drv_print_enable)\
	PrintLog("[DRV][%s:%d]"fmt"\r\n",__func__, __LINE__, ##arg);\
}while(0)
#define APP_PrintLog(fmt,arg...)          do{\
			if(drv_print_enable)\
			PrintLog("[APP][%s:%d]"fmt"\r\n",__func__, __LINE__, ##arg);\
		}while(0)
#else
#define MyPrintLog(format,...)
#define PrintLog(format,...)
#define PrintHex(pdat,len)
#define PrintChar(pdat,len)
#define DRV_DEBUG(fmt,arg...)
#define APP_DEBUG(fmt,arg...)
#endif


#if __NVRAM_LOG_ENABLE__
#define NVRAM_PrintLog(fmt,arg...)          do{\
	if(__NVRAM_LOG_ENABLE__)\
	PrintLog("[NVRAM][%s:%d]"fmt"\r\n",__func__, __LINE__, ##arg);\
}while(0)
#define NVRAM_PrintHex(pdat,dat_len)          do{\
			if(__NVRAM_LOG_ENABLE__)\
				{DEBUG_Print("[NVRAM]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define NVRAM_PrintChar(pdat,dat_len)          do{\
			if(__NVRAM_LOG_ENABLE__)\
				{DEBUG_Print("[NVRAM]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define NVRAM_PrintLog(fmt,arg...)
#define NVRAM_PrintHex(pdat,dat_len)
#define NVRAM_PrintChar(pdat,dat_len)
#endif

#if __FS_LOG_ENABLE__
#define FS_PrintLog(fmt,arg...)          do{\
	if(__FS_LOG_ENABLE__)\
	PrintLog("[FS][%s:%d]"fmt"\r\n",__func__, __LINE__, ##arg);\
}while(0)
#define FS_PrintHex(pdat,dat_len)          do{\
			if(__FS_LOG_ENABLE__)\
				{DEBUG_Print("[FS]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define FS_PrintChar(pdat,dat_len)          do{\
			if(__FS_LOG_ENABLE__)\
				{DEBUG_Print("[FS]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define FS_PrintLog(fmt,arg...)
#define FS_PrintHex(pdat,dat_len)
#define FS_PrintChar(pdat,dat_len)
#endif

#if __USB_LOG_ENABLE__
#define USB_PrintLog(fmt,arg...)          do{\
	if(__USB_LOG_ENABLE__)\
	PrintLog("[USB][%s:%d]"fmt"\r\n",__func__, __LINE__, ##arg);\
}while(0)
#define USB_PrintHex(pdat,dat_len)          do{\
			if(__USB_LOG_ENABLE__)\
				{DEBUG_Print("[USB]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define USB_PrintChar(pdat,dat_len)          do{\
			if(__USB_LOG_ENABLE__)\
				{DEBUG_Print("[USB]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define USB_PrintLog(fmt,arg...)
#define USB_PrintHex(pdat,dat_len)
#define USB_PrintChar(pdat,dat_len)
#endif


/*---------------------------------模块类定义--------------------------------*/



/*-------------------------------变量常量声明-------------------------------*/
//extern    xxxxx;



/*-------------------------------函数接口声明-------------------------------*/
extern void DEBUG_Print(char * format,...);
extern void DEBUG_PrintHex(unsigned char *pdat,unsigned int dat_len);
extern void DEBUG_PrintChar(unsigned char *pdat,unsigned int dat_len);



#endif//#if __SYS_DEBUG_SUPPORT__


#ifdef __cplusplus
}
#endif
#endif //#ifndef __STD_DEBUG_H__






