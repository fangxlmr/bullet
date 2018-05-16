#ifndef BULLET_QUEUE_H
#define BULLET_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

/* user defined QueueElemType */
typedef int QueueElemType;

typedef struct QueueNode {  /* node of queue */
    QueueElemType e;
    struct QueueNode *next;
}QueueNode, *pQueueNode;

typedef struct Queue {      /* queue info */
    pQueueNode front, rear; /* front and rear point */
    /* Some other data, say, count of nodes */
}Queue, *pQueue;

/* Create a new queue and initialize it.
 * Return NULL if malloc failed,
 * or return the address of malloced stack.
 * */
pQueue queue_new (void);

/* Push an Elem e into queue.
 * If NULL queue was used, print info, and program exits.
 * If malloced failed, return false,
 * or push the elem into queue and return true.
 * */
bool queue_push (pQueue queue, QueueElemType e);

/* Pop an Elem e out of queue.
 * If NULL queue was used, print info, and program exits.
 * If queue is already empty, then print info, and program exits.
 * Or pop the head of queue, and return true.
 * */
bool queue_pop (pQueue queue);

/* Destroy a stack completely.
 * If NULL queue was used, print info, and program exits.
 * Or free all nodes (QueueNode and Queue), and return true.
 * */
bool queue_destroy (pQueue queue);

/* Clear a queue.
 * If NULL queue was used, print info, and program exits.
 * Or clear all QueueNodes in the queue, and return true.
 * */
pQueue queue_clear (pQueue queue);

/* Check the queue is empty or not.
 * If NULL queue was used, print info, and program exits.
 * Return true if empty, or return false.
 * */
bool queue_isempty (pQueue queue);

/* Get the head of queue.
 * If NULL queue was used, print info, and program exits.
 * Print info if queue is empty, and program exits.
 * Or return the head value of queue.
 * */
QueueElemType queue_gethead (pQueue queue);

#endif /* BULLET_QUEUE_H */
