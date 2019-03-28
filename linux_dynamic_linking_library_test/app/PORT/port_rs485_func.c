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
* File name: port_rs485_func.c
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
#if __SYS_RS485_ENABLE__
#include "port_rs485_func.h"



/*-----------------------ģ���ں궨��-------------------------*/
#define    RS485_RX_DAT_Q_SIZE     (16)
#define    RS485_TX_DAT_Q_SIZE     (16)

#define    RS485_RX_DAT_BUF_SIZE     (512)
#define    RS485_TX_DAT_BUF_SIZE     (512)


/*----------------------ģ�����ඨ��--------------------------*/
typedef struct rs485_rx_buf_t{
	UINT32_T len;
	UINT8_T  buf[RS485_RX_DAT_BUF_SIZE];
}RS485_RX_BUF_T;

typedef struct rs485_tx_buf_t{
	UINT32_T len;
	UINT8_T  buf[RS485_TX_DAT_BUF_SIZE];
}RS485_TX_BUF_T;

typedef struct rs485_rx_ringbuf_t{
	UINT32_T rd;
	UINT32_T wr;
	RS485_RX_BUF_T  rx_buf[RS485_RX_DAT_Q_SIZE];
}RS485_RX_RINGBUF_T;

typedef struct rs485_tx_ringbuf_t{
	UINT32_T rd;
	UINT32_T wr;
	RS485_TX_BUF_T  tx_buf[RS485_TX_DAT_Q_SIZE];
}RS485_TX_RINGBUF_T;



/*----------------------������������--------------------------*/


RS485_RX_RINGBUF_T rs485_rx_ringbuf;
RS485_TX_RINGBUF_T rs485_tx_ringbuf;


/*****************************************************************************/
                         /* �������� */
/*****************************************************************************/

/******************************************************************************
* Function:    PORT_Rs485Init
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
int PORT_Rs485Init(const char *dev_path)
{
	int fd;                          
	printf("dev_path=%s\n",dev_path);

	fd = open(dev_path, O_RDWR|O_NOCTTY|O_NDELAY);	
	if(fd<=0)  
	{  
	   perror("Can't Open Serial Port");  
	   return (-1);  
	}  
	//�ָ�����Ϊ����״̬		
	
	printf("Open Serial Port,fd=%d!\n",fd);	
	if(fcntl(fd, F_SETFL, 0) < 0)  
	{  
	   printf("fcntl failed!\n");  
	   return (-1);  
	}	   
	else  
	{  
	   printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));  
	}  
	
	//�����Ƿ�Ϊ�ն��豸	  
	if(0 == isatty(STDIN_FILENO))  
	{  
	   printf("standard input is not a terminal device\n");  
	   return (-1);  
	}  
	else  
	{  
	   printf("isatty success!\n");  
	}				
	printf("fd->open=%d\n",fd);	
	return fd;  
}


/******************************************************************************
* Function:    PORT_Rs485Cfg
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
int PORT_Rs485Cfg(int fd,int band_rate,int flow_ctrl,int data_bits,int stop_bits,int parity)
{  
	 
	int   i;  
	int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};  
	int   name_arr[] = {115200,  19200,  9600,	4800,  2400,  1200,  300};	
		   
	struct termios options;  
	 
	/*tcgetattr(fd,&options)�õ���fdָ��������ز������������Ǳ�����options,�ú��������Բ��������Ƿ���ȷ���ô����Ƿ���õȡ������óɹ�����������ֵΪ0��������ʧ�ܣ���������ֵΪ1. 
	*/	
	if( tcgetattr( fd,&options)  !=  0)  
	{  
		perror("SetupSerial 1");	  
		return(FALSE);	 
	}  
	
	//���ô������벨���ʺ����������  
	for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)  
	{  
		if	(band_rate == name_arr[i])	
		{				
			cfsetispeed(&options, speed_arr[i]);   
			cfsetospeed(&options, speed_arr[i]);	
		}  
	}		
	 
	//�޸Ŀ���ģʽ����֤���򲻻�ռ�ô���  
	options.c_cflag |= CLOCAL;	
	//�޸Ŀ���ģʽ��ʹ���ܹ��Ӵ����ж�ȡ��������  
	options.c_cflag |= CREAD;  
	
	//��������������  
	switch(flow_ctrl)  
	{  
		
		case 0 ://��ʹ��������  
			  options.c_cflag &= ~CRTSCTS;	
			  break;	 
		
		case 1 ://ʹ��Ӳ��������  
			  options.c_cflag |= CRTSCTS;  
			  break;  
		case 2 ://ʹ�����������  
			  options.c_cflag |= IXON | IXOFF | IXANY;	
			  break;  
	}  
	//��������λ  
	//����������־λ  
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
	//����У��λ  
	switch (parity)  
	{	 
		case 'n':  
		case 'N': //����żУ��λ��  
				 options.c_cflag &= ~PARENB;   
				 options.c_iflag &= ~INPCK; 	 
				 break;   
		case 'o':	 
		case 'O'://����Ϊ��У��	   
				 options.c_cflag |= (PARODD | PARENB);	 
				 options.c_iflag |= INPCK;				 
				 break;   
		case 'e':	
		case 'E'://����ΪżУ��	 
				 options.c_cflag |= PARENB; 		
				 options.c_cflag &= ~PARODD;		 
				 options.c_iflag |= INPCK;		  
				 break;  
		case 's':  
		case 'S': //����Ϊ�ո�   
				 options.c_cflag &= ~PARENB;  
				 options.c_cflag &= ~CSTOPB;  
				 break;   
		default:	
				 fprintf(stderr,"Unsupported parity\n");	  
				 return (FALSE);   
	}	
	// ����ֹͣλ	 
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
	 
	//�޸����ģʽ��ԭʼ�������  
	options.c_oflag &= ~OPOST;	
	
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  
	//options.c_lflag &= ~(ISIG | ICANON);	
	options.c_iflag &= ~(ICRNL | IXON);
	//���õȴ�ʱ�����С�����ַ�  
	options.c_cc[VTIME] = 1; /* ��ȡһ���ַ��ȴ�1*(1/10)s */	
	options.c_cc[VMIN] = 1; /* ��ȡ�ַ������ٸ���Ϊ1 */  
	 
	//�����������������������ݣ����ǲ��ٶ�ȡ ˢ���յ������ݵ��ǲ���  
	tcflush(fd,TCIFLUSH);  
	 
	//�������� (���޸ĺ��termios�������õ������У�  
	if (tcsetattr(fd,TCSANOW,&options) != 0)	
	{  
		perror("com set error!\n");    
		return (FALSE);   
	}  
	return (TRUE);	 
}


/******************************************************************************
* Function:    PORT_Rs485Read
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
UINT32_T PORT_Rs485Read(int fd, UINT8_T *rcv_buf,UINT32_T data_len)
{  
	UINT32_T len,fs_sel;  
	fd_set fs_read;  
	 
	struct timeval time;  
	 
	FD_ZERO(&fs_read);	
	FD_SET(fd,&fs_read);  
	 
	time.tv_sec = 0;  
	time.tv_usec = 0;  
	 
	//ʹ��selectʵ�ִ��ڵĶ�·ͨ��	
	fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);  
	//printf("fs_sel = %d\n",fs_sel);  
	if(fs_sel)	
	{  
		len = read(fd,rcv_buf,data_len);  
		printf("I am right!(len = %d fs_sel = %d\n",len,fs_sel);  
		return len;  
	}  
	else  
	{  
		//printf("Sorry,I am wrong!\r\n");  
		return FALSE;  
	}		
}  


/******************************************************************************
* Function:    PORT_Rs485Write
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
UINT32_T PORT_Rs485Write(int fd, UINT8_T *snd_buf, UINT32_T data_len)
{  
	UINT32_T len = 0;  
	 
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
* Function:    RS485_WrRxToRcvBuf()
* Input:	   xxx
* Output:	   xxx
* Return:	   xxx
* Description: RS485�����յ���������д���Ļ�����rs485_rx_ringbuf
*
*
******************************************************************************/
UINT32_T RS485_WrRcvToRxBuf(UINT8_T *pbuf, UINT32_T wlen)
{
	UINT32_T cnt=0;
	if(!wlen)
		return 0;
	
	if((rs485_rx_ringbuf.wr+1)%RS485_RX_DAT_Q_SIZE != rs485_rx_ringbuf.rd)
	{
	
		//RS485_PrintLog("RS485_WrRcvToRxBuf[%d]:\r\n",wlen);
		//RS485_PrintHex(pbuf, wlen);
		if(wlen > RS485_RX_DAT_BUF_SIZE)
		{
			wlen=RS485_RX_DAT_BUF_SIZE;
			RS485_PrintLog("ERROR: %s:%d Write overflow! \r\n",__func__,__LINE__);
		}
		cnt = wlen;
		memcpy(rs485_rx_ringbuf.rx_buf[rs485_rx_ringbuf.wr].buf,pbuf,wlen);
		rs485_rx_ringbuf.rx_buf[rs485_rx_ringbuf.wr].len=wlen;
		rs485_rx_ringbuf.wr =(rs485_rx_ringbuf.wr+1)%RS485_RX_DAT_Q_SIZE;
	}
	else
		;//RS485_PrintLog("ERROR: %s:%d Write failed!,buf is full!\r\n",__func__,__LINE__);
	return cnt;
}


/******************************************************************************
* Function:    RS485_RdSndBufToTx()
* Input:	   xxx
* Output:	   xxx
* Return:	   xxx
* Description: RS485 ģ��ӻ�������rs485_tx_ringbuf���ж���Ҫ���͵�����
*
*
******************************************************************************/
UINT32_T RS485_RdTxBufToSnd(UINT8_T *pbuf, UINT32_T rlen)
{
	UINT32_T cnt=0;
	if(!rlen)
		return 0;
	if(rs485_tx_ringbuf.rd != rs485_tx_ringbuf.wr)
	{
		cnt=rs485_tx_ringbuf.tx_buf[rs485_tx_ringbuf.rd].len;
		if(cnt>rlen)
		{
			cnt=rlen;
			RS485_PrintLog("ERROR: %s:%d rlen < buf len. overflow! \r\n",__func__,__LINE__);
		}
		memcpy(pbuf,rs485_tx_ringbuf.tx_buf[rs485_tx_ringbuf.rd].buf,cnt);
		rs485_tx_ringbuf.rd =(rs485_tx_ringbuf.rd+1)%RS485_TX_DAT_Q_SIZE;
		//RS485_PrintLog("RS485_RdTxBufToSnd[%d]:\r\n",cnt);
		//RS485_PrintHex(pbuf, cnt);
	}
	else
		;//RS485_PrintLog("ERROR: %s:%d Read failed!,buf is empty!\r\n",__func__,__LINE__);
	return cnt;
}



/******************************************************************************
* Function:    PORT_Rs485WrTxBuf()
* Input:	   xxx
* Output:	   xxx
* Return:	   xxx
* Description: �ⲿģ�齫Ҫ���͵�����д��RS485�ķ��ͻ�������rs485_tx_ringbuf��
*
*
******************************************************************************/
UINT32_T PORT_Rs485WrTxBuf(UINT8_T *pbuf, UINT32_T wlen)
{
	UINT32_T cnt=0;
	if(!wlen)
		return 0;
	if(((rs485_tx_ringbuf.wr+1)%RS485_TX_DAT_Q_SIZE) != rs485_tx_ringbuf.rd)
	{
		//RS485_PrintLog("PORT_Rs485WrTxBuf[%d]:%d,%d\r\n",wlen,rs485_tx_ringbuf.wr,rs485_tx_ringbuf.rd);
		//RS485_PrintHex(pbuf, wlen);
		if(wlen > RS485_TX_DAT_BUF_SIZE)
		{
			wlen=RS485_TX_DAT_BUF_SIZE;
			RS485_PrintLog("ERROR: %s:%d Write overflow! \r\n",__func__,__LINE__);
		}
		cnt=wlen;
		memcpy(rs485_tx_ringbuf.tx_buf[rs485_tx_ringbuf.wr].buf,pbuf,wlen);
		rs485_tx_ringbuf.tx_buf[rs485_tx_ringbuf.wr].len=wlen;
		rs485_tx_ringbuf.wr =(rs485_tx_ringbuf.wr+1)%RS485_TX_DAT_Q_SIZE;
		
	}else
		;//RS485_PrintLog("ERROR: %s:%d Write failed!,buf is full!\r\n",__func__,__LINE__);
	return cnt;
}



/******************************************************************************
* Function:    PORT_Rs485RdRxBuf()
* Input:	   xxx
* Output:	   xxx
* Return:	   xxx
* Description: �ⲿģ��ͨ��rs485_rx_ringbuf����ȡ���յ�������
*
*
******************************************************************************/
UINT32_T PORT_Rs485RdRxBuf(UINT8_T *pbuf, UINT32_T rlen)
{
	UINT32_T cnt=0;
	if(!rlen)
		return 0;
	if(rs485_rx_ringbuf.rd != rs485_rx_ringbuf.wr)
	{
		cnt=rs485_rx_ringbuf.rx_buf[rs485_rx_ringbuf.rd].len;
		if(cnt > rlen)
		{
			cnt=rlen;
			RS485_PrintLog("ERROR: %s:%d rlen < buf len. overflow! \r\n",__func__,__LINE__);
		}
		memcpy(pbuf,rs485_rx_ringbuf.rx_buf[rs485_rx_ringbuf.rd].buf,cnt);
		rs485_rx_ringbuf.rd =(rs485_rx_ringbuf.rd+1)%RS485_RX_DAT_Q_SIZE;
		//RS485_PrintLog("PORT_Rs485RdRxBuf[%d]:\r\n",cnt);
		//RS485_PrintHex(pbuf, cnt);
	}
	else
		;//RS485_PrintLog("ERROR: %s:%d Read failed!,buf is empty!\r\n",__func__,__LINE__);
	return cnt;
}



/******************************************************************************
* Function:    APP_Rs485Thread
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
void* PORT_Rs485Thread(void *p_arg)
{
	//UINT32_T i;
	SINT_T fd;
	//UINT32_T rcv_len=0;
	//UINT32_T	snd_len=0;
	//UINT8_T rcv_buf[RS485_RX_DAT_BUF_SIZE];
	//UINT8_T snd_buf[RS485_TX_DAT_BUF_SIZE];
	PORT_RS485_CFG_T *pcfg=p_arg;
	UINT32_T rlen=0;
	UINT32_T wlen=0;
	char pipe_wbuf[128]={"COM:ABCDEFGHIJ!\r\n"};
	char pipe_rbuf[128];
	//char interface[1024];


	
	memset(&rs485_rx_ringbuf,0,sizeof(rs485_rx_ringbuf));
	memset(&rs485_tx_ringbuf,0,sizeof(rs485_tx_ringbuf));
	
	printf("%s:%d\r\n",__func__,__LINE__);
	fd=PORT_Rs485Init(pcfg->dev_path);
	if(fd<0)
	{
		printf("PORT RS485 Init failed!\r\n");
		pthread_exit(NULL); 
	}

	if(PORT_Rs485Cfg(fd,pcfg->band_rate,pcfg->flow_ctrl,pcfg->data_bits,pcfg->stop_bits,pcfg->parity) == FALSE)
	{
		printf("PORT RS485 Cfg failed!\r\n");
		pthread_exit(NULL); 
	}

	#if 1
		
	while (1)
	{
		//RS485_PrintLog("Hello,APP_Rs485Thread!\r\n");
		#if 0
		snd_len=PORT_Rs485Write(fd,snd_buf,snd_len);
		if(snd_len)
		{
			RS485_PrintLog("********************Snd New Dat:%d\r\n",snd_len);
			RS485_PrintHex((unsigned char*)snd_buf,snd_len);
		}
		sleep(1);
		rcv_len=PORT_Rs485Read(fd, rcv_buf,300);
		if(rcv_len)
		{
			RS485_PrintLog("=====================Rcv New Dat:%d\r\n",rcv_len);
			RS485_PrintHex((unsigned char*)rcv_buf,rcv_len);
		}

		#endif
		
		wlen=COMM_CommWriteDat(1,pipe_wbuf,128);
		if(wlen == 128)
			printf("=============COM SND[%d]:%s\r\n",wlen,pipe_wbuf);
		usleep(500);

		memset(pipe_rbuf,0,128);
		rlen=COMM_CommReadDat(1,pipe_rbuf,128);
		if(rlen)
			printf("&&&&&&&&&&&&&COM RCV[%d]:%s\r\n",rlen,pipe_rbuf);
	}
	#else
	while(1)
	{
	
		snd_len=RS485_RdTxBufToSnd(snd_buf,RS485_TX_DAT_BUF_SIZE);
		snd_len=PORT_Rs485Write(fd,snd_buf,snd_len);
		if(snd_len)
		{
			printf("Snd New Dat:%d\r\n",snd_len);
			//RS485_PrintHex(snd_buf,snd_len);
		}
		rcv_len=PORT_Rs485Read(fd,rcv_buf,RS485_RX_DAT_BUF_SIZE);
		rcv_len=RS485_WrRcvToRxBuf(rcv_buf,rcv_len);
		if(rcv_len)
		{
			printf("Rcv New Dat:%d\r\n",rcv_len);
			//RS485_PrintHex(rcv_buf,rcv_len);
		}


	}
	#endif
	return NULL;
}

#endif//#if __SYS_RS485_ENABLE__




