#include <stdio.h>
#include "zlog.h"

int main(int argc, char** argv)

{
	int rc;
	rc = dzlog_init("test_default.conf", "my_cat");

	if (rc) {
		printf("init failed\n");
		return -1;
	}
	while(1)
	{
		dzlog_info("2.hello, zlog,xxxxxxxxxxxxxxxxxxxxx");

		
		sleep(1);
	}
	zlog_fini();
	return 0;
} 
