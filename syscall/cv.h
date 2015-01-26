#ifndef _CV_H_
#define _CV_H_


#include <lib.h>
#include <minix/rs.h>
#include <minix/endpoint.h>
#include <stdio.h>

#define CV get_cv_proc_nr()

endpoint_t get_cv_proc_nr() {
	endpoint_t cv_pt;
	int result = minix_rs_lookup("cv", &cv_pt);
	if (result == 0) {
		return cv_pt;
	}
	else {
		//TODO
	}
}

int cs_lock(int);
int cs_unlock(int);

int cs_wait(int, int);
int cs_broadcast(int);
#endif	/* !_CV_H_ */
