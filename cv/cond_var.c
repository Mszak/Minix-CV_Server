#include <errno.h>
#include <stdio.h>
#include <minix/endpoint.h>
#include <minix/ipc.h>

#include "constants.h"
#include "queue.h"
#include "mutex.h"

#define OK 0
#define PROC_NR 100

struct cvar {
	int id;
	struct queue* q;
	struct queue* m_q;
};

static int current_cvars_count;
static struct cvar cvars[PROC_NR];

static void add_to_wait_q(int, int, int);
static int get_cvar_pos(int);
static void notify_succ(int);

void init_cvar_table() {
	current_cvars_count = 0;
	for (int i = 0; i < PROC_NR; ++i) {
		cvars[i].q = create_queue();
		cvars[i].m_q = create_queue();
	}
}

int wait(int cvar_id, int mutex_id, int proc_id) {
	int m_pos = get_mutex_pos(mutex_id);
	if (m_pos != -1) {
		int m_owner = get_owner(m_pos);
		if (m_owner == proc_id) {
			printf("CV_WAIT on cvar %d on mutex %d, proc: %d\n", cvar_id, mutex_id, proc_id);
			unlock(mutex_id, proc_id);
			add_to_wait_q(cvar_id, proc_id, mutex_id);
			return -EDONTREPLY;
		}
	}
	
	return -EINVAL;
}

void broadcast(int cvar_id) {
	int cv_pos = get_cvar_pos(cvar_id);
	if (cv_pos != -1) {
		while (!isEmpty(cvars[cv_pos].q)) {
			int proc_id = pop(cvars[cv_pos].q);
			int mutex_id = pop(cvars[cv_pos].m_q);
			printf("CV_BROADCAST: %d on mutex %d\n", proc_id, mutex_id);
			if (lock(mutex_id, proc_id) == OK) {
				notify_succ(proc_id);
			}
		}
		cvars[cv_pos] = cvars[--current_cvars_count];
	}
}

static void add_to_wait_q(int cvar_id, int proc_id, int mutex_id) {
	for (int i = 0; i < current_cvars_count; ++i) {
		if (cvars[i].id == cvar_id) {
			push(cvars[i].q, proc_id);
			push(cvars[i].m_q, mutex_id);
			return;
		}
	}

	cvars[current_cvars_count].id = cvar_id;
	push(cvars[current_cvars_count].m_q, mutex_id);
	push(cvars[current_cvars_count++].q, proc_id);
}

static int get_cvar_pos(int cvar_id) {
	for (int i = 0; i < current_cvars_count; ++i) {
		if (cvars[i].id == cvar_id) {
			return i;
		}
	}

	return -1;
}

static void notify_succ(int proc) {
	message m;
	m.m_type = OK;
	int s = send(proc, &m);
  	if (OK != s) {
    	printf("CV: unable to send reply to %d: %d\n", proc, s);
  	}
}