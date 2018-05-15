#include "bstree.h"

/* Create and initialize a BST.
 * Return true if success,
 * Or return false.
 * */
pBSTNode bst_new (void) {
    return bt_new();
}


/* If tree is empty, return true.
 * Or return false.
 * */
bool bst_isempty (pBSTNode root) {
    if (!root)
        return true;
    return false;
}


/* Return depth of the tree (recursively).
 * Return 0, if NULL.
 * */
/* TODO it iteratively */
size_t bst_depth (pBSTNode root) {
    return bt_depth(root);
}


/* Destroy a bst.
 * Do it post-order-transversely
 * */
void bst_destroy (pBSTNode *root) {
    bt_destroy(root);
}


/* Search BST to find a key
 * Return true if key was find,
 * or return false.
 * */
bool bst_key_search (pBSTNode root, BSTNodeType key) {
    if (!root) {
        return false;
    }
    if (key == root->b) {
        return true;
    }
    if (key < root->b) {
        return bst_key_search(root->left,  key);
    } else {
        return bst_key_search(root->right, key);
    }
}


/* Insert a key into BST
 * If there is a node with value key, then ignore it, and return true.
 * If there is no such node with key,
 * insert key, and return true.
 * Or return false.
 * */
bool bst_key_insert (pBSTNode *root, BSTNodeType key) {
    if (!*root) {
        pBSTNode p = (pBSTNode) malloc(sizeof(BSTNode));
        p->b = key;
        p->left = p->right = NULL;
        *root = p;
        return true;
    } else if (key < (*root)->b) {
        bst_key_insert(&(*root)->left, key);
    } else {
        bst_key_insert(&(*root)->right, key);
    }
}


/* Delete a node with key.
 * If no node with key, ignore it and return true.
 * If exits a node with key, delete the node,
 * and return true.
 * Or return false;
 * */
bool bst_key_delete (pBSTNode *root, BSTNodeType key) {
    if (!*root) {
        return true;
    }
    if ((*root)->b == key) {
        return true;
    } else if (key < (*root)->b) {
        bst_key_delete(&(*root)->left, key);
    } else {
        bst_key_delete(&(*root)->right, key);
    }
}


/* Return an array of preorder traversl of BST. */
BSTNodeType *bst_preorder (pBSTNode root) {
    return bt_preorder (root);
}


/* Return an array of inorder traversl of BST. */
BSTNodeType *bst_inorder (pBSTNode root) {
    return bt_inorder (root);
}


/* Return an array of postorder traversl of BST. */
BSTNodeType *bst_postorder (pBSTNode root) {
    return bt_postorder (root);
}