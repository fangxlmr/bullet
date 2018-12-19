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

#include <stddef.h>
#include "queue.h"
struct entry {
    queueElem x;
    struct entry *next;
};

struct _queue {
    struct entry *head;
    struct entry *tail;
    size_t size;
};

int queue_new(queue_t *queue)
{
    queue_t new_queue;

    new_queue = (queue_t) malloc(sizeof(*new_queue));
    if (queue == NULL) {
        return -1;
    } else {
        new_queue->head = NULL;
        new_queue->tail = NULL;
        new_queue->size = 0;
        *queue = new_queue;
        return 0;
    }
}

void queue_free(queue_t *queue)
{
    queueElem x;

    while (queue_isempty(*queue) == 0) {
        queue_pop(*queue, &x);
    }
    free(*queue);
    *queue = NULL;
}

int queue_push(queue_t queue, queueElem x)
{
    struct entry *e;

    e = (struct entry *) malloc(sizeof(*e));
    if (e == NULL) {
        return -1;
    } else {
        e->x = x;
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

int queue_pop(queue_t queue, queueElem *x)
{
    struct entry *e;

    if (queue_isempty(queue)) {
        return -1;
    } else {
        e = queue->head;
        queue->head = e->next;
        *x = e->x;
        free(e);

        if (queue->head == NULL) {
            queue->tail = NULL;
        }
        queue->size--;
        return 0;
    }
}

int queue_peek(queue_t queue, queueElem *x)
{
    if (queue_isempty(queue)) {
        return -1;
    } else {
        *x = queue->head->x;
        return 0;
    }
}

int queue_isempty(queue_t queue)
{
    return queue->head == NULL;
}

size_t queue_get_size(queue_t queue)
{
    return queue->size;
}
