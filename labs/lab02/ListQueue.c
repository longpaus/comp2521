// Implementation of the Queue ADT using a linked list

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

typedef struct node *Node;
struct node {
	Item item;
	Node next;
};

struct queue {
	Node head;
	Node tail;
	int size;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	Node curr = q->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	Node newNode = malloc(sizeof(Node));
	newNode->item = it;
	newNode->next = NULL;
	if (q->head == NULL && q->tail == NULL) {
		q->head = newNode;
		q->tail = newNode;
	} else {
		q->tail->next = newNode;
		q->tail = newNode;
	}
	q->size += 1;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	Item v = q->head->item;
	Node tmp = q->head;
	q->head = q->head->next;
	free(tmp);
	q->size -= 1;
	return v;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->head->item;
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the items in the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (Node curr = q->head; curr != NULL; curr = curr->next) {
		fprintf(fp, "%d ", curr->item);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {
	Node curr = q->head;
	while (curr != NULL) {
		printf("%d\n", curr->item);
		curr = curr->next;
	}
}
