#include <minix/endpoint.h>
#include <stdlib.h>

#include "queue.h"

struct queue* create_queue() {
	struct queue* new_queue = malloc(sizeof(struct queue));
	new_queue->head = malloc(sizeof(struct queue_node));
	new_queue->head->next = NULL;
	new_queue->tail = new_queue->head;
	return new_queue;
}

void push(struct queue* q, endpoint_t e) {
	q->tail->next = malloc(sizeof(struct queue_node));
	q->tail = q->tail->next;

	q->tail->proc_nr = e;
	q->tail->next = NULL;
}

endpoint_t pop(struct queue* q) {
	struct queue_node* result = q->head->next;
	q->head->next = result->next;
	if (q->head->next == NULL) {
		q->tail = q->head;
	}
	int result_proc = result->proc_nr;
	free(result);
	return result_proc;
}

int isEmpty(struct queue* q) {
	return q->head == q->tail;
}

void destroy(struct queue* q) {
	while (!isEmpty(q)) {
		pop(q);
	}

	free(q->head);
	free(q);
}