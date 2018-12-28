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
    size_t level;
    struct boxes **next;
};

struct _skiplist {
    struct boxes *head;
    size_t levels;
    comparator cmp;
};

static size_t get_level(void)
{
    size_t level = 0;

    srand((unsigned)time(NULL));
    while (rand() % 2) {    /* Coin filp */
        level++;
    }
    return level < MAX_LEVEL ? level: MAX_LEVEL;
}

/*
 * new_boxes - Create new boxes
 *
 * @nb[out]: new boxes
 * @x[in]: input value
 * @level[in]: the size of the boxes
 *
 * Return 0 if create new boxes successfully, -1 if out of memory.
 */
static int new_boxes(struct boxes **nb, const skiplistElem x, const size_t level)
{
    struct boxes **next;

    *nb = (struct boxes *) malloc(sizeof(struct boxes));
    if (*nb == NULL) {
        return -1;
    } else {
        next = (struct boxes **) malloc(level * sizeof(*next));
        if (next == NULL) {
            free(nb);
            return -1;
        } else {
            (*nb)->next = next;
            (*nb)->level = level;
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
        if (new_boxes(&new_head, 0, MAX_LEVEL) == 0){
            free(new_skiplist);
            return -1;
        } else {
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
     * p is work pointer, update is used to store prev pointers of
     * new boxes.
     */
    struct boxes *p, *update[MAX_LEVEL];
    struct boxes *nb;   /* New boxes */
    comparator cmp;
    size_t i, level;

    p = skiplist->head;
    cmp = skiplist->cmp;

    /* Find the correct position to insert.  */
    for (i = skiplist->levels - 1; i >= 0; i--) {
        while (p->next && cmp(x, p->next[i]->x) < 0) {
            p = p->next[i];
        }
        if (p->next != NULL && cmp(x, p->next[i]->x) == 0) {
            return 0;       /* Ignore dupllicate value. */
        } else {
            update[i] = p;  /* Memorizing prev pointers. */
        }
    }

    /* Get a level by coin flip. */
    level = get_level();
    if (new_boxes(&nb, x, level) == 0) {
        return -1;
    } else {
        /* Insert and update new boxes' prev and next pointers. */
        for (i = 0; i < level; i++) {
            nb->next[i] = update[i]->next[i];
            update[i]->next[i] = nb;
        }
        return 0;
    }
}

int skiplist_remove(skiplist_t skiplist, skiplistElem x)
{
    struct boxes *p, *update[MAX_LEVEL];
    comparator cmp;
    size_t i;

    for (i = skiplist->levels - 1; i >= 0; i--) {
        while (p->next && cmp(x, p->next[i]->x) < 0) {
            p = p->next[i];
        }
        update[i] = p;
    }
    if (p->next != NULL && cmp(x, p->next[0]->x) == 0) {
        for (i = p->level - 1; i >= 0; i--) {
            update[i]->next[i] = p->next[i];
        }
        free_boxes(&p);
        return 0;
    } else {
        return -1;
    }
}

int skiplist_contains(skiplist_t skiplist, skiplistElem x)
{
    struct boxes *p;
    comparator cmp;
    size_t i;

    p = skiplist->head;
    cmp = skiplist->cmp;
    for (i = skiplist->levels - 1; i >= 0; i--) {
        while (p->next && cmp(x, p->next[i]->x) < 0) {  /* Level scan. */
            p = p->next[i];
        }
        if (p->next != NULL && cmp(x, p->next[i]->x) == 0) {
            return 1;       /* Found it. */
        }
    }
    return 0;
}
