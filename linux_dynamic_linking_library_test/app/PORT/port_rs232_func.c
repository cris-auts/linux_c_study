/********************************************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of WAN XING Tech. Co., Ltd.(C) 2020.
*
*  Copyright (C), 2018-2030, WAN XING Tech. Co., Ltd.
*
*********************************************************************************************************
*
* File name: port_rs232_func.c
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
#if __SYS_RS232_ENABLE__
#include "port_rs232_func.h"



/*-----------------------模块内宏定义-------------------------*/
#define    RS232_RX_DAT_Q_SIZE     (8)
#define    RS232_TX_DAT_Q_SIZE     (8)

#define    RS232_RX_DAT_BUF_SIZE     (512)
#define    RS232_TX_DAT_BUF_SIZE     (512)


/*----------------------模块内类定义--------------------------*/
typedef struct rs232_rx_buf_t{
	UINT32_T len;
	UINT8_T  buf[RS232_RX_DAT_BUF_SIZE];
}RS232_RX_BUF_T;

typedef struct rs232_tx_buf_t{
	UINT32_T len;
	UINT8_T  buf[RS232_TX_DAT_BUF_SIZE];
}RS232_TX_BUF_T;

typedef struct rs232_rx_ringbuf_t{
	UINT32_T rd;
	UINT32_T wr;
	RS232_RX_BUF_T  rx_buf[RS232_RX_DAT_Q_SIZE];
}RS232_RX_RINGBUF_T;

typedef struct rs232_tx_ringbuf_t{
	UINT32_T rd;
	UINT32_T wr;
	RS232_TX_BUF_T  tx_buf[RS232_TX_DAT_Q_SIZE];
}RS232_TX_RINGBUF_T;



/*----------------------变量常量定义--------------------------*/


RS232_RX_RINGBUF_T rs232_rx_ringbuf;
RS232_TX_RINGBUF_T rs232_tx_ringbuf;



/*****************************************************************************/
                         /* 函数定义 */
/*****************************************************************************/

/******************************************************************************
* Function:    PORT_Rs232Init
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
int PORT_Rs232Init(const char *dev_path)
{
	int fd;                          
	printf("dev_path=%s\n",dev_path);

	fd = open(dev_path, O_RDWR|O_NOCTTY|O_NDELAY);	
	if(fd<=0)  
	{  
	   perror("Can't Open Serial Port");  
	   return (-1);  
	}  
	//恢复串口为阻塞状态		
	
	printf("Open Serial Port,fd=%d!\n",fd);	
	if(fcntl(fd, F_SETFL, 0) < 0)  
	{  
	   printf("fcntl failed!\n");  
	   return(-1);  
	}	   
	else  
	{  
	   printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));  
	}  
	
	//测试是否为终端设备	  
	if(0 == isatty(STDIN_FILENO))  
	{  
	   printf("standard input is not a terminal device\n");  
	   return(-1);  
	}  
	else  
	{  
	   printf("isatty success!\n");  
	}				
	printf("fd->open=%d\n",fd);	
	return fd;  
}


/******************************************************************************
* Function:    PORT_Rs232Cfg
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
int PORT_Rs232Cfg(int fd,int band_rate,int flow_ctrl,int data_bits,int stop_bits,int parity)
{  
	 
	int   i;  
	int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};  
	int   name_arr[] = {115200,  19200,  9600,	4800,  2400,  1200,  300};	
		   
	struct termios options;  
	 
	/*tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数还可以测试配置是否正确，该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1. 
	*/	
	if( tcgetattr( fd,&options)  !=  0)  
	{  
		perror("SetupSerial 1");	  
		return(FALSE);	 
	}  
	
	//设置串口输入波特率和输出波特率  
	for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)  
	{  
		if	(band_rate == name_arr[i])	
		{				
			cfsetispeed(&options, speed_arr[i]);   
			cfsetospeed(&options, speed_arr[i]);	
		}  
	}		
	 
	//修改控制模式，保证程序不会占用串口  
	options.c_cflag |= CLOCAL;	
	//修改控制模式，使得能够从串口中读取输入数据  
	options.c_cflag |= CREAD;  
	
	//设置数据流控制  
	switch(flow_ctrl)  
	{  
		
		case 0 ://不使用流控制  
			  options.c_cflag &= ~CRTSCTS;	
			  break;	 
		
		case 1 ://使用硬件流控制  
			  options.c_cflag |= CRTSCTS;  
			  break;  
		case 2 ://使用软件流控制  
			  options.c_cflag |= IXON | IXOFF | IXANY;	
			  break;  
	}  
	//设置数据位  
	//屏蔽其他标志位  
	options.c_cflag &= ~CSIZE;	
	switch (data_bits)  
	{	 
		case 5	  :  
					 options.c_cflag |= CS5;  
					 break;  
		case 6	  :  
					 options.c_cflag |= CS6;  
					 break;  
		case 7	  : 	 
				 options.c_cflag |= CS7;  
				 break;  
		case 8: 	 
				 options.c_cflag |= CS8;  
				 break;    
		default:	 
				 fprintf(stderr,"Unsupported data size\n");  
				 return (FALSE);   
	}  
	//设置校验位  
	switch (parity)  
	{	 
		case 'n':  
		case 'N': //无奇偶校验位。  
				 options.c_cflag &= ~PARENB;   
				 options.c_iflag &= ~INPCK; 	 
				 break;   
		case 'o':	 
		case 'O'://设置为奇校验	   
				 options.c_cflag |= (PARODD | PARENB);	 
				 options.c_iflag |= INPCK;				 
				 break;   
		case 'e':	
		case 'E'://设置为偶校验	 
				 options.c_cflag |= PARENB; 		
				 options.c_cflag &= ~PARODD;		 
				 options.c_iflag |= INPCK;		  
				 break;  
		case 's':  
		case 'S': //设置为空格   
				 options.c_cflag &= ~PARENB;  
				 options.c_cflag &= ~CSTOPB;  
				 break;   
		default:	
				 fprintf(stderr,"Unsupported parity\n");	  
				 return (FALSE);   
	}	
	// 设置停止位	 
	switch (stop_bits)  
	{	 
		case 1: 	
				 options.c_cflag &= ~CSTOPB; break;   
		case 2: 	
				 options.c_cflag |= CSTOPB; break;	
		default:	 
					   fprintf(stderr,"Unsupported stop bits\n");	
					   return (FALSE);	
	}  
	 
	//修改输出模式，原始数据输出  
	options.c_oflag &= ~OPOST;	
	
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  
	//options.c_lflag &= ~(ISIG | ICANON);	
	options.c_iflag &= ~(ICRNL | IXON);
	//设置等待时间和最小接收字符  
	options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */	
	options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */  
	 
	//如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读  
	tcflush(fd,TCIFLUSH);  
	 
	//激活配置 (将修改后的termios数据设置到串口中）  
	if (tcsetattr(fd,TCSANOW,&options) != 0)	
	{  
		perror("com set error!\n");    
		return (FALSE);   
	}  
	return (TRUE);	 
}


/******************************************************************************
* Function:    PORT_Rs232Read
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
UINT32_T PORT_Rs232Read(int fd, UINT8_T *rcv_buf,UINT32_T data_len)
{  
	int len,fs_sel;  
	fd_set fs_read;  
	 
	struct timeval time;  
	 
	FD_ZERO(&fs_read);	
	FD_SET(fd,&fs_read);  
	 
	time.tv_sec = 1;  
	time.tv_usec = 0;  
	 
	//使用select实现串口的多路通信	
	fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);  
	//printf("fs_sel = %d\n",fs_sel);  
	if(fs_sel)	
	{  
		len = read(fd,rcv_buf,data_len);  
		//printf("I am right!(len = %d fs_sel = %d\n",len,fs_sel);  
		return len;  
	}  
	else  
	{  
		printf("Sorry,I am wrong!");  
		return FALSE;  
	}		
}  


/******************************************************************************
* Function:    PORT_Rs232Write
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
UINT32_T PORT_Rs232Write(int fd, UINT8_T *snd_buf,UINT32_T data_len)
{  
	int len = 0;  
	 
	len = write(fd,snd_buf,data_len);	
	if (len == data_len )  
	{  
		//printf("Send data: \"%s\"\n",snd_buf);
		return len;  
	}		
	else	 
	{  
				 
		tcflush(fd,TCOFLUSH);  
		return FALSE;  
	}  
	 
}  

/******************************************************************************
* Function:    RS232_WrRxToRcvBuf()
* Input:	   xxx
* Output:	   xxx
* Return:	   xxx
* Description: RS232将接收到的新数据写到的缓冲区rs232_rx_ringbuf
*
*
******************************************************************************/
UINT32_T RS232_WrRcvToRxBuf(UINT8_T *pbuf, UINT32_T wlen)
{
	UINT32_T cnt=0;
	if(!wlen)
		return 0;
	RS232_PrintLog("RS232_WrRcvToRxBuf[%d]:\r\n",wlen);
	RS232_PrintHex(pbuf, wlen);
	
	if((rs232_rx_ringbuf.wr+1)%RS232_RX_DAT_Q_SIZE != rs232_rx_ringbuf.rd)
	{
		if(wlen > RS232_RX_DAT_BUF_SIZE)
		{
			wlen=RS232_RX_DAT_BUF_SIZE;
			RS232_PrintLog("ERROR: %s:%d Write overflow! \r\n",__func__,__LINE__);
		}
		cnt = wlen;
		memcpy(rs232_rx_ringbuf.rx_buf[rs232_rx_ringbuf.wr].buf,pbuf,wlen);
		rs232_rx_ringbuf.rx_buf[rs232_rx_ringbuf.wr].len=wlen;
		rs232_rx_ringbuf.wr =(rs232_rx_ringbuf.wr+1)%RS232_RX_DAT_Q_SIZE;
	}
	else
		RS232_PrintLog("ERROR: %s:%d Write failed!,buf is full!\r\n",__func__,__LINE__);
	return cnt;
}


/******************************************************************************
* Function:    RS232_RdSndBufToTx()
* Input:	   xxx
* Output:	   xxx
* Return:	   xxx
* Description: RS232 模块从缓冲区（rs232_tx_ringbuf）中读出要发送的数据
*
*
******************************************************************************/
UINT32_T RS232_RdTxBufToSnd(UINT8_T *pbuf, UINT32_T rlen)
{
	UINT32_T cnt=0;
	if(!rlen)
		return 0;
	if(rs232_tx_ringbuf.rd != rs232_tx_ringbuf.wr)
	{
		cnt=rs232_tx_ringbuf.tx_buf[rs232_tx_ringbuf.rd].len;
		if(cnt>rlen)
		{
			cnt=rlen;
			RS232_PrintLog("ERROR: %s:%d rlen < buf len. overflow! \r\n",__func__,__LINE__);
		}
		memcpy(pbuf,rs232_tx_ringbuf.tx_buf[rs232_tx_ringbuf.rd].buf,cnt);
		rs232_tx_ringbuf.rd =(rs232_tx_ringbuf.rd+1)%RS232_TX_DAT_Q_SIZE;
		RS232_PrintLog("RS232_RdTxBufToSnd[%d]:\r\n",cnt);
		RS232_PrintHex(pbuf, cnt);
	}
	else
		RS232_PrintLog("ERROR: %s:%d Read failed!,buf is empty!\r\n",__func__,__LINE__);
	return cnt;
}



/******************************************************************************
* Function:    PORT_Rs232WrTxBuf()
* Input:	   xxx
* Output:	   xxx
* Return:	   xxx
* Description: 外部模块将要发送的数据写到RS232的发送缓冲区（rs232_tx_ringbuf）
*
*
******************************************************************************/
UINT32_T PORT_Rs232WrTxBuf(UINT8_T *pbuf, UINT32_T wlen)
{
	UINT32_T cnt=0;
	if(!wlen)
		return 0;
	if(((rs232_tx_ringbuf.wr+1)%RS232_TX_DAT_Q_SIZE) != rs232_tx_ringbuf.rd)
	{
		RS232_PrintLog("PORT_Rs232WrTxBuf[%d]:%d,%d\r\n",wlen,rs232_tx_ringbuf.wr,rs232_tx_ringbuf.rd);
		RS232_PrintHex(pbuf, wlen);
		if(wlen > RS232_TX_DAT_BUF_SIZE)
		{
			wlen=RS232_TX_DAT_BUF_SIZE;
			RS232_PrintLog("ERROR: %s:%d Write overflow! \r\n",__func__,__LINE__);
		}
		cnt=wlen;
		memcpy(rs232_tx_ringbuf.tx_buf[rs232_tx_ringbuf.wr].buf,pbuf,wlen);
		rs232_tx_ringbuf.tx_buf[rs232_tx_ringbuf.wr].len=wlen;
		rs232_tx_ringbuf.wr =(rs232_tx_ringbuf.wr+1)%RS232_TX_DAT_Q_SIZE;
		
	}else
		RS232_PrintLog("ERROR: %s:%d Write failed!,buf is full!\r\n",__func__,__LINE__);
	return cnt;
}



/******************************************************************************
* Function:    PORT_Rs232RdRxBuf()
* Input:	   xxx
* Output:	   xxx
* Return:	   xxx
* Description: 外部模块通过rs232_rx_ringbuf来读取接收到的数据
*
*
******************************************************************************/
UINT32_T PORT_Rs232RdRxBuf(UINT8_T *pbuf, UINT32_T rlen)
{
	int cnt=0;
	if(!rlen)
		return 0;
	if(rs232_rx_ringbuf.rd != rs232_rx_ringbuf.wr)
	{
		cnt=rs232_rx_ringbuf.rx_buf[rs232_rx_ringbuf.rd].len;
		if(cnt > rlen)
		{
			cnt=rlen;
			RS232_PrintLog("ERROR: %s:%d rlen < buf len. overflow! \r\n",__func__,__LINE__);
		}
		memcpy(pbuf,rs232_rx_ringbuf.rx_buf[rs232_rx_ringbuf.rd].buf,cnt);
		rs232_rx_ringbuf.rd =(rs232_rx_ringbuf.rd+1)%RS232_RX_DAT_Q_SIZE;
		RS232_PrintLog("PORT_Rs232RdRxBuf[%d]:\r\n",cnt);
		RS232_PrintHex(pbuf, cnt);
	}
	else
		RS232_PrintLog("ERROR: %s:%d Read failed!,buf is empty!\r\n",__func__,__LINE__);
	return cnt;
}

/******************************************************************************
* Function:    APP_Rs232Thread
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
void* PORT_Rs232Thread(void *p_arg)
{
	UINT32_T i;
	SINT_T fd;
	UINT32_T rcv_len=0;
	UINT32_T snd_len=0;
	UINT8_T rcv_buf[512];
	UINT8_T snd_buf[512];
	PORT_RS232_CFG_T *pcfg=p_arg;
	
	fd=PORT_Rs232Init(pcfg->dev_path);
	if(fd<0)
	{
		RS232_PrintLog("PORT RS232 Init failed!\r\n");
		pthread_exit(NULL); 
	}

	if(PORT_Rs232Cfg(fd,pcfg->band_rate,pcfg->flow_ctrl,pcfg->data_bits,pcfg->stop_bits,pcfg->parity) == FALSE)
	{
		RS232_PrintLog("PORT RS232 Cfg failed!\r\n");
		pthread_exit(NULL); 
	}

	memcpy(snd_buf,"Hello,APP_Rs232Thread!\r\n",sizeof("Hello,APP_Rs232Thread!\r\n"));
	snd_len=sizeof("Hello,APP_Rs232Thread!\r\n");

	for(i=0;i<256;i++)
		snd_buf[i]=i;
	snd_len=256;
		
	while (1)
	{
		//RS232_PrintLog("Hello,APP_Rs232Thread!\r\n");

		snd_len=PORT_Rs232Write(fd,snd_buf,snd_len);
		if(snd_len)
		{
			RS232_PrintLog("Snd New Dat:%d\r\n",snd_len);
			RS232_PrintHex(snd_buf,snd_len);

		}
		sleep(1);
		rcv_len=PORT_Rs232Read(fd, rcv_buf,300);
		if(rcv_len)
		{
			RS232_PrintLog("Rcv New Dat:%d\r\n",rcv_len);
			
			RS232_PrintHex(rcv_buf,rcv_len);
		}
		
	}
	return NULL;
}





#endif//#if __SYS_RS232_ENABLE__






