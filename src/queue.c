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

	printf("item1 address %p\n", &item1);
	printf("item2 address %p\n", &item2);

	enqueue(&item1);
	printf("LAST ELEMENT %p, with value %d\n", headers.tail, headers.tail->data);
	enqueue(&item2);
	printf("LAST ELEMENT %p, with value %d\n", headers.tail, headers.tail->data);

	QUEUEITEM q = head;

	while(1) {

		printf("data %d\n", q.data);
		if (q.next == NULL) {
			break;
		}

		q = *q.next;
	}

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
