/* 
 * queue.h
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

#ifndef BULLET_QUEUE_H
#define BULLET_QUEUE_H

#include <stdlib.h>

/**
 * Define a new data type: queue_t 
 */
typedef struct _queue *queue_t;

/**
 * Define a new queueElem type.
 */
typedef void *queueElem;

/**
 * queue_new - Create a new queue
 *
 * @queue[out]: the queue
 *
 * Return 0 if success, -1 if failed to alloc memory.
 */
extern int queue_new(queue_t *queue);

/**
 * queue_free - Destroy a queue
 *
 * @queue[in]: the queue to be destoyed
 */
extern void queue_free(queue_t *queue);

/**
 * queue_push - Enqueue an element
 *
 * @queue[in]: the queue
 * @x[in]: value to be stored
 *
 * Return 0 if success, -1 if failed to alloc memory.
 */
extern int queue_push(queue_t queue, queueElem x);

/**
 * queue_pop - Dequeue an element
 *
 * @queue[in]: the queue
 * @x[out]: output value
 *
 * Return 0 if success, -1 if queue is already empty.
 */
extern int queue_pop(queue_t queue, queueElem *x);

/**
 * queue_peek - Peek value without removing it
 *
 * @queue[in]: the queue
 * @x[out]: output value
 *
 * Return 0 if success, -1 if queue is already empty.
 */
extern int queue_peek(queue_t queue, queueElem *x);

/**
 * queue_isempty - Check if queue is empty or not
 *
 * @queue[in]: the queue
 *
 * Return non-zero if the queue is empty, 0 it is.
 */
extern int queue_isempty(queue_t queue);

/**
 * queue_get_size - Get size of queue
 *
 * @queue[in]: the queue
 *
 * Return size of the queue, 0 if queue is already empty.
 */
extern size_t queue_get_size(queue_t queue);

#endif /* BULLET_QUEUE_H */
