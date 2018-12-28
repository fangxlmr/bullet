/* 
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
#include <string.h>
#include "trie.h"
/*
 * Only support 26 lower case letters for now.
 * We can extend it in the future to support more.
 */
#define ALPHABAT_SIZE 26

struct _trie {
    char c;
    int eow;           /* End of word, which means if it is a word. */
    size_t count;       /* Frequency. */
    struct _trie *children[ALPHABAT_SIZE];
};

static int get_index(char c)
{
    return c - 'a';
}

static int new_trie_node(trie_t *trie, char c)
{
    *trie = (trie_t) malloc(sizeof(struct _trie));

    if (*trie == NULL) {
        return -1;
    } else {
        /* Initialize node. */
        (*trie)->c = c;
        (*trie)->count = 1;
        memset((*trie)->children, 0, ALPHABAT_SIZE * sizeof(struct _trie));
        return 0;
    }
}

int trie_new(trie_t *trie)
{
    if (new_trie_node(trie, '\0') == -1) {
        return -1;
    } else {
        (*trie)->eow = 1;
        return 0;
    }
}

void trie_free(trie_t *trie)
{
    int i;

    if (*trie == NULL) {
        return;
    } else {
        for (i = 0; i < ALPHABAT_SIZE; ++i) {
            trie_free(&(*trie)->children[i]);
        }
        free(*trie);
    }
    *trie = NULL;
}

int trie_add(trie_t trie, char *word)
{
    int i, j;
    char *p = word;

    while (*p) {
        i = get_index(*p);
        if (trie->children[i] == NULL) {     /* Need to alloc new node. */
            if (new_trie_node(&trie->children[i], *p) == -1) {
                return -1;
            }
        }
        trie = trie->children[i];
        p++;
    }
    trie->eow = 1;
    trie->count++;
    return 0;
}

int trie_contains(trie_t trie, char *word)
{
    int i;
    char *p = word;

    while (*p) {
        i = get_index(*p);
        if (trie->children[i] == NULL) {
            return 0;
        } else {
            trie = trie->children[i];
            p++;
        }
    }
    return trie->eow;
}

int trie_startswith(trie_t trie, char *word)
{
    int i;
    char *p = word;

    while (*p) {
        i = get_index(*p);
        if (trie->children[i] == NULL) {
            return 0;
        } else {
            trie = trie->children[i];
            p++;
        }
    }
    return 1;
}