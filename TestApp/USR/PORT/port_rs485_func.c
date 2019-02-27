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



/*-----------------------模块内宏定义-------------------------*/
//#define    xxxxxx              (xxxxxxxx)
#define PORT_RS485			"/dev/ttyUSB0"


/*----------------------模块内类定义--------------------------*/



/*----------------------变量常量定义--------------------------*/




/*****************************************************************************/
                         /* 函数定义 */
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
	   return(FALSE);  
	}  
	//恢复串口为阻塞状态		
	
	printf("Open Serial Port,fd=%d!\n",fd);	
	if(fcntl(fd, F_SETFL, 0) < 0)  
	{  
	   printf("fcntl failed!\n");  
	   return(FALSE);  
	}	   
	else  
	{  
	   printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));  
	}  
	
	//测试是否为终端设备	  
	if(0 == isatty(STDIN_FILENO))  
	{  
	   printf("standard input is not a terminal device\n");  
	   return(FALSE);  
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
* Function:    PORT_Rs485Read
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
int PORT_Rs485Read(int fd, char *rcv_buf,int data_len)
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
* Function:    PORT_Rs485Write
* Input:       xxx
* Output:      xxx
* Return:      xxx
* Description: xxxxx
*
*
******************************************************************************/
int PORT_Rs485Write(int fd, char *snd_buf,int data_len)
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
	int fd;
	int rcv_len=0;
	int	snd_len=0;
	char rcv_buf[512];
	char snd_buf[512];
	PORT_RS485_CFG_T *pcfg=p_arg;
	
	fd=PORT_Rs485Init(pcfg->dev_path);
	if(fd<0)
	{
		RS485_PrintLog("PORT RS485 Init failed!\r\n");
		pthread_exit(NULL); 
	}

	if(PORT_Rs485Cfg(fd,pcfg->band_rate,pcfg->flow_ctrl,pcfg->data_bits,pcfg->stop_bits,pcfg->parity) == FALSE)
	{
		RS485_PrintLog("PORT RS485 Cfg failed!\r\n");
		pthread_exit(NULL); 
	}

	memcpy(snd_buf,"Hello,APP_Rs485Thread!\r\n",sizeof("Hello,APP_Rs485Thread!\r\n"));
	snd_len=sizeof("Hello,APP_Rs485Thread!\r\n");

	for(int i=0;i<256;i++)
		snd_buf[i]=i;
	snd_len=256;
		
	while (1)
	{
		//RS485_PrintLog("Hello,APP_Rs485Thread!\r\n");

		snd_len=PORT_Rs485Write(fd,snd_buf,snd_len);
		if(snd_len)
		{
			RS485_PrintLog("Snd New Dat:%d\r\n",snd_len);
			RS485_PrintHex((unsigned char*)snd_buf,snd_len);

		}
		sleep(1);
		rcv_len=PORT_Rs485Read(fd, rcv_buf,300);
		if(rcv_len)
		{
			RS485_PrintLog("Rcv New Dat:%d\r\n",rcv_len);
			
			RS485_PrintHex((unsigned char*)rcv_buf,rcv_len);
		}
		
	}
	return NULL;
}





#endif//#if __SYS_RS485_ENABLE__




