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
/*---------------------------------�ӿ�ͷ�ļ�--------------------------------*/
//#include "xxx_xxx.h"



/*---------------------------------ģ��궨��--------------------------------*/


/*---------------------------------ģ���ඨ��--------------------------------*/


/*-------------------------------������������-------------------------------*/
//extern    xxxxx;



/*-------------------------------�����ӿ�����-------------------------------*/
extern UINT16_T GetDatCheckSum(UINT8_T* pdat,UINT16_T len);
extern UINT16_T GetDatKeyCheckSum(UINT16_T cs_key,UINT8_T* pdat,UINT16_T len);



#endif//#if __STD_FUNCS_ENABLE__


#ifdef __cplusplus
}
#endif
#endif //#ifndef __STD_FUNCS_H__






