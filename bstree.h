/**
 * bstree - binary search tree
 */

#ifndef BULLET_BSTREE_H
#define BULLET_BSTREE_H

/**
 * define a bstree_t
 */
typedef struct _bstree bstree_t;

/**
 * bstree_cf - bstree comparing function (call back function)
 *
 * If *x1 < *x2, return -1.
 * If *x1 = *x2, return  0.
 * If *x1 > *x2, retutn  1.
 */
typedef int (*bstree_cf)(void *x1, void *x2);

/**
 * bstree_new - Create a new bstree
 *
 * @cmp: comparing function
 *
 * Return 0 if success, -1 otherwise.
 */
extern bstree_t *bstree_new(bstree_cf cmp);

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
extern int bstree_add(bstree_t *bstree, void *x);

/**
 * bstree_remove - Remove an element from bstree
 *
 * @bstree: the bstree
 * @x: the value
 *
 * Return 0 if the match node is removed successfully,
 * -1 if no match node exists
 */
extern int bstree_remove(bstree_t *bstree, void *x);

/**
 * bstree_contains - Check bstree contains given element or not
 *
 * @bstree: the bstree
 * @x: the value
 *
 * Return 1 if the value is in bstree, 0 otherwise.
 */
extern int bstree_contains(bstree_t *bstree, void *x);

/**
 * bstree_depth - Find depth of bstree
 *
 * @bstree: the bstree
 *
 * Return depth of the bstree, 0 if bstree is empty.
 */
extern int bstree_depth(bstree_t *bstree);

/**
 * bstree_isempty - Check bstree is empty or not
 *
 * @bstree: the bstree
 *
 * Return 1 if bstree is empty, 0 otherwise.
 */
extern int bstree_isempty(bstree_t *bstree);

/**
 * bstree_min - Find min value in bstree
 *
 * @bstree: the bstree
 *
 * Return min value in bstree, NULL if bstree is empty.
 */
extern void *bstree_min(bstree_t *bstree);

/**
 * bstree_max - Find max value in bstree
 *
 * @bstree: the bstree
 *
 * Return max value in bstree, NULL if bstree is empty.
 */
extern void *bstree_max(bstree_t *bstree);

#endif /* BULLET_BSTREE_H */
