#ifndef BULLET_BSTREE_H
#define BULLET_BSTREE_H

#include "btree.h"

/**
 * Redefine BTElemType in btnode.h into BSTElemType.
 * Redefine BTNode in btnode.h into BSTNode.
 *
 * In btree.h, user defines ElemType
 *      typedef int BTElemType;
 *
 *      typedef struct BTNode {
 *          BTElemType b;
 *          struct BTNode *left, *right;
 *      }BTNode, *pBTNode;
 *
 * You should use BSTElemType, BSTNode, pBSTNode
 * when include this file.
 */
typedef BTElemType BSTElemType;
typedef BTNode BSTNode, *pBSTNode;

/**
 * bts_creat - Create and initialize a BST.
 *
 * Return a pointer of pBSTNode if successes, null otherwise.
 */
extern pBSTNode bst_create (void);

/**
 * bst_isempty - check bstree empty or not
 *
 * Return true if tree is empty, false otherwise.
 */
extern bool bst_empty (pBSTNode root);

/**
 * bst_depth - find the depth of bstree
 *
 * Return depth of the bstree.
 * Return 0 if null.
 */
extern size_t bst_depth (pBSTNode root);

/**
 * bst_destroy - destroy a bstree
 */
extern void bst_destroy (pBSTNode *root);

/**
 * bst_key_search - search BST to find a key
 *
 * @root:   struct pointer
 * @key:    a key value to be searched
 *
 * Return true if key was find, or return false.
 */
extern bool bst_key_search (pBSTNode root, BSTElemType key);

/**
 * bst_key_insert - insert a key into BST
 *
 * @root:   struct pointer
 * @key:    a key value to be inserted
 */
extern void bst_key_insert (pBSTNode *root, BSTElemType key);

/**
 * bst_key_delet - delete a node whose value equals key.
 */
extern void bst_key_delete (pBSTNode *root, BSTElemType key);


//TODO: the following was to be continued
/**
 * Return an array of preorder traversl of BST.
 */
extern void bst_preorder (pBSTNode root);

/**
 * Return an array of inorder traversl of BST.
 */
extern void bst_inorder (pBSTNode root);

/**
 * Return an array of postorder traversl of BST.
 */
extern void bst_postorder (pBSTNode root);

#endif /* BULLET_BSTREE_H */