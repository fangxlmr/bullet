/* 
 * avltree.h - avl balanced tree
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

#ifndef BULLET_AVLTREE_H
#define BULLET_AVLTREE_H

#include "comparator.h"

/**
 * Define a new data type: avltree_t
 */
typedef struct _avltree *avltree_t;

/**
 * Define a new avltreeElem type
 */
typedef void *avltreeElem;

/**
 * avltree_new - Create a new avl-tree
 *
 * @avl[out]: the avl-tree
 * @cmp[in]: comparing function
 *
 * Return 0 if success, -1 if failed to alloc memory.
 *
 * If cmp set to be NULL, then function will load default
 * comparator of intagers.
 */
extern int avltree_new(avltree_t *avl, const comparator cmp);

/**
 * avltree_free - Destroy an avl-tree
 *
 * @avltree[in]: the avl-tree
 */
extern void avltree_free(avltree_t *avl);

/**
 * bstee_add - Add an element to the avl-tree
 *
 * @avltree[in]: the avl-tree
 * @x[in]: the value
 *
 * Return 0 if success, -1 if failed to alloc memory.
 * Duplicate values are ignored and return 0.
 */
extern int avltree_add(avltree_t avl, const avltreeElem x);

/**
 * avltree_remove - Remove an element from a avl-tree
 *
 * @avltree[in]: the avl-tree
 * @x[out]: the value
 *
 * Return 0 if the match node is removed successfully,
 * -1 if no match node exists.
 */
extern int avltree_remove(avltree_t avl, const avltreeElem x);

/**
 * valtree_contains - Check avl-tree contains given element or not
 *
 * @avltree[in]: the avl-tree
 * @x[in]: the value
 *
 * Return non-zero if the value is in avltree, 0 if not.
 */
extern int avltree_contains(avltree_t avl, const avltreeElem x);

/**
 * avltree_get_height - Find height of avl-tree
 *
 * @avltree[in]: the avltree
 *
 * Return height of the avl-tree, 0 if avltree is empty.
 */
extern int avltree_get_height(avltree_t avl);

/**
 * avltree_isempty - Check if avl-tree is empty or not
 *
 * @avltree[in]: the avl-tree
 *
 * Return non-zero if avl-tree is empty, 0 if not.
 */
extern int avltree_isempty(avltree_t avl);

/**
 * avltree_get_min - Find min value in avl-tree
 *
 * @avltree[in]: the avl-tree
 * @x[out]: output min value
 *
 * Return 0 if find minimum value in avl-tree, -1 if avl-tree is empty.
 */
extern int avltree_get_min(avltree_t avl, avltreeElem *x);

/**
 * avltree_get_max - Find max value in avl-tree
 *
 * @avltree[in]: the avl-tree
 * @x[out]: output max value
 *
 * Return 0 if find maximum value in avl-tree, -1 if avl-tree is empty.
 */
extern int avltree_get_max(avltree_t avl, avltreeElem *x);
#endif /* BULLET_AVLTREE_H */
