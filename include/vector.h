/* 
 * vector.h - Dynamic array
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
 */
extern vector_t *vector_new(const size_t n);

/**
 * vector_free - Destroy a vector
 *
 * @vector: the vector
 */
extern void vector_free(vector_t *vector);

/**
 * vector_len - Get the size of current vector
 *
 * @vector: the vector
 *
 * Return used space of vector.
 */
extern size_t vector_len(vector_t *vector);

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
extern int vector_set(vector_t *vector, const size_t idx, void *x);

/**
 * vector_append - Append an element at the end of vector
 *
 * @vector: the vector
 * @x: the value
 *
 * Return 0 if success, -1 if append failed.
 */
extern int vector_append(vector_t *vector, void *x);

/**
  * vector_pop - Pop the value at the end of vector
  *
  * @vector: the vector
  */
extern void *vector_pop(vector_t *vector);

#endif /* BULLET_VECTOR_H */
