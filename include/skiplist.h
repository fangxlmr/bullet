/* 
 * skiplist.h
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

#ifndef BULLET_SKIPLIST_H
#define BULLET_SKIPLIST_H

#include "comparator.h"

/**
 * Define a new data type: skiplist_t
 */
typedef struct _skiplist *skiplist_t;

/**
 * Define a new skiplistElem type
 */
typedef void *skiplistElem;

/**
 * skiplist_new - Create a new skiplist
 *
 * @skiplist[out]: the skiplist
 * @cmp[in]: comparator
 *
 * Return 0 if create a new skiplist successfully,
 * -1 if failed to alloc memory.
 */
extern int skiplist_new(skiplist_t *skiplist, comparator cmp);

/**
 * skiplist_free - Destroy a skiplist
 *
 * @skiplist[in]: the skiplist
 */
extern void skiplist_free(skiplist_t *skiplist);

/**
 * skiplist_add - Add an element to a skiplist
 *
 * @skiplist[in]: the skiplist
 * @x[in]: input value
 *
 * Return 0 if success, -1 if failed to alloc memory.
 */
extern int skiplist_add(skiplist_t skiplist, skiplistElem x);

/**
 * skiplist_remove - Remove an element from the skiplist
 *
 * @skiplist[in]: the skiplist
 * @x[in]: input value
 *
 * Return 0 if success, -1 if given element is not in the skiplist.
 * Duplicate element will be added too.
 */
extern int skiplist_remove(skiplist_t skiplist, skiplistElem x);

/**
 * skiplist_contains - Check if skipllist contians given element
 *
 * @skiplist[in]: the skiplist
 * @x[in]: input value
 *
 * Return 0 if success, -1 if given element is not in the skiplist.
 */
extern int skiplist_contains(skiplist_t skiplist, skiplistElem x);

#endif /*  BULLET_SKIPLIST_H */
