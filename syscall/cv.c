#include <lib.h>
#include <cv.h>

#define mutex_number m1_i1
#define cond_var_number m1_i2

int cs_lock(mutex_id)
int mutex_id;
{
	message m;
	m.mutex_number = mutex_id;
	return(_syscall(CV, CV_LOCK, &m));
}

int cs_unlock(mutex_id)
int mutex_id;
{
	message m;
	m.mutex_number = mutex_id;
	return(_syscall(CV, CV_UNLOCK, &m));
}

int cs_wait(cond_var_id, mutex_id)
int cond_var_id;
int mutex_id;
{
	message m;
	m.cond_var_number = cond_var_id;
	m.mutex_number = mutex_id;
	return(_syscall(CV, CV_WAIT, &m));
}

int cs_broadcast(cond_var_id)
int cond_var_id;
{
	message m;
	m.cond_var_number = cond_var_id;
	return(_syscall(CV, CV_BRAODCAST, &m));
}