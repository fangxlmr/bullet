/**
 * avl-tree
 */

#ifndef BULLET_AVLTREE_H
#define BULLET_AVLTREE_H

typedef struct _avltree avltree_t;

/**
 * avltree_cf - avltree comparing function (call back function)
 *
 * If *x1 < *x2, return -1.
 * If *x1 = *x2, return  0.
 * If *x1 > *x2, retutn  1.
 */
typedef int (*avltree_cf)(void *x1, void *x2);

/**
 * avltree_new - Create a new avl-tree
 *
 * @cmp: comparing function
 *
 * Return 0 if success, -1 otherwise.
 */
extern avltree_t *avl_new(avltree_cf cmp);

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
extern int avltree_add(avltree_t *avl, void *x);

/**
 * avltree_remove - Remove an element from avl-tree
 *
 * @avltree: the avl-tree
 * @x: the value
 *
 * Return 0 if the match node is removed successfully,
 * -1 if no match node exists
 */
extern int avltree_remove(avltree_t *avl, void *x);

/**
 * valtree_contains - Check avl-tree contains given element or not
 
 * @avltree: the avl-tree
 * @x: the value
 *
 * Return 1 if the value is in avltree, 0 otherwise.
 */
extern int avltree_contains(avltree_t *avl, void *x);

/**
 * avltree_depth - Find depth of avl-tree
 *
 * @avltree: the avltree
 *
 * Return depth of the avl-tree, 0 if avltree is empty.
 */
extern int avltree_depth(avltree_t *avl);

/**
 * avltree_isempty - Check avl-tree is empty or not
 *
 * @avltree: the avl-tree
 *
 * Return 1 if avl-tree is empty, 0 otherwise.
 */
extern int avltree_isempty(avltree_t *avl);

/**
 * avltree_min - Find min value in avl-tree
 *
 * @avltree: the avlt-ree
 *
 * Return min value in avl-tree, NULL if avl-tree is empty.
 */
extern void *avltree_min(avltree_t *avl);

/**
 * avltree_max - Find max value in avl-tree
 *
 * @avltree: the avl-tree
 *
 * Return max value in avl-tree, NULL if avl-tree is empty.
 */
extern void *avltree_max(avltree_t *avl);
#endif /* BULLET_AVLTREE_H */
