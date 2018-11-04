/* 
 * dict.h
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

#ifndef BULLET_DICT_H
#define BULLET_DICT_H

#include "comparator.h"

/**
 * Define a new data type: dict_t
 */
typedef struct _dict dict_t;

/**
 * hash_f - Hash function
 *
 * @key: hash key
 */
typedef unsigned int (*hash_f)(const void *key);

/**
 * dict_new - Create a new dict
 *
 * @hash: hash function
 * @cmp: comparing function
 *
 * Return dict_t pointer if success, NULL pointer otherwise.
 *
 * If cmp set to be NULL, then default
 * integer comparator will be used.
 */
extern dict_t *dict_new(const hash_f hash, const comparator cmp);

/**
 * dict_free - Destroy a dict
 *
 * @dict: the dict
 */
extern void dict_free(dict_t *dict);

/**
 * dict_add - Add a new key-value pair
 *
 * @dict: the dict
 * @k: the key
 * @v: the value
 *
 * Return 0 if success, -1 otherwise.
 *
 * If given key can be found in dict, this function
 * will update (overlay) the old value by the new given one.
 */
extern int dict_add(dict_t *dict, const void *k, const void *v);

/**
 * dict_get - Get value by key
 *
 * @dict: the dict
 * @k: the key
 *
 * Return value if key-value pairs exists in dict,
 * NULL otherwise.
 */
extern void *dict_get(dict_t *dict, const void *k);

/**
 * dict_pop - Remove key-value pair by given key
 *
 * @dict: the dict
 * @k: the key
 *
 * Return 0 if key-value pair exists and be removed successfully,
 * -1 if key-value doesn't exists.
 */
extern int dict_pop(dict_t *dict, const void *k);

#endif /* BULLET_DICT_H */
