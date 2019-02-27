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



/*-----------------------ģ���ں궨��-------------------------*/
#define    RS232_RX_DAT_Q_SIZE     (8)
#define    RS232_TX_DAT_Q_SIZE     (8)

#define    RS232_RX_DAT_BUF_SIZE     (512)
#define    RS232_TX_DAT_BUF_SIZE     (512)


/*----------------------ģ�����ඨ��--------------------------*/
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



/*----------------------������������--------------------------*/


RS232_RX_RINGBUF_T rs232_rx_ringbuf;
RS232_TX_RINGBUF_T rs232_tx_ringbuf;



/*****************************************************************************/
                         /* �������� */
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
	//�ָ�����Ϊ����״̬		
	
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
	
	//�����Ƿ�Ϊ�ն��豸	  
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
* Function:    PORT_Rs232Read
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
int PORT_Rs232Read(int fd, char *rcv_buf,int data_len)
{  
	int len,fs_sel;  
	fd_set fs_read;  
	 
	struct timeval time;  
	 
	FD_ZERO(&fs_read);	
	FD_SET(fd,&fs_read);  
	 
	time.tv_sec = 1;  
	time.tv_usec = 0;  
	 
	//ʹ��selectʵ�ִ��ڵĶ�·ͨ��	
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
int PORT_Rs232Write(int fd, char *snd_buf,int data_len)
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
* Description: RS232�����յ���������д���Ļ�����rs232_rx_ringbuf
*
*
******************************************************************************/
int RS232_WrRcvToRxBuf(char *pbuf, int wlen)
{
	int cnt=0;
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
* Description: RS232 ģ��ӻ�������rs232_tx_ringbuf���ж���Ҫ���͵�����
*
*
******************************************************************************/
int RS232_RdTxBufToSnd(char *pbuf, int rlen)
{
	int cnt=0;
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
* Description: �ⲿģ�齫Ҫ���͵�����д��RS232�ķ��ͻ�������rs232_tx_ringbuf��
*
*
******************************************************************************/
int PORT_Rs232WrTxBuf(char *pbuf, int wlen)
{
	int cnt=0;
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
* Description: �ⲿģ��ͨ��rs232_rx_ringbuf����ȡ���յ�������
*
*
******************************************************************************/
int PORT_Rs232RdRxBuf(char *pbuf, int rlen)
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
	int fd;
	int rcv_len=0;
	int	snd_len=0;
	char rcv_buf[512];
	char snd_buf[512];
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

	for(int i=0;i<256;i++)
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






