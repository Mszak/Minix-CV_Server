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

int main(int argx, char** argv)
{
	printf("%d\n", cs_lock(5));
	printf("%d\n", cs_unlock(5));
	printf("%d\n", cs_wait(5, 4));
	printf("%d\n", cs_broadcast(5));
	return 0;
}
