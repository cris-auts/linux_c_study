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
* File name: prtc_dlt645_func.c
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
* Description:  xxxxxxxxxxxxxxxxxxxxxxxx
*
* ------------------------------------------------------------------------
*
* History:
*
* Date                   Author             Change Id             Release Description Of Change
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
/*------------------------------------------------------------------*/
#include "std_globals.h"
#if __SYS_DLT645_ENABLE__
#include "prtc_dlt645_func.h"



/*-----------------------模块内宏定义-------------------------*/



/*----------------------模块内类定义--------------------------*/



/*----------------------变量常量定义--------------------------*/
DLT645_CTRL_COMMON_MASK_T g_dlt645_ctrl_common_mask;

DLT645_DI_DATA_T 	g_dlt645_di_data;
DLT645_CTRL_FUN_MASK_T g_dlt645_ctrl_fun_mask;

DLT645_T dlt645;

/*****************************************************************************/
                         /* 函数定义 */
/*****************************************************************************/

/******************************************************************************
* Function:    DLT_645_BCD2DEC
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/
int DLT_645_BCD2DEC(unsigned int s_dat)
{
	int s_temp=0;
	s_temp+=(unsigned char)(s_dat&0x0f);
	s_temp+=((unsigned char)(s_dat>>4)&0x0f)*10;
	s_temp+=((unsigned char)(s_dat>>8)&0x0f)*100;
	s_temp+=((unsigned char)(s_dat>>12)&0x0f)*1000;
	return s_temp;
}

/******************************************************************************
* Function:    DLT_645_CS
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

unsigned char DLT_645_CS(unsigned char * p_input_buff,unsigned short s_buff_len)
{
	 unsigned short  s_buff_count=0,s_cs=0;
	 for(s_buff_count=0;s_buff_count<s_buff_len;s_buff_count++)
	 	{
			s_cs+=p_input_buff[s_buff_count];
	 	}
	 return s_cs;
}

/******************************************************************************
* Function:    DLT_645_Strcat
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: 南瑞单项表数据域数据已+0x33数据导出时需减去0X33
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/
void DLT_645_Strcat(unsigned char *p_function_buff1,unsigned char *p_function_buff2,unsigned short s_function_len)
{
   unsigned short i=0;
   for(;i<s_function_len;i++)
	 {
	   p_function_buff1[i]=p_function_buff2[i]-0X33;
	 }
}



/******************************************************************************
* Function:    DLT_645_Master_Tx_data
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

//发送据帧(长度会也在句柄中的输出长度赋值)
void DLT_645_Master_Tx_data(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	unsigned char	s_dlt_645_master_cs=0;
    unsigned short  s_dlt_645_master_tmep=0,s_dlt_645_master_count=0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_start=DLT_645_START;    //自动补充头尾
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_stop=DLT_645_STOP;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_start;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a0;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a1;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a2;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a3;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a4;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a5;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_start;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_len;
	//将数据域数据填入发送区
	for(s_dlt_645_master_count=0;s_dlt_645_master_count<p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_len;s_dlt_645_master_count++)
		{
			p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_data_output[s_dlt_645_master_count];
		}
	s_dlt_645_master_cs=DLT_645_CS(p_dlt_645_master_handle->dlt_645_output,s_dlt_645_master_tmep);
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=s_dlt_645_master_cs;
	p_dlt_645_master_handle->dlt_645_output[s_dlt_645_master_tmep++]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_stop;
	*p_dlt_645_master_handle->dlt_645_output_len=s_dlt_645_master_tmep;
}





/******************************************************************************
* Function:    DLT_645_SET_DI02DI3
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/
void DLT_645_SET_DI02DI3(unsigned char * p_dlt645_out,unsigned int dlt645_di)
{
	p_dlt645_out[0]=(unsigned char)((dlt645_di))+0x33;
	p_dlt645_out[1]=(unsigned char)((dlt645_di)>>8)+0x33;
	p_dlt645_out[2]=(unsigned char)((dlt645_di)>>16)+0x33;
	p_dlt645_out[3]=(unsigned char)((dlt645_di)>>24)+0x33;
}


/******************************************************************************
* Function:    DLT_645_Master_Read_Data
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*   g_dlt645_master_handle.dlt_645_dat_out_info.dlt_645_read_mode=1;
	g_dlt645_master_handle.dlt_645_dat_out_info.dlt_645_data_domain.dlt_645_di=DLT645_MET_RUNWORD;
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/
void DLT_645_Master_Read_Data(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_READ_DATA_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_len=4;
	DLT_645_SET_DI02DI3(p_dlt_645_master_handle->dlt_645_data_output,p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_domain.dlt_645_di);
	if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_read_mode==2)  //读数据模式2
	{
		p_dlt_645_master_handle->dlt_645_data_output[4]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_domain.dlt_645_block_num;
		p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_len+=1;
#if DLT645_LOG_EN
		DLT645_LOG("DLT645_READ_MODE:2");
#endif		
	}
	else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_read_mode==3)
	{
#if DLT645_LOG_EN
				DLT645_LOG("DLT645_READ_MODE:3");
#endif

	}
	else
	{
#if DLT645_LOG_EN
		DLT645_LOG("DLT645_READ_MODE:1");
#endif
	}
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);

}
/******************************************************************************
* Function:    DLT_645_Master_ContinueRead_Data
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

// 68 a0 a1 a2 a3 a4 a5 68 12 9 1 2 3 4 5 6 7 8 9 33 16 
void DLT_645_Master_ContinueRead_Data(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_READ_DATA_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_len=5;
	DLT_645_SET_DI02DI3(p_dlt_645_master_handle->dlt_645_data_output,p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_domain.dlt_645_di);
	p_dlt_645_master_handle->dlt_645_data_output[4]=p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_domain.dlt_645_seq;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_Write_Data
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_Write_Data(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_WRITE_DATA_MASK;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_Read_Addr
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: 固格式68 aa aa aa aa aa aa 68 13 0 df 16 无需数据域
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/
void DLT_645_Master_Read_Addr(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_READ_ADDR_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_len=0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a0=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a1=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a2=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a3=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a4=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a5=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_len=0;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_Write_Addr
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_Write_Addr(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_WRITE_ADDR_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a0=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a1=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a2=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a3=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a4=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_dev_a5=0xaa;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_data_len=6;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_Calibration_Time
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_Calibration_Time(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CALIBRATION_TIME_MASK;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_Frozen
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_Frozen(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_FROZEN_MASK;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_Change_Speed
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_Change_Speed(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CHANGE_SPEED_MASK;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_Change_Password
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_Change_Password(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CHANGE_PASS_WORD_MASK;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_CL_MAX_Demand
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_CL_MAX_Demand(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CL_MAX_DEMAND_MASK;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_CL_Dev
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_CL_Dev(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CL_DEV_MASK;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}
/******************************************************************************
* Function:    DLT_645_Master_CL_Event
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_CL_Event(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
	
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl = 0;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_DIR_MASTER_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_ACK_OK_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CONTINUE_NULL_MASK;
	p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl |= DLT645_CTRL_CL_EVENT_MASK;
    DLT_645_Master_Tx_data(p_dlt_645_master_handle);
}


/******************************************************************************
* Function:    DLT_645_Master_function
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
* Others:
*
* -------------------------------------------------------------------
* History:
*     Date         Author     Change Id     Release Description Of Change
* 2019-02-20       chenyanan  1st           created
*
*
******************************************************************************/

void DLT_645_Master_function(DLT_645_MASTER_HANDLE_T * p_dlt_645_master_handle)
{
/*
=====================================发送645报文===============================================================
==================================输出数据指针非空===============================================
*/
    unsigned char s_dlt645_temp=0;
    if(p_dlt_645_master_handle->dlt_645_data_output != NULL)
    {
	    if (p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_READ_DATA_MASK)
	    {
		    DLT_645_Master_Read_Data(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_READ_COMP");
#endif		
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除
	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_CALIBRATION_TIME_MASK)
	    {
		    DLT_645_Master_Calibration_Time(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_CALIBRATION_TIME_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_CONTINUE_READ_DATA_MASK)
	    {
		    DLT_645_Master_ContinueRead_Data(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_CONTINUE_READ_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_READ_ADDR_MASK)
	    {
		    DLT_645_Master_Read_Addr(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_READ_ADDR_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除
	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_WRITE_DATA_MASK)
	    {
		    DLT_645_Master_Write_Data(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_WRITE_DATA_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_WRITE_ADDR_MASK)
	    {
		    DLT_645_Master_Write_Addr(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_WRITE_ADDR_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_FROZEN_MASK)
	    {
		    DLT_645_Master_Frozen(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_FROZEN_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_CHANGE_SPEED_MASK)
	    {
		    DLT_645_Master_Change_Speed(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_CHANGE_SPEED_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除


	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_CHANGE_PASS_WORD_MASK)
	    {
		    DLT_645_Master_Change_Password(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_CHANGE_PASS_WORD_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }

	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_CL_MAX_DEMAND_MASK)
	    {
		    DLT_645_Master_CL_MAX_Demand(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_CL_MAX_DEMAND_COMP");
#endif
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }
	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_CL_DEV_MASK)
	    {
		    DLT_645_Master_CL_Dev(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_CL_DEV_COMP");
#endif			
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }

	    else if(p_dlt_645_master_handle->dlt_645_dat_out_info.dlt_645_ctrl==DLT645_CTRL_CL_EVENT_MASK)
	    {
		    DLT_645_Master_CL_Event(p_dlt_645_master_handle);
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_CL_EVENT_COMP");
#endif		
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除

	    }
	    else
	    {
#if DLT645_LOG_EN
		    DLT645_LOG("DLT645_SEND_CTRL_CMD_ERR");
#endif			
		    p_dlt_645_master_handle->dlt_645_data_output=NULL;//发送完成将发送缓冲区从该句柄移除
	    }
    }
	else
	{
#if DLT645_LOG_EN
			DLT645_LOG("DLT645_LOSS_OUT_HANDLE");
#endif	
	}
/*
=====================================解析645报文===============================================================
==================================输入指针非空并且输入长度大于零===============================================
68 32 0 0 0 0 0 68 91 a 33 32 35 35 33 33 33 32 32 32 32 32 32 34 16(0)当前电流
68 32 0 0 0 0 0 68 91 16 32 38 33 37 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 33 16 (0)电表运行状态
68 32 0 0 0 0 0 68 91 7 33 40 63 36 33 33 33 3f 16 (1)
68 32 0 0 0 0 0 68 91 7 33 34 35 35 33 33 33 04 16 (1)
68 32 0 0 0 0 0 68 91 10 33 32 36 35 33 33 33 33 33 33 32 32 32 32 32 32 d1 16(1)有功功率
68 32 0 0 0 0 0 68 d1 1 35 9 16(1)无功功率
68 32 0 0 0 0 0 68 91 7 33 33 63 36 34 33 33 33 16(1)编程次数
68 32 0 0 0 0 0 68 d1 1 35 9 16(1)A相欠压总累计时间
68 32 0 0 0 0 0 68 91 7 35 34 33 37 58 3c 49 4a 16(1)电表时间
*/
	if((p_dlt_645_master_handle->dlt_645_input != NULL)&&(p_dlt_645_master_handle->dlt_645_input_len>0))
	{
#if DLT645_LOG_EN
		DLT645_LOG("DLT645_INPUT_OK");
#endif
		if((p_dlt_645_master_handle->dlt_645_input[0]==p_dlt_645_master_handle->dlt_645_input[7])&&(p_dlt_645_master_handle->dlt_645_input[0]==DLT_645_START))
		{
#if DLT645_LOG_EN
		DLT645_LOG("DLT645_STA_OK");
#endif
			if(p_dlt_645_master_handle->dlt_645_input[11+p_dlt_645_master_handle->dlt_645_input[9]]==DLT_645_STOP)
			{
#if DLT645_LOG_EN
				DLT645_LOG("DLT645_STO_OK");
#endif	
				if((p_dlt_645_master_handle->dlt_645_input[8]&DLT645_CTRL_DIR_SLAVER_MASK)==DLT645_CTRL_DIR_SLAVER_MASK)
				{
#if DLT645_LOG_EN
					DLT645_LOG("DLT645_DIR_OK");
#endif				
					s_dlt645_temp=DLT_645_CS(p_dlt_645_master_handle->dlt_645_input,10+p_dlt_645_master_handle->dlt_645_input[9]);
#if DLT645_LOG_EN
					DLT645_LOG("DLT645_CS_OK");
#endif

					if(s_dlt645_temp==p_dlt_645_master_handle->dlt_645_input[10+p_dlt_645_master_handle->dlt_645_input[9]])
					{
#if DLT645_LOG_EN
					DLT645_LOG("DLT645_LOAD_DATA");
#endif
						/*==============================提取报文信息=========================================================*/
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_cs=s_dlt645_temp;
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_ctrl=p_dlt_645_master_handle->dlt_645_input[8];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_data_len=p_dlt_645_master_handle->dlt_645_input[9];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_dev_a0=p_dlt_645_master_handle->dlt_645_input[1];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_dev_a1=p_dlt_645_master_handle->dlt_645_input[2];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_dev_a2=p_dlt_645_master_handle->dlt_645_input[3];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_dev_a3=p_dlt_645_master_handle->dlt_645_input[4];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_dev_a4=p_dlt_645_master_handle->dlt_645_input[5];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_dev_a5=p_dlt_645_master_handle->dlt_645_input[6];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_start=p_dlt_645_master_handle->dlt_645_input[0];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_data_len=p_dlt_645_master_handle->dlt_645_input[9];
						p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_stop=p_dlt_645_master_handle->dlt_645_input[11+p_dlt_645_master_handle->dlt_645_input[9]];
						//提取数据域
						DLT_645_Strcat(p_dlt_645_master_handle->dlt_645_data_input,&p_dlt_645_master_handle->dlt_645_input[10],p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_data_len);
						p_dlt_645_master_handle->dlt_645_input=NULL;//解析完成将输入从该句柄中移除
						if((p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_ctrl & DLT645_CTRL_CONTINUE_FLAG_MASK)==DLT645_CTRL_CONTINUE_FLAG_MASK)
						{
							p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_continue_count+=1;//后续帧号计数值
						}
						else
							p_dlt_645_master_handle->dlt_645_dat_in_info.dlt_645_continue_count=0;	
#if DLT645_LOG_EN
						DLT645_LOG("DLT645_FRAME_OK");
#endif
					}
				}
			}
		}
	}
	else
	{
#if DLT645_LOG_EN
		DLT645_LOG("DLT645_LOSS_IN_DATA_HANDLe_or_INPUT_LEN==0");
#endif	
	}
}

#endif//#if __SYS_DLT645_ENABLE__




