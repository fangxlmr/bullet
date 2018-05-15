#include "btree.h"

/* max of two variables */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


/* Create and initialize a BT.
 * Return true if success,
 * Or return false.
 * */
pBTNode bt_new (void) {
    pBTNode p = (pBTNode) calloc(1, sizeof(BTNode));
    if (!p)
        return NULL;
    return p;
}


/* If tree is empty, return true.
 * Or return false.
 * */
bool bt_isempty (pBTNode root) {
    if (!root)
        return true;
    return false;
}


/* Return depth of the tree (recursively).
 * Return 0, if NULL.
 * */
/* TODO it iteratively */
size_t bt_depth (pBTNode root) {
    if (!root)
        return 0;
    return MAX(bt_depth(root->left), bt_depth(root->right)) + 1;
}


/* Destroy a bt.
 * Do it post-order-transversely
 * */
void bt_destroy (pBTNode *root) {
    pBTNode *p = root;
    if (!*root) {
        return;
    }
    bt_destroy(&(*root)->left);
    (*root)->left = NULL;
    bt_destroy(&(*root)->right);
    (*root)->right = NULL;
    free(*p);
    *p = NULL;
}

/* Return an array of preorder traversl of BT. */
BTNodeType *bt_preorder (pBTNode root) {
    if (!root) {
        return NULL;
    }

}

/* Return an array of inorder traversl of BT. */
BTNodeType *bt_inorder (pBTNode root) {
}

/* Return an array of postorder traversl of BT. */
BTNodeType *bt_postorder (pBTNode root) {
}