/* 
 * skiplistc
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

#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"

static const size_t MAX_LEVEL = 32;

struct boxes {      /* Node structure */
    skiplistElem x;
    size_t level;           /* Current level. */
    struct boxes **next;
};

struct _skiplist {
    struct boxes *head;
    size_t levels;
    comparator cmp;
};

static size_t get_level(void)
{
    int level = 1;

    srand((unsigned int) time(NULL));
    while (rand() % 2) {    /* Coin flip. */
        level++;
    }
    return level < MAX_LEVEL ? level : MAX_LEVEL;
}

/*
 * new_boxes - Create and initialize new boxes
 *
 * @nb[out]: new boxes
 * @x[in]: input value
 * @level[in]: the size of the boxes
 *
 * Return 0 if create new boxes successfully, -1 if out of memory.
 */
static int new_boxes(struct boxes **nb, const skiplistElem x, const size_t level)
{
    struct boxes **new_next;

    *nb = (struct boxes *) malloc(sizeof(struct boxes));
    if (*nb == NULL) {
        return -1;
    } else {
        new_next = (struct boxes **) malloc(level * sizeof(new_next[0]));
        if (new_next == NULL) {
            free(nb);
            return -1;
        } else {
            /* Init new box with `x`, `level`. */
            (*nb)->x = x;
            (*nb)->level = level;
            (*nb)->next = new_next;
            return 0;
        }
    }
}

static void free_boxes(struct boxes **fb)
{
    free((*fb)->next);
    free(*fb);
    *fb = NULL;
}

int skiplist_new(skiplist_t *skiplist, comparator cmp)
{
    skiplist_t new_skiplist;
    struct boxes *new_head;

    new_skiplist = (skiplist_t) malloc(sizeof(*new_skiplist));
    if (new_skiplist == NULL) {
        return -1;
    } else {
        /* Init head with value of 0. */
        if (new_boxes(&new_head, 0, MAX_LEVEL) == -1){
            free(new_skiplist);
            return -1;
        } else {
            /* Init head with NULL pointers. */
            int i;
            for (i = 0; i < MAX_LEVEL; ++i) {
                new_head->next[i] = NULL;
            }
            new_skiplist->head = new_head;
            new_skiplist->levels = MAX_LEVEL;
            new_skiplist->cmp = (cmp != NULL) ? cmp : cmp_int;

            *skiplist = new_skiplist;
            return 0;
        }
    }
}

void skiplist_free(skiplist_t *skiplist)
{
    struct boxes *del, *cur;

    cur = (*skiplist)->head;
    while (cur != NULL) {
        del = cur;
        cur = cur->next[0];
        free_boxes(&del);
    }
    free(*skiplist);
    *skiplist = NULL;
}

int skiplist_add(skiplist_t skiplist, skiplistElem x)
{
    /* 
     * p is work pointer, update array is used
     * to store prev pointers of new boxes.
     */
    struct boxes *p, *update[MAX_LEVEL];
    struct boxes *nb;   /* New boxes */
    comparator cmp;
    int i;

    p = skiplist->head;
    cmp = skiplist->cmp;

    /* Find the correct position to insert.  */
    for (i = skiplist->levels - 1; i >= 0; i--) {
        while (p->next[i] && cmp(x, p->next[i]->x) > 0) {
            p = p->next[i];
        }
        if (p->next[i] != NULL && cmp(x, p->next[i]->x) == 0) {
            return 0;       /* Ignore dupllicate value. */
        } else {
            update[i] = p;  /* Memorizing prev pointers. */
        }
    }

    /* Get a random level by coin flip. */
    size_t level = get_level();
    if (new_boxes(&nb, x, level) == -1) {
        return -1;
    } else {
        /* Insert and update new boxes */
        for (i = 0; i < level; ++i) {
            nb->next[i] = update[i]->next[i];
            update[i]->next[i] = nb;
        }
        return 0;
    }
}

int skiplist_remove(skiplist_t skiplist, skiplistElem x)
{
    struct boxes *p, *q, *update[MAX_LEVEL];
    comparator cmp;
    int i;

    p = skiplist->head;
    cmp = skiplist->cmp;

    for (i = skiplist->levels - 1; i >= 0; i--) {
        while (p->next[i] && cmp(x, p->next[i]->x) > 0) {
            p = p->next[i];     /* Level scan. */
        }
        update[i] = p;   /* Save prev pointers for updating later on. */
    }

    /* Found and remove. */
    if (p->next[0] != NULL && cmp(x, p->next[0]->x) == 0) {
        q = p->next[0];
        for (i = q->level - 1; i >= 0; i--) {
            update[i]->next[i] = q->next[i];    /* Update. */
        }
        free_boxes(&q);
        return 0;
    } else {
        return -1;   /* Not found. */
    }
}

int skiplist_contains(skiplist_t skiplist, skiplistElem x)
{
    struct boxes *p;
    comparator cmp;
    int i;

    p = skiplist->head;
    cmp = skiplist->cmp;
    for (i = skiplist->levels - 1; i >= 0; i--) {
        while (p->next[i] && cmp(x, p->next[i]->x) > 0) {  /* Level scan. */
            p = p->next[i];
        }
        if (p->next[i] != NULL && cmp(x, p->next[i]->x) == 0) {
            return 1;       /* Found it. */
        }
    }
    return 0;   /* Not found. */
}
