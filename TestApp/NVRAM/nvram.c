/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of  WAN XING Tech. Co., Ltd.(C) 2012.
*
*  Copyright (C), 2010-2020, WAN XING Tech. Co., Ltd.
*
*********************************************************************************************************
*
* File name: nvram.c
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
* Date                   Author             Change Id             Release Description Of Change
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
/*------------------------------------------------------------------*/
#include "std_globals.h"
#if __SYS_NVRAM_ENABLE__
#include "nvram.h"

#if __SYS_MODBUS_ENABLE__
#include "prtc_modbus_func.h"
#endif
#if __SYS_DLT645_ENABLE__
#include "prtc_dlt645_func.h"
#endif
#if __SYS_METER_ENABLE__
#include "app_meter_task.h"
#endif

#define NVRAM_CHECKSUM_KEY				(0x2468)

#define NVRAM_CS_DISABLE				(0x55)
#define NVRAM_CS_ENABLE					(0xAA)

#define NVRAM_BKUP_DISABLE				(0x55)
#define NVRAM_BKUP_ENABLE				(0xAA)

#define NVRAM_MAIN_STORAGE_ADDR			(0x1000)
#define NVRAM_BKUP_STORAGE_ADDR			(0x1000)


#define NVRAM_MAIN_STORAGE_PATH			("/nvram.main.dat")
#define NVRAM_BKUP_STORAGE_PATH			("/nvram.bkup.dat")


//数据主存储--------------------------------------------------------------
#define NVRAM_DEV_PRM_START_ADDR		(NVRAM_MAIN_STORAGE_ADDR)
#define NVRAM_DEV_PRM_END_ADDR			(NVRAM_DEV_PRM_START_ADDR+0x00010000)

#define NVRAM_DEV_DAT_START_ADDR		(NVRAM_DEV_PRM_END_ADDR)
#define NVRAM_DEV_DAT_END_ADDR			(NVRAM_DEV_DAT_START_ADDR+0x00010000)

#define NVRAM_USR_PRM_START_ADDR		(NVRAM_DEV_DAT_END_ADDR)
#define NVRAM_USR_PRM_END_ADDR			(NVRAM_USR_PRM_START_ADDR+0x00010000)

#define NVRAM_USR_DAT_START_ADDR		(NVRAM_USR_PRM_END_ADDR)
#define NVRAM_USR_DAT_END_ADDR			(NVRAM_USR_DAT_START_ADDR+0x00010000)


#define NVRAM_RUN_PRM_START_ADDR		(NVRAM_USR_DAT_END_ADDR)
#define NVRAM_RUN_PRM_END_ADDR			(NVRAM_RUN_PRM_START_ADDR+0x00010000)

#define NVRAM_RUN_DAT_START_ADDR		(NVRAM_RUN_PRM_END_ADDR)
#define NVRAM_RUN_DAT_END_ADDR			(NVRAM_RUN_DAT_START_ADDR+0x00010000)



#define NVRAM_MODBUS_START_ADDR			(NVRAM_RUN_DAT_END_ADDR)
#define NVRAM_MODBUS_END_ADDR			(NVRAM_MODBUS_START_ADDR+0x00010000)

#define NVRAM_DLT645_START_ADDR			(NVRAM_MODBUS_END_ADDR)
#define NVRAM_DLT645_END_ADDR			(NVRAM_DLT645_START_ADDR+0x00010000)

#define NVRAM_METER_START_ADDR			(NVRAM_DLT645_END_ADDR)
#define NVRAM_METER_END_ADDR			(NVRAM_METER_START_ADDR+0x00010000)


//数据备份存储-------------------------------------------------------------
#define NVRAM_DEV_PRM_START_BKADDR		(NVRAM_BKUP_STORAGE_ADDR)
#define NVRAM_DEV_PRM_END_BKADDR		(NVRAM_DEV_PRM_START_BKADDR+0x00010000)

#define NVRAM_DEV_DAT_START_BKADDR		(NVRAM_DEV_PRM_END_BKADDR)
#define NVRAM_DEV_DAT_END_BKADDR		(NVRAM_DEV_DAT_START_BKADDR+0x00010000)

#define NVRAM_USR_PRM_START_BKADDR		(NVRAM_DEV_DAT_END_BKADDR)
#define NVRAM_USR_PRM_END_BKADDR		(NVRAM_USR_PRM_START_BKADDR+0x00010000)

#define NVRAM_USR_DAT_START_BKADDR		(NVRAM_USR_PRM_END_BKADDR)
#define NVRAM_USR_DAT_END_BKADDR		(NVRAM_USR_DAT_START_BKADDR+0x00010000)

#define NVRAM_RUN_PRM_START_BKADDR		(NVRAM_USR_DAT_END_BKADDR)
#define NVRAM_RUN_PRM_END_BKADDR		(NVRAM_RUN_PRM_START_BKADDR+0x00010000)

#define NVRAM_RUN_DAT_START_BKADDR		(NVRAM_RUN_PRM_END_BKADDR)
#define NVRAM_RUN_DAT_END_BKADDR		(NVRAM_RUN_DAT_START_BKADDR+0x00010000)



#define NVRAM_MODBUS_START_BKADDR		(NVRAM_RUN_DAT_END_BKADDR)
#define NVRAM_MODBUS_END_BKADDR			(NVRAM_MODBUS_START_BKADDR+0x00010000)

#define NVRAM_DLT645_START_BKADDR		(NVRAM_MODBUS_END_BKADDR)
#define NVRAM_DLT645_END_BKADDR			(NVRAM_DLT645_START_BKADDR+0x00010000)

#define NVRAM_METER_START_BKADDR		(NVRAM_DLT645_END_BKADDR)
#define NVRAM_METER_END_BKADDR			(NVRAM_METER_START_BKADDR+0x00010000)


/*----------------------模块内类定义--------------------------*/
typedef enum nvram_type_t
{
	NVRAM_STORE_FLASH,
	NVRAM_STORE_FRAM,
	NVRAM_STORE_EEPROM,
	NVRAM_STORE_FILE,
	NVRAM_STORE_MAX_ID,
}NVRAM_TYPE_T;


typedef union nvram_cmn_buf_t
{
	DEV_PRM_NVRAM_T 	dev_prm_nvram;
	DEV_DAT_NVRAM_T 	dev_dat_nvram;
	USR_PRM_NVRAM_T 	usr_prm_nvram;
	USR_DAT_NVRAM_T 	usr_dat_nvram;
	RUN_PRM_NVRAM_T		run_prm_nvram;
	RUN_DAT_NVRAM_T		run_dat_nvram;
	#if __SYS_MODBUS_ENABLE__
	MODBUS_NVRAM_T 		modbus_nvram;
	#endif
	#if __SYS_DLT645_ENABLE__
	DLT645_NVRAM_T 		dlt645_nvram;
	#endif
	#if __SYS_METER_ENABLE__
	METER_NVRAM_T 		meter_nvram;
	#endif
}NVRAM_CMN_BUF_T;

typedef struct nvram_map_tab_t
{
	NVRAM_ID_T  id;				//存储当前NVRAM项的ID
	UINT8_T		units;			//存储单元数
	UINT8_T*	ram_addr;		//存储RAM地址
	UINT16_T	len;			//存储内容长度
	UINT8_T		cs_enable;		//是否需要校验
	NVRAM_TYPE_T store_type;	//存储类型
	UINT32_T	save_addr;		//存储内容地址
	UINT8_T		backup_enable;	//是否需要备份
	UINT32_T	save_bkaddr;	//参数存储备份地址
}NVRAM_MAP_TAB_T;

/*----------------------全局变量常量--------------------------*/

NVRAM_CMN_BUF_T nvram_cmn_buf;

const NVRAM_MAP_TAB_T	nvram_map_tab[] = 
{
	/*功能项目*/					/*单元数		参数RAM地址								参数内容长度							校验标识					存储类型					存储地址						备份标识			备份地址*/
	{NVRAM_DEV_PRM_ID,			1, 			(UINT8_T*)&g_dev_prm.nvram,			sizeof(g_dev_prm.nvram),		NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_DEV_PRM_START_ADDR, 		1,			NVRAM_DEV_PRM_START_BKADDR},
	{NVRAM_DEV_DAT_ID,			1, 			(UINT8_T*)&g_dev_dat.nvram, 		sizeof(g_dev_dat.nvram),		NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_DEV_DAT_START_ADDR,		1,			NVRAM_DEV_DAT_START_BKADDR},
	{NVRAM_USR_PRM_ID,			1, 			(UINT8_T*)&g_usr_prm.nvram, 		sizeof(g_usr_prm.nvram),		NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_USR_PRM_START_ADDR,		1,			NVRAM_USR_PRM_START_BKADDR},
	{NVRAM_USR_DAT_ID,			1, 			(UINT8_T*)&g_usr_dat.nvram, 		sizeof(g_usr_dat.nvram),		NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_USR_DAT_START_ADDR,		1,			NVRAM_USR_DAT_START_BKADDR},
	{NVRAM_RUN_PRM_ID,			1,			(UINT8_T*)&g_run_prm.nvram, 		sizeof(g_run_prm.nvram),		NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_RUN_PRM_START_ADDR,		1,			NVRAM_RUN_PRM_START_BKADDR},
	{NVRAM_RUN_DAT_ID,			1,			(UINT8_T*)&g_run_dat.nvram, 		sizeof(g_run_dat.nvram),		NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_RUN_DAT_START_ADDR,		1,			NVRAM_RUN_DAT_START_BKADDR},
	#if __SYS_MODBUS_ENABLE__
	{NVRAM_MODBUS_ID,			1, 			(UINT8_T*)&modbus.nvram,			sizeof(modbus.nvram),			NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_MODBUS_START_ADDR, 		1,			NVRAM_MODBUS_START_BKADDR},
	#endif
	#if __SYS_DLT645_ENABLE__
	{NVRAM_DLT645_ID,			1,			(UINT8_T*)&dlt645.nvram,			sizeof(dlt645.nvram),			NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_DLT645_START_ADDR, 	 	1, 		 	NVRAM_DLT645_START_BKADDR},
	#endif
	#if __SYS_METER_ENABLE__
	{NVRAM_METER_ID,			1,			(UINT8_T*)&meter.nvram,			 	sizeof(meter.nvram),			NVRAM_CS_ENABLE,		NVRAM_STORE_FILE,		NVRAM_METER_START_ADDR, 	 	1, 		 	NVRAM_METER_START_BKADDR},
	#endif
 };
/*----------------------内部静态变量--------------------------*/


/*----------------------内部静态函数--------------------------*/


/*****************************************************************************/
                         /* 函数定义 */
/*****************************************************************************/
/******************************************************************************
* Function:    NVRAM_AddCs
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
INT16_T NVRAM_AddCs(UINT8_T* pdat,UINT32_T len)
{
	UINT16_T checksum;
	
	if (len > 2)
	{
		checksum = GetDatKeyCheckSum(NVRAM_CHECKSUM_KEY,&pdat[2],len-2);
		pdat[0] = checksum&0xff;
		pdat[1] = (checksum>>8)&0xff;
		return NVRAM_HANDLE_OK;
	}
	return NVRAM_INVAILD_ERR;
}

/******************************************************************************
* Function:    NVRAM_CheckCs
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
INT16_T NVRAM_CheckCs(UINT8_T* pdat,UINT32_T len)
{
	UINT16_T checksum;
	checksum = (INT16_T)pdat[0]+((INT16_T)pdat[1]<<8);
	if (checksum == GetDatKeyCheckSum(NVRAM_CHECKSUM_KEY,&pdat[2],len-2))
	{
		return NVRAM_HANDLE_OK;
	}
	return NVRAM_VERIFY_ERR;
}


/******************************************************************************
* Function:    NVRAM_ReadMemory
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
INT16_T NVRAM_ReadMemory(UINT8_T store_type,UINT8_T* pdat,UINT32_T raddr,UINT32_T rlen)
{

	//读取FLASH、FRAM存储地址中的内容存入到RAM地址中
	if(store_type ==NVRAM_STORE_FRAM)
	{
		//Drv_FramRead(NVRAM_CHIP_FRAM, pdat,raddr,rlen);
	}
	else if(store_type ==NVRAM_STORE_FLASH)
	{
		//DRV_FlashRead(CHIP_SPI_FLASH, pdat,raddr,rlen);
	}
	else if(store_type ==NVRAM_STORE_FILE)
	{
		//DRV_FileRead(CHIP_SPI_FLASH, pdat,raddr,rlen);
	}
	else
	{
		NVRAM_PrintLog("ERROR: read failed,unknow memory chip type!\r\n");
		return NVRAM_UNKNOWN_ERR;
	}
	if(NVRAM_CheckCs(pdat, rlen) == NVRAM_HANDLE_OK)
		return NVRAM_HANDLE_OK;
	else
		return NVRAM_VERIFY_ERR;
}



/******************************************************************************
* Function:    NVRAM_WriteMemory
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
INT16_T NVRAM_WriteMemory(UINT8_T store_type,UINT8_T* pdat,UINT32_T waddr,UINT32_T wlen)
{
	if(NVRAM_AddCs(pdat, wlen) == NVRAM_HANDLE_OK)
	{
		//将pbuf的内容存入到FLASH、FRAM存储地址中
		if(store_type ==NVRAM_STORE_FRAM)
		{
			//DRV_FramWrite(NVRAM_CHIP_FRAM, pdat,waddr,wlen);
		}
		else if(store_type ==NVRAM_STORE_FLASH)
		{
			//DRV_FlashWrite(CHIP_SPI_FLASH, pdat,waddr,wlen);
		}
		else if(store_type ==NVRAM_STORE_FILE)
		{
			//DRV_FileWrite(CHIP_SPI_FLASH, pdat,waddr,wlen);
		}
		else
		{
			NVRAM_PrintLog("ERROR: write failed,unknow memory chip type!\r\n");
			return NVRAM_UNKNOWN_ERR;
		}
		return NVRAM_HANDLE_OK;
	}
	else
		return NVRAM_INVAILD_ERR;
}

/******************************************************************************
* Function:    NVRAM_Read
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
INT16_T NVRAM_Read(NVRAM_ID_T id,UINT8_T unit,void* pbuf)
{
	if (id < NVRAM_MAX_ID)
	{
		if (unit < nvram_map_tab[id].units)
		{
			if (NVRAM_CheckCs(nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,nvram_map_tab[id].len) == NVRAM_HANDLE_OK)
			{
				memcpy((UINT8_T*)pbuf, nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len, nvram_map_tab[id].len);
				return NVRAM_HANDLE_OK;
			}
			else
			{
				NVRAM_PrintLog("Ram data verify error! try to read memory!NVRAM_ID=%d\r\n",id);
				if(NVRAM_ReadMemory(nvram_map_tab[id].store_type,
					                nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,
					                nvram_map_tab[id].save_addr+unit*nvram_map_tab[id].len,
					                nvram_map_tab[id].len) == NVRAM_HANDLE_OK)
				{
					NVRAM_PrintLog("Read memory successful!NVRAM_ID=%d\r\n",id);
					memcpy((UINT8_T*)pbuf, nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len, nvram_map_tab[id].len);
					return NVRAM_HANDLE_OK;
				}
				else if(NVRAM_ReadMemory(nvram_map_tab[id].store_type,
										nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,
										nvram_map_tab[id].save_bkaddr+unit*nvram_map_tab[id].len,
										nvram_map_tab[id].len) == NVRAM_HANDLE_OK)
				{
					NVRAM_PrintLog("Read backup memory successful!write back to memory,NVRAM_ID=%d\r\n",id);
					NVRAM_WriteMemory(nvram_map_tab[id].store_type,
									nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,
									nvram_map_tab[id].save_addr+unit*nvram_map_tab[id].len,
									nvram_map_tab[id].len);
					
					memcpy((UINT8_T*)pbuf, nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len, nvram_map_tab[id].len);
					return NVRAM_HANDLE_OK;
				}
				else
				{
					NVRAM_PrintLog("Read backup memory failed!NVRAM Read failed!,NVRAM_ID=%d\r\n",id);
					return NVRAM_READ_ERR;
				}
			}
		}
		return NVRAM_INVAILD_ERR;//返回输入参数范围错误
	}
	return NVRAM_INVAILD_ERR;//返回输入参数选项错误
}



/******************************************************************************
* Function:    NVRAM_Write
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
INT16_T NVRAM_Write(NVRAM_ID_T id,UINT8_T unit,void* pbuf)
{
	if (id < NVRAM_MAX_ID)
	{
		if (unit < nvram_map_tab[id].units)
		{
			if (NVRAM_AddCs(pbuf,nvram_map_tab[id].len) == NVRAM_HANDLE_OK)
				memcpy(nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,(UINT8_T*)pbuf,nvram_map_tab[id].len);
			else
			{
				NVRAM_PrintLog("NVRAM_AddCs failed!NVRAM_ID=%d\r\n",id);
				return NVRAM_INVAILD_ERR;//返回输入参数范围错误
			}
			
			if(NVRAM_WriteMemory(nvram_map_tab[id].store_type,
				                nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,
				                nvram_map_tab[id].save_addr+unit*nvram_map_tab[id].len,
				                nvram_map_tab[id].len) == NVRAM_HANDLE_OK)
			{
				NVRAM_PrintLog("write memory successful!NVRAM_ID=%d\r\n",id);
			}
			else
			{
				NVRAM_PrintLog("write memory failed!NVRAM_ID=%d\r\n",id);
			}
			if(NVRAM_ReadMemory(nvram_map_tab[id].store_type,
				                nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,
				                nvram_map_tab[id].save_addr+unit*nvram_map_tab[id].len,
				                nvram_map_tab[id].len) == NVRAM_HANDLE_OK)
			{
				NVRAM_PrintLog("read back verify memory successful!NVRAM_ID=%d\r\n",id);
			}
			else
			{
				NVRAM_PrintLog("read back verify memory failed!NVRAM_ID=%d\r\n",id);
			}
			
			if(NVRAM_WriteMemory(nvram_map_tab[id].store_type,
								nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,
								nvram_map_tab[id].save_bkaddr+unit*nvram_map_tab[id].len,
								nvram_map_tab[id].len) == NVRAM_HANDLE_OK)
			{
				NVRAM_PrintLog("write backup memory successful!NVRAM_ID=%d\r\n",id);
			}
			else
			{
				NVRAM_PrintLog("write backup memory failed!NVRAM_ID=%d\r\n",id);
			}
			if(NVRAM_ReadMemory(nvram_map_tab[id].store_type,
								nvram_map_tab[id].ram_addr+unit*nvram_map_tab[id].len,
								nvram_map_tab[id].save_bkaddr+unit*nvram_map_tab[id].len,
								nvram_map_tab[id].len)== NVRAM_HANDLE_OK)
			{
				NVRAM_PrintLog("read back verify backup memory successful!NVRAM_ID=%d\r\n",id);
				return NVRAM_HANDLE_OK;
			}
			else
			{
				NVRAM_PrintLog("read back verify backup memory failed!NVRAM_ID=%d\r\n",id);
				return NVRAM_WRITE_ERR;
			}
		}
		return NVRAM_INVAILD_ERR;//返回输入参数范围错误
	}
	return NVRAM_INVAILD_ERR;//返回输入参数选项错误
}

/******************************************************************************
* Function:    NVRAM_Init
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
INT16_T NVRAM_Init(void)
{
	memset(&g_dev_prm.nvram,0,sizeof(g_dev_prm.nvram));
	NVRAM_Write(NVRAM_DEV_PRM_ID, 0, &g_dev_prm.nvram);
	memset(&g_dev_dat.nvram,0,sizeof(g_dev_prm.nvram));
	NVRAM_Write(NVRAM_DEV_DAT_ID, 0, &g_dev_dat.nvram);
	memset(&g_usr_prm.nvram,0,sizeof(g_usr_prm.nvram));
	NVRAM_Write(NVRAM_USR_PRM_ID, 0, &g_dev_prm.nvram);
	memset(&g_usr_dat.nvram,0,sizeof(g_usr_dat.nvram));
	NVRAM_Write(NVRAM_USR_DAT_ID, 0, &g_usr_dat.nvram);
	
	memset(&g_run_prm.nvram,0,sizeof(g_run_prm.nvram));
	NVRAM_Write(NVRAM_USR_PRM_ID, 0, &g_run_prm.nvram);
	memset(&g_run_dat.nvram,0,sizeof(g_run_dat.nvram));
	NVRAM_Write(NVRAM_USR_DAT_ID, 0, &g_run_dat.nvram);
	#if __SYS_MODBUS_ENABLE__
	modbus.nvram.rsv[0]=0;
	modbus.nvram.rsv[1]=1;
	modbus.nvram.rsv[2]=2;
	modbus.nvram.rsv[3]=3;
	modbus.nvram.rsv[4]=4;
	modbus.nvram.rsv[5]=5;
	modbus.nvram.rsv[6]=6;
	modbus.nvram.rsv[7]=7;
	NVRAM_Write(NVRAM_MODBUS_ID, 0, &modbus.nvram);
	#endif
	return NVRAM_HANDLE_OK;
}
/******************************************************************************
* Function:    NVRAM_Load
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
INT16_T NVRAM_Load(void)
{
	if(NVRAM_Read(NVRAM_DEV_PRM_ID, 0, &g_dev_prm.nvram) == NVRAM_HANDLE_OK)
	{
		NVRAM_PrintLog("NVRAM_Load NVRAM_DEV_PRM_ID Successful\r\n");
	}
	else
		NVRAM_PrintLog("NVRAM_Load NVRAM_DEV_PRM_ID Failed\r\n");
	
	if(NVRAM_Read(NVRAM_DEV_DAT_ID, 0, &g_dev_dat.nvram) == NVRAM_HANDLE_OK)
	{
		NVRAM_PrintLog("NVRAM_Load NVRAM_DEV_DAT_ID Successful\r\n");
	}
	else
		NVRAM_PrintLog("NVRAM_Load NVRAM_DEV_DAT_ID Failed\r\n");
	
	if(NVRAM_Read(NVRAM_USR_PRM_ID, 0, &g_usr_prm.nvram) == NVRAM_HANDLE_OK)
	{
		NVRAM_PrintLog("NVRAM_Load NVRAM_USR_PRM_ID Successful\r\n");
	}
	else
		NVRAM_PrintLog("NVRAM_Load NVRAM_USR_PRM_ID Failed\r\n");

	
	if(NVRAM_Read(NVRAM_USR_DAT_ID, 0, &g_usr_dat.nvram) == NVRAM_HANDLE_OK)
	{
		NVRAM_PrintLog("NVRAM_Load NVRAM_USR_DAT_ID Successful\r\n");
	}
	else
		NVRAM_PrintLog("NVRAM_Load NVRAM_USR_DAT_ID Failed\r\n");


	if(NVRAM_Read(NVRAM_RUN_PRM_ID, 0, &g_run_prm.nvram) == NVRAM_HANDLE_OK)
	{
		NVRAM_PrintLog("NVRAM_Load NVRAM_RUN_PRM_ID Successful\r\n");
	}
	else
		NVRAM_PrintLog("NVRAM_Load NVRAM_RUN_PRM_ID Failed\r\n");

	
	if(NVRAM_Read(NVRAM_RUN_DAT_ID, 0, &g_run_dat.nvram) == NVRAM_HANDLE_OK)
	{
		NVRAM_PrintLog("NVRAM_Load NVRAM_RUN_DAT_ID Successful\r\n");
	}
	else
		NVRAM_PrintLog("NVRAM_Load NVRAM_RUN_DAT_ID Failed\r\n");



	#if __SYS_MODBUS_ENABLE__
	if(NVRAM_Read(NVRAM_MODBUS_ID, 0, &modbus.nvram) == NVRAM_HANDLE_OK)
	{
		NVRAM_PrintLog("NVRAM_Load NVRAM_MODBUS_ID Successful\r\n");
		NVRAM_PrintLog("modbus.nvram.rsv[0]=%d\r\n",modbus.nvram.rsv[0]);
		NVRAM_PrintLog("modbus.nvram.rsv[1]=%d\r\n",modbus.nvram.rsv[1]);
		NVRAM_PrintLog("modbus.nvram.rsv[2]=%d\r\n",modbus.nvram.rsv[2]);
		NVRAM_PrintLog("modbus.nvram.rsv[3]=%d\r\n",modbus.nvram.rsv[3]);
		NVRAM_PrintLog("modbus.nvram.rsv[4]=%d\r\n",modbus.nvram.rsv[4]);
		NVRAM_PrintLog("modbus.nvram.rsv[5]=%d\r\n",modbus.nvram.rsv[5]);
		NVRAM_PrintLog("modbus.nvram.rsv[6]=%d\r\n",modbus.nvram.rsv[6]);
		NVRAM_PrintLog("modbus.nvram.rsv[7]=%d\r\n",modbus.nvram.rsv[7]);
	}
	else
		NVRAM_PrintLog("NVRAM_Load NVRAM_MODBUS_ID Failed\r\n");
	#endif

	return NVRAM_HANDLE_OK;
}

#endif//#if __SYS_NVRAM_ENABLE__

