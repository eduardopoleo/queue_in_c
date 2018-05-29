	/*
 ============================================================================
 Name        : queue.c
 Author      : eduardo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// typedef is just alias that allows to shorten the struct
// definition in the global name space
// it does not matter that these bare the same name since they are
// defined on different name spaces. There is the struct name space and
// the global name space given by typedef

// Copy the queue onto another queue
	// - by dequeueing the first list (shallow copying)
		// remember that memcpy a pointer will only copy the reference.
	// - by having to exact same lists (deep copying)
// remove an item in the middle of the list at a given position (regardless of data) (remember to free memory)
// add an item to a arbitrary position of the list.

typedef struct queueitem {
	struct queueitem *next;
	struct queueitem *prev;
	int data;
} QUEUEITEM;

typedef struct queueheaders {
	struct queueitem *head;
	struct queueitem *tail;
} QUEUEHEADERS;

// why can't I play around with these vars on this scope?

void enqueue(QUEUEHEADERS *headers, QUEUEITEM *item) {
	if (headers->head == NULL) {
		printf("No items in the queue. Setting the given item as head and tail\n");
		headers->head = item;
		headers->tail = item;

		return;
	}

	item->prev = headers->tail;
	item->next = NULL;

	headers->tail->next = item;
	headers->tail = item;
}

int size(QUEUEHEADERS headers) {
	int size;

	QUEUEITEM * q;

	q = headers.head;

	size = 0;

	// if current element is null
	while (q != NULL) {
		size++;
		q = q->next; //
	}

	return size;
}

QUEUEHEADERS copy(QUEUEHEADERS headers) {
	QUEUEHEADERS copy_headers;
	copy_headers.head = NULL;
	copy_headers.tail = NULL;

	QUEUEITEM *current_item = headers.head;
//
	while (current_item != NULL) {
		QUEUEITEM *item = (QUEUEITEM *)malloc(sizeof(QUEUEITEM));
		memcpy(item, current_item, sizeof(QUEUEITEM));
		item->data = current_item->data;
		enqueue(&copy_headers, item);
//
		current_item = current_item->next;
	}
//
	return copy_headers;
}

QUEUEITEM dequeue(QUEUEHEADERS headers) {
	// TODO remember to free non used memory.
	QUEUEITEM *current_head = headers.head;
	if (headers.head == NULL) {
		printf("Current queue is empty, returning an unlinked item\n");
		QUEUEITEM orphan_item;
		return orphan_item;
	}

	if (current_head->next == NULL) {
		printf("Current Head is the last node in the queue\n");
		headers.head = NULL;
		return *current_head;
	}

	headers.head = current_head->next;
	current_head->next = NULL;
	headers.head->prev = NULL;

	return *current_head;
}

int main(void) {
	// C does not like to when one uses uninitialized references.
	// So when possible use the actual thing and use indirection when needed.
	QUEUEHEADERS headers;

	QUEUEITEM item1;
	QUEUEITEM item2;
	QUEUEITEM item3;

	item1.data = 1;
	item2.data = 2;
	item3.data = 3;

	enqueue(&headers, &item1);
	enqueue(&headers, &item2);
	enqueue(&headers, &item3);

	int queue_size = size(headers);

	printf("Original queue size %d\n", queue_size);

	QUEUEITEM *q = headers.head;

	while(q != NULL) {
		printf("data %d, address %p\n", q->data, q);
		q = q->next;
	}

	QUEUEHEADERS copy_headers = copy(headers);

	int copy_queue_size = size(copy_headers);

	printf("Copy queue size %d\n", copy_queue_size);

	q = copy_headers.head;

	while(q != NULL) {
		printf("data %d, address %p\n", q->data, q);
		q = q->next;
	}

	return EXIT_SUCCESS;
}
