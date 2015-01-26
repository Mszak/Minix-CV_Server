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
};

static int current_cvars_count;
static struct cvar cvars[PROC_NR];

static void add_to_wait_q(int, int);

void init_cvar_table() {
	current_cvars_count = 0;
	for (int i = 0; i < PROC_NR; ++i) {
		cvars[i].q = create_queue();
	}
}

int wait(int cvar_id, int mutex_id, int proc_id) {
	int m_pos = get_mutex_pos(mutex_id);
	if (m_pos != -1) {
		int m_owner = get_owner(m_pos);
		if (m_owner == proc_id) {
			unlock(mutex_id, proc_id);
			add_to_wait_q(cvar_id, proc_id);
			return -EDONTREPLY;
		}
	}
	
	return -EINVAL;
}

int broadcast(int cvar_id) {
	return OK;
}

static void add_to_wait_q(int cvar_id, int proc_id) {
	for (int i = 0; i < current_cvars_count; ++i) {
		if (cvars[i].id == cvar_id) {
			push(cvars[i].q, proc_id);
			return;
		}
	}

	cvars[current_cvars_count].id = cvar_id;
	push(cvars[current_cvars_count++].q, proc_id);
}