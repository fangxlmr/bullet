#ifndef LIB_BTREE_H
#define LIB_BTREE_H

#include <stdbool.h>
#include <stdlib.h>
/* User defined BTNodeType */
typedef int BTNodeType;

/* BTNode structure */
typedef struct BTNode {
    BTNodeType b;
    struct BTNode *left, *right;
}BTNode, *pBTNode;


/* Create and initialize a BT.
 * Return true if success,
 * Or return false.
 * */
extern pBTNode bt_new (void);

/* If tree is empty, return true.
 * Or return false.
 * */
extern bool bt_isempty (pBTNode root);

/* Return depth of the tree.
* Return 0, if NULL.
* */
extern size_t bt_depth (pBTNode root);

/* Destroy a BT.*/
extern void bt_destroy (pBTNode *root);

/* Return an array of preorder traversl of BT. */
BTNodeType *bt_preorder (pBTNode root);

/* Return an array of inorder traversl of BT. */
BTNodeType *bt_inorder (pBTNode root);

/* Return an array of postorder traversl of BT. */
BTNodeType *bt_postorder (pBTNode root);

#endif /* LIB_BTREE_H */
