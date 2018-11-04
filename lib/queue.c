/* 
 * queue.c
 *
 * Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include "queue.h"

struct entry {
    void *x;
    struct entry *next;
};

struct _queue {
    struct entry *head;
    struct entry *tail;
    size_t size;
};

queue_t *queue_new(void)
{
    queue_t *queue;

    queue = (queue_t *) malloc(sizeof(*queue));

    if (queue == NULL) {
        return NULL;
    } else {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
        return queue;
    }
}

void queue_free(queue_t *queue)
{
    assert(queue);
    while (! queue_isempty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

int enqueue(queue_t *queue, const void *x)
{
    struct entry *e;

    assert(queue);
    assert(x);

    e = (struct entry *) malloc(sizeof(*e));
    if (e == NULL) {
        return -1;
    } else {
        e->x = (void *) x;
        e->next = NULL;
    }

    if (queue_isempty(queue)) {
        queue->tail = e;
        queue->head = e;
    } else {
        queue->tail->next = e;
        queue->tail = e;
    }
    queue->size++;
    return 0;
}

void *dequeue(queue_t *queue) {
    struct entry *e;
    void *x;

    assert(queue);

    if (queue_isempty(queue)) {
        return NULL;

    } else {
        e = queue->head;
        queue->head = e->next;
        x = e->x;
        free(e);

        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        queue->size--;
        return x;
    }
}

void *queue_peek(queue_t *queue)
{
    assert(queue);
    if (queue_isempty(queue)) {
        return NULL;
    } else {
        return queue->head->x;
    }
}

int queue_isempty(queue_t *queue)
{
    assert(queue);
    return queue->head == NULL;
}

size_t queue_size(queue_t *queue)
{
    assert(queue);
    return queue->size;
}
