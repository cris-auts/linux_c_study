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


/*----------------------����ͷ�ļ�----------------------------*/
#include "std_globals.h"
#if __SYS_DLT645_ENABLE__

//#include "xxx_xxx.h"


/*----------------------�����궨��----------------------------*/
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


/*----------------------�����ඨ��----------------------------*/
/*
00000������
01000���㲥Уʱ
10001��������
10010������������
10011����ͨ�ŵ�ַ
10100��д����
10101��дͨ�ŵ�ַ
10110����������
10111������ͨ������
11000���޸�����
11001�������������
11010���������
11011���¼�����
*/

//�����ֹ�������
typedef enum 
{
DLT645_CTRL_NULL_MASK			  =0X00,		  //����
DLT645_CTRL_CALIBRATION_TIME_MASK  =0X08,		  //Уʱ
DLT645_CTRL_READ_DATA_MASK		  =0X11,		  //������
DLT645_CTRL_CONTINUE_READ_DATA_MASK=0X12,		  //����������
DLT645_CTRL_READ_ADDR_MASK		  =0X13,		  //��ͨ�ŵ�ַ
DLT645_CTRL_WRITE_DATA_MASK		  =0X14,		  //д����
DLT645_CTRL_WRITE_ADDR_MASK		  =0X15,		  //дͨ�ŵ�ַ
DLT645_CTRL_FROZEN_MASK			  =0X16,		  //����
DLT645_CTRL_CHANGE_SPEED_MASK	  =0X17,		  //����ͨ���ٶ�
DLT645_CTRL_CHANGE_PASS_WORD_MASK  =0X18,		  //����������
DLT645_CTRL_CL_MAX_DEMAND_MASK	  =0X19,		  //���������
DLT645_CTRL_CL_DEV_MASK			  =0X1A,		  //�������
DLT645_CTRL_CL_EVENT_MASK		  =0X1B,		  //�¼�����
DLT645_CTRL_ALARM_MASK			  =0X1C,		  //����.����բ.����
DLT645_CTRL_OUT_CTRL_MASK		  =0X1D,		  //�๦�ܶ����������
DLT645_CTRL_SAFETY_CERTIFICTAION_MASK=0X03,		  //��ȫ��֤

}DLT645_CTRL_FUN_MASK_T;



//��������ͨ����
typedef enum 
{
DLT645_CTRL_DIR_MASK 			  =0X80,		  //���䷽��
DLT645_CTRL_DIR_MASTER_MASK		  =0X00,		  //���䷽��(����)
DLT645_CTRL_DIR_SLAVER_MASK		  =0X80,		  //���䷽��(�ӻ�)

DLT645_CTRL_ACK_MASK 			  =0X40,		  //�ӻ�Ӧ��
DLT645_CTRL_ACK_OK_MASK			  =0X00,		  //�ӻ�����Ӧ��
DLT645_CTRL_ACK_ERR_MASK 		  =0X40,		  //�ӻ��쳣Ӧ��

DLT645_CTRL_CONTINUE_MASK		  =0X20,		  //����֡
DLT645_CTRL_CONTINUE_FLAG_MASK	  =0X20,		  //�к���֡
DLT645_CTRL_CONTINUE_NULL_MASK	  =0X00,		  //�޺���֡
}DLT645_CTRL_COMMON_MASK_T;



/*
NOTICE:
	   DIֵΪ0X0202FF00��DLT645_CRRT��������������ݸ���������
	   DIֵΪ0x040005FF��DLT645_MET_RUNWORD��������������������������
*/
//DIֵ
typedef enum 
{
DLT645_MET_RUNWORD				=0x040005FF,		  //�������״̬		
DLT645_MET_TIME					=0X04000102,		  //���ʱ��		  
DLT645_MET_DATE					=0X04000101,		  //�������		  
DLT645_VOLT						=0X0201FF00,		  //��ǰ��ѹ									
DLT645_CRRT						=0X0202FF00,		  //��ǰ����		  
DLT645_ACT_POW					=0X0203FF00,		  //�й�����		  
DLT645_REAL_POW					=0X0204FF00,		  //�޹����� 
DLT645_SZ_POW					=0X0205FF00,		  //ʵ�ڹ���			
DLT645_POW_FACT					=0X0206FF00,		  //��������		  
DLT645_COMP_ACTENGY				=0X0000FF00,		  //����й�����		 
DLT645_POS_ACTENGY				=0X0001FF00,		  //�����й�����		
DLT645_NEG_ACTENGY				=0X0002FF00,		  //�����й�����		
DLT645_COMP1_REAENGY 			=0X0003FF00,		  //���1�޹����� 	  
DLT645_COMP2_REAENGY 			=0X0004FF00,		  //���2�޹����� 	   
DLT645_QUAD1_REAENGY 			=0X0005FF00,		  //����1�޹����� 	
DLT645_QUAD2_REAENGY 			=0X0006FF00,		  //����2�޹����� 	
DLT645_QUAD3_REAENGY 			=0X0007FF00,		  //����3�޹����� 	
DLT645_QUAD4_REAENGY 			=0X0008FF00,		  //����4�޹����� 	
DLT645_EVT_PROG_NUM				=0X03300000,		  //��̴���			  
DLT645_EVT_PROG_LAST 			=0X03300001,		  //��1�α��			 
DLT645_EVT_CLRMET_NUM			=0X03300100,		  //����������		
DLT645_EVT_CLRMET_LAST			=0X03300101,		  //��1�ε������ 	 
DLT645_EVT_OPENTAB_NUM			=0X03300D00,		  //������ܴ���		
DLT645_EVT_OPENTAB_LAST			=0x03300D01,		  //��1�ο����	   
DLT645_LOSS_ENGY_NUM 			=0x03110000,		  //�����ܴ��� 	   
DLT645_LOSS_ENGY_LAST			=0x03110001,		  //��1�ε���		  
DLT645_ClEAR_ENGY_NEED_NUM		=0x03300200,		  //���������ܴ���	 
DLT645_ClEAR_ENGY_NEED_LAST		=0x03300201,		  //��1���������� 	
DLT645_CLEAR_EVENT_NUM			=0x03300300,		  //�¼������ܴ���	 
DLT645_CLEAR_EVENT_LAST			=0x03300301,		  //��1���¼����� 	
DLT645_PROTIME_NUM				=0x03300400,		  //Уʱ�ܴ��� 	   
DLT645_PROTIME_LAST				=0x03300401,		  //��1��Уʱ		  
DLT645_OPEN_JOINT_NUM			=0x03300E00,		  //����ť�ܴ���	  
DLT645_OPEN_JOINT_LAST			=0x03300E01,		  //��1�ο���ť 
DLT645_AllLOSS_VOLT_NUM			=0x03050000,		  //ȫʧѹ�ܴ���	  
DLT645_AllLOSS_VOLT_LAST 		=0x03050001,		  //��1��ȫʧѹ   
DLT645_REV_VOLT_NUM				=0x14000001,		  //��ѹ�������ܴ���	 
DLT645_REV_VOLT_LAST 			=0x14000101,		  //��1�ε�ѹ������	 
DLT645_LOSS_BLAI_NUM 			=0x16000001,		  //��ѹ��ƽ���ܴ���  
DLT645_LOSS_BLAI_LAST			=0x16000101,		  //��1�ε�ѹ��ƽ��	 
DLT645_LOSS_VOLT_NUMA			=0x10010001,		  //A��ʧѹ�ܴ��� 	
DLT645_LOSS_VOLT_NUMB			=0x10020001,		  //B��ʧѹ�ܴ��� 	
DLT645_LOSS_VOLT_NUMC			=0x10030001,		  //C��ʧѹ�ܴ��� 	
DLT645_LOSS_VOLT_TIME_NUMA		=0x10010002,		  //A��ʧѹ���ۼ�ʱ�� 
DLT645_LOSS_VOLT_TIME_NUMB		=0x10020002,		  //B��ʧѹ���ۼ�ʱ�� 
DLT645_LOSS_VOLT_TIME_NUMC		=0x10030002,		  //C��ʧѹ���ۼ�ʱ�� 
DLT645_LOSS_VOLT_LASTA			=0x10010101,		  //��1��A��ʧѹ	   
DLT645_LOSS_VOLT_LASTB			=0x10020101,		  //��1��B��ʧѹ	   
DLT645_LOSS_VOLT_LASTC			=0x10030101,		  //��1��C��ʧѹ	   
DLT645_OWE_VOLT_NUMA 			=0x11010001,		  //A��Ƿѹ�ܴ��� 	
DLT645_OWE_VOLT_NUMB 			=0x11020001,		  //B��Ƿѹ�ܴ��� 	
DLT645_OWE_VOLT_NUMC 			=0x11030001,		  //C��Ƿѹ�ܴ��� 	
DLT645_OWE_VOLT_TIMEA			=0x11010002,		  //A��Ƿѹ���ۼ�ʱ�� 
DLT645_OWE_VOLT_TIMEB			=0x11020002,		  //B��Ƿѹ���ۼ�ʱ�� 
DLT645_OWE_VOLT_TIMEC			=0x11030002,		  //C��Ƿѹ���ۼ�ʱ�� 
DLT645_OWE_VOLT_LASTA			=0x11010101,		  //��1��A��Ƿѹ	   
DLT645_OWE_VOLT_LASTB			=0x11020101,		  //��1��B��Ƿѹ	   
DLT645_OWE_VOLT_LASTC			=0x11030101,		  //��1��C��Ƿѹ	   
DLT645_BEYO_VOLT_NUMA			=0x12010001,		  //A���ѹ�ܴ��� 	
DLT645_BEYO_VOLT_NUMB			=0x12020001,		  //B���ѹ�ܴ��� 	
DLT645_BEYO_VOLT_NUMC			=0x12030001,		  //C���ѹ�ܴ��� 	
DLT645_BEYO_VOLT_TIMEA			=0x12010002,		  //A���ѹ���ۼ�ʱ�� 
DLT645_BEYO_VOLT_TIMEB			=0x12020002,		  //B���ѹ���ۼ�ʱ�� 
DLT645_BEYO_VOLT_TIMEC			=0x12030002,		  //B���ѹ���ۼ�ʱ�� 
DLT645_BEYO_VOLT_LASTA			=0x12010101,		  //��1��A���ѹ	
DLT645_BEYO_VOLT_LASTB			=0x12020101,		  //��1��B���ѹ		
DLT645_BEYO_VOLT_LASTC			=0x12030101,		  //��1��C���ѹ		  
DLT645_BREAK_VOLT_NUMA			=0x13010001,		  //A������ܴ��� 	
DLT645_BREAK_VOLT_NUMB			=0x13020001,		  //B������ܴ���   
DLT645_BREAK_VOLT_NUMC			=0x13030001,		  //C������ܴ��� 	
DLT645_BREAK_VOLT_TIMEA			=0x13010002,		  //A��������ۼ�ʱ��	
DLT645_BREAK_VOLT_TIMEB			=0x13020002,		  //B��������ۼ�ʱ�� 
DLT645_BREAK_VOLT_TIMEC			=0x13030002,		  //C��������ۼ�ʱ�� 
DLT645_BREAK_VOLT_LASTA			=0x13010101,		  //��1��A�����	   
DLT645_BREAK_VOLT_LASTB			=0x13020101,		  //��1��B�����	   
DLT645_BREAK_VOLT_LASTC			=0x13030101,		  //��1��C�����	   
}DLT645_DI_DATA_T;




typedef struct
{

unsigned char   dlt_645_block_num;		 //���ݿ���Ŀ
unsigned int    dlt_645_di;				 //���ݱ�ʶ
unsigned int    dlt_645_seq; 			 //֡��

}DLT_645_Data_DOMAIN_T;					 //����������
typedef struct
{
DLT_645_Data_DOMAIN_T dlt_645_data_domain;//����������

unsigned char   dlt_645_dev_a0;			 //��ַ��0
unsigned char   dlt_645_dev_a1;			 //��ַ��1
unsigned char   dlt_645_dev_a2;			 //��ַ��2
unsigned char   dlt_645_dev_a3;			 //��ַ��3
unsigned char   dlt_645_dev_a4;			 //��ַ��4
unsigned char   dlt_645_dev_a5;			 //��ַ��5
unsigned char   dlt_645_ctrl;			 //������
unsigned char   dlt_645_data_len;		 //���ݳ���
unsigned char   dlt_645_read_mode;		 //�����ݵ�ģʽ��3�֣�
//���ͱ���ʱ�����������Ϣ������ͨ������õ���
unsigned char   dlt_645_start;			 //��ʼ��
unsigned char   dlt_645_cs;				 //У��
unsigned char   dlt_645_stop;			 //������
unsigned char   dlt_645_continue_count;	 //�������֡����

}DLT_645_DATA_INFO_T;

typedef struct
{
DLT_645_DATA_INFO_T	dlt_645_dat_in_info;	  //����������Ϣ�������������ĵĻ�����Ϣ��
DLT_645_DATA_INFO_T	dlt_645_dat_out_info;	  //���������Ϣ�����뷢�ͱ��ĵĻ�����Ϣ��
unsigned char * dlt_645_input;				  //������ı���
unsigned short  dlt_645_input_len;			  //�������ĳ���
unsigned char * dlt_645_output;				  //���ͱ�������ŵ�ַ
unsigned short *    dlt_645_output_len;		  //�������ͱ��ĳ���
unsigned char * dlt_645_data_input;			  //���Ľ�����ɾ������ݴ��λ��
unsigned char * dlt_645_data_output; 		  //��������跢�͵ľ�������λ��
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


/*-----------------ģ�����ӿڱ�������-----------------------*/
extern DLT645_T dlt645;
extern DLT645_T dlt645;
extern DLT645_CTRL_COMMON_MASK_T g_dlt645_ctrl_common_mask;
extern DLT645_DI_DATA_T 	g_dlt645_di_data;
extern DLT645_CTRL_FUN_MASK_T g_dlt645_ctrl_fun_mask;


/*-----------------ģ�����ӿں�������-----------------------*/
extern void* APP_Dlt645Thread(void *p_arg);
/*
���ͽ�������ͬһ���ӿ�
ʹ�ö�Ӧ�������ȹ�����Ӧ�Ľӿ�����
�磺ʹ�÷��͹����轫�������������ݵ�ַ�����������ݳ��ȹ��ڵ���Ӧ��output�������У�dlt_645_dat_out_info��dlt_645_output��dlt_645_output_len��dlt_645_data_output��
    ʹ�ñ��Ľ�������ͬ����Ҫ�˲��������input���ݼ�����������ݵ�ַ���������������Ϣ�ᷴ����dlt_645_dat_in_info����������ŵ�dlt_645_data_input��
*/
//modbus_master��֡������ģ��
void DLT_645_Master_function(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle); 

//BCDת10����
int DLT_645_BCD2DEC(unsigned int s_dat);


#endif//#if __SYS_DLT645_ENABLE__

#ifdef __cplusplus
}
#endif
#endif //#ifndef __APP_DLT645_TASK_H__





