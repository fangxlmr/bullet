/**
 * dict.h
 *
 */

#ifndef BULLET_HASHMAP_H
#define BULLET_HASHMAP_H

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
 * dict_cf - Hashmap comparing function (call back function)
 *
 * @k1: key1
 * @k2: key2
 *
 * Return values depends on the two keys:
 * k1 < k2, return -1.
 * k1 = k2, return  0.
 * k1 > k2, return  1.
 */
typedef int (*dict_cf)(void *key1, void *key2);

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
 * hashap_free - Destroy a dict
 *
 * @dict: the dict
 */
extern void dict_free(dict_t *dict);

/**
 * dict_put          将键值对插入或修改已存在的键值对
 *
 * @dict: the dict
 * @key           键
 * @value         键对应的值
 * @return              插入或修改成功，则返回非0值，
 *                      失败（主要是内存分配失败），则返回0。
 */
extern int dict_put(dict_t *dict,
                       void *  key,
                       void *value);

/**
 * dict_get          获取键所对应的值
 *
 * @dict: the dict
 * @key           键
 * @return              若键值对存在，则返回键所对应的值，
 *                      若键值对不存在，则返回HASHMAP_NULL。
 */
extern void *dict_get(dict_t *dict,
                                void *key);

/**
 * dict_del          删除键值对
 *
 * @dict: the dict
 * @key           键
 * @return              键值对存在，并删除成功，则返回非0值，
 *                      若键值对不存在，则返回0。
 */
extern int dict_del(dict_t *dict, void *key);

#endif /* BULLET_HASHMAP_H */
