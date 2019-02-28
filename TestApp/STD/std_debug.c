/**************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of WAN XING Tech. Co., Ltd.(C) 2020..
* 
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
***************************************************************************************************
*
* File name: std_debug.c
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
* Description:  This file defines cstd debug functions.
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

#include "std_globals.h"
#if __STD_DEBUG_ENABLE__
/*---------------------------------接口头文件--------------------------------*/
#include "std_debug.h"
#if __SYS_PRINT_UART1__
#include "drv_uart.h"
#endif

/*--------------------------------模块内宏定义-------------------------------*/

#define    PRINT_BUF_LEN       (4096)


/*--------------------------------模块内类定义-------------------------------*/



/*--------------------------------变量常量定义-------------------------------*/

static unsigned char print_buf[PRINT_BUF_LEN];


/*--------------------------------静态函数声明--------------------------------*/




/*************************************************************************************************/
                                   /* 函数定义 */
/*************************************************************************************************/

/******************************************************************************
* Function:    DRV_Print
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2012-12-15    Cris          1st                    created
*
*
******************************************************************************/
static void DRV_Print(unsigned char *pdat,unsigned int dat_len)
{
    #if __SYS_PRINT_UART1__
    DRV_Uart1Write(pdat,dat_len);
    #endif
}


/******************************************************************************
* Function:    DEBUG_Print
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2012-12-15    Cris          1st                    created
*
*
******************************************************************************/
void DEBUG_Print(char * format,...)
{	
    static unsigned int print_len=0;
    va_list args;
    va_start(args, format);
    print_len = vsprintf((char*)print_buf, format, args);
    va_end(args);
	printf("%s",print_buf);
    DRV_Print(print_buf,print_len);
}


/******************************************************************************
* Function:    DEBUG_PrintHex
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2012-12-15    Cris          1st                    created
*
*
******************************************************************************/
void DEBUG_PrintHex(UINT8_T *pdat, UINT32_T dat_len)
{
    unsigned int i;
    //DEBUG_Print("HEX: ");
    for (i = 0; i < dat_len; i++)
    {
        //DEBUG_Print("0x%.2X ",pdat[i]);
        DEBUG_Print("%.2X ",pdat[i]);
    }
    DEBUG_Print("\r\n");
}


/******************************************************************************
* Function:    DEBUG_PrintChar
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2012-12-15    Cris          1st                    created
*
*
******************************************************************************/
void DEBUG_PrintChar(UINT8_T *pdat, UINT32_T dat_len)
{
    unsigned int i;
    //DEBUG_Print("HEX: ");
    for (i = 0; i < dat_len; i++)
    {
        DEBUG_Print("%c",pdat[i]);
    }
}


#endif//#if __STD_DEBUG_ENABLE__

