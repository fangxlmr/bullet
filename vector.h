/**
 * vector.h
 *
 */

#ifndef BULLET_VECTOR_H
#define BULLET_VECTOR_H

#include <stdlib.h>

/**
 * Define a new data type: vector_t
 */
typedef struct _vector vector_t;

/**
 * vector_new - Create a new vector
 *
 * @n: size of vetor
 *
 * Return vector_t pointer if success, NULL
 * pointer if failed.
 *
 * The vector will not be initialized. If you
 * want to do so, please initialize it 
 * using vector_init().
 */
extern vector_t *vector_new(const size_t n);

/**
 * vector_init - Initialize a vector
 *
 * @vector: the vector
 *
 * All elements in vector will be set to 0.
 * And size of vector will be reset to 0.
 */
extern void vector_init(vector_t *vector);

/**
 * vector_free - Destroy a vector
 *
 * @vector: the vector
 */
extern void vector_free(vector_t *vector);

/**
 * vector_size - Get the size of current vector
 *
 * @vector: the vector
 *
 * Return used space of vector.
 */
extern size_t vector_size(vector_t *vector);

/**
 * vector_get - Get value from vector
 *
 * @vector: the vector
 * @idx: the index
 *
 * Get value from vector by a given index.
 */
extern void *vector_get(vector_t *vector, const size_t idx);

/**
 * vector_set - Set value in vector
 *
 * @vector: the vector
 * @idx: the index
 * @x: set value
 *
 * Return 0 if success, -1 if index exceeds the size of the vector.
 */
extern int vector_set(vector_t *vector, const size_t idx, const void *x);

/*
 * vector_append - Append an element at the end of vector
 *
 * @vector: the vector
 * @x: the value
 *
 * Return 0 if success, -1 if append failed.
 */
extern int vector_append(vector_t *vector, const void *x);
#endif /* BULLET_VECTOR_H */
