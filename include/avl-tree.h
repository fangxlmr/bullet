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
typedef struct _avltree avltree_t;

/**
 * avltree_new - Create a new avl-tree
 *
 * @cmp: comparing function
 *
 * Return 0 if success, -1 otherwise.
 *
 * If cmp set to be NULL, then default
 * integer comparator will be used.
 */
extern avltree_t *avl_new(const comparator cmp);

/**
 * avltree_free - Destroy an avl-tree
 *
 * @avltree: the avl-tree
 */
extern void avltree_free(avltree_t *avl);

/**
 * bstee_add - Add an element to the avl-tree
 *
 * @avltree: the avl-tree
 * @x: the value
 *
 * Return 0 if success, -1 otherwise.
 * Return 0 if duplicated.
 */
extern int avltree_add(avltree_t *avl, const void *x);

/**
 * avltree_remove - Remove an element from avl-tree
 *
 * @avltree: the avl-tree
 * @x: the value
 *
 * Return 0 if the match node is removed successfully,
 * -1 if no match node exists
 */
extern int avltree_remove(avltree_t *avl, const void *x);

/**
 * valtree_contains - Check avl-tree contains given element or not
 
 * @avltree: the avl-tree
 * @x: the value
 *
 * Return 1 if the value is in avltree, 0 otherwise.
 */
extern int avltree_contains(avltree_t *avl, const void *x);

/**
 * avltree_get_hight - Find hight of avl-tree
 *
 * @avltree: the avltree
 *
 * Return hight of the avl-tree, 0 if avltree is empty.
 */
extern int avltree_get_hight(avltree_t *avl);

/**
 * avltree_isempty - Check avl-tree is empty or not
 *
 * @avltree: the avl-tree
 *
 * Return 1 if avl-tree is empty, 0 otherwise.
 */
extern int avltree_isempty(avltree_t *avl);

/**
 * avltree_get_min - Find min value in avl-tree
 *
 * @avltree: the avlt-ree
 *
 * Return min value in avl-tree, NULL if avl-tree is empty.
 */
extern void *avltree_get_min(avltree_t *avl);

/**
 * avltree_get_max - Find max value in avl-tree
 *
 * @avltree: the avl-tree
 *
 * Return max value in avl-tree, NULL if avl-tree is empty.
 */
extern void *avltree_get_max(avltree_t *avl);
#endif /* BULLET_AVLTREE_H */
