/* 
 * bstree.h - Binary search tree
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

#ifndef BULLET_BSTREE_H
#define BULLET_BSTREE_H

#include <stddef.h>
#include "comparator.h"

/**
 * Define a new data type: bstee_t
 */
typedef struct _bstree *bstree_t;

/**
 * Define a new bstreeElem type
 */
typedef void *bstreeElem;

/**
 * bstree_new - Create a new bstree
 *
 * @cmp[in]: comparing function
 *
 * Return 0 if success, -1 if failed to alloc memory.
 * If cmp = NULL, then default comparator function would be used.
 */
extern int bstree_new(bstree_t *bstree, const comparator cmp);

/**
 * bstree_free - Destroy a bstree
 *
 * @bstree[in]: the bstree
 */
extern void bstree_free(bstree_t *bstree);

/**
 * bstee_add - Add an element to bstree
 *
 * @bstree[in]: the bstree
 * @x[in]: input value
 *
 * Return 0 if success, -1 if failed to alloc memory.
 * Duplicate value will be ignored, and return 0.
 */
extern int bstree_add(bstree_t bstree, const bstreeElem x);

/**
 * bstree_remove - Remove an element from bstree
 *
 * @bstree[in]: the bstree
 * @x[in]: the value
 *
 * Return 0 if remove node successfully, -1 if not find.
 */
extern int bstree_remove(bstree_t bstree, const bstreeElem x);

/**
 * bstree_contains - Check bstree contains given element or not
 *
 * @bstree[in]: the bstree
 * @x[in]: the value
 *
 * Return 1 if the value is in bstree, 0 otherwise.
 */
extern int bstree_contains(bstree_t bstree, const bstreeElem x);

/**
 * bstree_get_height - Get height of bstree
 *
 * @bstree[in]: the bstree
 *
 * Return height of the bstree, 0 if bstree is empty.
 */
extern size_t bstree_get_height(bstree_t bstree);

/**
 * bstree_isempty - Check if bstree is empty
 *
 * @bstree[in]: the bstree
 *
 * Return non-zero if bstree is empty, 0 otherwise.
 */
extern int bstree_isempty(bstree_t bstree);

/**
 * bstree_get_min - Get min value in bstree
 *
 * @bstree[in]: the bstree
 * @x[out]: output value
 *
 * Return 0 if find minimum element, -1 if not find.
 */
extern int bstree_get_min(bstree_t bstree, bstreeElem *x);

/**
 * bstree_get_max - Get max value in bstree
 *
 * @bstree[in]: the bstree
 * @x[out]: output value
 *
 * Return 0 if find maximum element, -1 if not find.
 */
extern int bstree_get_max(bstree_t bstree, bstreeElem *x);

#endif /* BULLET_BSTREE_H */
