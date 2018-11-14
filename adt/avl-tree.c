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
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct entry {
    void *x;                /* data */
    int height;             /* balance factor */
    struct entry *left;     /* left child of the node */
    struct entry *right;    /* right child of the node */
};

struct _avltree {
    struct entry *root;
    comparator cmp;
};

avltree_t *avltree_new(const comparator cmp)
{
    avltree_t *avl;

    avl = (avltree_t *) malloc(sizeof(avltree_t));
    if (!avl) {
        return NULL;

    } else {
        avl->root = NULL;
        avl->cmp  = (cmp != NULL) ? cmp : cmp_int;
        return avl;
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
}

void avltree_free(avltree_t *avl)
{
    subtree_free(avl->root);
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
 * rr_rotate - Right-right rotate (left rotation)
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
    root->height = MAX(get_height(root->left), get_height(root->right)) + 1;
    tmp->height  = MAX(get_height(tmp->left),  get_height(tmp->right)) + 1;

    /* Update root node */
    *e = tmp;
}

/*
 * ll_rotate - Left-left rotate (right rotation)
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
    root->height = MAX(get_height(root->left), get_height(root->right)) + 1;
    tmp->height  = MAX(get_height(tmp->left),  get_height(tmp->right)) + 1;
    
    /* Update root node */
    *e = tmp;
}

/*
 * lr_rotate - Left-right double rotation
 */
static void lr_rotate(struct entry **node)
{
    /*
     * 
     * 
     */
    rr_rotate(&(*node)->left);
    /*
     * 
     */
    ll_rotate(node);
}

/*
 * rl_rotate - Right-left double rotation
 */
static void rl_rotate(struct entry **node)
{
    /*
     * 
     * 
     */
    ll_rotate(&(*node)->right);
    /*
     * 
     */
    rr_rotate(node);
}

/*
 * subtree_add - Add a new node
 */
static int subtree_add(struct entry **e, const void *x, comparator cmp)
{
    struct entry *new_e;

    if (*e == NULL) {
        new_e = (struct entry *) malloc(sizeof(struct entry));
        if (!new_e) {
            return -1;

        } else {
            new_e->x = (void *) x;
            new_e->height = 1;
            new_e->left = NULL;
            new_e->right = NULL;

            *e = new_e;
        }

    } else if (cmp(x, (*e)->x) < 0) {
        subtree_add(&(*e)->left, x, cmp);

        /* Re-balance */
        if (get_height((*e)->left) - get_height((*e)->right) == 2) {
            if (cmp(x, (*e)->left) < 0) {
                ll_rotate(e);
            } else {
                lr_rotate(e);
            }
        }

    } else if (cmp(x, (*e)->x) > 0) {
        subtree_add(&(*e)->right, x, cmp);

        /* Re-balance */
        if (get_height((*e)->right) - get_height((*e)->left) == 2) {
            if (cmp(x, (*e)->x) < 0) {
                rl_rotate(e);
            } else {
                rr_rotate(e);
            }
        }

        /* Duplicated and ignore. */
    } else {
        return 0;
    }

    /* Update height*/
    (*e)->height = MAX(get_height((*e)->left), get_height((*e)->right)) + 1;
    return 0;
}

int avltree_add(avltree_t *avl, void *value)
{
    return subtree_add(&avl->root, value, avl->cmp);
}

int avltree_contains(avltree_t *avl, const void *value)
{
    struct entry *e;
    comparator cmp;

    e = avl->root;
    cmp  = avl->cmp;

    while (e != NULL && cmp(value, e->x) != 0) {
        if (cmp(value, e->x) < 0) {
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
static int subtree_remove(struct entry **e, const void *value, comparator cmp)
{
    struct entry *root;
    struct entry *tmp;

    root = *e;

    if (root == NULL) {
        return -1;

        /* Target node is in left subtree */
    } else if (cmp(value, root->x) < 0) {
        subtree_remove(&root->left, value, cmp);

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
    } else if (cmp(value, root->x) > 0) {
        subtree_remove(&root->right, value, cmp);

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
             * in left subtree and copy value to current node, 
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
                 * in right subtree and copy value to current node,
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
        (*e)->height = MAX(get_height((*e)->left), get_height((*e)->right)) + 1;
    }
    return 0;
}


int avltree_remove(avltree_t *avl, const void *x)
{
    return subtree_remove(&avl->root, x, avl->cmp);
}

int avltree_get_hight(avltree_t *avl)
{
    return get_height(avl->root);
}

int avltree_isempty(avltree_t *avl)
{
    return avl->root == NULL;
}

void *avltree_get_min(avltree_t *avl)
{
    struct entry *e;

    e = avl->root;
    while (e != NULL && e->left != NULL) {
        e = e->left;
    }

    if (e != NULL) {
        return e->x;
    } else {
        return NULL;
    }
}

void *avl_get_max(avltree_t *avl)
{
    struct entry *e;

    e = avl->root;
    while (e != NULL && e->right != NULL) {
        e = e->right;
    }

    if (e != NULL) {
        return e->x;
    } else {
        return NULL;
    }
}
