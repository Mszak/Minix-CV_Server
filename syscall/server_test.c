#include <sys/cdefs.h>
#include <lib.h>

#include <minix/rs.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <errno.h>
#include <minix/endpoint.h>
#include <stdio.h>
#include <unistd.h>
#include <cv.h>
#include <errno.h>
#include <string.h>

int main(int argx, char** argv)
{
	cs_lock(5);
	// printf("Got lock\n");
	// int x;
	// scanf("%d", &x);
	printf("%d, errno: %s\n", cs_wait(5, 5), strerror(errno));
	return 0;
}
