/**
 * vector.h
 *
 */

#ifndef BULLET_VECTOR_H
#define BULLET_VECTOR_H

#include <stdlib.h>

/**
 * define a dynamic array structure - vector
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
 * by vector_init();
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
 * vector_size - Get used space of vector
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
extern void *vector_get(vector_t *vector, const int idx);

/**
 * vector_set - Set value in vector
 *
 * @vector: the vector
 * @idx: the index
 * @x: set value
 *
 * Return 0 if success, -1 otherwise.
 *
 * Note:
 * 1) Pointer of the vestor may vary after resize,
 *    but variable "vector" still hold it.
 * 2) If idx is too big for vector, making blanks
 *    in the vector. These blanks will be init to 0.
 */
extern int vector_set(vector_t *vector, int idx, void *x);

#endif /* BULLET_VECTOR_H */
