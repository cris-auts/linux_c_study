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
* File name: dbase.h
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
* Description:  database wrapper api declares.
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
#ifndef __DBASE_H__
#define __DBASE_H__
#ifdef __cplusplus
extern "C" {
#endif


/*----------------------公共头文件----------------------------*/
#include "std_globals.h"
#if 1


/*----------------------接口头文件----------------------------*/


/*----------------------公共宏定义----------------------------*/
#define OPERATE_TABLE_SIMULTANE  1 //同时操作多张表 1使能 0失能
#define OPERATE_TABLE_INCREMENT_ID  1 //表自增ID    1使能 0失能
#define PORT_LIST_MAX  10	//侦听端口列表最大个数
#define ID_NUM_MAX 20
#define MOBILE_COMM_PRM_MAX 10	//移动通信参数最大个数

/*----------------------公共类定义----------------------------*/
typedef enum sql_err
{
	SQL_OK,
	SQL_TABLE_EXIST,//表已存在
	SQL_TABLE_ID_ERR,//表号错误
	SQL_CMD_OVERFLOW,//SQL指令超出既定缓存长度
	SQL_FAIL
}SQL_ERR_T;

typedef enum sql_select
{
	SQL_SELECT_NUM,
	SQL_SELECT_DATA
}SQL_SELECT_T;

typedef enum sql_screen
{
	SQL_SCREEN_TABLE1_ID,
	SQL_SCREEN_TABLE2_ID
}SQL_SCREEN_T;

typedef enum dbase_err
{
	DBASE_OK,
	DBASE_FAIL
}DBASE_ERR_T;

typedef enum comm_port
{
	COMM_RS485_1,
	COMM_RS485_2,
	COMM_RS232_1,
	COMM_RS232_2,
	COMM_ETH_1,
	COMM_ETH_2,
	COMM_WIFI_1,
	COMM_GPRS_1
}COMM_PORT_T;//物理通道

typedef enum prtc_type
{
	PRTC_DLT698, //DLT698.45规约
	PRTC_MAINT	  //maint维护规约
}PRTC_TYPE_T;//规约类型

typedef enum mobile_comm_port
{
  MCP_MOBILE_2G,//移动2G
  MCP_MOBILE_4G,//移动4G
  MCP_MOBILE_IoT,//移动物联网
  MCP_TELECOM_2G,//电信2G
  MCP_TELECOM_4G,//电信4G
  MCP_TELECOM_IoT,//电信物联网
  MCP_UNICOM_2G,//联通2G
  MCP_UNICOM_4G,//联通4G
  MCP_UNICOM_IoT,//联通物联网
  MCP_CUSTOMIZE_NET//专网
}MOBILE_COMM_PORT_T;//移动通信通道(运营商)

/*----------------------------------------------通道配置表----------------------------------------------*/
typedef struct table_comm_cfg
{
	UINT16_T          cs;//校验
	UINT8_T           enable;//失能(0)、使能(1)
	UINT16_T		  cfg_sn;//配置序号
	COMM_PORT_T     comm_port;//物理通道
	union
	{
		struct  
		{
			UINT32_T bps;	//波特率
			UINT8_T check_bit;	//校验位 NONE(0)，ODD(1)，EVEN(2)
			UINT8_T data_bit;		//数据位 5位(0)，6位(1)，7位(2)，8位(3)
			UINT8_T stop_bit;	//停止位 1.5位(0)，1位(1)，2位(2)
		}uart_cfg;//底层uart配置
		struct  
		{
			UINT8_T ip_type;			//ip类型 IPV4(0) IPV6(1)
			UINT8_T ip_mode;        // DHCP（0），静态（1），PPPoE（2）
			UINT8_T ip_addr[6];       //IP地址  
			UINT8_T subnet_mask[6];  //子网掩码    
			UINT8_T gateway_addr[6];  //网关地址   
			UINT8_T dns_addr[6];		//DNS地址
			UINT8_T mac_addr[6];		//MAC地址
			UINT8_T ppoe_name[20]; //PPPoE用户名 
			UINT8_T ppoe_passwd[20]; //PPPoE密码    
		}eth_cfg;//底层以太网配置
		struct
		{
			UINT8_T wifi_type;		//wifi类型 热点失能(0) 热点使能(1)
			UINT8_T ip_type;			//ip类型 IPV4(0) IPV6(1)
			UINT8_T ip_mode;		// DHCP（0），静态（1），PPPoE（2）
			UINT8_T ip_addr[6]; 	  //IP地址	
			UINT8_T subnet_mask[6];  //子网掩码    
			UINT8_T gateway_addr[6];  //网关地址   
			UINT8_T dns_addr[6];		//DNS地址
			UINT8_T mac_addr[6];		//MAC地址
			UINT8_T ppoe_name[20]; //PPPoE用户名 
			UINT8_T ppoe_passwd[20]; //PPPoE密码	
		}wifi_cfg;//底层wifi配置
		struct  
		{
			MOBILE_COMM_PORT_T mobile_comm_port;//移动通信通道(运营商)
			UINT8_T apn[20];    //apn;
			UINT8_T username[20];    //用户名
			UINT8_T passwd[20];      //密码
		}mobile_cfg[MOBILE_COMM_PRM_MAX];//底层移动通信配置
	}port_cfg;
}TABLE_COMM_CFG_T,*P_TABLE_COMM_CFG_T;

/*----------------------------------------------通信参数表----------------------------------------------*/
typedef struct table_comm_prm
{
	UINT16_T          cs;//校验
	UINT8_T            enable;//失能(0)、使能(1)
	UINT16_T			  cfg_sn;//配置序号
	PRTC_TYPE_T      prtc_type;//规约类型
	UINT8_T			  prtc_level;//规约权限等级 	从(0)、主(1)
	COMM_PORT_T      comm_port;//物理通道
	UINT8_T run_mode;//运行模式   客户端(0)、服务器(1)、混合模式(2)
	UINT8_T link_mode;//连接模式   TCP(0)、UDP(1)
	UINT8_T link_app_mode;//连接应用模式  主备模式(0)、多连接模式(1)
	union
	{
		/*串行接口参数*/
		struct
		{
			UINT32_T resend_count;       //重发次数
			UINT32_T timeout;            //超时时间
			UINT32_T time_wait;          //发送等待间隔时间
		}uart_prm;
		/*以太网参数*/
		struct
		{
			UINT8_T ip_type;           //ip类型 IPV4(0) IPV6(1)
			UINT8_T ip[6];				//ip地址
			UINT32_T port_num;         //端口号
			UINT8_T ip_backup_type;    //备用ip类型
			UINT8_T ip_backup [6];		//备用ip地址
			UINT32_T port_backup_num;  //备用端口号
			UINT32_T port_list_num;     //侦听端口列表有效数据长度
			UINT32_T port_list[PORT_LIST_MAX];          //侦听端口列表
			UINT8_T ip_proxy_type;     //代理ip类型
			UINT8_T ip_proxy [6];		//代理ip地址
			UINT32_T port_proxy_num;    //代理端口号
			UINT32_T resend_count;       //重发次数
			UINT32_T timeout;            //超时时间
			UINT32_T time_wait;          //发送等待间隔时间
			UINT32_T cardiac_cycle;        //心跳周期		
		}eth_prm;
		/*WIFI参数*/
		struct
		{
			UINT8_T user_name[20];//用户名
			UINT8_T user_passwd[20];//密码
			UINT8_T root_name[20];//root名
			UINT8_T root_passwd[20];//root密码
			UINT8_T ip_type;           //ip类型 IPV4(0) IPV6(1)
			UINT8_T ip[6];				//ip地址
			UINT32_T port_num;         //端口号
			UINT8_T ip_backup_type;    //备用ip类型
			UINT8_T ip_backup [6];		//备用ip地址
			UINT32_T port_backup_num;  //备用端口号
			UINT32_T port_list_num;     //侦听端口列表有效数据长度
	        UINT32_T port_list[PORT_LIST_MAX];          //侦听端口列表
			UINT32_T resend_count;       //重发次数
			UINT32_T timeout;            //超时时间
			UINT32_T time_wait;          //发送等待间隔时间
			UINT32_T cardiac_cycle;      //心跳周期
		}wifi_prm;
		/*移动通信参数*/
		struct
		{            
			MOBILE_COMM_PORT_T mobile_comm_port;//移动通信通道(运营商)
			UINT8_T ip_type;           //ip类型 IPV4(0) IPV6(1)
			UINT8_T ip[6];				//ip地址
			UINT32_T port_num;         //端口号
			UINT8_T ip_backup_type;    //备用ip类型
			UINT8_T ip_backup[6];		//备用ip地址
			UINT32_T port_backup_num;  //备用端口号
			UINT8_T online_mode;      //在线模式 0：永久连接1：被动激活
			UINT32_T port_list_num;     //侦听端口列表有效数据长度
	        UINT32_T port_list[PORT_LIST_MAX];          //侦听端口列表
			UINT32_T resend_count;     //重发次数
			UINT32_T timeout;           //超时时间
			UINT32_T time_wait;          //发送等待间隔时间
			UINT32_T cardiac_cycle;      //心跳周期
		}mobile_prm[MOBILE_COMM_PRM_MAX];
	}port_prm;
}TABLE_COMM_PRM_T,*P_TABLE_COMM_PRM_T;
/*----------------------------------------------总表----------------------------------------------*/
typedef enum table_id_t
{
	SQL_TABLE_COMM_CFG,
	SQL_TABLE_COMM_PRM,
	SQL_TABLE_MAX
}SQL_TABLE_ID_T;

/*-----------------模块对外接口变量声明-----------------------*/
//extern    xxxxx;


/*-----------------模块对外接口函数声明-----------------------*/
extern DBASE_ERR_T DBASE_OpenDataBase(const char *db_name);
extern DBASE_ERR_T DBASE_CloseDataBase();

/*-----------------通道配置表接口函数声明-----------------------*/
//查询表记录总数
extern DBASE_ERR_T DBASE_QueryCommCfgRecordNum(UINT32_T *total_num);
//查询表所有配置序号
extern DBASE_ERR_T DBASE_QueryCommCfgRecordCfgSn(UINT16_T *cfg_sn);
//根据配置序号查询配置参数
extern DBASE_ERR_T DBASE_SelectCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_comm_cfg);
//根据配置序号添加配置参数
extern DBASE_ERR_T DBASE_InsertCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_comm_cfg);
//根据配置序号更新配置参数
extern DBASE_ERR_T DBASE_UpdateCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_comm_cfg);
//根据配置序号删除配置参数
extern DBASE_ERR_T DBASE_DelectCommCfgAccordCfgSn(UINT16_T cfg_sn);
//清空表
extern DBASE_ERR_T DBASE_ClearCommCfgRecord();

/*-----------------通新参数表接口函数声明-----------------------*/
//查询表记录总数
extern DBASE_ERR_T DBASE_QueryCommPrmRecordNum(UINT32_T *total_num);
//查询表所有配置序号
extern DBASE_ERR_T DBASE_QueryCommPrmRecordCfgSn(UINT16_T *cfg_sn);
//根据配置序号查询配置参数
extern DBASE_ERR_T DBASE_SelectCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_comm_cfg);
//根据配置序号添加配置参数
extern DBASE_ERR_T DBASE_InsertCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_comm_cfg);
//根据配置序号更新配置参数
extern DBASE_ERR_T DBASE_UpdateCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_comm_cfg);
//根据配置序号删除配置参数
extern DBASE_ERR_T DBASE_DelectCommPrmAccordCfgSn(UINT16_T cfg_sn);
//清空表
extern DBASE_ERR_T DBASE_ClearCommPrmRecord();

#endif//#if __SYS_DBASE_ENABLE__
#ifdef __cplusplus
}
#endif
#endif //#ifndef __DB_H__




