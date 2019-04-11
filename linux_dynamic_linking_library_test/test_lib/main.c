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
#include "comm_interface.h"
#include "dbase.h"





int main(int argc, char** argv)
{   
	UINT32_T rlen=0;
	UINT32_T wlen=0;
	char pipe_wbuf[128]={"APP:1234567890!\r\n"};
	
	char pipe_wbuf1[128]={"APP:ABCDEFGHIJ!\r\n"};
	char pipe_rbuf[128];
	UINT32_T ch_id=0;
	UINT32_T ch_id1=0;
	UINT32_T ch_id2=0;
	UINT32_T ch_id3=0;
	USR_CFG_T usr_cfg;
	
	IPC_Init();
	sleep(1);
	//注册通道1==================================================
	usr_cfg.slaver_run_mode=RUN_MODE_CLIENT;//分解后运行模式
	usr_cfg.slaver_run_ip_index=CLIENT_IP_NUM1;//分解后运行ip索引

	usr_cfg.comm_prm.cs=0;//校验
	usr_cfg.comm_prm.enable=1;//失能(0)、使能(1)
	usr_cfg.comm_prm.cfg_sn=1;//配置序号
	usr_cfg.comm_prm.prtc_type=PRTC_DLT698;//规约类型
	usr_cfg.comm_prm.prtc_level=0;//规约权限等级
	usr_cfg.comm_prm.prtc_buff_size=1024;//规约占用缓冲区尺寸
	usr_cfg.comm_prm.comm_port=COMM_ETH_1;//物理通道
	usr_cfg.comm_prm.run_mode=RUN_MODE_CLIENT;//运行模式   混合模式(0)、客户端(1)、服务器(2)
	usr_cfg.comm_prm.link_mode=0;//连接模式   TCP(0)、UDP(1)
	usr_cfg.comm_prm.link_app_mode=0;//连接应用模式  主备模式(0)、多连接模式(1)


	usr_cfg.comm_prm.port_prm.eth_prm.ip_type=0;		   //ip类型 IPV4(0) IPV6(1)
	usr_cfg.comm_prm.port_prm.eth_prm.ip[0]=192;		   //ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[1]=168;			//ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[2]=2;				//ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[3]=6;				//ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[4]=0;				//ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[5]=0;				//ip地址

	
	usr_cfg.comm_prm.port_prm.eth_prm.port_num=8000;		   //端口号
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup_type=0;    //备用ip类型IPV4(0) IPV6(1)
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [0]=192;		//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [1]=168;		//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [2]=2;			//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [3]=7;			//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [4]=0;			//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [5]=0;			//备用ip地址
	
	usr_cfg.comm_prm.port_prm.eth_prm.port_backup_num=8001;  //备用端口号
	usr_cfg.comm_prm.port_prm.eth_prm.port_list_num=2; 	//侦听端口列表有效数据长度
	
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[0]=9000;	//侦听端口列表,最大10个
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[1]=9001;	//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[2]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[3]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[4]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[5]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[6]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[7]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[8]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[9]=0;		//侦听端口列表

	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy_type=0;	   //代理ip类型
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [0]=192;	//代理ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [1]=168;	//代理ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [2]=2;	//代理ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [3]=8;	//代理ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [4]=0;	//代理ip地
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [5]=0;	//代理ip地址

	
	usr_cfg.comm_prm.port_prm.eth_prm.port_proxy_num=8002;	//代理端口号
	usr_cfg.comm_prm.port_prm.eth_prm.resend_count=3;		//重发次数
	usr_cfg.comm_prm.port_prm.eth_prm.timeout=5;			//超时时间，单位：s
	usr_cfg.comm_prm.port_prm.eth_prm.time_wait=1; 			//发送等待间隔时间，单位：s
	usr_cfg.comm_prm.port_prm.eth_prm.cardiac_cycle=120;	//心跳周期，单位：s		
	
	printf("sizeof(USR_CFG_T)=%lu\r\n",sizeof(USR_CFG_T));
	if(IPC_ChRegister(&usr_cfg,sizeof(USR_CFG_T),5000,&ch_id) == 0)
		printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id);
	else
		printf("1IPC_ChRegister failed!\r\n");
	sleep(1);

	#if 0
	//注册通道2==================================================
	//usr_cfg.slaver_run_mode=RUN_MODE_CLIENT;//分解后运行模式
	//usr_cfg.slaver_run_ip_index=CLIENT_IP_NUM1;//分解后运行ip索引
	
	usr_cfg.comm_prm.cs=0;//校验
	usr_cfg.comm_prm.enable=1;//失能(0)、使能(1)
	usr_cfg.comm_prm.cfg_sn=2;//配置序号
	usr_cfg.comm_prm.prtc_type=PRTC_MAINT;//规约类型
	usr_cfg.comm_prm.prtc_level=0;//规约权限等级
	usr_cfg.comm_prm.prtc_buff_size=1024;//规约占用缓冲区尺寸
	usr_cfg.comm_prm.comm_port=COMM_RS485_1;//物理通道
	usr_cfg.comm_prm.run_mode=RUN_MODE_CLIENT;//运行模式   混合模式(0)、客户端(1)、服务器(2)
	usr_cfg.comm_prm.link_mode=0;//连接模式   TCP(0)、UDP(1)
	usr_cfg.comm_prm.link_app_mode=0;//连接应用模式  主备模式(0)、多连接模式(1)

	usr_cfg.comm_prm.port_prm.uart_prm.resend_count=3;		//重发次数
	usr_cfg.comm_prm.port_prm.uart_prm.timeout=5;			//超时时间，单位：s
	usr_cfg.comm_prm.port_prm.uart_prm.time_wait=1; 			//发送等待间隔时间，单位：s

	
	if(IPC_ChRegister(&usr_cfg,sizeof(usr_cfg),5000,&ch_id1) == 0)
		printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id1);
	else
		printf("2IPC_ChRegister failed!\r\n");
	sleep(1);
	#endif

	//注册通道3==================================================
	usr_cfg.slaver_run_mode=RUN_MODE_CLIENT;//分解后运行模式
	usr_cfg.slaver_run_ip_index=CLIENT_IP_NUM1;//分解后运行ip索引

	usr_cfg.comm_prm.cs=0;//校验
	usr_cfg.comm_prm.enable=1;//失能(0)、使能(1)
	usr_cfg.comm_prm.cfg_sn=3;//配置序号
	usr_cfg.comm_prm.prtc_type=PRTC_MAINT;//规约类型
	usr_cfg.comm_prm.prtc_level=0;//规约权限等级
	usr_cfg.comm_prm.prtc_buff_size=1024;//规约占用缓冲区尺寸
	usr_cfg.comm_prm.comm_port=COMM_ETH_1;//物理通道
	usr_cfg.comm_prm.run_mode=RUN_MODE_CLIENT;//运行模式   混合模式(0)、客户端(1)、服务器(2)
	usr_cfg.comm_prm.link_mode=0;//连接模式   TCP(0)、UDP(1)
	usr_cfg.comm_prm.link_app_mode=0;//连接应用模式  主备模式(0)、多连接模式(1)


	usr_cfg.comm_prm.port_prm.eth_prm.ip_type=0;		   //ip类型 IPV4(0) IPV6(1)
	usr_cfg.comm_prm.port_prm.eth_prm.ip[0]=192;		   //ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[1]=168;			//ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[2]=2;				//ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[3]=6;				//ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[4]=0;				//ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip[5]=0;				//ip地址

	
	usr_cfg.comm_prm.port_prm.eth_prm.port_num=8000;		   //端口号
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup_type=0;    //备用ip类型IPV4(0) IPV6(1)
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [0]=192;		//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [1]=168;		//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [2]=2;			//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [3]=7;			//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [4]=0;			//备用ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [5]=0;			//备用ip地址
	
	usr_cfg.comm_prm.port_prm.eth_prm.port_backup_num=8001;  //备用端口号
	usr_cfg.comm_prm.port_prm.eth_prm.port_list_num=2; 	//侦听端口列表有效数据长度
	
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[0]=9000;	//侦听端口列表,最大10个
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[1]=9001;	//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[2]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[3]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[4]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[5]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[6]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[7]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[8]=0;		//侦听端口列表
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[9]=0;		//侦听端口列表

	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy_type=0;	   //代理ip类型
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [0]=192;	//代理ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [1]=168;	//代理ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [2]=2;	//代理ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [3]=8;	//代理ip地址
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [4]=0;	//代理ip地
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [5]=0;	//代理ip地址

	
	usr_cfg.comm_prm.port_prm.eth_prm.port_proxy_num=8002;	//代理端口号
	usr_cfg.comm_prm.port_prm.eth_prm.resend_count=3;		//重发次数
	usr_cfg.comm_prm.port_prm.eth_prm.timeout=5;			//超时时间，单位：s
	usr_cfg.comm_prm.port_prm.eth_prm.time_wait=1; 			//发送等待间隔时间，单位：s
	usr_cfg.comm_prm.port_prm.eth_prm.cardiac_cycle=120;	//心跳周期，单位：s		
	
	printf("sizeof(USR_CFG_T)=%lu\r\n",sizeof(USR_CFG_T));
	if(IPC_ChRegister(&usr_cfg,sizeof(USR_CFG_T),5000,&ch_id2) == 0)
		printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id2);
	else
		printf("1IPC_ChRegister failed!\r\n");
	sleep(1);


	
	//注册通道4==================================================
	//usr_cfg.slaver_run_mode=RUN_MODE_CLIENT;//分解后运行模式
	//usr_cfg.slaver_run_ip_index=CLIENT_IP_NUM1;//分解后运行ip索引
	
	usr_cfg.comm_prm.cs=0;//校验
	usr_cfg.comm_prm.enable=1;//失能(0)、使能(1)
	usr_cfg.comm_prm.cfg_sn=4;//配置序号
	usr_cfg.comm_prm.prtc_type=PRTC_DLT698;//规约类型
	usr_cfg.comm_prm.prtc_level=0;//规约权限等级
	usr_cfg.comm_prm.prtc_buff_size=1024;//规约占用缓冲区尺寸
	usr_cfg.comm_prm.comm_port=COMM_RS485_1;//物理通道
	usr_cfg.comm_prm.run_mode=RUN_MODE_CLIENT;//运行模式   混合模式(0)、客户端(1)、服务器(2)
	usr_cfg.comm_prm.link_mode=0;//连接模式   TCP(0)、UDP(1)
	usr_cfg.comm_prm.link_app_mode=0;//连接应用模式  主备模式(0)、多连接模式(1)

	usr_cfg.comm_prm.port_prm.uart_prm.resend_count=3;		//重发次数
	usr_cfg.comm_prm.port_prm.uart_prm.timeout=5;			//超时时间，单位：s
	usr_cfg.comm_prm.port_prm.uart_prm.time_wait=1; 			//发送等待间隔时间，单位：s

	
	if(IPC_ChRegister(&usr_cfg,sizeof(usr_cfg),5000,&ch_id3) == 0)
		printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id3);
	else
		printf("2IPC_ChRegister failed!\r\n");
	sleep(1);


	
	sleep(2);
	while(1)
	{
		#if 1
		memset(pipe_rbuf,0,128);
		rlen=IPC_AppReadDat(ch_id,pipe_rbuf,128);
		if(rlen)
			printf("ch_id=%d@@@@@@@@@@APP RCV[%d]:%s\r\n",ch_id,rlen,pipe_rbuf);
		sleep(1);
		
		wlen=IPC_AppWriteDat(ch_id,pipe_wbuf,128);
		if(wlen == 128)
			printf("ch_id=%d**********APP SND[%d]:%s\r\n",ch_id,wlen,pipe_wbuf);

		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\r\n");
		memset(pipe_rbuf,0,128);
		rlen=IPC_AppReadDat(ch_id1,pipe_rbuf,128);
		if(rlen)
			printf("ch_id1=%d$$$$$$$$$APP RCV[%d]:%s\r\n",ch_id1,rlen,pipe_rbuf);
		sleep(1);
		
		wlen=IPC_AppWriteDat(ch_id1,pipe_wbuf1,128);
		if(wlen == 128)
			printf("ch_id1=%d+++++++++APP SND[%d]:%s\r\n",ch_id1,wlen,pipe_wbuf1);

		
		printf("###########################################################\r\n\r\n\r\n");
		#endif
	}

	return 0;
}
 





