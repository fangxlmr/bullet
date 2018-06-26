/*
 * 队列(queue)的代码实现
 */

#include <stdlib.h>
#include "queue.h"

/*
 * 队列结点结构
 */
typedef struct _QueueEntry QueueEntry;

struct _QueueEntry {
    QueueValue data;
    QueueEntry *next;
};

/*
 * 队列
 */
struct _Queue {
    QueueEntry *head;
    QueueEntry *tail;
};

Queue *queue_new(void)
{
    Queue *queue;

    queue = (Queue *) malloc(sizeof(Queue));

    if (!queue) {
        return QUEUE_NULL;
    }

    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void queue_free(Queue *queue)
{
    while (!queue_is_empty(queue)) {
        queue_pop(queue);
    }

    free(queue);
}

int queue_push(Queue *queue, QueueValue data)
{
    QueueEntry *new_entry;

    new_entry = (QueueEntry *) malloc(sizeof(QueueEntry));

    if (!new_entry) {
        return 0;
    }

    /*
     * 给结点赋值
     */
    new_entry->data = data;
    new_entry->next = NULL;

    /*
     * 插入队列。
     */
    if (queue_is_empty(queue)) {
        /*
         * 空队列
         */
        queue->tail = new_entry;
        queue->head = new_entry;

    } else {
        /*
         * 非空队列
         */
        queue->tail->next = new_entry;
        queue->tail = new_entry;
    }

    return 1;
}

QueueValue queue_pop(Queue *queue) {
    QueueEntry *entry;
    QueueValue result;

    if (queue_is_empty(queue)) {
        return QUEUE_NULL;
    }

    entry = queue->head;
    queue->head = entry->next;
    result = entry->data;

    /*
     * 释放最后一个元素，
     * 则需要把队尾结点也置空
     */
    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    free(entry);
    return result;
}

QueueValue queue_get_head(Queue *queue)
{
    if (queue_is_empty(queue)) {
        return QUEUE_NULL;
    }

    return queue->head->data;
}

QueueValue queue_get_tail(Queue *queue)
{
    if (queue_is_empty(queue)) {
        return QUEUE_NULL;
    }

    return queue->tail->data;
}

int queue_is_empty(Queue *queue)
{
    return queue->head == NULL;
}