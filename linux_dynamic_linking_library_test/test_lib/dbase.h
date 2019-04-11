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
#include "std_globals.h"
#if __SYS_DBASE_ENABLE__


/*----------------------�ӿ�ͷ�ļ�----------------------------*/
//#include "xxx_xxx.h"


/*----------------------�����궨��----------------------------*/
#define OPERATE_TABLE_SIMULTANE  1 //ͬʱ�������ű� 1ʹ�� 0ʧ��
#define OPERATE_TABLE_INCREMENT_ID  1 //������ID    1ʹ�� 0ʧ��
#define PORT_LIST_MAX  10	//�����˿��б�������
#define ID_NUM_MAX 20
#define MOBILE_COMM_PRM_MAX 10	//�ƶ�ͨ�Ų���������

/*----------------------�����ඨ��----------------------------*/
typedef enum dbase_err
{
	DBASE_OK,//�ɹ�
	DBASE_NO_RECORD,//�޸ü�¼
	DBASE_MULTI_CFGSN,//��������ظ�(��Ψһ)
	DBASE_CHECK_ERR,//У�����
	DBASE_FAIL//ʧ��
}DBASE_ERR_T;

typedef enum table_id_t
{
	DBASE_TABLE_COMM_CFG,
	DBASE_TABLE_COMM_PRM,
	DBASE_TABLE_MAX
}DBASE_TABLE_ID_T;

typedef enum client_ip_index_t
{
	CLIENT_IP_NUM0=0,	 	//�ͻ�����ȡ�����������ID
	CLIENT_IP_NUM1=1,       //�ͻ�����ȡ��IP1
	CLIENT_IP_NUM2=2	       //�ͻ�����ȡ����IP2
}CLIENT_IP_INDEX_T;

typedef enum prm_stat_t
{
	PRM_DISABLE = 0,	//������Ч
	PRM_ENABLE = 1 	//������Ч
}PRM_STAT_T;//����״̬

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

typedef enum prtc_level
{
	PRTC_LEVEL_0,//��߼�
	PRTC_LEVEL_1
}PRTC_LEVEL_T;//��ԼȨ�޵ȼ�

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

typedef enum run_mode_t
{
	RUN_MODE_MIX = 0,   //���ģʽ(0)
	RUN_MODE_CLIENT = 1,  //�ͻ���(1)
	RUN_MODE_SEVER = 2   //������(2)
}RUN_MODE_T;//����ģʽ

typedef enum link_mode_t
{
	LINK_MODE_TCP = 0, //TCP
	LINK_MODE_UDP = 1 //UDP
}LINK_MODE_T;//����ģʽ

typedef enum link_app_mode_t
{
	LINK_APP_MODE_BACKUP = 0, //����ģʽ
	LINK_APP_MODE_ALL = 1		//������
}LINK_APP_MODE_T;//����Ӧ��ģʽ

/*----------------------------------------------ͨ�����ñ�----------------------------------------------*/
typedef struct table_comm_cfg
{
	UINT16_T          cs;//У��
	PRM_STAT_T       enable;//ʧ��(0)��ʹ��(1)
	UINT16_T			 cfg_sn;//�������
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
	PRM_STAT_T        enable;//ʧ��(0)��ʹ��(1)
	UINT16_T			  cfg_sn;//�������
	PRTC_TYPE_T      prtc_type;//��Լ����
	PRTC_LEVEL_T	 prtc_level;//��ԼȨ�޵ȼ�
	UINT32_T          prtc_buff_size;//��Լռ�û������ߴ�
	COMM_PORT_T      comm_port;//����ͨ��
	RUN_MODE_T 		  run_mode;//����ģʽ   ���ģʽ(0)���ͻ���(1)��������(2)
	LINK_MODE_T 	  link_mode;//����ģʽ   TCP(0)��UDP(1)
	LINK_APP_MODE_T link_app_mode;//����Ӧ��ģʽ  ����ģʽ(0)��������ģʽ(1)
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
			UINT16_T port_num;         //�˿ں�
			UINT8_T ip_backup_type;    //����ip����
			UINT8_T ip_backup [6];		//����ip��ַ
			UINT16_T port_backup_num;  //���ö˿ں�
			UINT32_T port_list_num;     //�����˿��б���Ч���ݳ���
			UINT16_T port_list[PORT_LIST_MAX];          //�����˿��б�
			UINT8_T ip_proxy_type;     //����ip����
			UINT8_T ip_proxy [6];		//����ip��ַ
			UINT16_T port_proxy_num;    //����˿ں�
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
/*-----------------ģ�����ӿڱ�������-----------------------*/


#endif//#if __SYS_DBASE_ENABLE__
#ifdef __cplusplus
}
#endif
#endif //#ifndef __DBASE_H__




