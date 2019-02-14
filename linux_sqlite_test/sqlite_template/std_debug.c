/**************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of  CRIS Technologies, Inc.
* 
*  Copyright (C), 2010-2015 CRIS Technologies, Inc.
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
#if __SYS_DEBUG_SUPPORT__
/*---------------------------------�ӿ�ͷ�ļ�--------------------------------*/
#include "std_debug.h"
#if __SYS_PRINT_UART1__
#include "drv_uart.h"
#endif

/*--------------------------------ģ���ں궨��-------------------------------*/

#define    PRINT_BUF_LEN       (1024)


/*--------------------------------ģ�����ඨ��-------------------------------*/



/*--------------------------------������������-------------------------------*/

static unsigned char print_buf[PRINT_BUF_LEN];


/*--------------------------------��̬��������--------------------------------*/




/*************************************************************************************************/
                                   /* �������� */
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
void DEBUG_PrintHex(unsigned char *pdat,unsigned int dat_len)
{
    unsigned int i;
    //DEBUG_Print("HEX: ");
    for (i = 0; i < dat_len; i++)
    {
        DEBUG_Print("0x%.2X ",pdat[i]);
    }
    //DEBUG_Print("\r\n");
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
void DEBUG_PrintChar(unsigned char *pdat,unsigned int dat_len)
{
    
    //DEBUG_Print("CHAR: ");
    DRV_Print(pdat,dat_len);
    //DEBUG_Print("\r\n");
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
	DEBUG_Print("Wrong parameters value: file %s on line %d\r\n", file, line);
	while(1);
}
#endif

#endif//#if __SYS_DEBUG_SUPPORT__
