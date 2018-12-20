/* 
 * binary-minheap.h
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

#ifndef BULLET_BINARY_MINHEAP_H
#define BULLET_BINARY_MINHEAP_H

#include <stdlib.h>
#include "comparator.h"

/**
 * Define a new data type: binary_minbinary_minheap_t
 */
typedef struct _binary_minheap *binary_minheap_t;

/**
 * Define a new binaryMinHeapElem type
 */
typedef void *binaryMinHeapElem;

/**
 * binary_minheap_new - Create a new binary minheap
 *
 * @heap[out]: the binary minheap
 * @n[in]: size of heap
 * @cmp[in]: a comparator
 * 
 * Return 0 if success, -1 if failed to alloc memory.
 *
 * If cmp set to be NULL, then default
 * integer comparator will be used.
 */
extern int binary_minheap_new(binary_minheap_t *heap, 
        const size_t n, const comparator cmp);

/**
 * binary_minheap_free - Destroy a binary minheap
 *
 * @heap[in]: the binary minheap
 */
extern void binary_minheap_free(binary_minheap_t *heap);

/**
 * binary_minheap_add - Add an element to heap
 *
 * @heap[in]: the binary minheap
 * @x[in]: valure to be stored
 *
 * Return 0 if heap is not full, -1 otherwise.
 */
extern int binary_minheap_add(binary_minheap_t heap, const binaryMinHeapElem x);

/**
 * binary_minheap_poll - Poll the root node of heap
 *
 * @heap[in]: the binary minheap
 * @x[out]: output value
 *
 * Return 0 if root exists, -1 otherwise.
 *
 * Root will be retrived and removed after this operation.
 */
extern int binary_minheap_poll(binary_minheap_t heap, binaryMinHeapElem *x);

/**
 * binary_minheap_peek - Peek root value of the heap
 *
 * @heap[in]: the binary minheap
 * @x[out]: output value
 *
 * Return 0 if root exists, -1 otherwise.
 *
 * Root will be retrived after this operation, different with binary_minheap_poll().
 */
extern int binary_minheap_peek(binary_minheap_t heap, binaryMinHeapElem *x);

/**
 * binary_minheap_get_size - Count elements in heap
 *
 * @heap[in]: the binary minheap
 *
 * Count the elements in heap. Return 0 if heap is empty.
 */
extern size_t binary_minheap_get_size(binary_minheap_t heap);

/**
 * binary_minheap_isempty - Check if the heap is empty or not
 *
 * @heap[in]: the binary minheap
 *
 * Return non-zero if heap is empty, 0 otherwise.
 */
extern int binary_minheap_isempty(binary_minheap_t heap);

/**
 * binary_minheap_isfull - Check if the heap is full or not
 *
 * @heap[in]: the binary minheap
 * 
 * Return non-zero if heap is full, 0 otherwise.
 */
extern int binary_minheap_isfull(binary_minheap_t heap);

#endif /* BULLET_BINARY_MINHEAP_H */
