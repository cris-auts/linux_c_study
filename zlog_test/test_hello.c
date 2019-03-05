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

	dzlog_info("hello, zlog");

	zlog_fini();

	return 0;
} 