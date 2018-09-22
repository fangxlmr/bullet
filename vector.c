/* Implementation of vector  */

#include <string.h>
#include <assert.h>
#include "vector.h"
#define RESIZE_FACTOR 2

struct _vector {
    void **array;
    size_t capacity;  /* capacity of the array  */
    size_t size;      /* used space of the array  */
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
        vector->size = 0;
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

void vector_init(vector_t *vector)
{
    void **array;
    size_t n;

    assert(vector);
    array = vector->array;
    n  = vector->capacity;

    memset(array, 0, n * sizeof(void *));
    vector->size = 0;
}

void vector_free(vector_t *vector)
{
    assert(vector);
    free(vector->array);
    free(vector);
}

size_t vector_size(vector_t *vector)
{
    assert(vector);
    return vector->size;
}

void *vector_get(vector_t *vector, const int idx)
{
    assert(vector);
    assert(idx >=0 && idx < vector->size);
    return (vector->array)[idx];
}

/**
 * vector_resize - Resize vector
 *
 * Resize factor is pre-defined at the beginning
 * of this file. Default value is 2.
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

    assert(vector);
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

int vector_set(vector_t *vector, const int idx, const void *x)
{
    assert(vector);
    assert(idx >= 0 && idx < vector->size);
    assert(x);

    void **array;
    size_t size;

    array = vector->array;
    size = vector->size;

    if ((size_t) idx < vector->capacity) {
        array[idx] = (void *) x;

        if ((size_t )idx + 1 > size) {
            memset(array + size, 0, idx + 1 - size);
            vector->size = idx + 1;
        }
        return 0;

    } else {
        /* resize  */
        if (vector_resize(vector)) {
            vector->array[idx] = (void *) x;
            vector->size = (size_t) idx + 1 > vector->size ? \
                           (size_t) idx + 1 : vector->size;
            return 0;

        } else {
            return -1;
        }
    }
}
