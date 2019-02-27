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
//#define    xxxxxx              (xxxxxxxx)
#define PORT_RS485			"/dev/ttyUSB0"


/*----------------------ģ�����ඨ��--------------------------*/



/*----------------------������������--------------------------*/




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
	   return(FALSE);  
	}  
	//�ָ�����Ϊ����״̬		
	
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
	
	//�����Ƿ�Ϊ�ն��豸	  
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
	PORT_RS485_CFG_T *pcfg=p_arg;
	fd=PORT_Rs485Init(pcfg->dev_path);
	if(fd<0)
	{
		METER_PrintLog("PORT RS485 Init failed!\r\n");
		pthread_exit(NULL); 
	}

	if(PORT_Rs485Cfg(fd,pcfg->band_rate,pcfg->flow_ctrl,pcfg->data_bits,pcfg->stop_bits,pcfg->parity) == FALSE)
	{
		METER_PrintLog("PORT RS485 Cfg failed!\r\n");
		pthread_exit(NULL); 
	}

	
	while (1)
	{
		METER_PrintLog("Hello,APP_Rs485Thread!\r\n");
		sleep(1);
	}
	return NULL;
}





#endif//#if __SYS_RS485_ENABLE__




