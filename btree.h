#ifndef BULLET_BTREE_H
#define BULLET_BTREE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "darray.h"

/**
 * This head file defined the basic node struct, functions
 * used in binary tree.
 * You can redefined the basic node struct according to your
 * own requirements.
 */

/**
 * User defined int as BTElemType.
 * You can redefined it.
 */
typedef int BTElemType;

/**
 * BTNode structure
 *
 * @b:      key value in struct BTNode
 * @*left:  next left  pointer
 * @*right: next right pointer
 */
typedef struct BTNode {
    BTElemType b;
    struct BTNode *left, *right;
}BTNode, *pBTNode;


/**
 * bt_creat - create and initialize a BT.
 *
 * Return a pBTNode if success, or return false.
 */
extern pBTNode bt_create (void);

/**
 * bt_isempty - check btree is empty or not
 *
 * If tree is empty, return true.
 * Or return false.
 */
extern bool bt_empty (pBTNode root);

/**
 * bst_depth - find the depth of btree
 *
 * Return depth of the btree.
 * Return 0 if null.
 */
extern size_t bt_depth (pBTNode root);

/**
 * bt_destroy - destroy a btree.
 */
extern void bt_destroy (pBTNode *root);

/**
 * bt_preoder - preorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_preorder (pBTNode root);

/**
 * bt_inoder - inorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_inorder (pBTNode root);

/**
 * bt_postoder - postorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_postorder (pBTNode root);

#endif /* BULLET_BTREE_H */
