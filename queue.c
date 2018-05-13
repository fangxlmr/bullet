#include "queue.h"

/* Static functions */
/* Queue_isnull function
 * Print info if queue is NULL, and program exits.
 * Or do nothing.
 * */
static void queue_isnull (pQueue queue);


/* External functions */
/* Create a new queue and initialize it */
pQueue queue_new (void) {
    pQueueNode q = (pQueueNode) malloc(sizeof(QueueNode));
    if (!q) {
        return NULL;
    }
    memset(q, 0, sizeof(QueueNode));
    pQueue queue = (pQueue) malloc(sizeof(Queue));
    if (!queue)
        return NULL;
    queue->front = queue->rear = q;
    return queue;
}


/* push an Elem e into queue (at rear) */
bool queue_push (pQueue queue, QueueElemType e) {
    queue_isnull(queue);
    pQueueNode q = (pQueueNode) malloc(sizeof(QueueNode));
    if (!q){
        return false;
    }
    q->e = e;
    q->next = NULL;
    queue->rear->next = q;
    queue->rear = q;
    return true;
}


/* pop an Elem e out of queue (at front) */
bool queue_pop (pQueue queue) {
    if (queue_isempty(queue)) {
        printf("Queue is already empty, and can't be popped.\n");
        printf("Program exits.\n");
        exit(-1);
    }
    if (queue->front->next == queue->rear) {
        /* if there is only one node in queue */
        free(queue->rear);
        queue->rear = queue->front;
        queue->front->next = NULL;
    } else {
        /* two or more nodes in queue */
        pQueueNode q = queue->front->next;
        queue->front->next = q->next;
        free(q);
    }
    return true;
}


/* destroy a queue completely */
bool queue_destroy (pQueue queue) {
    queue_clear(queue);
    free(queue);
    return true;
}

/* clear a queue */
pQueue queue_clear (pQueue queue) {
    queue_isnull(queue);
    if (queue->front == queue->rear) {
        /* it is already clear */
        return queue;
    }

    /* clear all nodes in queue */
    pQueueNode q;
    while (queue->front->next != queue->rear) {
        q = queue->front->next;
        queue->front->next = q->next;
        free(q);
    }
    q = queue->rear;
    free(q);
    queue->rear = queue->front;
    queue->front->next = NULL;
    return queue;
}

/* queue is empty or not */
bool queue_isempty (pQueue queue) {
    queue_isnull(queue);
    return (queue->front == queue->rear) ? true : false;
}

/* get the top of queue */
QueueElemType queue_gethead (pQueue queue) {
    if (queue_isempty(queue)) {
        printf("Queue is empty, no head value. Program exits.\n");
        exit(-1);
    }
    return queue->front->next->e;
}


static void queue_isnull (pQueue queue) {
    if (!queue) {
        printf("NULL queue was used. Program exits.\n");
        exit(-1);
    }
}