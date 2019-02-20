#include"std_globals.h"
#include "dbase.h"

#if __SYS_MODBUS_ENABLE__
#include "app_modbus_task.h"
#endif
#if __SYS_DLT645_ENABLE__
#include "app_dlt645_task.h"
#endif
#if __SYS_METER_ENABLE__
#include "app_meter_task.h"
#endif



typedef enum thread_idx_t
{
	#if __SYS_MODBUS_ENABLE__
    THREAD_MODBUS=0,
    #endif
	#if __SYS_DLT645_ENABLE__
    THREAD_DLT645,
	#endif
	#if __SYS_METER_ENABLE__
    THREAD_METER,
	#endif
    THREAD_MAX
}THREAD_IDX_T;


typedef struct thread_info_t{
	THREAD_IDX_T 	thread_idx;
    char*    		thread_name;
	pthread_t*   	thread;
	void* 			(*pthread_func)(void *p_arg);
	pthread_attr_t* pthread_attr;
}THREAD_INFO_T;


THREAD_INFO_T thread_info[THREAD_MAX]={     
	#if __SYS_MODBUS_ENABLE__
	{THREAD_MODBUS,		"MODBUS",	&modbus.gpram.thread,	APP_ModbusThread,	NULL},
	#endif
	#if __SYS_DLT645_ENABLE__
	{THREAD_DLT645,		"DLT645",	&dlt645.gpram.thread,	APP_Dlt645Thread,	NULL},
	#endif
	#if __SYS_METER_ENABLE__
	{THREAD_METER,		"METER",	&meter.gpram.thread,	APP_MeterThread,	NULL},
	#endif
};


int main(int argc, char** argv)
{
	int res=0;
	int thread_idx=0;
	memset(&g_dev_prm.debug_log_st,1,sizeof(g_dev_prm.debug_log_st));

	for(thread_idx=0;thread_idx<THREAD_MAX;thread_idx++)
	{
		res=pthread_create(thread_info[thread_idx].thread,
						   thread_info[thread_idx].pthread_attr,
						   thread_info[thread_idx].pthread_func,
						   &thread_info[thread_idx]);
		if(res != 0)
		{
			pthread_detach(*thread_info[thread_idx].thread);
			PrintLog("create thread %s failed!\r\n",thread_info[thread_idx].thread_name);
		}
		else
			PrintLog("Create thread %s successfully\r\n",thread_info[thread_idx].thread_name);
	}
	
	while(1)
		sleep(1);
	return 0;
}
 

