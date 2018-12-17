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
typedef struct _vector *vector_t;

/**
 * Define vectorEntry type
 */
typedef void *vectorEntry;

/**
 * vector_new - Create a new vector
 *
 * @vector[out]: the vector
 *
 * Return 0 if success and set vector to the new pointer,
 * -1 if fail to alloc memory.
 */
extern int vector_new(vector_t *vector);

/**
 * vector_free - Destroy a vector
 *
 * @vector[in]: the vector
 */
extern void vector_free(vector_t *vector);

/**
 * vector_get_size - Get the size of current vector
 *
 * @vector[in]: the vector
 *
 * Return 0 if vector is empty, otherwise return actual size of the vecor.
 */
extern size_t vector_get_size(vector_t vector);

/**
 * vector_get - Get value from vector
 *
 * @vector[in]: the vector
 * @idx[in]: the index
 * @e[out]: output entry value
 *
 * Get value from vector by a given index.
 * Return -1 if idx exceeds the size of the vector, otherwise return 0.
 */
extern int vector_get_entry(vector_t vector, const size_t idx, vectorEntry *e);

/**
 * vector_set_entry - Set entry value in a vector
 *
 * @vector[in]: the vector
 * @idx[in]: the index
 * @e[in]: input value
 *
 * Return 0 if success, -1 if index exceeds the size of the vector.
 */
extern int vector_set_entry(vector_t vector, const size_t idx, vectorEntry e);

/**
 * vector_append_entry - Append an entry to a vector
 *
 * @vector[in]: the vector
 * @e[in]: input value
 *
 * Return 0 if success, -1 if failed to alloc memory.
 */
extern int vector_append_entry(vector_t vector, vectorEntry e);

/**
  * vector_pop_entry - Pop the value at the end of vector
  *
  * @vector[in]: the vector
  * @e[out]: output value
  *
  * Return -1 if the vector is already empty, otherwise pop out
  * the end entry of the vector.
  */
extern int vector_pop_entry(vector_t vector, vectorEntry *e);


/**
 * vector_isempty - Check if vector is empty
 *
 * @vector[in]: the vector
 *
 * Return non-zero if vector is empty, 0 if not.
 */
extern int vector_isempty(vector_t vector);

#endif /* BULLET_VECTOR_H */
