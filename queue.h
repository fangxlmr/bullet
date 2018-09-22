/*
 * queue.h
 * 
 * Written by fangxl (fangxlmr@foxmail.com) on 22/09/2018.
 *                                                                      
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3.0 of the License, or
 * (at your option) any later version.
 *   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *     
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see the file COPYING, or write
 * to the Free Software Foundation, Inc.
 */

#ifndef BULLET_QUEUE_H
#define BULLET_QUEUE_H

#include <stdlib.h>

/**
 * define a queue_t structure
 */
typedef struct _queue queue_t;

/**
 * queue_new - Create a new queue
 *
 * Return a queue_t pointer if success,
 * NULL pointer otherwise.
 */
extern queue_t *queue_new(void);

/**
 * queue_free - Destroy a queue
 *
 * @queue: the queue to be destoyed
 */
extern void queue_free(queue_t *queue);

/**
 * enqueue - Enqueue an element
 *
 * @queue: the queue
 * @x: value to be stored
 *
 * Return 0 if success, -1 otherwise.
 *
 * Note that NULL queue or NULL x are invalid.
 */
extern int enqueue(queue_t *queue, const void *x);

/**
 * dequeue - Dequeue an element
 *
 * @queue: the queue
 *
 * Return an element and remove it from queue.
 * If the queue is already empty, return NULL.
 */
extern void *dequeue(queue_t *queue);

/**
 * queue_peek_head - Peek value of head node
 *
 * @queue: the queue
 *
 * Return value of head node and queue remain 
 * unchanged. Return NULL if the queue is empty.
 */
extern void *queue_peek(queue_t *queue);

/**
 * queue_isempty - Check queue is empty or not
 *
 * @queue: the queue
 *
 * Return 1 if the queue is empty, 0 otherwise.
 */
extern int queue_isempty(queue_t *queue);

/**
 * queue_size - Get size of queue
 *
 * @queue: the queue
 *
 * Return size of the queue, and return 0 if
 * queue is already empty.
 */
extern size_t queue_size(queue_t *queue);

#endif /* BULLET_QUEUE_H */
