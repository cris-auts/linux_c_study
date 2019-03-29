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


/*----------------------����ͷ�ļ�----------------------------*/
//#include "std_globals.h"
#if 1


/*----------------------�ӿ�ͷ�ļ�----------------------------*/


/*----------------------�����궨��----------------------------*/
#define OPERATE_TABLE_SIMULTANE  1 //ͬʱ�������ű� 1ʹ�� 0ʧ��
#define OPERATE_TABLE_INCREMENT_ID  1 //������ID    1ʹ�� 0ʧ��
#define PORT_LIST_MAX  10	//�����˿��б�������
#define ID_NUM_MAX 20
#define MOBILE_COMM_PRM_MAX 10	//�ƶ�ͨ�Ų���������

/*----------------------�����ඨ��----------------------------*/
typedef enum sql_err
{
	SQL_OK,
	SQL_TABLE_EXIST,//���Ѵ���
	SQL_TABLE_ID_ERR,//��Ŵ���
	SQL_CMD_OVERFLOW,//SQLָ����ȶ����泤��
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
}COMM_PORT_T;//����ͨ��

typedef enum prtc_type
{
	PRTC_DLT698, //DLT698.45��Լ
	PRTC_MAINT	  //maintά����Լ
}PRTC_TYPE_T;//��Լ����

typedef enum mobile_comm_port
{
  MCP_MOBILE_2G,//�ƶ�2G
  MCP_MOBILE_4G,//�ƶ�4G
  MCP_MOBILE_IoT,//�ƶ�������
  MCP_TELECOM_2G,//����2G
  MCP_TELECOM_4G,//����4G
  MCP_TELECOM_IoT,//����������
  MCP_UNICOM_2G,//��ͨ2G
  MCP_UNICOM_4G,//��ͨ4G
  MCP_UNICOM_IoT,//��ͨ������
  MCP_CUSTOMIZE_NET//ר��
}MOBILE_COMM_PORT_T;//�ƶ�ͨ��ͨ��(��Ӫ��)

/*----------------------------------------------ͨ�����ñ�----------------------------------------------*/
typedef struct table_comm_cfg
{
	UINT16_T          cs;//У��
	UINT8_T           enable;//ʧ��(0)��ʹ��(1)
	UINT16_T		  cfg_sn;//�������
	COMM_PORT_T     comm_port;//����ͨ��
	union
	{
		struct  
		{
			UINT32_T bps;	//������
			UINT8_T check_bit;	//У��λ NONE(0)��ODD(1)��EVEN(2)
			UINT8_T data_bit;		//����λ 5λ(0)��6λ(1)��7λ(2)��8λ(3)
			UINT8_T stop_bit;	//ֹͣλ 1.5λ(0)��1λ(1)��2λ(2)
		}uart_cfg;//�ײ�uart����
		struct  
		{
			UINT8_T ip_type;			//ip���� IPV4(0) IPV6(1)
			UINT8_T ip_mode;        // DHCP��0������̬��1����PPPoE��2��
			UINT8_T ip_addr[6];       //IP��ַ  
			UINT8_T subnet_mask[6];  //��������    
			UINT8_T gateway_addr[6];  //���ص�ַ   
			UINT8_T dns_addr[6];		//DNS��ַ
			UINT8_T mac_addr[6];		//MAC��ַ
			UINT8_T ppoe_name[20]; //PPPoE�û��� 
			UINT8_T ppoe_passwd[20]; //PPPoE����    
		}eth_cfg;//�ײ���̫������
		struct
		{
			UINT8_T wifi_type;		//wifi���� �ȵ�ʧ��(0) �ȵ�ʹ��(1)
			UINT8_T ip_type;			//ip���� IPV4(0) IPV6(1)
			UINT8_T ip_mode;		// DHCP��0������̬��1����PPPoE��2��
			UINT8_T ip_addr[6]; 	  //IP��ַ	
			UINT8_T subnet_mask[6];  //��������    
			UINT8_T gateway_addr[6];  //���ص�ַ   
			UINT8_T dns_addr[6];		//DNS��ַ
			UINT8_T mac_addr[6];		//MAC��ַ
			UINT8_T ppoe_name[20]; //PPPoE�û��� 
			UINT8_T ppoe_passwd[20]; //PPPoE����	
		}wifi_cfg;//�ײ�wifi����
		struct  
		{
			MOBILE_COMM_PORT_T mobile_comm_port;//�ƶ�ͨ��ͨ��(��Ӫ��)
			UINT8_T apn[20];    //apn;
			UINT8_T username[20];    //�û���
			UINT8_T passwd[20];      //����
		}mobile_cfg[MOBILE_COMM_PRM_MAX];//�ײ��ƶ�ͨ������
	}port_cfg;
}TABLE_COMM_CFG_T,*P_TABLE_COMM_CFG_T;

/*----------------------------------------------ͨ�Ų�����----------------------------------------------*/
typedef struct table_comm_prm
{
	UINT16_T          cs;//У��
	UINT8_T            enable;//ʧ��(0)��ʹ��(1)
	UINT16_T			  cfg_sn;//�������
	PRTC_TYPE_T      prtc_type;//��Լ����
	UINT8_T			  prtc_level;//��ԼȨ�޵ȼ� 	��(0)����(1)
	COMM_PORT_T      comm_port;//����ͨ��
	UINT8_T run_mode;//����ģʽ   �ͻ���(0)��������(1)�����ģʽ(2)
	UINT8_T link_mode;//����ģʽ   TCP(0)��UDP(1)
	UINT8_T link_app_mode;//����Ӧ��ģʽ  ����ģʽ(0)��������ģʽ(1)
	union
	{
		/*���нӿڲ���*/
		struct
		{
			UINT32_T resend_count;       //�ط�����
			UINT32_T timeout;            //��ʱʱ��
			UINT32_T time_wait;          //���͵ȴ����ʱ��
		}uart_prm;
		/*��̫������*/
		struct
		{
			UINT8_T ip_type;           //ip���� IPV4(0) IPV6(1)
			UINT8_T ip[6];				//ip��ַ
			UINT32_T port_num;         //�˿ں�
			UINT8_T ip_backup_type;    //����ip����
			UINT8_T ip_backup [6];		//����ip��ַ
			UINT32_T port_backup_num;  //���ö˿ں�
			UINT32_T port_list_num;     //�����˿��б���Ч���ݳ���
			UINT32_T port_list[PORT_LIST_MAX];          //�����˿��б�
			UINT8_T ip_proxy_type;     //����ip����
			UINT8_T ip_proxy [6];		//����ip��ַ
			UINT32_T port_proxy_num;    //����˿ں�
			UINT32_T resend_count;       //�ط�����
			UINT32_T timeout;            //��ʱʱ��
			UINT32_T time_wait;          //���͵ȴ����ʱ��
			UINT32_T cardiac_cycle;        //��������		
		}eth_prm;
		/*WIFI����*/
		struct
		{
			UINT8_T user_name[20];//�û���
			UINT8_T user_passwd[20];//����
			UINT8_T root_name[20];//root��
			UINT8_T root_passwd[20];//root����
			UINT8_T ip_type;           //ip���� IPV4(0) IPV6(1)
			UINT8_T ip[6];				//ip��ַ
			UINT32_T port_num;         //�˿ں�
			UINT8_T ip_backup_type;    //����ip����
			UINT8_T ip_backup [6];		//����ip��ַ
			UINT32_T port_backup_num;  //���ö˿ں�
			UINT32_T port_list_num;     //�����˿��б���Ч���ݳ���
	        UINT32_T port_list[PORT_LIST_MAX];          //�����˿��б�
			UINT32_T resend_count;       //�ط�����
			UINT32_T timeout;            //��ʱʱ��
			UINT32_T time_wait;          //���͵ȴ����ʱ��
			UINT32_T cardiac_cycle;      //��������
		}wifi_prm;
		/*�ƶ�ͨ�Ų���*/
		struct
		{            
			MOBILE_COMM_PORT_T mobile_comm_port;//�ƶ�ͨ��ͨ��(��Ӫ��)
			UINT8_T ip_type;           //ip���� IPV4(0) IPV6(1)
			UINT8_T ip[6];				//ip��ַ
			UINT32_T port_num;         //�˿ں�
			UINT8_T ip_backup_type;    //����ip����
			UINT8_T ip_backup[6];		//����ip��ַ
			UINT32_T port_backup_num;  //���ö˿ں�
			UINT8_T online_mode;      //����ģʽ 0����������1����������
			UINT32_T port_list_num;     //�����˿��б���Ч���ݳ���
	        UINT32_T port_list[PORT_LIST_MAX];          //�����˿��б�
			UINT32_T resend_count;     //�ط�����
			UINT32_T timeout;           //��ʱʱ��
			UINT32_T time_wait;          //���͵ȴ����ʱ��
			UINT32_T cardiac_cycle;      //��������
		}mobile_prm[MOBILE_COMM_PRM_MAX];
	}port_prm;
}TABLE_COMM_PRM_T,*P_TABLE_COMM_PRM_T;
/*----------------------------------------------�ܱ�----------------------------------------------*/
typedef enum table_id_t
{
	SQL_TABLE_COMM_CFG,
	SQL_TABLE_COMM_PRM,
	SQL_TABLE_MAX
}SQL_TABLE_ID_T;

/*-----------------ģ�����ӿڱ�������-----------------------*/
//extern    xxxxx;


/*-----------------ģ�����ӿں�������-----------------------*/
extern DBASE_ERR_T DBASE_OpenDataBase(const char *db_name);
extern DBASE_ERR_T DBASE_CloseDataBase();

/*-----------------ͨ�����ñ�ӿں�������-----------------------*/
//��ѯ���¼����
extern DBASE_ERR_T DBASE_QueryCommCfgRecordNum(UINT32_T *total_num);
//��ѯ�������������
extern DBASE_ERR_T DBASE_QueryCommCfgRecordCfgSn(UINT16_T *cfg_sn);
//����������Ų�ѯ���ò���
extern DBASE_ERR_T DBASE_SelectCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_comm_cfg);
//�����������������ò���
extern DBASE_ERR_T DBASE_InsertCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_comm_cfg);
//����������Ÿ������ò���
extern DBASE_ERR_T DBASE_UpdateCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_comm_cfg);
//�����������ɾ�����ò���
extern DBASE_ERR_T DBASE_DelectCommCfgAccordCfgSn(UINT16_T cfg_sn);
//��ձ�
extern DBASE_ERR_T DBASE_ClearCommCfgRecord();

/*-----------------ͨ�²�����ӿں�������-----------------------*/
//��ѯ���¼����
extern DBASE_ERR_T DBASE_QueryCommPrmRecordNum(UINT32_T *total_num);
//��ѯ�������������
extern DBASE_ERR_T DBASE_QueryCommPrmRecordCfgSn(UINT16_T *cfg_sn);
//����������Ų�ѯ���ò���
extern DBASE_ERR_T DBASE_SelectCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_comm_cfg);
//�����������������ò���
extern DBASE_ERR_T DBASE_InsertCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_comm_cfg);
//����������Ÿ������ò���
extern DBASE_ERR_T DBASE_UpdateCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_comm_cfg);
//�����������ɾ�����ò���
extern DBASE_ERR_T DBASE_DelectCommPrmAccordCfgSn(UINT16_T cfg_sn);
//��ձ�
extern DBASE_ERR_T DBASE_ClearCommPrmRecord();

#endif//#if __SYS_DBASE_ENABLE__
#ifdef __cplusplus
}
#endif
#endif //#ifndef __DB_H__




