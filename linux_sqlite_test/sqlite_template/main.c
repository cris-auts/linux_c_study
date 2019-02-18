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




int main(int argc, char** argv)
{
	int res=0;
	pthread_t thread_modbus;
	void* thrd_ret;
	PrintLog("Hello,World!\r\n");
	memset(&g_dev_prm.debug_log_st,1,sizeof(g_dev_prm.debug_log_st));

	res=pthread_create(&thread_modbus,NULL,APP_ModbusTask,NULL);
	if(res != 0)
	{
		PrintLog("create thread_modbus failed!\r\n");
	}
	PrintLog("Create thread_modbus successfully, wait for thread to finished...\r\n");
	res=pthread_join(thread_modbus,&thrd_ret);
	if(res != 0)
	{
		PrintLog("thread_modbus joined failed.\r\n");
	}
	else
		PrintLog("thread_modbus joined.\r\n");
	return 0;
}
 

