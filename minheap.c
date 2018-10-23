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
#include <assert.h>
#include "heap.h"

struct _heap {
    void **array;    /* heap array  */
    size_t free;     /* free space  */
    size_t used;     /* used space  */
    comparator cmp;  /* comparing function  */
    int h_flag;      /* heap flag, 0 denotes minheap  */
                     /* 1 denotes maxheap  */
};

static void swap(void *v[], const int x, const int y)
{
    void *temp;

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
static void shiftdown(heap_t *heap, int idx)
{
    int h_flag;
    int t;
    size_t n;
    size_t ileft, iright;
    void **h;
    comparator cmp;

    /* flag to denote type of heap, 0 denotes
     * minheap while 1 denotes maxheap.  */
    h_flag = heap->h_flag;

    n = heap->used;         /* used space in heap  */
    h = heap->array;        /* heap array  */
    ileft  = 2 * idx + 1;   /* index of left child  */
    iright = 2 * idx + 2;   /* index of right child  */
    cmp = heap->cmp;

    /* left child exists at least  */
    while (ileft < n) {

        /* find a smaller value if using minheap,
         * a larger value if using maxheap.  */
        if ((h_flag == 0 && cmp(h[idx], h[ileft]) > 0) ||
            (h_flag == 1 && cmp(h[idx], h[ileft]) < 0)) {

            t = ileft;

        } else {
            t = idx;
        }

        if (iright < n) {   /* right child exists  */

            /* find a smaller (larger) one comparing with
             * right child of current node in minheap (maxheap).  */
            if ((h_flag == 0 && cmp(h[t], h[iright]) > 0) || 
                (h_flag == 1 && cmp(h[t], h[iright]) < 0)) {
                t = iright;
            }
        }
        

        /* re-heapify  */
        if (t != idx) {
            swap(h, t, idx);

            /* keep shifting  */
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
static void shiftup(heap_t *heap, int idx)
{
    int h_flag;
    int n;
    void **h;
    int parent;
    comparator cmp;

    h_flag = heap->h_flag;
    n = heap->used;    /* used space  */
    h = heap->array;   /* heap array  */
    parent = (int) floor((idx - 1) / 2.0);  /* index of parent  */
    cmp = heap->cmp;

    /* index of current node have to be inside heap array.  */
    if (idx >= n) {
        return;

    } else {
        /* parent node shall exists.  */
        while (parent >= 0) {
            /* re-heapify  */
            if ((h_flag == 0 && cmp(h[idx], h[parent]) < 0) ||
                (h_flag == 1 && cmp(h[idx], h[parent]) > 0)) {
                swap(h, idx, parent);

                /* keep shifting  */
                idx = parent;
                parent = (int) floor((idx - 1) / 2.0);

            } else {
                break;
            }
        }
    }

}

heap_t *heap_new(const int h_flag, 
                 const size_t n, const comparator cmp)
{
    void **array;
    heap_t *heap;

    heap = (heap_t *) malloc(sizeof(heap_t));
    if (!heap) {
        return NULL;
    } else {
        heap->cmp  = (cmp != NULL) ? cmp : cmp_int;
        heap->free = n;
        heap->used = 0;
        heap->h_flag = h_flag;
    }

    array = (void **) malloc(n * sizeof(void *));
    if (!array) {
        free(heap);
        return NULL;
    } else {
        heap->array = array;
        return heap;
    }
}

void heap_free(heap_t *heap)
{
    assert(heap);

    free(heap->array);
    free(heap);
}

int heap_add(heap_t *heap, const void *x)
{
    int h_flag;
    comparator cmp;

    assert(heap);
    assert(x);

    h_flag = heap->h_flag;
    cmp = heap->cmp;

    if (heap_isfull(heap)) {
            return -1; /* failed  */
    } else {
        heap->array[heap->used] = (void *) x;
        heap->used++;
        heap->free--;
        shiftup(heap, heap->used - 1);

        return 0;   /* success  */
    }
}

void *heap_poll(heap_t *heap)
{
    void **h;
    void *x;

    assert(heap);
    assert(x);

    h = heap->array;
    if (heap_isempty(heap)) {
        return NULL;

    } else {
        x = h[0];
        swap(h, 0, heap->used - 1);
        heap->used--;
        heap->free++;
        shiftdown(heap, 0);
        return x;
    }
}

void *heap_peek(heap_t *heap)
{
    void **h;

    assert(heap);
    assert(x);

    h = heap->array;
    if (heap_isempty(heap)) {
        return NULL;

    } else {
        return h[0];
    }
}

int heap_size(heap_t *heap)
{
    assert(heap);

    return heap->free + heap->used;
}

int heap_isempty(heap_t *heap)
{
    assert(heap);
    return heap->used == 0;
}

int heap_isfull(heap_t *heap)
{
    assert(heap);
    return heap->free == 0;
}
