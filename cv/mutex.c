#include <errno.h>
#include <stdio.h>

#include "constants.h"
#include "queue.h"

#define OK 0

enum m_status {
	FREE, LOCKED
};

struct mutex {
	int owner;
	int id;
	struct queue* q;
	enum m_status status;
};

static int current_mutex_count;
static struct mutex mutexes[MAX_MUTEX_AMOUNT];


/* Local functions declaration */
static int get_mutex_pos(int id);
static int get_owner(int m_pos) ;

void init_mutex_table() {
	current_mutex_count = 0;
	for (int i = 0; i < MAX_MUTEX_AMOUNT; ++i) {
		mutexes[i].q = create_queue();
		mutexes[i].status = FREE;
	}
}

int lock(int mutex_id, int proc_id) {
	int mutex_pos = get_mutex_pos(mutex_id);
	printf("MUTEX_LOCK: id: %d, pos: %d\n", mutex_id, mutex_pos);
	if (mutex_pos == -1) {
		mutexes[current_mutex_count].owner = proc_id;
		mutexes[current_mutex_count].id = mutex_id;
		mutexes[current_mutex_count++].status = LOCKED;
		return OK;
	}
	else {
		int mutex_owner = get_owner(mutex_pos);
		printf("MUTEX_LOCK: id: %d, owner: %d\n", mutex_id, mutex_owner);
		/* Treat mutex as re-entrant lock */
		if (mutex_owner == proc_id) {
			return OK;
		}
		else {
			printf("MUTEX_LOCK_DO_NOT_REPLY: id: %d, asker: %d\n", mutex_id, proc_id);
			push(mutexes[mutex_pos].q, proc_id);
			return -EDONTREPLY; //WHY NOT MINUS!!!
		}
	}
}

static int get_mutex_pos(int id) {
	for (int i = 0; i < current_mutex_count; ++i) {
		if (mutexes[i].id == id) {
			return i;
		}
	}

	return -1;
}

static int get_owner(int m_pos) {
	return mutexes[m_pos].owner;
}