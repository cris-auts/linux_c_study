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
* File name: std_types.h
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
* Description:  This file defines all customer-standard data types for
*               the project.
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

#ifndef __STD_TYPES_H__
#define __STD_TYPES_H__

#if (__DEBUG_IN_32BIT_SYSTEM__)
typedef char               		   CHAR_T;               /* Signed    8 bit quantity           */
typedef signed char                SCHAR_T;              /* Signed    8 bit quantity           */
typedef unsigned char              UCHAR_T;              /* Unsigned  8 bit quantity           */

typedef short                      SHORT_T;               /* Signed   16 bit quantity           */
typedef short                      SSHORT_T;              /* Signed   16 bit quantity           */
typedef unsigned short             USHORT_T;              /* Unsigned   16 bit quantity           */

typedef int                        INT_T;                /* Signed  int         */
typedef int                        SINT_T;               /* Signed  int         */
typedef unsigned int               UINT_T;               /* Unsigned int       */

typedef long                   	   LONG_T;              /* Signed   32 bit quantity           */
typedef long                       SLONG_T;             /* Signed   32 bit quantity           */
typedef unsigned long              ULONG_T;             /* Unsigned   32 bit quantity           */

typedef long long                  LLONG_T;              /* Signed   64 bit quantity           */
typedef long long                  SLLONG_T;             /* Signed   64 bit quantity           */
typedef unsigned long long         ULLONG_T;             /* Unsigned   64 bit quantity           */

typedef float                      FLOAT_T;              /* Single precision floating point    */
typedef double                     DOUBLE_T;             /* Double precision floating point    */


typedef char                	   INT8_T;                 /* Signed    8 bit quantity           */
typedef signed char                SINT8_T;                /* Signed    8 bit quantity           */
typedef unsigned char              UINT8_T;                /* Unsigned  8 bit quantity           */
typedef unsigned char              BYTE_T;                 /* Unsigned  8 bit quantity           */


typedef short                      INT16_T;                /* Signed   16 bit quantity           */
typedef signed short               SINT16_T;               /* Signed   16 bit quantity           */
typedef unsigned short             UINT16_T;               /* Unsigned 16 bit quantity           */
typedef unsigned short             WORD_T;                 /* Unsigned 16 bit quantity           */
typedef unsigned short             WCHAR_T;                /* Unsigned 16 bit quantity           */

typedef int                        INT32_T;                /* Signed   32 bit quantity           */
typedef signed int                 SINT32_T;               /* Signed   32 bit quantity           */
typedef unsigned int               UINT32_T;               /* Unsigned 32 bit quantity           */
typedef unsigned int               DWORD_T;                /* Unsigned 32 bit quantity           */

typedef long long                  INT64_T;                /* Signed   64 bit quantity           */
typedef unsigned long long         UINT64_T;               /* Unsigned 64 bit quantity           */
typedef signed long long           SINT64_T;               /* Signed   64 bit quantity           */

typedef float                      FP32_T;                 /* Single precision floating point    */
typedef double                     FP64_T;                 /* Double precision floating point    */
//typedef long double                FP64_T;                   /* Double precision floating point    */

#else//default
#warning "No compiler define, use default compiler type config!"
//#error "No compiler define, use default compiler type config!"
typedef int                        INT_T;                /* Signed  int         */
typedef int                        SINT_T;                /* Signed  int         */
typedef unsigned int               UINT_T;                /* Unsigned int       */

typedef signed char                INT8_T;                 /* Signed    8 bit quantity           */
typedef unsigned char              UINT8_T;                /* Unsigned  8 bit quantity           */
typedef signed char                SINT8_T;                /* Signed    8 bit quantity           */
typedef signed char                CHAR_T;                /* Signed    8 bit quantity           */
typedef unsigned char              UCHAR_T;                /* Unsigned  8 bit quantity           */
typedef signed char                SCHAR_T;                /* Signed    8 bit quantity           */
typedef unsigned char              BYTE_T;                 /* Unsigned  8 bit quantity           */

typedef short                      INT16_T;                /* Signed   16 bit quantity           */
typedef unsigned short             UINT16_T;               /* Unsigned 16 bit quantity           */
typedef signed short               SINT16_T;               /* Signed   16 bit quantity           */
typedef unsigned short             WORD_T;                 /* Unsigned 16 bit quantity           */
typedef unsigned short             WCHAR_T;                /* Unsigned 16 bit quantity           */

typedef int                        INT32_T;                /* Signed   32 bit quantity           */
typedef unsigned int               UINT32_T;               /* Unsigned 32 bit quantity           */
typedef signed int                 SINT32_T;               /* Signed   32 bit quantity           */
typedef unsigned int               DWORD_T;                /* Unsigned 32 bit quantity           */

typedef long long                  INT64_T;                /* Signed   64 bit quantity           */
typedef unsigned long long         UINT64_T;               /* Unsigned 64 bit quantity           */
typedef signed long long           SINT64_T;               /* Signed   64 bit quantity           */

typedef float                      FP32_T;                 /* Single precision floating point    */
typedef double                     FP64_T;                 /* Double precision floating point    */
//typedef long double                FP64_T;                   /* Double precision floating point    */

typedef int                        int_t;                /* Signed  int         */
typedef int                        sint_t;                /* Signed  int         */
typedef unsigned int               uint_t;                  /* Unsigned int       */

typedef signed char                int8_t;                 /* Signed    8 bit quantity           */
typedef unsigned char              uint8_t;                /* Unsigned  8 bit quantity           */
typedef signed char                sint8_t;                /* Signed    8 bit quantity           */
typedef signed char                char_t;                /* Signed    8 bit quantity           */
typedef unsigned char              uchar_t;                /* Unsigned  8 bit quantity           */
typedef signed char                schar_t;                /* Signed    8 bit quantity           */
typedef unsigned char              byte_t;                 /* Unsigned  8 bit quantity           */

typedef short                      int16_t;                /* Signed   16 bit quantity           */
typedef unsigned short             uint16_t;               /* Unsigned 16 bit quantity           */
typedef signed short               sint16_t;               /* Signed   16 bit quantity           */
typedef unsigned short             word_t;                 /* Unsigned 16 bit quantity           */
typedef unsigned short             wchar_t;                /* Unsigned 16 bit quantity           */

typedef int                        int32_t;                /* Signed   32 bit quantity           */
typedef unsigned int               uint32_t;               /* Unsigned 32 bit quantity           */
typedef signed int                 sint32_t;               /* Signed   32 bit quantity           */
typedef unsigned int               dword_t;                /* Unsigned 32 bit quantity           */

typedef long long                  int64_t;                /* Signed   64 bit quantity           */
typedef unsigned long long         uint64_t;               /* Unsigned 64 bit quantity           */
typedef signed long long           sint64_t;               /* Signed   64 bit quantity           */

typedef float                      fp32_t;                 /* Single precision floating point    */
typedef double                     fp64_t;                 /* Double precision floating point    */
//typedef long double                fp64_t;                   /* Double precision floating point    */


#endif//#if (__DEBUG_STM32_IN_MDK__)


//-------------------------------------------------------------------------------------------------------

#ifndef TRUE
#define TRUE                       (bool)(1==1)
#endif

#ifndef FALSE
#define FALSE                      (bool)(1==0)
#endif


#ifndef NULL
#define NULL                       (0)
#endif


#define ERR_NONE                       	(0)//无错误
#define ERR_INVAILD                    	(1)//无效参数
#define ERR_TIMEOUT                    	(2)//超时
#define ERR_BUSY                 	   	(3)//忙
#define ERR_VERIFYERR                 	(4)//校验错误
#define ERR_UNKNOWN              		(0xff)//未知错误


typedef enum demo_enum_t {
    DEMO_ENUM1,
} DEMO_ENUM_T; 


#define  BUFFER_SIZE 512



typedef struct msg_t{
    LONG_T msg_type;
    CHAR_T msg_text[BUFFER_SIZE];
}MSG_T;
#endif//#ifndef __STD_TYPES_H__



