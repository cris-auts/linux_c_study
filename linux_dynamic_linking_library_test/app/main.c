#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>      /*�ļ����ƶ���*/  
#include <termios.h>    /*PPSIX �ն˿��ƶ���*/  
#include <errno.h>      /*����Ŷ���*/  
#include <sys/types.h>   
#include <sys/stat.h>     
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include "msg_handle.h"



int LoadDbasePortCfg(void)
{
	/*
		1. �����ݿ��м����豸��������˿ڵĲ���
		2.����Щ���������һ�Ŵ�ı����
		3.�ڴ�������ͬ�Ͷ˿��߳�ʱ����Ҫ���������в�ѯ���˿�Ӧ�����õĲ���
		4.������������뵽�˿��߳����档�˿��߳��Լ�ȥ��ʼ���˿ڡ�
	*/
	return 0;
}






int main(int argc, char** argv)
{   
	g_dev_prm.nvram.debug_log_st.rs485_log=1;

	memset (ch_port_map,0,sizeof(ch_port_map));

	LoadDbasePortCfg();
	
	while(1)
	{
		MSG_MonitorHandle();
	}
}
 





