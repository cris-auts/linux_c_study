/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of  WAN XING Tech. Co., Ltd.(C) 2012.
*
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
*********************************************************************************************************
*
* File name: prtc_dlt645_func.h
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
#ifndef __APP_DLT645_TASK_H__
#define __APP_DLT645_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------公共头文件----------------------------*/
#include "std_globals.h"
#if __SYS_DLT645_ENABLE__

//#include "xxx_xxx.h"


/*----------------------公共宏定义----------------------------*/
#define DLT_645_START 0X68
#define DLT_645_STOP  0X16

#define DLT645_LOG_EN   1


#define DLT645_LOG_HEAD "\r\n[DLT645_LOG]:"
#define DLT645_LOG_END  "==>"
#define DLT645_LOG(format,...)    do{     printf(DLT645_LOG_HEAD);                       \
										  printf(format,##__VA_ARGS__);                  \
										  printf(DLT645_LOG_END);                        \
										  printf(__FUNCTION__);                          \
                                       }while(0);


/*----------------------公共类定义----------------------------*/
/*
00000：保留
01000：广播校时
10001：读数据
10010：读后续数据
10011：读通信地址
10100：写数据
10101：写通信地址
10110：冻结命令
10111：更改通信速率
11000：修改密码
11001：最大需量清零
11010：电表清零
11011：事件清零
*/

//控制字功能掩码
typedef enum 
{
DLT645_CTRL_NULL_MASK			  =0X00,		  //保留
DLT645_CTRL_CALIBRATION_TIME_MASK  =0X08,		  //校时
DLT645_CTRL_READ_DATA_MASK		  =0X11,		  //读数据
DLT645_CTRL_CONTINUE_READ_DATA_MASK=0X12,		  //读后续数据
DLT645_CTRL_READ_ADDR_MASK		  =0X13,		  //读通信地址
DLT645_CTRL_WRITE_DATA_MASK		  =0X14,		  //写数据
DLT645_CTRL_WRITE_ADDR_MASK		  =0X15,		  //写通信地址
DLT645_CTRL_FROZEN_MASK			  =0X16,		  //冻结
DLT645_CTRL_CHANGE_SPEED_MASK	  =0X17,		  //更改通信速度
DLT645_CTRL_CHANGE_PASS_WORD_MASK  =0X18,		  //读后续数据
DLT645_CTRL_CL_MAX_DEMAND_MASK	  =0X19,		  //最大需清零
DLT645_CTRL_CL_DEV_MASK			  =0X1A,		  //电表清零
DLT645_CTRL_CL_EVENT_MASK		  =0X1B,		  //事件清零
DLT645_CTRL_ALARM_MASK			  =0X1C,		  //报警.跳合闸.保电
DLT645_CTRL_OUT_CTRL_MASK		  =0X1D,		  //多功能端子输出控制
DLT645_CTRL_SAFETY_CERTIFICTAION_MASK=0X03,		  //安全认证

}DLT645_CTRL_FUN_MASK_T;



//控制字普通掩码
typedef enum 
{
DLT645_CTRL_DIR_MASK 			  =0X80,		  //传输方向
DLT645_CTRL_DIR_MASTER_MASK		  =0X00,		  //传输方向(主机)
DLT645_CTRL_DIR_SLAVER_MASK		  =0X80,		  //传输方向(从机)

DLT645_CTRL_ACK_MASK 			  =0X40,		  //从机应答
DLT645_CTRL_ACK_OK_MASK			  =0X00,		  //从机正常应答
DLT645_CTRL_ACK_ERR_MASK 		  =0X40,		  //从机异常应答

DLT645_CTRL_CONTINUE_MASK		  =0X20,		  //后续帧
DLT645_CTRL_CONTINUE_FLAG_MASK	  =0X20,		  //有后续帧
DLT645_CTRL_CONTINUE_NULL_MASK	  =0X00,		  //无后续帧
}DLT645_CTRL_COMMON_MASK_T;



/*
NOTICE:
	   DI值为0X0202FF00（DLT645_CRRT）南瑞单相表返回数据个数有问题
	   DI值为0x040005FF（DLT645_MET_RUNWORD）南瑞单相表返回数据域个数有问题
*/
//DI值
typedef enum 
{
DLT645_MET_RUNWORD				=0x040005FF,		  //电表运行状态		
DLT645_MET_TIME					=0X04000102,		  //电表时间		  
DLT645_MET_DATE					=0X04000101,		  //电表日期		  
DLT645_VOLT						=0X0201FF00,		  //当前电压									
DLT645_CRRT						=0X0202FF00,		  //当前电流		  
DLT645_ACT_POW					=0X0203FF00,		  //有功功率		  
DLT645_REAL_POW					=0X0204FF00,		  //无功功率 
DLT645_SZ_POW					=0X0205FF00,		  //实在功率			
DLT645_POW_FACT					=0X0206FF00,		  //功率因数		  
DLT645_COMP_ACTENGY				=0X0000FF00,		  //组合有功电能		 
DLT645_POS_ACTENGY				=0X0001FF00,		  //正向有功电能		
DLT645_NEG_ACTENGY				=0X0002FF00,		  //反向有功电能		
DLT645_COMP1_REAENGY 			=0X0003FF00,		  //组合1无功电能 	  
DLT645_COMP2_REAENGY 			=0X0004FF00,		  //组合2无功电能 	   
DLT645_QUAD1_REAENGY 			=0X0005FF00,		  //象限1无功电能 	
DLT645_QUAD2_REAENGY 			=0X0006FF00,		  //象限2无功电能 	
DLT645_QUAD3_REAENGY 			=0X0007FF00,		  //象限3无功电能 	
DLT645_QUAD4_REAENGY 			=0X0008FF00,		  //象限4无功电能 	
DLT645_EVT_PROG_NUM				=0X03300000,		  //编程次数			  
DLT645_EVT_PROG_LAST 			=0X03300001,		  //上1次编程			 
DLT645_EVT_CLRMET_NUM			=0X03300100,		  //电表清零次数		
DLT645_EVT_CLRMET_LAST			=0X03300101,		  //上1次电表清零 	 
DLT645_EVT_OPENTAB_NUM			=0X03300D00,		  //开表盖总次数		
DLT645_EVT_OPENTAB_LAST			=0x03300D01,		  //上1次开表盖	   
DLT645_LOSS_ENGY_NUM 			=0x03110000,		  //掉电总次数 	   
DLT645_LOSS_ENGY_LAST			=0x03110001,		  //上1次掉电		  
DLT645_ClEAR_ENGY_NEED_NUM		=0x03300200,		  //需量清零总次数	 
DLT645_ClEAR_ENGY_NEED_LAST		=0x03300201,		  //上1次需量清零 	
DLT645_CLEAR_EVENT_NUM			=0x03300300,		  //事件清零总次数	 
DLT645_CLEAR_EVENT_LAST			=0x03300301,		  //上1次事件清零 	
DLT645_PROTIME_NUM				=0x03300400,		  //校时总次数 	   
DLT645_PROTIME_LAST				=0x03300401,		  //上1次校时		  
DLT645_OPEN_JOINT_NUM			=0x03300E00,		  //开端钮总次数	  
DLT645_OPEN_JOINT_LAST			=0x03300E01,		  //上1次开端钮 
DLT645_AllLOSS_VOLT_NUM			=0x03050000,		  //全失压总次数	  
DLT645_AllLOSS_VOLT_LAST 		=0x03050001,		  //上1次全失压   
DLT645_REV_VOLT_NUM				=0x14000001,		  //电压逆相序总次数	 
DLT645_REV_VOLT_LAST 			=0x14000101,		  //上1次电压逆相序	 
DLT645_LOSS_BLAI_NUM 			=0x16000001,		  //电压不平衡总次数  
DLT645_LOSS_BLAI_LAST			=0x16000101,		  //上1次电压不平衡	 
DLT645_LOSS_VOLT_NUMA			=0x10010001,		  //A相失压总次数 	
DLT645_LOSS_VOLT_NUMB			=0x10020001,		  //B相失压总次数 	
DLT645_LOSS_VOLT_NUMC			=0x10030001,		  //C相失压总次数 	
DLT645_LOSS_VOLT_TIME_NUMA		=0x10010002,		  //A相失压总累计时间 
DLT645_LOSS_VOLT_TIME_NUMB		=0x10020002,		  //B相失压总累计时间 
DLT645_LOSS_VOLT_TIME_NUMC		=0x10030002,		  //C相失压总累计时间 
DLT645_LOSS_VOLT_LASTA			=0x10010101,		  //上1次A相失压	   
DLT645_LOSS_VOLT_LASTB			=0x10020101,		  //上1次B相失压	   
DLT645_LOSS_VOLT_LASTC			=0x10030101,		  //上1次C相失压	   
DLT645_OWE_VOLT_NUMA 			=0x11010001,		  //A相欠压总次数 	
DLT645_OWE_VOLT_NUMB 			=0x11020001,		  //B相欠压总次数 	
DLT645_OWE_VOLT_NUMC 			=0x11030001,		  //C相欠压总次数 	
DLT645_OWE_VOLT_TIMEA			=0x11010002,		  //A相欠压总累计时间 
DLT645_OWE_VOLT_TIMEB			=0x11020002,		  //B相欠压总累计时间 
DLT645_OWE_VOLT_TIMEC			=0x11030002,		  //C相欠压总累计时间 
DLT645_OWE_VOLT_LASTA			=0x11010101,		  //上1次A相欠压	   
DLT645_OWE_VOLT_LASTB			=0x11020101,		  //上1次B相欠压	   
DLT645_OWE_VOLT_LASTC			=0x11030101,		  //上1次C相欠压	   
DLT645_BEYO_VOLT_NUMA			=0x12010001,		  //A相过压总次数 	
DLT645_BEYO_VOLT_NUMB			=0x12020001,		  //B相过压总次数 	
DLT645_BEYO_VOLT_NUMC			=0x12030001,		  //C相过压总次数 	
DLT645_BEYO_VOLT_TIMEA			=0x12010002,		  //A相过压总累计时间 
DLT645_BEYO_VOLT_TIMEB			=0x12020002,		  //B相过压总累计时间 
DLT645_BEYO_VOLT_TIMEC			=0x12030002,		  //B相过压总累计时间 
DLT645_BEYO_VOLT_LASTA			=0x12010101,		  //上1次A相过压	
DLT645_BEYO_VOLT_LASTB			=0x12020101,		  //上1次B相过压		
DLT645_BEYO_VOLT_LASTC			=0x12030101,		  //上1次C相过压		  
DLT645_BREAK_VOLT_NUMA			=0x13010001,		  //A相断相总次数 	
DLT645_BREAK_VOLT_NUMB			=0x13020001,		  //B相断相总次数   
DLT645_BREAK_VOLT_NUMC			=0x13030001,		  //C相断相总次数 	
DLT645_BREAK_VOLT_TIMEA			=0x13010002,		  //A相断相总累计时间	
DLT645_BREAK_VOLT_TIMEB			=0x13020002,		  //B相断相总累计时间 
DLT645_BREAK_VOLT_TIMEC			=0x13030002,		  //C相断相总累计时间 
DLT645_BREAK_VOLT_LASTA			=0x13010101,		  //上1次A相断相	   
DLT645_BREAK_VOLT_LASTB			=0x13020101,		  //上1次B相断相	   
DLT645_BREAK_VOLT_LASTC			=0x13030101,		  //上1次C相断相	   
}DLT645_DI_DATA_T;




typedef struct
{

unsigned char   dlt_645_block_num;		 //数据块数目
unsigned int    dlt_645_di;				 //数据标识
unsigned int    dlt_645_seq; 			 //帧号

}DLT_645_Data_DOMAIN_T;					 //数据域内容
typedef struct
{
DLT_645_Data_DOMAIN_T dlt_645_data_domain;//数据域内容

unsigned char   dlt_645_dev_a0;			 //地址码0
unsigned char   dlt_645_dev_a1;			 //地址码1
unsigned char   dlt_645_dev_a2;			 //地址码2
unsigned char   dlt_645_dev_a3;			 //地址码3
unsigned char   dlt_645_dev_a4;			 //地址码4
unsigned char   dlt_645_dev_a5;			 //地址码5
unsigned char   dlt_645_ctrl;			 //控制码
unsigned char   dlt_645_data_len;		 //数据长度
unsigned char   dlt_645_read_mode;		 //读数据的模式（3种）
//发送报文时需给出以上信息（以下通过计算得到）
unsigned char   dlt_645_start;			 //起始码
unsigned char   dlt_645_cs;				 //校验
unsigned char   dlt_645_stop;			 //结束码
unsigned char   dlt_645_continue_count;	 //传输后续帧计数

}DLT_645_DATA_INFO_T;

typedef struct
{
DLT_645_DATA_INFO_T	dlt_645_dat_in_info;	  //输入数据信息（反馈解析报文的基础信息）
DLT_645_DATA_INFO_T	dlt_645_dat_out_info;	  //输出数据信息（填入发送报文的基础信息）
unsigned char * dlt_645_input;				  //需解析的报文
unsigned short  dlt_645_input_len;			  //解析报文长度
unsigned char * dlt_645_output;				  //发送报文最后存放地址
unsigned short *    dlt_645_output_len;		  //给出发送报文长度
unsigned char * dlt_645_data_input;			  //报文解析完成具体数据存放位置
unsigned char * dlt_645_data_output; 		  //输出报文需发送的具体数据位置
}DLT_645_MASTER_HANDLE_T;





typedef struct dlt645_nvram_t {//nvram data
    unsigned int demo_value;
} DLT645_NVRAM_T;

typedef struct dlt645_gpram_t {//gpram data
} DLT645_GPRAM_T;

typedef struct dlt645_t {
    DLT645_NVRAM_T nvram;
    DLT645_GPRAM_T gpram;
} DLT645_T;


/*-----------------模块对外接口变量声明-----------------------*/
extern DLT645_T dlt645;
extern DLT645_T dlt645;
extern DLT645_CTRL_COMMON_MASK_T g_dlt645_ctrl_common_mask;
extern DLT645_DI_DATA_T 	g_dlt645_di_data;
extern DLT645_CTRL_FUN_MASK_T g_dlt645_ctrl_fun_mask;


/*-----------------模块对外接口函数声明-----------------------*/
extern void* APP_Dlt645Thread(void *p_arg);
/*
发送解析调用同一个接口
使用对应功能需先挂在相应的接口数据
如：使用发送功能需将发送数据域数据地址和数据域数据长度挂在到相应的output参数集中（dlt_645_dat_out_info，dlt_645_output，dlt_645_output_len，dlt_645_data_output）
    使用报文解析功能同样需要此操作需挂载input数据及需解析的数据地址，解析完成数据信息会反馈到dlt_645_dat_in_info中数据域会存放到dlt_645_data_input中
*/
//modbus_master组帧及解析模块
void DLT_645_Master_function(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle); 

//BCD转10进制
int DLT_645_BCD2DEC(unsigned int s_dat);


#endif//#if __SYS_DLT645_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __APP_DLT645_TASK_H__





