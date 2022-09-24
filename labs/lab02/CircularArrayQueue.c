// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16  // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	if (q->size == q->capacity) {
		int oldCap = q -> capacity;
		q->capacity *= 2;
		q->items = realloc(q->items, q->capacity * sizeof(Item));
		for(int i = 0; i < oldCap - q->frontIndex;i++)
			q->items[q->capacity - 1 - i] = q->items[oldCap - 1 - i];
		
		q->frontIndex = q->capacity - (oldCap - q->frontIndex);
	}
	int endIndex = 0;
	if (q->frontIndex + q->size < q->capacity)
		endIndex = q->frontIndex + q->size;
	else
		endIndex = (q->frontIndex + q->size) - q->capacity;
	q->items[endIndex] = it;
	q->size += 1;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	Item v = q->items[q->frontIndex];
	if (q->frontIndex == q->capacity - 1)
		q->frontIndex = 0;
	else
		q->frontIndex += 1;
	q->size -= 1;
	return v;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->items[q->frontIndex];
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
	for (int i = q->frontIndex, j = 0; j < q->size;
	     i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {
	if (q->frontIndex + q->size < q->capacity) {
		for (int i = q->frontIndex; i < q->size; i++)
			printf("%d\n", q->items[i]);
	} else {
		for (int i = q->frontIndex; i < q->capacity; i++)
			printf("%d\n", q->items[i]);
		for (int j = 0; j < (q->frontIndex + q->size) - q->capacity; j++)
			printf("%d\n", q->items[j]);
	}
}
