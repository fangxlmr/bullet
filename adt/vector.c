/* 
 * vector.c
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

#include <string.h>
#include "vector.h"
#define RESIZE_FACTOR 1.5
static const size_t DEFAULT_SIZE = 10;

struct _vector {
    vectorElem *array;
    size_t free;    /* Free space. */
    size_t used;    /* used space. */
};

static int vector_isfull(vector_t vector)
{
    return vector->free == 0;
}

/**
 * vector_resize - Resize vector
 *
 * Resize according to RESIZE_FACOTR.
 *
 * Return 0 if resize success, -1 if failed to alloc memory.
 */
static int vector_resize(vector_t vector)
{
    size_t old_cap;
    size_t new_cap;
    vectorElem *old_array;
    vectorElem *new_array;

    old_cap = vector->used;
    old_array = vector->array;

    new_cap = RESIZE_FACTOR * old_cap;
    new_array = (vectorElem *) malloc(new_cap * sizeof(vectorElem));

    if (new_array == NULL) {  /* No enough memory. */
        return -1;

    } else {        /* Resize successfuuly.  */
        memcpy(new_array, old_array, old_cap * sizeof(vectorElem));
        memset(new_array + old_cap, 0,(new_cap - old_cap) * sizeof(vectorElem));

        vector->array = new_array;
        vector->used = old_cap;
        vector->free = new_cap - old_cap;
        free(old_array);

        return 0;
    }
}

int vector_new(vector_t *vector)
{
    vector_t new_vector;
    vectorElem *new_array;

    new_vector = (vector_t) malloc(sizeof(*new_vector));
    if (new_vector == NULL) {
        return -1;
    } else {
        new_array  = (vectorElem *) malloc(DEFAULT_SIZE * sizeof(vectorElem));
        if (new_array == NULL) {
            free(vector);
            return -1;
        } else {
            new_vector->array = new_array;
            new_vector->free = DEFAULT_SIZE;
            new_vector->used = 0;
            *vector = new_vector;
            return 0;
        }
    }
}

void vector_free(vector_t *vector)
{
    free((*vector)->array);
    free(*vector);
    *vector = NULL;
}

size_t vector_get_size(vector_t vector)
{
    return vector->used;
}

int vector_get(vector_t vector, const size_t idx, vectorElem *x)
{
    if (idx >= vector->used) {
        return -1;
    } else {
        *x = (vector->array)[idx];
        return 0;
    }
}

int vector_set(vector_t vector, const size_t idx, vectorElem x)
{
    if (idx >= vector->used) {
        return -1;
    } else {
        vector->array[idx] = x;
        return 0;
    }
}

int vector_append(vector_t vector, vectorElem x)
{
    if (vector_isfull(vector) == 0) {
        vector->array[vector->used] = x;
        vector->used++;
        vector->free--;
        return 0;
    } else {
        if (vector_resize(vector) == -1) {
            return -1;
        } else {
            vector->array[vector->used] = x;
            vector->used++;
            vector->free++;
            return 0;
        }
    }
}

int vector_pop(vector_t vector, vectorElem *x)
{
    if (vector_isempty(vector)) {
        return -1;
    } else {
        *x = vector->array[vector->used];
        vector->used--;
        vector->used++;
        return 0;
    }
}

int vector_isempty(vector_t vector)
{
    return vector->used == 0;
}
