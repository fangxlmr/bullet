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

#include "comparator.h"

/**
 * Define a new data type: bstee_t
 */
typedef struct _bstree bstree_t;

/**
 * bstree_new - Create a new bstree
 *
 * @cmp: comparing function
 *
 * Return 0 if success, -1 otherwise.
 *
 * If cmp set to be NULL, then default
 * integer comparator will be used.
 */
extern bstree_t *bstree_new(const comparator cmp);

/**
 * bstree_free - Destroy a bstree
 *
 * @bstree: the bstree
 */
extern void bstree_free(bstree_t *bstree);

/**
 * bstee_add - Add an element into bstree
 *
 * @bstree: the bstree
 * @x: the value
 *
 * Return 0 if success, -1 otherwise.
 * Return 0 if duplicated.
 */
extern int bstree_add(bstree_t *bstree, const void *x);

/**
 * bstree_remove - Remove an element from bstree
 *
 * @bstree: the bstree
 * @x: the value
 *
 * Return 0 if the match node is removed successfully,
 * -1 if no match node exists
 */
extern int bstree_remove(bstree_t *bstree, const void *x);

/**
 * bstree_contains - Check bstree contains given element or not
 *
 * @bstree: the bstree
 * @x: the value
 *
 * Return 1 if the value is in bstree, 0 otherwise.
 */
extern int bstree_contains(bstree_t *bstree, const void *x);

/**
 * bstree_get_hight - Get hight of bstree
 *
 * @bstree: the bstree
 *
 * Return depth of the bstree, 0 if bstree is empty.
 */
extern int bstree_get_hight(bstree_t *bstree);

/**
 * bstree_isempty - Check bstree is empty or not
 *
 * @bstree: the bstree
 *
 * Return 1 if bstree is empty, 0 otherwise.
 */
extern int bstree_isempty(bstree_t *bstree);

/**
 * bstree_get_min - Get min value in bstree
 *
 * @bstree: the bstree
 *
 * Return min value in bstree, NULL if bstree is empty.
 */
extern void *bstree_get_min(bstree_t *bstree);

/**
 * bstree_get_max - Get max value in bstree
 *
 * @bstree: the bstree
 *
 * Return max value in bstree, NULL if bstree is empty.
 */
extern void *bstree_get_max(bstree_t *bstree);

#endif /* BULLET_BSTREE_H */
