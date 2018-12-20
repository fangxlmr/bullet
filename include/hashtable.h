/*
 * hashtable.h
 *
 * Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
   All rights reserved.
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

#ifndef BULLET_HASHTABLE_H
#define BULLET_HASHTABLE_H

#include "dict.h"

/**
 * Define a new data type: hashtable_t
 */
typedef dict_t hashtable_t;

/**
 * Define a new hashtableElem type
 */
typedef void *hashtableElem;

/**
 * hash_f - Hash function
 *
 * @key: the key
 */
typedef unsigned int (*hash_f)(const void *key);

/**
 * hashtable_new - Create a new hashtable
 *
 * @hashtable[out]: the hashtable
 * @hash[in]: hash function
 * @cmp[in]: comparing function
 *
 * Return 0 if success, -1 if failed to alloc memeory.
 *
 * If cmp set to be NULL, then default
 * integer comparator will be used. So do the cmp function.
 */
extern int hashtable_new(hashtable_t *hashtable, 
        const hash_f hash, const comparator cmp);

/**
 * hashtable_free - Destroy a hashtable
 *
 * @hashtable: the hashtable
 */
extern void hashtable_free(hashtable_t *hashtable);

/**
 * hashtable_add - Add a new element
 *
 * @hashtable[in]: the hashtable
 * @x[in]: input value
 *
 * Return 0 if success, -1 if failed to alloc memory.
 * Duplicate value will be ignored.
 */
extern int hashtable_add(hashtable_t hashtable, const hashtableElem x);

/**
 * hashtable_contaisn - Check if hashtabke contains element or not
 *
 * @hashtable[in]: the hashtable
 * @x[in]: input value
 *
 * Return non-zero if hashtable contains given element, 0 if not.
 */
extern int hashtable_contains(hashtable_t hashtable, const hashtableElem x);

/**
 * hashtable_remove - Remove the given element in hashtable
 *
 * @hashtable[in]: the hashtable
 * @x[in]: input value
 *
 * Return 0 if given element exists and be removed successfully,
 * -1 if given element doesn't exists in hashtable.
 */
extern int hashtable_remove(hashtable_t hashtable, const hashtableElem x);

#endif /* BULLET_HASHTABLE_H */
