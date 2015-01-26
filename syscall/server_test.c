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
	int x;
	scanf("%d", &x);
	if (x == 0) {
		cs_lock(5);
		cs_wait(5, 5);
		printf("GOT IT!\n");	
	}
	else {
		cs_broadcast(5);
	}
	
	return 0;
}
