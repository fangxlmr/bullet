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
#include "trie.h"
/*
 * Only support 26 lower case letters for now.
 * We can extend it in the future to support more.
 */
#define ALPHABAT_SIZE 26

struct _trie {
    struct _trie *children[ALPHABAT_SIZE];
    int word;           /* Is a word or not. */
    size_t count;       /* Frequency. */
};

static int get_index(char c)
{
    return c - 'a';
}

static int new_trie_node(trie_t *trie)
{
    *trie = (trie_t) malloc(sizeof(struct _trie));

    if (*trie == NULL) {
        return -1;
    } else {
        return 0;
    }
}

static void init_trie_node(trie_t trie)
{
    int i;

    for (i = 0; i < ALPHABAT_SIZE; ++i) {
        trie->children[i] = NULL;
    }
    trie->word = 0;     /* Not a word in the beginning. */
    trie->count = 0;    /* Frequency is 0. */
}

/*
 * add_trie_node - Add a new trie node to a the given trie
 *
 * @trie[in]: the trie
 * @c[in]: given char
 * @word[in]: is end of a word
 *
 * Return 0 if add trie node successfully,
 * -1 if out of memory.
 */
static int add_trie_node(trie_t *trie, int i, int word)
{
    trie_t nb;  /* New node. */

    if (*trie == NULL) {
        if (new_trie_node(&nb) == -1) {
            return -1;
        } else {
            init_trie_node(nb);
            (*trie)->children[i] = nb;
        }
    }
    (*trie)->word = word;
    (*trie)->count = word ? (*trie)->count++ : (*trie)->count;
}

static void free_trie_node(trie_t node)
{
    free(node);
}

int trie_new(trie_t *trie)
{
    if (new_trie_node(trie) == 0) {
        return -1;
    } else {
        init_trie_node(*trie);
    }
    return 0;
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
        free_trie_node(*trie);
    }
    *trie = NULL;
}

int trie_add(trie_t trie, char *word)
{
    int i;
    char *p = word;

    while (*p) {
        i = get_index(*p);
        if (add_trie_node(&trie, i, *(p + 1) == '\0') == -1) {
            return -1;
        } else {
            trie = trie->children[i];
            p++;
        }
    }
}

int trie_remove(trie_t trie, char *word)
{
    int i;
    char *p =  word;

    while (*p) {
        i = get_index(*p);
        trie = trie->children[i];
    }
    if (trie->word == 0) {
        return -1;      /* Not found. */
    } else {
        trie->count--;
        if (trie->count <= 0) {     /* Delete the word. */
            trie->word = 0;
        }
        return 0;
    }
}

int trie_contains(trie_t trie, char *word)
{
    int i;
    char *p = word;

    while (*p) {
        i = get_index(*p);
        trie = trie->children[i];
    }
    return trie->word;
}
