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
#define RESIZE_FACTOR 2

struct _vector {
    void **array;
    size_t capacity;  /* capacity of the array  */
    size_t len;      /* used space of the array  */
};

vector_t *vector_new(const size_t n)
{
    void **new_array;
    vector_t *vector;

    vector = (vector_t *) malloc(sizeof(*vector));
    if (vector == NULL) {
        return NULL;
    } else {
        vector->capacity = n;
        vector->len = 0;
    }

    new_array  = (void **) malloc(n * sizeof(void *));
    if (new_array == NULL) {
        free(vector);
        return NULL;
    } else {
        vector->array = new_array;
        return vector;
    }
}

void vector_free(vector_t *vector)
{
    free(vector->array);
    free(vector);
}

size_t vector_len(vector_t *vector)
{
    return vector->len;
}

void *vector_get(vector_t *vector, const size_t idx)
{
    if (idx >= vector->len) {
        //TODO error handling
        return NULL;
    } else {
        return (vector->array)[idx];
    }
}

/**
 * vector_resize - Resize vector
 *
 * Resize factor is pre-defined at the beginning
 * of this file with default value 2.
 *
 * Return 0 if resize success, -1 if failed.
 * If resize failed, variable "vector" still
 * hold the pointer of old vector.
 */
static int vector_resize(vector_t *vector)
{
    size_t old_capacity;
    size_t new_capacity;
    void **old_array;
    void **new_array;

    old_array = vector->array;
    old_capacity = vector->capacity;

    new_capacity = RESIZE_FACTOR * old_capacity;
    new_array = (void **) malloc(new_capacity * sizeof(void *));

    if (new_array == NULL) {  /* resize failed.  */
        return -1;

    } else {        /* resize success  */
        memcpy(new_array, old_array, old_capacity * sizeof(void *));
        memset(new_array + old_capacity, 0,(new_capacity - old_capacity) * sizeof(void *));

        vector->capacity = new_capacity;
        vector->array = new_array;
        free(old_array);

        return 0;
    }
}

int vector_set(vector_t *vector, const size_t idx, void *x)
{
    void **array;
    size_t len;

    array = vector->array;
    len = vector->len;

    if (idx < vector->len) {
        array[idx] = x;
        return 0;
    } else {
        //TODO error handling.
        return -1;
    }
}

int vector_append(vector_t *vector, void *x)
{
    if (vector->len < vector->capacity) {
        vector->array[vector->len] = x;
        vector->len++;
        return 0;
    } else {
        if (vector_resize(vector) == -1) {
            return -1;
        } else {
            vector->array[vector->len] = x;
            vector->len++;
            return 0;
        }
    }
}

void *vector_pop(vector_t *vector)
{
    if (vector->len == 0) {
        return -1;
    } else {
        return vector->arry[--vector->len];
    }
}
