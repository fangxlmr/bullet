/**
 * @file    hashmap.h
 *
 * @brief   哈希表
 *
 * 哈希表是一种数据结构，也较散列表，其访问效率很高。
 *
 * 哈希表根据关键码值(Key value)而直接进行访问的数据结构。
 * 它通过把关键码值映射到表中一个位置来访问记录，以加快查找的速度。
 *
 * 使用HashMapHashFunc函数类型来自定义哈希回调函数，
 * 使用HashMapEqualFunc函数类型来定义键比较函数。
 *
 * 使用hashmap_new创建新的哈希表，而使用hashmap_free销毁已存在的哈希表。
 *
 * 使用hashmap_put插入键值对，使用hashmap_get获取键所对应值，
 * 而使用hashmap_del删除键值对。
 */

#ifndef BULLET_HASHMAP_H
#define BULLET_HASHMAP_H

/**
 * 哈希表
 */
typedef struct _HashMap HashMap;

/**
 * 哈希表的键
 */
typedef void *HashMapKey;

/**
 * 哈希表的键对应的值
 */
typedef void *HashMapValue;

/**
 * 哈希表键值对内部结构
 */
typedef struct _HashMapPair {
    HashMapKey key;
    HashMapValue value;
} HashMapPair;

/**
 * 定义哈希表的空指针
 */
#define HASHMAP_NULL ((void *) 0)

/**
 * HashMapHashFunc      定义回调函数，哈希函数
 *
 * @param key           键值
 * @return              返回key对应的hash值
 */
typedef unsigned int (*HashMapHashFunc)(HashMapKey key);

/**
 * HashMapEqualFunc     定义回调函数，比较两个键值
 *
 * @param key1          键值1
 * @param key2          键值2
 * @return              若key1 == key2，返回非0值，
 *                      若key1 != key2，返回0。
 */
typedef int (*HashMapEqualFunc)(HashMapKey key1, HashMapKey key2);

/**
 * hashmap_new          创建哈希表
 *
 * @param hash_func     哈希函数
 * @param equal_func    判断键值是否相等的比较函数
 * @return              创建成功，则返回哈希表指针，
 *                      失败，则返回HASHMAP_NULL。
 */
extern HashMap *hashmap_new(HashMapHashFunc  hash_func,
                            HashMapEqualFunc equal_func);

/**
 * hashap_free          销毁哈希表
 *
 * @param               待销毁的哈希表
 */
extern void hashmap_free(HashMap *hashmap);

/**
 * hashmap_put          将键值对插入或修改已存在的键值对
 *
 * @param hashmap       哈希表
 * @param key           键
 * @param value         键对应的值
 * @return              插入或修改成功，则返回非0值，
 *                      失败（主要是内存分配失败），则返回0。
 */
extern int hashmap_put(HashMap      *hashmap,
                       HashMapKey   key,
                       HashMapValue value);

/**
 * hashmap_get          获取键所对应的值
 *
 * @param hashmap       哈希表
 * @param key           键
 * @return              若键值对存在，则返回键所对应的值，
 *                      若键值对不存在，则返回HASHMAP_NULL。
 */
extern HashMapValue hashmap_get(HashMap    *hashmap,
                                HashMapKey key);

/**
 * hashmap_del          删除键值对
 *
 * @param hashmap       哈希表
 * @param key           键
 * @return              键值对存在，并删除成功，则返回非0值，
 *                      若键值对不存在，则返回0。
 */
extern int hashmap_del(HashMap *hashmap, HashMapKey key);

#endif /* BULLET_HASHMAP_H */
