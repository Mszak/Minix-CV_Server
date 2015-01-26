#ifndef _QUEUE_H
#define _QUEUE_H

#include <minix/endpoint.h>

struct queue_node {
	endpoint_t proc_nr;
	queue_node* next;
};

struct queue {
	static queue_node* head;
	static queue_node* tail;
};

queue* create_queue();
void push(struct queue* q, endpoint_t e);
endpoint_t pop(struct queue* q);
int isEmpty(struct queue* q);
void destroy(struct queue* q);

#endif