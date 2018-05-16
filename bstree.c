#include "bstree.h"

/**
 * delete - delete a node p in bstree
 *
 * Handle 3 conditions:
 * [1]  left child is  null
 * [2]  right child is null
 * [3]  p have both left and right childs
 */
static void delete (pBSTNode *node) {
    pBSTNode p, q;
    if (!(*node)->left) {   /* [1] */
        p = *node;
        *node = (*node)->right;
        free(p);
    } else if (!(*node)->right) {   /* [2] */
        p = *node;
        *node = (*node)->left;
        free(p);
    } else {                /* [3] */
        p = *node;

        /*
         * Turn left, find the precursor of this node.
         * Handle left child of precursor p.
         */
        q = (*node)->left;
        while (q->right) {
            p = q;
            q = q->right;
        }
        (*node)->b = q->b;
        if (p == *node) {
            p->left = q->left;
            free(q);
        } else {
            p->right = q->left;
            free(q);
        }
    }
}


/**
 * bts_creat - Create and initialize a BST.
 *
 * Return a pointer of pBSTNode if successes, null otherwise.
 */
pBSTNode bst_create (void) {
    return bt_create();
}


/**
 * bst_isempty - check bstree empty or not
 *
 * Return true if tree is empty, false otherwise.
 */
bool bst_isempty (pBSTNode root) {
    if (!root)
        return true;
    return false;
}


/**
 * bst_depth - find the depth of bstree
 *
 * Return depth of the bstree.
 * Return 0 if null.
 */
/* TODO it iteratively */
size_t bst_depth (pBSTNode root) {
    return bt_depth(root);
}


/**
 * bst_destroy - destroy a bstree
 */
void bst_destroy (pBSTNode *root) {
    bt_destroy(root);
}


/**
 * bst_key_search - search BST to find a key
 *
 * @root:   struct pointer
 * @key:    a key value to be searched
 *
 * Return true if key was find, or return false.
 */
bool bst_key_search (pBSTNode root, BSTElemType key) {
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


/**
 * bst_key_insert - insert a key into BST
 *
 * @root:   struct pointer
 * @key:    a key value to be inserted
 *
 * NOTE: repeated values are ignored without notification.
 */
void bst_key_insert (pBSTNode *root, BSTElemType key) {
    if (!*root) {
        pBSTNode p = (pBSTNode) malloc(sizeof(BSTNode));
        p->b = key;
        p->left = p->right = NULL;
        *root = p;
        return;
    } else if (key == (*root)->b) {
        return;     /* ignore repeated value */
    } else if (key < (*root)->b) {
        bst_key_insert(&(*root)->left, key);
    } else {
        bst_key_insert(&(*root)->right, key);
    }
}


/**
 * bst_key_delet - delete a node whose value equals key.
 */
void bst_key_delete (pBSTNode *root, BSTElemType key) {
    if (!*root) {
        return;
    }
    if ((*root)->b == key) {
        delete(root);
        return;
    } else if (key < (*root)->b) {
        bst_key_delete(&(*root)->left, key);
    } else {
        bst_key_delete(&(*root)->right, key);
    }
}


/**
 * Return an array of preorder traversl of BST.
 */
void bst_preorder (pBSTNode root) {
    bt_preorder(root);
}


/**
 * Return an array of inorder traversl of BST.
 */
void bst_inorder (pBSTNode root) {
    bt_inorder(root);
}


/**
 * Return an array of postorder traversl of BST.
 */
void bst_postorder (pBSTNode root) {
    bt_postorder(root);
}