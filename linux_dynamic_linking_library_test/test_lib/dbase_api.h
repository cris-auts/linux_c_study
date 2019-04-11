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
* File name: dbase_api.h
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
#ifndef __DBASE_API_H__
#define __DBASE_API_H__
#ifdef __cplusplus
extern "C" {
#endif


/*----------------------����ͷ�ļ�----------------------------*/
#include "std_globals.h"
#if __SYS_DBASE_ENABLE__
/*----------------------�ӿ�ͷ�ļ�----------------------------*/
#include "dbase.h"


/*----------------------�����궨��----------------------------*/
/*-----------------ģ�����ӿڱ�������-----------------------*/



/*-----------------ģ�����ӿں�������-----------------------*/
extern void DBASE_LogEnable(UINT8_T enable);
extern DBASE_ERR_T DBASE_Init();
extern DBASE_ERR_T DBASE_DeInit();
extern DBASE_ERR_T DBASE_OpenDataBase();
extern DBASE_ERR_T DBASE_CloseDataBase();

/*-----------------ͨ�����ñ�ӿں�������-----------------------*/
//��ѯ���¼����
extern DBASE_ERR_T DBASE_QueryCommCfgRecordNum(UINT32_T *total_num);
//��ѯ�������������
extern DBASE_ERR_T DBASE_QueryCommCfgRecordCfgSn(UINT16_T *cfg_sn,UINT32_T num_lim_max);
//����������Ų�ѯ���ò���
extern DBASE_ERR_T DBASE_SelectCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_buff);
//�����������������ò���
extern DBASE_ERR_T DBASE_InsertCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_buff);
//����������Ÿ������ò���
extern DBASE_ERR_T DBASE_UpdateCommCfgAccordCfgSn(P_TABLE_COMM_CFG_T p_buff);
//�����������ɾ�����ò���
extern DBASE_ERR_T DBASE_DeleteCommCfgAccordCfgSn(UINT16_T cfg_sn);
//��ձ�
extern DBASE_ERR_T DBASE_ClearCommCfgRecord();

/*-----------------ͨ�Ų�����ӿں�������-----------------------*/
//��ѯ���¼����
extern DBASE_ERR_T DBASE_QueryCommPrmRecordNum(UINT32_T *total_num);
//��ѯ�������������
extern DBASE_ERR_T DBASE_QueryCommPrmRecordCfgSn(UINT16_T *cfg_sn,UINT32_T num_lim_max);
//����������Ų�ѯ���ò���
extern DBASE_ERR_T DBASE_SelectCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_buff);
//�����������������ò���
extern DBASE_ERR_T DBASE_InsertCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_buff);
//����������Ÿ������ò���
extern DBASE_ERR_T DBASE_UpdateCommPrmAccordCfgSn(P_TABLE_COMM_PRM_T p_buff);
//�����������ɾ�����ò���
extern DBASE_ERR_T DBASE_DeleteCommPrmAccordCfgSn(UINT16_T cfg_sn);
//��ձ�
extern DBASE_ERR_T DBASE_ClearCommPrmRecord();

#endif//#if __SYS_DBASE_ENABLE__
#ifdef __cplusplus
}
#endif
#endif //#ifndef __DBASE_API_H__




