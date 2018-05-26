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
QUEUEHEADERS headers;
QUEUEITEM head;

void enqueue(QUEUEITEM *item) {
	item->prev = headers.tail;
	item->next = NULL;
	headers.tail->next = item;
	headers.tail = item;
}

QUEUEITEM dequeue() {
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
	head.data = 1;
	headers.head = &head;
	headers.tail = &head;

	// C does not like to when one uses uninitialized references.
	// So when possible use the actual thing and use indirection when needed.
	QUEUEITEM item1;
	QUEUEITEM item2;

	item1.data = 2;
	item2.data = 3;

	enqueue(&item1);
	enqueue(&item2);

	QUEUEITEM q = head;

	while(1) {

		printf("data %d\n", q.data);
		if (q.next == NULL) {
			break;
		}

		q = *q.next;
	}

	QUEUEITEM dequeued_node = dequeue();
	printf("Dequeue node value, %d\n", dequeued_node.data);
	dequeued_node = dequeue();
	printf("Dequeue node value, %d\n", dequeued_node.data);
	dequeued_node = dequeue();
	printf("Dequeue node value, %d\n", dequeued_node.data);
	dequeued_node = dequeue();
	printf("Dequeue node value, %d\n", dequeued_node.data);

	// create a new queueitem
	//	enqueue(queueitem)
	//	--> associates the item with the current last
	//	--> appends makes item last
	//  dequeue()
	//	--> makes second element heads
	// 	--> sets null prev to old head
	//  --> returns the dequeued element
	// special case when the queue is empty.
	return EXIT_SUCCESS;
}
