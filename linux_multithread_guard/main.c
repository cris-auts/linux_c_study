#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include<unistd.h>
#include <signal.h>
#include <errno.h>
 
/*线程变量*/
pthread_t thread[3];
pthread_mutex_t mut;

 
void *thread1()
{
 
	/*线程互斥锁*/
 	//pthread_mutex_lock(&mut);
	//pthread_mutex_unlock(&mut);
	int i = 0;
	
	while(i++ < 10) {
		printf("111\n");
		sleep(1);
	}
	
	pthread_exit(NULL);
}
 
/*定时函数*/
void sigalrm_func(int sig)
{
	alarm(2); /*改为定时2s*/
	printf("222\n");
}
 
 
void *thread2()
{
	/*定时1s，处理函数为*/
	signal(SIGALRM, sigalrm_func);
	alarm(1);
 
	while(1);
	/*线程互斥锁*/
 	//pthread_mutex_lock(&mut);
	//pthread_mutex_unlock(&mut);
 
	pthread_exit(NULL);
}
 
void thread_wait(int i)
{
        /*等待线程结束*/
        if(thread[i] != 0) {
                pthread_join(thread[i],NULL);
        }
}
 typedef void *(*thread_func) (void *);
 thread_func switch_control_thread[3]={
 thread1,
 thread2,
};
/*pthread_kill的返回值：成功（0） 线程不存在（ESRCH） 信号不合法（EINVAL）*/
void test_pthread(int i) 
{
	int pthread_kill_err;
	pthread_kill_err = pthread_kill(thread[i],0);
 
	if(pthread_kill_err == ESRCH) {
		printf("pthread[%d] no existence or withdrawal.\n", i);
		pthread_join(thread[i],NULL);
		sleep(10);
		if((pthread_create(&thread[i], NULL, switch_control_thread, NULL)) != 0) {
			printf("[sqlite] -- switch_control_thread create error!\n");
        }
	}
	else if(pthread_kill_err == EINVAL)
		printf("unlawful transmission of signals.\n");
	else
		printf("pthread[%d] still alive.\n", i);
}
 
/*检测所有线程的存活状态*/
void *thread3()
{
	while(1) {
		sleep(3);
		test_pthread(0);
		test_pthread(1);
		test_pthread(2);
	}
	
	pthread_exit(NULL);
}
 
void thread_create(void)
{
        int temp;
        memset(&thread, 0, sizeof(thread));
        /*创建线程*/
        if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0) {
			printf("[sqlite] -- switch_control_thread create error!\n");
        }
 
        if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0) {
			printf("[sqlite] -- data_control_thread create error!\n");
        }
		
		if((temp = pthread_create(&thread[2], NULL, thread3, NULL)) != 0) {
			printf("[sqlite] -- data_control_thread create error!\n");
        }
}
 
int main()
{
	/*用默认属性初始化互斥锁*/
	pthread_mutex_init(&mut,NULL);
 
	thread_create();
	
	while(1);
	
	return 0;
}

