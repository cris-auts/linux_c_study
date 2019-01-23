#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>




int main(int argc, char** argv)
{
	static int parent_cnt=0;
	static int child_cnt=0;
	if(fork()==0)
	{
		while(1)
		{
			printf("This is child process!cnt=%d.\r\n",child_cnt++);
			sleep(1);
		}
	}	
	else
	{
		while(1)
		{
			printf("This is parent process!cnt=%d.\r\n",parent_cnt++);
			sleep(1);
		}
	}
}
