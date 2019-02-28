#include"std_globals.h"
#if __SYS_NVRAM_ENABLE__
#include "nvram.h"
#endif
#if __SYS_DBASE_ENABLE__
#include "dbase.h"
#endif
#if __SYS_METER_ENABLE__
#include "app_meter_task.h"
#endif


typedef enum thread_idx_t
{
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
	#if __SYS_METER_ENABLE__
	{THREAD_METER,		"METER",	&meter.gpram.thread,	APP_MeterThread,	NULL},
	#endif
};


int main(int argc, char** argv)
{
	int res=0;
	int thread_idx=0;
	memset(&g_dev_prm.nvram.debug_log_st,0,sizeof(g_dev_prm.nvram.debug_log_st));
	g_dev_prm.nvram.debug_log_st.rs485_log=1;
	//NVRAM_Load();
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
 

