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
#if __STD_DEBUG_ENABLE__
/*---------------------------------接口头文件--------------------------------*/
//#include "xxx_xxx.h"



/*---------------------------------模块宏定义--------------------------------*/
#if __SYS_DEBUG_LOG_ENABLE__
#define MyPrintLog(format,args...) 	DEBUG_Print("[cris-log][%s]%d:"format"\r\n",__FUNCTION__, __LINE__,##args)
#define PrintLog(format,args...)	DEBUG_Print(format,##args)
#define PrintHex(pdat,len)			DEBUG_PrintHex(pdat,len)
#define PrintChar(pdat,len)			DEBUG_PrintChar(pdat,len)
#else
#define MyPrintLog(format,...)
#define PrintLog(format,...)
#define PrintHex(pdat,len)
#define PrintChar(pdat,len)
#endif


#if __SYS_FUNCS_LOG_ENABLE__
#define FUNCS_PrintLog(fmt,arg...)          do{\
	if(g_dev_prm.nvram.debug_log_st.funcs_log)\
	PrintLog("[FUNCS]:"fmt"\r\n", ##arg);\
}while(0)
#define FUNCS_PrintHex(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.funcs_log)\
				{DEBUG_Print("[FUNCS]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define FUNCS_PrintChar(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.funcs_log)\
				{DEBUG_Print("[FUNCS]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define FUNCS_PrintLog(fmt,arg...)
#define FUNCS_PrintHex(pdat,dat_len)
#define FUNCS_PrintChar(pdat,dat_len)
#endif


#if __SYS_NVRAM_LOG_ENABLE__
#define NVRAM_PrintLog(fmt,arg...)          do{\
	if(g_dev_prm.nvram.debug_log_st.nvram_log)\
	PrintLog("[NVRAM]:"fmt, ##arg);\
}while(0)
#define NVRAM_PrintHex(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.nvram_log)\
				{DEBUG_Print("[NVRAM]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define NVRAM_PrintChar(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.nvram_log)\
				{DEBUG_Print("[NVRAM]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define NVRAM_PrintLog(fmt,arg...)
#define NVRAM_PrintHex(pdat,dat_len)
#define NVRAM_PrintChar(pdat,dat_len)
#endif



#if __SYS_DBASE_LOG_ENABLE__
#define DBASE_PrintLog(fmt,arg...)          do{\
	if(g_dev_prm.nvram.debug_log_st.dbase_log)\
	PrintLog("[DBASE]:"fmt, ##arg);\
}while(0)
#define DBASE_PrintHex(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.dbase_log)\
				{DEBUG_Print("[DBASE]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define DBASE_PrintChar(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.dbase_log)\
				{DEBUG_Print("[DBASE]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define DBASE_PrintLog(fmt,arg...)
#define DBASE_PrintHex(pdat,dat_len)
#define DBASE_PrintChar(pdat,dat_len)
#endif

#if __SYS_MODBUS_LOG_ENABLE__
#define MODBUS_PrintLog(fmt,arg...)          do{\
	if(g_dev_prm.nvram.debug_log_st.modbus_log)\
	PrintLog("[MODBUS]:"fmt,##arg);\
}while(0)
#define MODBUS_PrintHex(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.modbus_log)\
				{DEBUG_Print("[MODBUS]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define MODBUS_PrintChar(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.modbus_log)\
				{DEBUG_Print("[MODBUS]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define MODBUS_PrintLog(fmt,arg...)
#define MODBUS_PrintHex(pdat,dat_len)
#define MODBUS_PrintChar(pdat,dat_len)
#endif



#if __SYS_DLT645_LOG_ENABLE__
#define DLT645_PrintLog(fmt,arg...)          do{\
	if(g_dev_prm.nvram.debug_log_st.dlt645_log)\
	PrintLog("[DLT645]:"fmt,##arg);\
}while(0)
#define DLT645_PrintHex(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.dlt645_log)\
				{DEBUG_Print("[DLT645]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define DLT645_PrintChar(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.dlt645_log)\
				{DEBUG_Print("[DLT645]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define DLT645_PrintLog(fmt,arg...)
#define DLT645_PrintHex(pdat,dat_len)
#define DLT645_PrintChar(pdat,dat_len)
#endif

#if __SYS_METER_LOG_ENABLE__
#define METER_PrintLog(fmt,arg...)          do{\
	if(g_dev_prm.nvram.debug_log_st.meter_log)\
	PrintLog("[METER]:"fmt,##arg);\
}while(0)
#define METER_PrintHex(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.meter_log)\
				{DEBUG_Print("[METER]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define METER_PrintChar(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.meter_log)\
				{DEBUG_Print("[METER]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define METER_PrintLog(fmt,arg...)
#define METER_PrintHex(pdat,dat_len)
#define METER_PrintChar(pdat,dat_len)
#endif

#if __SYS_RS485_LOG_ENABLE__
#define RS485_PrintLog(fmt,arg...)          do{\
	if(g_dev_prm.nvram.debug_log_st.rs485_log)\
	PrintLog("[RS485]:"fmt,##arg);\
}while(0)
#define RS485_PrintHex(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.rs485_log)\
				{DEBUG_Print("[RS485]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define RS485_PrintChar(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.rs485_log)\
				{DEBUG_Print("[RS485]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define RS485_PrintLog(fmt,arg...)
#define RS485_PrintHex(pdat,dat_len)
#define RS485_PrintChar(pdat,dat_len)
#endif

#if __SYS_RS232_LOG_ENABLE__
#define RS232_PrintLog(fmt,arg...)          do{\
	if(g_dev_prm.nvram.debug_log_st.rs232_log)\
	PrintLog("[RS232]:"fmt,##arg);\
}while(0)
#define RS232_PrintHex(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.rs232_log)\
				{DEBUG_Print("[RS232]:HEX:");DEBUG_PrintHex(pdat,dat_len);}\
		}while(0)
		
#define RS232_PrintChar(pdat,dat_len)          do{\
	if(g_dev_prm.nvram.debug_log_st.rs232_log)\
				{DEBUG_Print("[RS232]:CHAR:");DEBUG_PrintChar(pdat,dat_len);}\
		}while(0)
#else
#define RS232_PrintLog(fmt,arg...)
#define RS232_PrintHex(pdat,dat_len)
#define RS232_PrintChar(pdat,dat_len)
#endif


/*---------------------------------模块类定义--------------------------------*/
typedef struct debug_log_st_t{
	UINT8_T debug_log;
	UINT8_T funcs_log;
	UINT8_T nvram_log;
	UINT8_T dbase_log;
	UINT8_T modbus_log;
	UINT8_T dlt645_log;
	UINT8_T meter_log;
	UINT8_T rs485_log;
	UINT8_T rs232_log;
}DEBUG_LOG_ST_T;



/*-------------------------------变量常量声明-------------------------------*/
//extern    xxxxx;



/*-------------------------------函数接口声明-------------------------------*/
extern void DEBUG_Print(char * format,...);
extern void DEBUG_PrintHex(UINT8_T *pdat, UINT32_T dat_len);
extern void DEBUG_PrintChar(UINT8_T *pdat, UINT32_T dat_len);



#endif//#if __STD_DEBUG_ENABLE__


#ifdef __cplusplus
}
#endif
#endif //#ifndef __STD_DEBUG_H__






