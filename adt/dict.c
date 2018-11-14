/* 
 * dict.c
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
#include "dict.h"
#define LOAD_FACTOR 0.75

struct pairs {
    void *key;
    void *value;
};

struct entry {
    pairs pair;
    struct entry *next;
};

struct _dict {
    struct entry **buckets;
    size_t size;     /* size of buckests  */
    size_t count;    /* count of key-value pairs in dict  */
    size_t idx;      /* index in primes table  */
    hash_f hash;     /* hash function  */
    comparator cmp;  /* comparing fucntion  */
};

/*
 * Primes table in common use
 * Link: http://planetmath.org/goodhashtableprimes
 */
static const unsigned int primes[] = {
    193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157,
    98317, 196613, 393241, 786433, 1572869, 3145739,
    6291469, 12582917, 25165843, 50331653, 100663319,
    201326611, 402653189, 805306457, 1610612741,
};
static const unsigned int primes_size
        = sizeof(primes) / sizeof(primes[0]);

/*
 * buckets_new - Alloc memory for buckets
 *
 * @dict: the dict
 *
 * Return 0 if success, -1 otherwise.
 */
static int buckets_new(dict_t *dict)
{
    size_t new_size;

    /*
     * If the size of buckets exceeds the size 
     * of primes table , it shows there is 
     * no usable primes in primes table. Here,
     * we just resize it as 10 times bigger. 
     */
    if (dict->idx < primes_size) {
        new_size = primes[dict->idx];
    } else {
        new_size = dict->count * 10;
    }

    dict->size = new_size;
    dict->buckets = (struct entry **) calloc(new_size, sizeof(struct entry *));

    if (dict->buckets == NULL) {
        return -1;
    } else {
        return 0;
    }
}

dict_t *dict_new(const hash_f hash, const comparator cmp)
{
    dict_t *dict;

    dict = (dict_t *) malloc(sizeof(*dict));

    if (!dict) {
        return NULL;

    } else {
        dict->hash  = hash;
        dict->cmp = (cmp != NULL) ? cmp : cmp_int;
        dict->count = 0;
        dict->idx = 0;     /* Use primes[0] as default buckets size  */

        if (buckets_new(dict) == -1) {  /* Alloc memory failed  */
            free(dict);
            return NULL;
        } else {
            return dict;
        }
    }
}

void dict_free(dict_t *dict)
{
    struct entry *walk;
    struct entry *del;
    size_t i;

    for (i = 0; i < dict->size; ++i) {
        walk = dict->buckets[i];

        while (walk != NULL) {
            del = walk;
            walk  = walk->next;
            free(del);
        }
    }

    free(dict->buckets);
    free(dict);
}

/**
 * dict_resize - Resize buckes in dict
 *
 * @dict: the dict
 *
 * Return 0 if success, -1 otherwise.
 * If resize failed, dict will remain unchanged.
 */
static int dict_resize(dict_t *dict)
{
    struct entry **old_buckets;
    struct entry *walk, *next;
    size_t old_size;
    size_t old_idx;
    pairs *pair;

    old_buckets = dict->buckets;
    old_size = dict->size;
    old_idx = dict->idx;

    dict->idx++;
    if (buckets_new(dict) == -1) {      /* Resize failed.  */
        dict->buckets = old_buckets;
        dict->size    = old_size;
        dict->idx   = old_idx;
        return -1;

    } else {        /* Resize success.  */
        size_t i, j;

        /* Re-hash each element in old dict,
         * and add to the new one.  */
        for (j = 0; j < old_size; ++j) {
            walk = old_buckets[j];
            while (walk != NULL) {
                pair = &(walk->pair);

                /* Re-hash */
                i = dict->hash(pair->key) % dict->size;
                next = walk->next;

                /* Add to new dict. */
                walk->next = dict->buckets[i];
                dict->buckets[i] = walk;

                walk = next;
            }
        }

        free(old_buckets);
        return 0;
    }

}

int dict_add(dict_t *dict, const void *k, const void *v)
{
    struct entry *e, *walk;
    pairs *pair;
    size_t i;
    
    /*
     * Check the amount of pairs exceeds LOAD_FACTOR,
     * if so, dict need to be resized.
     */
    if (dict->count > dict->size * LOAD_FACTOR) {
        if (dict_resize(dict) == -1) {
            return -1;      /* Resize failed. */
        }
    }
    
    /* Calcular hash code */
    i = dict->hash(k) % dict->size;
    walk = dict->buckets[i];

    while (walk != NULL) {
        pair = &(walk->pair);

        /* Update key-value pairs if it exists already. */
        if (dict->cmp(pair->key, k) == 0) {
            pair->key = (void *) k;
            pair->value = (void *) v;
            return 0;
        }
        walk = walk->next;
    }

    /* Create a new key-value pair if it doesn't exsit. */
    e = (struct entry *) malloc(sizeof(struct entry));
    if (e == NULL) {
        return -1;

    } else {
        e->pair.key = (void *) k;
        e->pair.value = (void *) v;

        e->next = dict->buckets[i];
        dict->buckets[i] = e;
        ++dict->count;

        return 0;
    }
}

void *dict_get(dict_t *dict, const void *k)
{
    struct entry *walk;
    size_t i;

    i = dict->hash(k) % dict->size;
    walk = dict->buckets[i];

    while (walk != NULL) {
        if (dict->cmp(walk->pair.key, k) == 0) {
            return walk->pair.value;
        }
        walk = walk->next;
    }

    return NULL;
}

int dict_pop(dict_t *dict, const void *k)
{
    struct entry **walk;
    struct entry *del;
    pairs  *pair;
    size_t i;

    /* hash code */ 
    i = dict->hash(k) % dict->size;
    walk = &(dict->buckets[i]);

    /* Find and delete match pair. */
    while (*walk != NULL) {
        pair = &((*walk)->pair);

        if (dict->cmp(pair->key, k) == 0) {
            del = *walk;
            *walk = del->next;
            free(del);
            dict->count--;

            return 1;
        }
        walk = &(*walk)->next;
    }

    return -1;
}
