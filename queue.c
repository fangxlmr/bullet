#include <stdlib.h>
#include <assert.h>
#include "queue.h"

#define T Queue_T

typedef struct elem {
    void *x;
    struct elem *next;
}elem;

struct T {
    int count;
    elem *front, *rear;
};


/* 新建队列，并初始化 */
T queue_new (void) {
    T que;

    que = (T) malloc(sizeof(struct T));
    que->count = 0;
    que->front = que->rear = NULL;
    return que;
}


/* 判断队列是否为空 */
int queue_empty (T que) {
    return que->count == 0;
}


/* 队列长度 */
int queue_size (T que) {
    assert(que);
    return que->count;
}


/* 元素入队 */
void enqueue (T que, void *x) {
    elem *t;

    t = (elem *)malloc(sizeof(elem));
    t->x = x;
    t->next = NULL;

    if (queue_empty(que)) {
        que->rear->next = t;
        que->rear = t;
        que->front = que->rear;
    } else {
        que->rear->next = t;
        que->rear = t;
    }
    que->count++;
}


/* 元素出队 */
void *dequeue (T que) {
    void *x;
    elem *t;

    assert(que);
    assert(que->count > 0);
    if (que->count == 1) {
         /* 队列只有一个元素 */
        t = que->front;
        que->rear = que->front = NULL;
    } else {
        /* 队列有2个及以上的元素 */
        t  = que->front;
        que->front = t->next;
    }
    que->count--;
    x = t->x;
    free(t);
    return x;
}


/* 释放队列 */
void queue_free (T *que) {
    elem *t, *u;

    assert(que && *que);
    for (t = (*que)->front; t; t = u) {
        u = t->next;
        free(t);
    }
    free(*que);
    *que = NULL;
}