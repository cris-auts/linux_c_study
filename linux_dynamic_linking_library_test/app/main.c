#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>      /*文件控制定义*/  
#include <termios.h>    /*PPSIX 终端控制定义*/  
#include <errno.h>      /*错误号定义*/  
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
		1. 从数据库中加载设备所有物理端口的参数
		2.将这些参数存放在一张大的表格中
		3.在创建各个同型端口线程时，需要从这个表格中查询出端口应该配置的参数
		4.将这个参数传入到端口线程里面。端口线程自己去初始化端口。
	*/
	p_dev_cfg_map=malloc(sizeof(PORT_DEV_CFG_T)*8);
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
 





