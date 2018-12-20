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
typedef struct _dict *dict_t;

/**
 * Define a new dictKey type
 */
typedef void *dictKey;

/**
 * Define a new dictValue type
 */
typedef void *dictValue;

/**
 * hash_f - Hash function
 *
 * @key: hash key
 */
typedef unsigned int (*hash_f)(const void *key);

/**
 * dict_new - Create a new dict
 *
 * @dict[out]: the dict
 * @hash[in]: hash function
 * @cmp: comparing function
 *
 * Return 0 if success, -1 if failed to alloc memory.
 *
 * If cmp set to be NULL, then default integer comparator will be used.
 * So do the cmp function.
 */
extern int dict_new(dict_t *dict, const hash_f hash, const comparator cmp);

/**
 * dict_free - Destroy a dict
 *
 * @dict[in]: the dict
 */
extern void dict_free(dict_t *dict);

/**
 * dict_add - Add a new key-value pair
 *
 * @dict[in]: the dict
 * @key[in]: the key
 * @value[in]: the value
 *
 * Return 0 if success, -1 if failed to alloc memory.
 *
 * If given key can be found in dict, this function
 * will update the old value by the new one.
 */
extern int dict_add(dict_t dict, const dictKey key, const dictValue value);

/**
 * dict_remove_key - Remove key-value pair by given key
 *
 * @dict[in]: the dict
 * @key[in]: the key
 *
 * Return 0 if key exists and key-value pair is removed successfully,
 * -1 if key doesn't exists in the dict.
 */
extern int dict_remove(dict_t dict, const dictKey key);

/**
 * dict_contains_key - Check if dict contains key or not
 *
 * @dict[in]: the dict
 * @key[in]: given key
 *
 * Return non-zero if dict contains the given key, -1 if not.
 */
extern int dict_contains_key(dict_t dict, const dictKey key);

/**
 * dict_get_value - Get value by key
 *
 * @dict[in]: the dict
 * @key[in]: the key
 * @value[out]: output value
 *
 * Return 0 if key-value pairs exists in dict,
 * -1 if the key doesn't exists in dict.
 */
extern int dict_get_value(dict_t dict, const dictKey key, dictValue *value);

#endif /* BULLET_DICT_H */
