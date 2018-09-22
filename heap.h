/* 
 * heap.h
 */

#ifndef BULLET_HEAP_H
#define BULLET_HEAP_H

#include <stdlib.h>

/**
 * define a heap_t structure
 */
typedef struct _heap heap_t;

/**
 * heap_cf - Comparing function (call back function)
 *
 * x1 and x2 are two elements to be compared.
 * 
 * Return values must be as follows:
 * *x1 < *x2, return -1.
 * *x1 = *x2, return  0.
 * *x1 > *x2, return  1.
 */
typedef int (*heap_cf)(const void *x1, const void *x2);

/**
 * heap_new - Create a new heap
 *
 * @h_flag: a flag to denote minheap (0) or maxheap (1).
 *          Only 0 and 1 are allowed for now.
 * @n: size of heap
 * @cmp: comparing function
 * 
 * Return heap_t pointer if success,
 * NULL pointer otherwise.
 */
extern heap_t *heap_new(const int h_flag, 
                        const size_t n, const heap_cf cmp);

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
 * Note that NULL heap and NULL x are invalid.
 */
extern int heap_add(heap_t *heap, const void *x);

/**
 * heap_poll - Poll the root node of heap
 *
 * @heap: the heap
 *
 * Return root value if it exists, NULL otherwise.
 *
 * Note that root will be removed after this operation,
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
 * Note that heap will remain unchanged unlike heap_poll().
 */
extern void *heap_peek(heap_t *heap);

/**
 * heap_size - Count elements in heap
 *
 * @heap: the heap
 * 
 * Return size of the heap. If heap is empty,
 * return 0.
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

#endif /* BULLET_HEAP_H */
