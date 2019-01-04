/* 
 * avltree.c
 * Implementation of avl-tree.
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
#include "avl-tree.h"
#define max(a, b) ((a) > (b) ? (a) : (b))

struct entry {
    avltreeElem x;          /* data */
    int height;             /* height of sub-avltree */
    struct entry *left;     /* left child of the node */
    struct entry *right;    /* right child of the node */
};

struct _avltree {
    struct entry *root;
    comparator cmp;
};

int avltree_new(avltree_t *avl, const comparator cmp)
{
    avltree_t new_avl;

    new_avl = (avltree_t) malloc(sizeof(*new_avl));
    if (new_avl == NULL) {
        return -1;

    } else {
        new_avl->root = NULL;
        new_avl->cmp  = (cmp != NULL) ? cmp : cmp_int;
        *avl = new_avl;
        return 0;
    }
}

/*
 * subtree_free - Destroy a subtree
 */
static void subtree_free(struct entry *root)
{
    if (!root) {
        return;
    }
    
    subtree_free(root->left);
    subtree_free(root->right);
    free(root);
    root = NULL;
}

void avltree_free(avltree_t *avl)
{
    subtree_free((*avl)->root);
    *avl = NULL;
}

/*
 * get_height - Get height of an avl-tree
 */
static int get_height(struct entry *e)
{
    if (e == NULL) {
        return 0;
    } else {
        return e->height;
    }
}

/*
 * get_height_diff - Get diff of height between left and right child.
 */
static int get_height_diff(struct entry *e)
{
    return get_height(e->left) - get_height(e->right);
}

/*
 * rr_rotate - Right-right rotate (left rotation)
 *
 * Schema:
 *    root--> x                      root--> y
 *           / \          rr_rotate        /   \
 *          a   y <--tmp     ==>          x     z
 *             / \                       / \   / \
 *            b   z                     a   b c   d
 *               / \
 *              c   d
 */
static void rr_rotate(struct entry **e)
{
    struct entry *root;
    struct entry *tmp;

    /* rr rotate */
    root = *e;
    tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;

    /* Update height of nodes */
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    tmp->height  = max(get_height(tmp->left),  get_height(tmp->right)) + 1;

    /* Update root node */
    *e = tmp;
}

/*
 * ll_rotate - Left-left rotate (right rotation)
 *
 * Schema:
 *
 *    root--> x                  root--> y
 *           / \     ll_rotate         /   \
 *   tmp--> y   a       ==>           z     x
 *         / \                       / \   / \
 *        z   b                     c   d b   a
 *       / \
 *      c   d
 */
static void ll_rotate(struct entry **e)
{
    struct entry *root;
    struct entry *tmp;

    /* ll rotate */
    root = *e;
    tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    
    /* Update height of nodes */
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    tmp->height  = max(get_height(tmp->left),  get_height(tmp->right)) + 1;
    
    /* Update root node */
    *e = tmp;
}

/*
 * lr_rotate - Left-right double rotation
 *
 * Schema:
 *
 *    root--> x                root--> x                  root--> z
 *           / \   rr_rotate         /   \    ll_rotate         /   \
 *          y   b      ==>          z     b      ==>           y     x
 *         / \                     / \                        / \   / \
 *        a   z                   y   d                      a   c d   b
 *           / \                 / \
 *          c   d               a   c
 */
static void lr_rotate(struct entry **node)
{
    rr_rotate(&(*node)->left);
    ll_rotate(node);
}

/*
 * rl_rotate - Right-left double rotation
 *
 * Schema:
 *
 *    root--> x                root--> x                  root--> z
 *           / \   ll_rotate         /   \    rr_rotate         /   \
 *          a   y      ==>          a     z      ==>           x     y
 *             / \                       / \                  / \   / \
 *            z   b                     c   y                a   c d   b
 *           / \                           / \
 *          c   d                         d   b
 */
static void rl_rotate(struct entry **node)
{
    ll_rotate(&(*node)->right);
    rr_rotate(node);
}

/*
 * rebalance - Re-balance the sub-avl tree
 */
static void rebalance(struct entry **e)
{

    if (get_height_diff(*e) == 2) {
        if (get_height_diff((*e)->left) > 0) {
            ll_rotate(e);
        } else {
            lr_rotate(e);
        }
    } else if (get_height_diff(*e) == -2) {
        if (get_height_diff((*e)->right) > 0) {
            rl_rotate(e);
        } else {
            rr_rotate(e);
        }
    }

}

/*
 * subtree_add - Add a new node
 */
static int subtree_add(struct entry **e, const avltreeElem x, comparator cmp)
{
    struct entry *new_e;
    int res;

    if (*e == NULL) {
        new_e = (struct entry *) malloc(sizeof(struct entry));
        if (!new_e) {
            return -1;

        } else {
            new_e->x = x;
            new_e->height = 1;
            new_e->left = NULL;
            new_e->right = NULL;

            *e = new_e;
        }

    } else if (cmp(x, (*e)->x) < 0) {
        res = subtree_add(&(*e)->left, x, cmp);     /* Go left subtree. */

    } else if (cmp(x, (*e)->x) > 0) {
        res = subtree_add(&(*e)->right, x, cmp);    /* Go right subtree. */

    } else {
        return 0;   /* Duplicated and ignore. */
    }

    if (res == -1) {
        return -1;  /* Out of memory, failed to add new node. */
    } else {
        rebalance(e);   /* Re-balance subree. */

        (*e)->height = 1 + max(get_height((*e)->left),
                               get_height((*e)->right));    /* Update height*/
    }
    return 0;
}

int avltree_add(avltree_t avl, const avltreeElem x)
{
    return subtree_add(&avl->root, x, avl->cmp);
}

int avltree_contains(avltree_t avl, const avltreeElem x)
{
    struct entry *e;
    comparator cmp;

    e = avl->root;
    cmp  = avl->cmp;

    while (e != NULL && cmp(x, e->x) != 0) {
        if (cmp(x, e->x) < 0) {
            e = e->left;
        } else {
            e = e->right;
        }
    }

    return e != NULL;
}

/*
 * subree_remove - Remove a target node in subtree
 *
 * Return 0 if success, -1 if no match node found.
 */
static int subtree_remove(struct entry **e, const avltreeElem x, comparator cmp)
{
    struct entry *root;
    struct entry *tmp;

    root = *e;

    if (root == NULL) {
        return -1;

        /* Target node is in left subtree */
    } else if (cmp(x, root->x) < 0) {
        subtree_remove(&root->left, x, cmp);

        /* Re-balance */
        if (get_height(root->right) - get_height(root->left) == 2) {
            tmp = root->right;

            if (get_height(tmp->right) > get_height(tmp->left)) {
                rr_rotate(e);
            } else {
                rl_rotate(e);
            }
        }

        /* Target node is in right subtree */
    } else if (cmp(x, root->x) > 0) {
        subtree_remove(&root->right, x, cmp);

        /* Re-balance */
        if (get_height(root->left) - get_height(root->right) == 2) {
            tmp = root->left;

            if (get_height(tmp->left) > get_height(tmp->right)) {
                ll_rotate(e);
            } else {
                lr_rotate(e);
            }
        }

        /* Current node is target node. */
    } else {
        if (root->left != NULL && root->right != NULL) {
            /*
             * The height of left subtree is larger than 
             * the height of right subtree. Find the precursor 
             * in left subtree and copy x to current node, 
             * and free precursor. Now, avl-tree is still balanced.
             */
            if (get_height(root->left) > get_height(root->right)) {
                struct entry *max;

                max = root->left;
                while (max && max->right) {
                    max = max->right;
                }
                root->x = max->x;
                subtree_remove(&root->left, max->x, cmp);

                /*
                 * The height of left subtree is lower than 
                 * the height of right subtree. Find the successor 
                 * in right subtree and copy x to current node,
                 * and free successor. Now, avl-tree is still balanced.
                 */
            } else {
                struct entry *min;

                min = root->right;
                while (min && min->left) {
                    min = min->left;
                }
                root->x = min->x;
                subtree_remove(&root->right, min->x, cmp);
            }

        /* Left subtree or right subtree is NULL.  */
        } else {
            tmp = *e;

            *e = root->left ? root->left : root->right;
            free(tmp);
        }
    }

    /* Update the height of nodes */
    if (*e != NULL) {
        (*e)->height = max(get_height((*e)->left), get_height((*e)->right)) + 1;
    }
    return 0;
}


int avltree_remove(avltree_t avl, const avltreeElem x)
{
    return subtree_remove(&avl->root, x, avl->cmp);
}

int avltree_get_hight(avltree_t avl)
{
    return get_height(avl->root);
}

int avltree_isempty(avltree_t avl)
{
    return avl->root == NULL;
}

int avltree_get_min(avltree_t avl, avltreeElem *x)
{
    struct entry *e;

    e = avl->root;
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

int avltree_get_max(avltree_t avl, avltreeElem *x)
{
    struct entry *e;

    e = avl->root;
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
