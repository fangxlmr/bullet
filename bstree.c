/* Implementation of binary search tree. */

#include <stdlib.h>
#include <assert.h>
#include "bstree.h"
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

struct entry {
    void *x;
    struct entry *left;
    struct entry *right;
};

struct _bstree {
    struct entry *root;  /* root node of bstree */
    comparator cmp;      /* comparing function */
};

bstree_t *bstree_new(const comparator cmp)
{
    bstree_t *bstree;

    bstree = (bstree_t *) malloc(sizeof(*bstree));

    if (bstree == NULL) {
        return NULL;

    } else {
        bstree->root = NULL;
        bstree->cmp  = (cmp != NULL) ? cmp : cmp_int;

        return bstree;
    }

}

/**
 * subtree_free - Destroy a subtree 
 */
static void subtree_free(struct entry *root)
{
    if (root == NULL) {
        return;
    }
    
    subtree_free(root->left);
    subtree_free(root->right);
    free(root);
}

void bstree_free(bstree_t *bstree)
{
    subtree_free(bstree->root);
    free(bstree);
}

/**
 * subtree_add - Add an element to subtree
 *
 * @root: the root of sub tree
 * @x: the value
 * @cmp: comparing funciton
 *
 * Return 0 if success, -1 otherwise.
 * Return 0 if duplicated.
 */
static int subtree_add(struct entry **root, const void *x, comparator cmp)
{
    struct entry *e;

    while (*root != NULL && cmp(x, (*root)->x) != 0) {
        /* Turn left */
        if (cmp(x, (*root)->x) < 0) {
            root = &(*root)->left;

            /* Turn right */
        } else {
            root = &(*root)->right;
        }
    }

    if (*root != NULL) {
        /* Ignore duplicated value. */
        return 0;

        /* No match node, create a new one.  */
    } else {
        e = (struct entry *) malloc(sizeof(*e));
        if (!e) {
            return -1;
        } else {
            e->x = (void *) x;
            e->left = NULL;
            e->right = NULL;
            *root = e;
            return 0;
        }
    }
}

int bstree_add(bstree_t *bstree, const void *value)
{
    return subtree_add(&bstree->root, value, bstree->cmp);
}

/**
 * subtree_contains - Check subtree contains the value or not
 *
 * @root: the root of subtree
 * @x: the value
 * @cmp: comparing function
 *
 * Return 1 if contains, 0 otherwise.
 */
static int subtree_contains(struct entry *root, const void *x, comparator cmp)
{
    while (root != NULL && cmp(x, root->x) != 0) {
        /* Turn left */
        if (cmp(x, root->x) < 0) {
            root = root->left;

            /* Turn right */
        } else {
            root = root->right;
        }
    }
    return root != NULL;
}

int bstree_contains(bstree_t *bstree, void *value)
{
    return subtree_contains(bstree->root, value, bstree->cmp);
}

/**
 * delete_node - Delete a single node in bstree
 *
 * @node: second rank pointer
 *
 * There are 3 different situation to be handled:
 * [1]  Left child is empty.
 * [2]  Right child is empty.
 * [3]  Both exists.
 */
static void delete_node(struct entry **node) {
    struct entry *p, *q;

    /* [1] */
    if ((*node)->left == NULL) {
        p = *node;
        *node = p->right;
        free(p);

     /* [2] */
    } else if ((*node)->right == NULL){
        p = *node;
        *node = p->left;
        free(p);

    /* [3] */
    } else {
        /* Turn left, find the precursor. */
        p = *node;
        q = p->left;
        while (q->right) {
            p = q;
            q = q->right;
        }
        /*
         * Copy value from precursor to 
         * current node, i.g. delete current node.
         */
        (*node)->x = q->x;

        /*
         * If left child of current node only
         * have left child, then the precursor of
         * current node will be its left child.
         * We need to connect left subtree of left
         * child to current node.
         *
         *  *node,p -->  58  (current node)
         *              /
         *       q-->  47  (precursor)
         *            /
         *          35  (left subtree of precursor)
         */
        if (p == *node) {
            p->left = q->left;
            free(q);

        /*
         * If left child of current node have left
         * and right child, then the precursor of
         * current node will be its left child.
         * We need to connect left subtree of
         * cprecursor to current node.
         *
         *  *node -->  58  (current node) 
         *            /
         *    p -->  47 
         *          /  \
         *         35  49 <--q  (precursor)
         *            /
         *           48  (left subtree of precursor)
         */
        } else {
            p->right = q->left;
            free(q);
        }
    }
}

/**
 * subtree_remove - Remove a node with a given value
 *
 * @root: the root of subtree
 * @x: the value
 * @cmp: comparing function
 *
 * Return 0 if success, -1 otherwise.
 */
static int subtree_remove(struct entry **root, const void *x, comparator cmp)
{
    while (*root != NULL && cmp(x, (*root)->x) != 0) {
        /* Turn left */
        if (cmp(x, (*root)->x) < 0) {
            root = &(*root)->left;

            /* Turn right  */
        } else {
            root = &(*root)->right;
        }
    }

    if (*root != NULL) {
        delete_node(root);
        return 0;
    } else {
        return -1;
    }
}

int bstree_remove(bstree_t *bstree, const void *value)
{
    return subtree_remove(&bstree->root, value, bstree->cmp);
}

/**
 * subtree_depth - Find depth of subtree
 */
static int subtree_depth(struct entry *root)
{
    if (!root)
        return 0;

    return 1 + MAX( subtree_depth(root->left),
                    subtree_depth(root->right) );
}

int bstree_depth(bstree_t *bstree)
{
    return subtree_depth(bstree->root);
}

int bstree_isempty(bstree_t *bstree)
{
    return bstree->root == NULL;
}

void *bstree_min(bstree_t *bstree)
{
    struct entry *e;

    e = bstree->root;
    while (e != NULL && e->left != NULL) {
        e = e->left;
    }

    if (e != NULL) {
        return e->x;
    } else {
        return NULL;
    }
}

void *bstree_max(bstree_t *bstree)
{
    struct entry *e;

    e = bstree->root;
    while (e != NULL && e->right != NULL) {
        e = e->right;
    }

    if (e != NULL) {
        return e->x;
    } else {
        return NULL;
    }

}
