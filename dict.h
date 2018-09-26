/**
 * dict.h
 *
 */

#ifndef BULLET_DICT_H
#define BULLET_DICT_H

/**
 * define a dict
 */
typedef struct _dict dict_t;

/**
 * hash_f - Hash function
 *
 * @key: hash key
 */
typedef unsigned int (*hash_f)(void *key);

/**
 * dict_cf - Dict comparing function (call back function)
 *
 * @k1: key1
 * @k2: key2
 *
 * Return values depends on the two keys:
 * k1 < k2, return -1.
 * k1 = k2, return  0.
 * k1 > k2, return  1.
 */
typedef int (*dict_cf)(void *k1, void *k2);

/**
 * dict_new - Create a new dict
 *
 * @hash: hash function
 * @cmp: comparing function
 *
 * Return dict_t pointer if success, NULL pointer otherwise.
 */
extern dict_t *dict_new(hash_f hash, dict_cf cmp);

/**
 * dict_free - Destroy a dict
 *
 * @dict: the dict
 */
extern void dict_free(dict_t *dict);

/**
 * dict_add - Add a new key-value pair
 *
 * @dict: the dict
 * @k: the key
 * @v: the value
 *
 * Return 0 if success, -1 otherwise.
 *
 * If given key can be found in dict, this function
 * will update (overlay) the old value by the new given one.
 */
extern int dict_add(dict_t *dict, void *k, void *v);

/**
 * dict_get - Get value by key
 *
 * @dict: the dict
 * @k: the key
 *
 * Return value if key-value pairs exists in dict,
 * NULL otherwise.
 */
extern void *dict_get(dict_t *dict, void *k);

/**
 * dict_pop - Remove key-value pair by given key
 *
 * @dict: the dict
 * @k: the key
 *
 * Return 0 if key-value pair exists and be removed successfully,
 * -1 if key-value doesn't exists.
 */
extern int dict_pop(dict_t *dict, void *k);

#endif /* BULLET_DICT_H */
