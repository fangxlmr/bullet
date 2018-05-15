#ifndef LIB_BSTREE_H
#define LIB_BSTREE_H

#include "btree.h"
//     In btree.h
//
//    /* User defined BTNodeType */
//    typedef int BTNodeType;
//
//    /* BTNode structure */
//    typedef struct BTNode {
//        BTNodeType b;
//        struct BTNode *left, *right;
//    }BTNode, *pBTNode;
//


/* Redefine BTNodeType in btree.h into BSTNodeType. */
typedef BTNodeType BSTNodeType;

/* Redefine BTNode in btree.h into BSTNode. */
typedef BTNode BSTNode, *pBSTNode;

/* Create and initialize a BST.
 * Return true if success,
 * Or return false.
 * */
extern pBSTNode bst_new (void);

/* If tree is empty, return true.
 * Or return false.
 * */
extern bool bst_isempty (pBSTNode root);

/* Return depth of the bstree.
* Return 0, if NULL.
* */
extern size_t bst_depth (pBSTNode root);

/* Destroy a BST.*/
extern void bst_destroy (pBSTNode *root);

/* Search BST to find a key
 * Return true if key was find,
 * or return false.
 * */
extern bool bst_key_search (pBSTNode root, BSTNodeType key);

/* Insert a key into BST
 * If there is a node with value key, then ignore it, and return true.
 * If there is no such node with key,
 * insert key, and return true.
 * Or return false.
 * */
extern bool bst_key_insert (pBSTNode *root, BSTNodeType key);

/* Delete a node with key.
 * If no node with key, ignore it and return true.
 * If exits a node with key, delete the node,
 * and return true.
 * Or return false;
 * */
extern bool bst_key_delete (pBSTNode *root, BSTNodeType key);

/* Return an array of preorder traversl of BST. */
extern BSTNodeType *bst_preorder (pBSTNode root);

/* Return an array of inorder traversl of BST. */
extern BSTNodeType *bst_inorder (pBSTNode root);

/* Return an array of postorder traversl of BST. */
extern BSTNodeType *bst_postorder (pBSTNode root);

#endif /* LIB_BSTREE_H */
