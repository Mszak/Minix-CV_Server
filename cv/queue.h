#ifndef _QUEUE_H
#define _QUEUE_H

#include <minix/endpoint.h>

struct queue_node {
	endpoint_t proc_nr;
	struct queue_node* next;
};

struct queue {
	struct queue_node* head;
	struct queue_node* tail;
};

struct queue* create_queue();
void push(struct queue* q, endpoint_t e);
endpoint_t pop(struct queue* q);
int isEmpty(struct queue* q);
void destroy(struct queue* q);

#endif