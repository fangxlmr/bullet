/* 
 * heap.h
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

#ifndef BULLET_MINHEAP_H
#define BULLET_MINHEAP_H

#include <stdlib.h>
#include "comparator.h"
/**
 * Define a new data type: heap_t
 */
typedef struct _heap heap_t;

/**
 * heap_new - Create a new heap
 *
 * @h_flag: a flag to denote minheap (0) or maxheap (1).
 * @n: size of heap
 * @cmp: a comparator
 * 
 * Return heap_t pointer if success,
 * NULL pointer otherwise.
 *
 * If cmp set to be NULL, then default
 * integer comparator will be used.
 */
extern heap_t *heap_new(const int h_flag, 
                        const size_t n, const comparator cmp);

/**
 * heap_free - Destroy a heap
 *
 * @heap: the heap
 */
extern void heap_free(heap_t *heap);

/**
 * heap_add - Add an element to heap
 *
 * @heap: the heap
 * @x: valure to be stored
 *
 * Return 0 if heap is not full, -1 otherwise.
 *
 * NULL heap and NULL x are invalid.
 */
extern int heap_add(heap_t *heap, const void *x);

/**
 * heap_poll - Poll the root node of heap
 *
 * @heap: the heap
 *
 * Return root value if it exists, NULL otherwise.
 *
 * Root will be removed after this operation,
 * and a new root will shiftup.
 */
extern void *heap_poll(heap_t *heap);

/**
 * heap_peek - Peek root value of the heap
 *
 * @heap: the heap
 *
 * Return root value if it exists, NULL otherwise.
 *
 * The heap will remain unchanged unlike heap_poll().
 */
extern void *heap_peek(heap_t *heap);

/**
 * heap_size - Count elements in heap
 *
 * @heap: the heap
 * 
 * Return size of the heap.
 */
extern int heap_size(heap_t *heap);

/**
 * heap_isempty - Check the heap is empty or not
 *
 * @heap: the heap
 *
 * Return 1 if heap is empty, 0 otherwise.
 */
extern int heap_isempty(heap_t *heap);

/**
 * heap_isfull - Check the heap is full or not
 *
 * @heap: the heap
 * 
 * Return 1 if heap is full, 0 otherwise.
 */
extern int heap_isfull(heap_t *heap);

#endif /* BULLET_MINHEAP_H */
