#include "btree.h"


/** max of two variables */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


/**
 * bt_creat - create and initialize a BT.
 *
 * Return a pBTNode if success, or return false.
 */
pBTNode bt_create (void) {
    pBTNode p = (pBTNode) calloc(1, sizeof(BTNode));
    if (!p)
        return NULL;
    return p;
}


/**
 * bt_isempty - check btree is empty or not
 *
 * If tree is empty, return true.
 * Or return false.
 */
bool bt_empty (pBTNode root) {
    if (!root)
        return true;
    return false;
}


/**
 * bst_depth - find the depth of btree
 *
 * Return depth of the btree.
 * Return 0 if null.
 */
/* TODO it iteratively */
size_t bt_depth (pBTNode root) {
    if (!root)
        return 0;
    return MAX(bt_depth(root->left), bt_depth(root->right)) + 1;
}


/**
 * bt_destroy - destroy a btree.
 */
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


/**
 * bt_preoder - preorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_preorder (pBTNode root) {
    if (!root) {
        return NULL;
    }
    /* TODO: Define a dynamic array at the beginning
     * TODO: save values in a dynamic array: darray_append()
     */
    printf("val = %d", root->b);
    bt_preorder(root->left);
    bt_preorder(root->right);

}

/**
 * bt_inoder - inorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_inorder (pBTNode root) {
    if (!root) {
        return NULL;
    }
    /* TODO: Define a dynamic array at the beginning
     * TODO: save values in a dynamic array: darray_append()
     * */
    bt_inorder(root->left);
    printf("%d, ", root->b);
    bt_inorder(root->right);
}

/**
 * bt_postoder - postorder traversal of btree
 *
 * Return an array of preorder traversl of btree if tree exits.
 * Or return null.
 */
void bt_postorder (pBTNode root) {
    if (!root) {
        return NULL;
    }
    /* TODO: Define a dynamic array at the beginning
     * TODO: save values in a dynamic array: darray_append()
     * */
    bt_postorder(root->left);
    bt_postorder(root->right);
    printf("%d\n", root->b);
}