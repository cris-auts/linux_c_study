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
#include "comm_interface.h"
#include "dbase.h"





int main(int argc, char** argv)
{   
	UINT32_T rlen=0;
	UINT32_T wlen=0;
	char pipe_wbuf[128]={"APP:0123456789!\r\n"};
	char pipe_wbuf1[128]={"APP:ABCDEFGHIJ!\r\n"};
	char pipe_wbuf2[128]={"APP:QRSTUVWXYZ!\r\n"};
	char pipe_wbuf3[128]={"APP:98765432d10!\r\n"};

	
	char pipe_rbuf[128];
	UINT32_T ch_id=0;
	UINT32_T ch_id1=0;
	UINT32_T ch_id2=0;
	UINT32_T ch_id3=0;

	
	UINT32_T ch_st=0;
	UINT32_T ch_st1=0;
	UINT32_T ch_st2=0;
	UINT32_T ch_st3=0;
	USR_CFG_T usr_cfg;
	
	IPC_Init();
	sleep(1);
	#if 1
	//ע��ͨ��1==================================================
	usr_cfg.slaver_run_mode=RUN_MODE_CLIENT;//�ֽ������ģʽ
	usr_cfg.slaver_run_ip_index=CLIENT_IP_NUM1;//�ֽ������ip����

	usr_cfg.comm_prm.cs=0;//У��
	usr_cfg.comm_prm.enable=1;//ʧ��(0)��ʹ��(1)
	usr_cfg.comm_prm.cfg_sn=1;//�������
	usr_cfg.comm_prm.prtc_type=PRTC_DLT698;//��Լ����
	usr_cfg.comm_prm.prtc_level=0;//��ԼȨ�޵ȼ�
	usr_cfg.comm_prm.prtc_buff_size=1024;//��Լռ�û������ߴ�
	usr_cfg.comm_prm.comm_port=COMM_ETH_1;//����ͨ��
	usr_cfg.comm_prm.run_mode=RUN_MODE_CLIENT;//����ģʽ   ���ģʽ(0)���ͻ���(1)��������(2)
	usr_cfg.comm_prm.link_mode=0;//����ģʽ   TCP(0)��UDP(1)
	usr_cfg.comm_prm.link_app_mode=0;//����Ӧ��ģʽ  ����ģʽ(0)��������ģʽ(1)


	usr_cfg.comm_prm.port_prm.eth_prm.ip_type=0;		   //ip���� IPV4(0) IPV6(1)
	usr_cfg.comm_prm.port_prm.eth_prm.ip[0]=192;		   //ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[1]=168;			//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[2]=2;				//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[3]=6;				//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[4]=0;				//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[5]=0;				//ip��ַ

	
	usr_cfg.comm_prm.port_prm.eth_prm.port_num=8000;		   //�˿ں�
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup_type=0;    //����ip����IPV4(0) IPV6(1)
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [0]=192;		//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [1]=168;		//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [2]=2;			//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [3]=7;			//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [4]=0;			//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [5]=0;			//����ip��ַ
	
	usr_cfg.comm_prm.port_prm.eth_prm.port_backup_num=8001;  //���ö˿ں�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list_num=2; 	//�����˿��б���Ч���ݳ���
	
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[0]=9000;	//�����˿��б�,���10��
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[1]=9001;	//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[2]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[3]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[4]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[5]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[6]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[7]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[8]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[9]=0;		//�����˿��б�

	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy_type=0;	   //����ip����
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [0]=192;	//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [1]=168;	//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [2]=2;	//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [3]=8;	//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [4]=0;	//����ip��
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [5]=0;	//����ip��ַ

	
	usr_cfg.comm_prm.port_prm.eth_prm.port_proxy_num=8002;	//����˿ں�
	usr_cfg.comm_prm.port_prm.eth_prm.resend_count=3;		//�ط�����
	usr_cfg.comm_prm.port_prm.eth_prm.timeout=5;			//��ʱʱ�䣬��λ��s
	usr_cfg.comm_prm.port_prm.eth_prm.time_wait=1; 			//���͵ȴ����ʱ�䣬��λ��s
	usr_cfg.comm_prm.port_prm.eth_prm.cardiac_cycle=120;	//�������ڣ���λ��s		
	
	printf("sizeof(USR_CFG_T)=%lu\r\n",sizeof(USR_CFG_T));
	if(IPC_ChRegister(&usr_cfg,sizeof(USR_CFG_T),5000,&ch_id) == 0)
		printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id);
	else
		printf("1IPC_ChRegister failed!\r\n");
	sleep(1);
	#endif
	#if 1
	//ע��ͨ��2==================================================
	//usr_cfg.slaver_run_mode=RUN_MODE_CLIENT;//�ֽ������ģʽ
	//usr_cfg.slaver_run_ip_index=CLIENT_IP_NUM1;//�ֽ������ip����
	
	usr_cfg.comm_prm.cs=0;//У��
	usr_cfg.comm_prm.enable=1;//ʧ��(0)��ʹ��(1)
	usr_cfg.comm_prm.cfg_sn=2;//�������
	usr_cfg.comm_prm.prtc_type=PRTC_MAINT;//��Լ����
	usr_cfg.comm_prm.prtc_level=0;//��ԼȨ�޵ȼ�
	usr_cfg.comm_prm.prtc_buff_size=1024;//��Լռ�û������ߴ�
	usr_cfg.comm_prm.comm_port=COMM_RS485_1;//����ͨ��
	usr_cfg.comm_prm.run_mode=RUN_MODE_CLIENT;//����ģʽ   ���ģʽ(0)���ͻ���(1)��������(2)
	usr_cfg.comm_prm.link_mode=0;//����ģʽ   TCP(0)��UDP(1)
	usr_cfg.comm_prm.link_app_mode=1;//����Ӧ��ģʽ  ����ģʽ(0)��������ģʽ(1)

	usr_cfg.comm_prm.port_prm.uart_prm.resend_count=3;		//�ط�����
	usr_cfg.comm_prm.port_prm.uart_prm.timeout=5;			//��ʱʱ�䣬��λ��s
	usr_cfg.comm_prm.port_prm.uart_prm.time_wait=1; 			//���͵ȴ����ʱ�䣬��λ��s

	
	if(IPC_ChRegister(&usr_cfg,sizeof(usr_cfg),5000,&ch_id1) == 0)
		printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id1);
	else
		printf("2IPC_ChRegister failed!\r\n");
	sleep(1);
	#endif

	//ע��ͨ��3==================================================
	usr_cfg.slaver_run_mode=RUN_MODE_CLIENT;//�ֽ������ģʽ
	usr_cfg.slaver_run_ip_index=CLIENT_IP_NUM0;//�ֽ������ip����

	usr_cfg.comm_prm.cs=0;//У��
	usr_cfg.comm_prm.enable=1;//ʧ��(0)��ʹ��(1)
	usr_cfg.comm_prm.cfg_sn=3;//�������
	usr_cfg.comm_prm.prtc_type=PRTC_MAINT;//��Լ����
	usr_cfg.comm_prm.prtc_level=0;//��ԼȨ�޵ȼ�
	usr_cfg.comm_prm.prtc_buff_size=1024;//��Լռ�û������ߴ�
	usr_cfg.comm_prm.comm_port=COMM_ETH_1;//����ͨ��
	usr_cfg.comm_prm.run_mode=RUN_MODE_CLIENT;//����ģʽ   ���ģʽ(0)���ͻ���(1)��������(2)
	usr_cfg.comm_prm.link_mode=0;//����ģʽ   TCP(0)��UDP(1)
	usr_cfg.comm_prm.link_app_mode=0;//����Ӧ��ģʽ  ����ģʽ(0)��������ģʽ(1)


	usr_cfg.comm_prm.port_prm.eth_prm.ip_type=0;		   //ip���� IPV4(0) IPV6(1)
	usr_cfg.comm_prm.port_prm.eth_prm.ip[0]=192;		   //ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[1]=168;			//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[2]=2;				//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[3]=6;				//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[4]=0;				//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip[5]=0;				//ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.port_num=8002;		//�˿ں�
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup_type=0;    //����ip����IPV4(0) IPV6(1)
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [0]=192;		//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [1]=168;		//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [2]=2;			//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [3]=6;			//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [4]=0;			//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_backup [5]=0;			//����ip��ַ
	
	usr_cfg.comm_prm.port_prm.eth_prm.port_backup_num=8003;  //���ö˿ں�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list_num=2; 	//�����˿��б���Ч���ݳ���
	
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[0]=9000;	//�����˿��б�,���10��
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[1]=9001;	//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[2]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[3]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[4]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[5]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[6]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[7]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[8]=0;		//�����˿��б�
	usr_cfg.comm_prm.port_prm.eth_prm.port_list[9]=0;		//�����˿��б�

	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy_type=0;	   //����ip����
	
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [0]=192;	//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [1]=168;	//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [2]=2;	//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [3]=8;	//����ip��ַ
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [4]=0;	//����ip��
	usr_cfg.comm_prm.port_prm.eth_prm.ip_proxy [5]=0;	//����ip��ַ

	
	usr_cfg.comm_prm.port_prm.eth_prm.port_proxy_num=8002;	//����˿ں�
	usr_cfg.comm_prm.port_prm.eth_prm.resend_count=3;		//�ط�����
	usr_cfg.comm_prm.port_prm.eth_prm.timeout=5;			//��ʱʱ�䣬��λ��s
	usr_cfg.comm_prm.port_prm.eth_prm.time_wait=1; 			//���͵ȴ����ʱ�䣬��λ��s
	usr_cfg.comm_prm.port_prm.eth_prm.cardiac_cycle=120;	//�������ڣ���λ��s		
	
	printf("sizeof(USR_CFG_T)=%lu\r\n",sizeof(USR_CFG_T));
	if(IPC_ChRegister(&usr_cfg,sizeof(USR_CFG_T),5000,&ch_id2) == 0)
		printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id2);
	else
		printf("1IPC_ChRegister failed!\r\n");
	sleep(1);


	
	//ע��ͨ��4==================================================
	//usr_cfg.slaver_run_mode=RUN_MODE_CLIENT;//�ֽ������ģʽ
	//usr_cfg.slaver_run_ip_index=CLIENT_IP_NUM1;//�ֽ������ip����
	
	usr_cfg.comm_prm.cs=0;//У��
	usr_cfg.comm_prm.enable=1;//ʧ��(0)��ʹ��(1)
	usr_cfg.comm_prm.cfg_sn=4;//�������
	usr_cfg.comm_prm.prtc_type=PRTC_DLT698;//��Լ����
	usr_cfg.comm_prm.prtc_level=0;//��ԼȨ�޵ȼ�
	usr_cfg.comm_prm.prtc_buff_size=1024;//��Լռ�û������ߴ�
	usr_cfg.comm_prm.comm_port=COMM_RS485_1;//����ͨ��
	usr_cfg.comm_prm.run_mode=RUN_MODE_CLIENT;//����ģʽ   ���ģʽ(0)���ͻ���(1)��������(2)
	usr_cfg.comm_prm.link_mode=0;//����ģʽ   TCP(0)��UDP(1)
	usr_cfg.comm_prm.link_app_mode=0;//����Ӧ��ģʽ  ����ģʽ(0)��������ģʽ(1)

	usr_cfg.comm_prm.port_prm.uart_prm.resend_count=3;		//�ط�����
	usr_cfg.comm_prm.port_prm.uart_prm.timeout=5;			//��ʱʱ�䣬��λ��s
	usr_cfg.comm_prm.port_prm.uart_prm.time_wait=1; 			//���͵ȴ����ʱ�䣬��λ��s

	
	if(IPC_ChRegister(&usr_cfg,sizeof(usr_cfg),5000,&ch_id3) == 0)
		printf("$$$$$$$$$$$$$$$$$$ch_id=%d\r\n",ch_id3);
	else
		printf("2IPC_ChRegister failed!\r\n");
	sleep(1);

	IPC_GetChStatus(ch_id, &ch_st,500);
	
	//sleep(1);
	IPC_GetChStatus(ch_id1, &ch_st1,500);
	
	//sleep(1);
	IPC_GetChStatus(ch_id2, &ch_st2,500);
	//sleep(1);
	IPC_GetChStatus(ch_id3, &ch_st3,500);
	printf("ch_st=%d,ch_st1=%d,ch_st2=%d,ch_st3=%d,\r\n",ch_st,ch_st1,ch_st2,ch_st3);
	sleep(2);
	while(1)
	{
		#if 1
		if(ch_st)
		{
			printf("\r\n\r\n\r\nCH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0CH0\r\n");
			memset(pipe_rbuf,0,128);
			rlen=IPC_AppReadDat(ch_id,pipe_rbuf,128);
			if(rlen)
				printf("ch_id=%d000000000000APP RCV[%d]:%s\r\n",ch_id,rlen,pipe_rbuf);
			sleep(1);
			
			wlen=IPC_AppWriteDat(ch_id,pipe_wbuf,128);
			if(wlen == 128)
				printf("ch_id=%d00000000000APP SND[%d]:%s\r\n",ch_id,wlen,pipe_wbuf);
		}
		
		if(ch_st1)
		{
			printf("\r\n\r\n\r\nCH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1CH1\r\n");
			memset(pipe_rbuf,0,128);
			rlen=IPC_AppReadDat(ch_id1,pipe_rbuf,128);
			if(rlen)
				printf("ch_id1=%d1111111111APP RCV[%d]:%s\r\n",ch_id1,rlen,pipe_rbuf);
			usleep(50000);
			
			wlen=IPC_AppWriteDat(ch_id1,pipe_wbuf1,128);
			if(wlen == 128)
				printf("ch_id1=%d1111111111APP SND[%d]:%s\r\n",ch_id1,wlen,pipe_wbuf1);
		}
		
		if(ch_st2)
		{
			printf("\r\n\r\n\r\nCH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2CH2\r\n");
			memset(pipe_rbuf,0,128);
			rlen=IPC_AppReadDat(ch_id2,pipe_rbuf,128);
			if(rlen)
				printf("ch_id1=%d2222222222APP RCV[%d]:%s\r\n",ch_id2,rlen,pipe_rbuf);
			usleep(50000);
			
			wlen=IPC_AppWriteDat(ch_id2,pipe_wbuf2,128);
			if(wlen == 128)
				printf("ch_id1=%d2222222222APP SND[%d]:%s\r\n",ch_id2,wlen,pipe_wbuf2);

		}

		if(ch_st3)
		{
			printf("\r\n\r\n\r\nCH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3CH3\r\n");
			memset(pipe_rbuf,0,128);
			rlen=IPC_AppReadDat(ch_id3,pipe_rbuf,128);
			if(rlen)
				printf("ch_id1=%d333333333333APP RCV[%d]:%s\r\n",ch_id3,rlen,pipe_rbuf);
			usleep(50000);
			wlen=IPC_AppWriteDat(ch_id3,pipe_wbuf1,128);
			if(wlen == 128)
				printf("ch_id1=%d33333333333APP SND[%d]:%s\r\n",ch_id3,wlen,pipe_wbuf3);

		}
		#endif
	}

	return 0;
}
 





