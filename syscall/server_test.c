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
	cs_lock(5);
	printf("Got lock\n");
	int x;
	scanf("%d", &x);
	cs_unlock(5);
	return 0;
}
