/* 
 * heap.c
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

#include <math.h>
#include "binary-minheap.h"

struct _binary_minheap {
    binaryMinHeapElem *array;    /* heap array  */
    size_t free;     /* free space  */
    size_t used;     /* used space  */
    comparator cmp;  /* comparing function  */
};

static void swap(binaryMinHeapElem v[], const int x, const int y)
{
    binaryMinHeapElem temp;

    temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

/**
 * shiftdown - Shift down element in the heap
 *
 * @heap: the heap
 * @idx: element index
 */
static void shiftdown(binary_minheap_t heap, int idx)
{
    int t;
    size_t n;
    size_t ileft, iright;
    binaryMinHeapElem *array;
    comparator cmp;

    n = heap->used;         /* used space in heap  */
    array = heap->array;        /* heap array  */
    ileft  = 2 * idx + 1;   /* index of left child  */
    iright = 2 * idx + 2;   /* index of right child  */
    cmp = heap->cmp;

    /* left child exists at least  */
    while (ileft < n) {

        /* Find a smaller value if using minheap */
        if (cmp(array[idx], array[ileft]) > 0) {
            t = ileft;
        } else {
            t = idx;
        }

        if (iright < n) {   /* right child exists  */

            /* Find a smaller one comparing with
             * right child of current node in minheap.  */
            if (cmp(array[t], array[iright]) > 0) {
                t = iright;
            }
        }
        

        /* Re-heapify  */
        if (t != idx) {
            swap(array, t, idx);

            /* Keep shifting  */
            idx = t;
            ileft  = 2 * idx + 1;
            iright = 2 * idx + 2;
        } else {
            break;
        }
    }
}

/**
 * shiftup - Shift up element in the heap
 *
 * @heap: the heap
 * @idx: element index
 */
static void shiftup(binary_minheap_t heap, int idx)
{
    int n;
    binaryMinHeapElem *array;
    int parent;
    comparator cmp;

    n = heap->used;    /* used space  */
    array = heap->array;   /* heap array  */
    parent = (int) floor((idx - 1) / 2.0);  /* index of parent  */
    cmp = heap->cmp;

    /* index of current node have to be inside heap array.  */
    if (idx >= n) {
        return;

    } else {
        /* parent node shall exists.  */
        while (parent >= 0) {
            /* re-heapify  */
            if (cmp(array[idx], array[parent]) < 0) {
                swap(array, idx, parent);

                /* keep shifting  */
                idx = parent;
                parent = (int) floor((idx - 1) / 2.0);

            } else {
                break;
            }
        }
    }

}

int binary_minheap_new(binary_minheap_t *heap, const size_t n, const comparator cmp)
{
    binaryMinHeapElem *array;
    binary_minheap_t new_heap;

    new_heap = (binary_minheap_t) malloc(sizeof(*new_heap));
    if (new_heap == NULL) {
        return -1;
    } else {
        new_heap->cmp  = (cmp != NULL) ? cmp : cmp_int;
        new_heap->free = n;
        new_heap->used = 0;
    }

    array = (binaryMinHeapElem *) malloc(n * sizeof(*array));
    if (array == NULL) {
        free(heap);
        return -1;
    } else {
        new_heap->array = array;
        *heap = new_heap;
        return 0;
    }
}

void binary_minheap_free(binary_minheap_t *heap)
{
    free((*heap)->array);
    free(*heap);
    *heap = NULL;
}

int binary_minheap_add(binary_minheap_t heap, const binaryMinHeapElem x)
{
    if (binary_minheap_isfull(heap)) {
            return -1; /* failed */
    } else {
        heap->array[heap->used] = x;
        heap->used++;
        heap->free--;
        shiftup(heap, heap->used - 1);

        return 0;   /* success  */
    }
}

int binary_minheap_poll(binary_minheap_t heap, binaryMinHeapElem *x)
{
    if (binary_minheap_isempty(heap)) {
        return -1;
    } else {
        *x = heap->array[0];
        swap(heap->array, 0, heap->used - 1);
        heap->used--;
        heap->free++;
        shiftdown(heap, 0);
        return 0;
    }
}

int binary_minheap_peek(binary_minheap_t heap, binaryMinHeapElem *x)
{
    if (binary_minheap_isempty(heap)) {
        return -1;

    } else {
        *x = heap->array[0];
        return 0;
    }
}

size_t binary_minheap_get_size(binary_minheap_t heap)
{

    return heap->used;
}

int binary_minheap_isempty(binary_minheap_t heap)
{
    return heap->used == 0;
}

int binary_minheap_isfull(binary_minheap_t heap)
{
    return heap->free == 0;
}
