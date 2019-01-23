#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define THREAD_NUMBER	(3)
#define REPEAT_NUMBER	(5)
#define DELAY_TIME_LEVELS	(10.0)





void* thrd_func(void* arg)
{
	int thrd_no = (int)arg;
	int delay_time = 0;
	int count = 0;

	printf("Thread %d is starting\r\n",thrd_no);
	for(count = 0; count < REPEAT_NUMBER; count++)
	{
		delay_time = (int)(rand()*DELAY_TIME_LEVELS/(RAND_MAX))+1;
		sleep(delay_time);
		printf("\tThread %d: job %d delay=%ds\r\n",thrd_no,count,delay_time);
	}
	printf("Thread %d finished.\r\n",thrd_no);
	pthread_exit(NULL); 
} 






int main(int argc, char** argv)
{
	pthread_t thread[THREAD_NUMBER];	
	int no=0,res=0;
	void* thrd_ret;
	
	srand(time(NULL));
	for(no=0;no<THREAD_NUMBER;no++)
	{
		res=pthread_create(&thread[no],NULL,thrd_func,(void*)no);
		if(res != 0)
		{
			printf("create thread %d failed!\r\n",no);
		}

	}
	printf("Create thread successfully, wait for thread to finished...\r\n");
	
	for(no=0;no<THREAD_NUMBER;no++)
	{
		res=pthread_join(thread[no],&thrd_ret);
		if(res != 0)
		{
			printf("thread %d joined failed.\r\n",no);
		}
		else
			printf("thread %d joined.\r\n",no);
	}
	return 0;
}
