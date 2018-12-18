/* 
 * bstree.c
 * Implementation of binary search tree.
 *
 * Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include "bstree.h"
#define max(a, b) (((a) > (b)) ? (a) : (b))

struct entry {
    bstreeElem x;
    struct entry *left;
    struct entry *right;
};

struct _bstree {
    struct entry *root;  /* root node of bstree */
    comparator cmp;      /* comparing function */
};

int bstree_new(bstree_t *bstree, const comparator cmp)
{
    bstree_t new_bstree;

    new_bstree = (bstree_t) malloc(sizeof(*new_bstree));

    if (new_bstree == NULL) {
        return -1;

    } else {
        new_bstree->root = NULL;
        new_bstree->cmp  = (cmp != NULL) ? cmp : cmp_int;
        *bstree = new_bstree;
        return 0;
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
    subtree_free((*bstree)->root);
    free(*bstree);
    *bstree = NULL;
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
static int subtree_add(struct entry **root, const bstreeElem x, comparator cmp)
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
            e->x = x;
            e->left = NULL;
            e->right = NULL;
            *root = e;
            return 0;
        }
    }
}

int bstree_add(bstree_t bstree, const bstreeElem x)
{
    return subtree_add(&bstree->root, x, bstree->cmp);
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
static int subtree_contains(struct entry *root, const bstreeElem x, comparator cmp)
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

int bstree_contains(bstree_t bstree, const bstreeElem x)
{
    return subtree_contains(bstree->root, x, bstree->cmp);
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
static int subtree_remove(struct entry **root, const bstreeElem x, comparator cmp)
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

int bstree_remove(bstree_t bstree, const bstreeElem x)
{
    return subtree_remove(&bstree->root, x, bstree->cmp);
}

/**
 * subtree_get_height - Get height of subtree
 */
static int subtree_get_height(struct entry *root)
{
    if (!root)
        return 0;

    return 1 + max(subtree_get_height(root->left),
            subtree_get_height(root->right));
}

size_t bstree_get_height(bstree_t bstree)
{
    return subtree_get_height(bstree->root);
}

int bstree_isempty(bstree_t bstree)
{
    return bstree->root == NULL;
}

int bstree_get_min(bstree_t bstree, bstreeElem *x)
{
    struct entry *e;

    e = bstree->root;
    while (e != NULL && e->left != NULL) {
        e = e->left;
    }

    if (e != NULL) {
        *x = e->x;
        return 0;
    } else {
        return -1;
    }
}

int bstree_get_max(bstree_t bstree, bstreeElem *x)
{
    struct entry *e;

    e = bstree->root;
    while (e != NULL && e->right != NULL) {
        e = e->right;
    }

    if (e != NULL) {
        *x = e->x;
        return 0;
    } else {
        return -1;
    }

}
