/*
 * 哈希表的代码实现
 * 
 * hashmap库通过拉链法处理哈希冲突。
 * 使用hash_func返回的哈希码，通过除以哈希表长度求余来计算哈希值。
 * 
 * 哈希表可以动态扩容。
 * 当元素充满哈希表超过内部定义的装填因子时，
 * 哈希表将自动扩容。
 */

#include <stdlib.h>
#include "hashmap.h"
#define LOAD_FACTOR 0.75    /* 装填因子 */

/*
 * 哈希表的元素
 */
typedef struct _HashMapEntry HashMapEntry;

struct _HashMapEntry {
    /*
     * HashMapPair为哈希表的键值对，
     * 定义在hashmap.h中，如下：
     *
     * typedef _HashMapPair {
     *      HashMapKey   key;
     *      HashMapValue value;
     * } HashMapPair;
     */
    HashMapPair  pair;
    HashMapEntry *next;
};

/*
 * 哈希表
 */
struct _HashMap {
    HashMapEntry        **buckets;     /* 桶数组 */
    unsigned int        size;          /* 桶数组长度（桶长度） */
    HashMapHashFunc     hash_func;     /* 哈希函数 */
    HashMapEqualFunc    equal_func;    /* 键码比较函数 */
    unsigned int        count;         /* 哈希表内的键值对数量 */

    unsigned int        index;         /* 哈希表使用的桶长度 */
                                       /* 在哈希质数表中的位置 */
};

/*
 * 常用哈希质数表
 * 来自：http://planetmath.org/goodhashtableprimes
 */
static const unsigned int primes[] = {
    193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157,
    98317, 196613, 393241, 786433, 1572869, 3145739,
    6291469, 12582917, 25165843, 50331653, 100663319,
    201326611, 402653189, 805306457, 1610612741,
};
static const unsigned int primes_size
        = sizeof(primes) / sizeof(primes[0]);

/**
 * hashmap_alloc_buckets    请求分配桶数组的内存
 *
 * @param hashmap           哈希表
 * @return                  分配成功，返回非0值，
 *                          失败，则返回0。
 */
static int hashmap_alloc_buckets(HashMap *hashmap)
{
    unsigned int new_size;

    /*
     * 判断桶长度。
     *
     * 如果哈希表中的index索引不超过哈希质数表的长度，
     * 则桶长度为哈希质数表中的值。
     *
     * 否则，表明哈希质数表内的质数已经耗尽，
     * 将当前桶长度扩大10倍。
     */
    if (hashmap->index < primes_size) {
        new_size = primes[hashmap->index];
    } else {
        new_size = hashmap->count * 10;
    }

    /*
     * 给桶分配内存
     */
    hashmap->size = new_size;
    hashmap->buckets = calloc(new_size, sizeof(HashMapEntry *));

    /*
     * 分配成功，返回1，
     * 否则，返回0。
     */
    return hashmap->buckets != NULL;
}

HashMap *hashmap_new(HashMapHashFunc  hash_func,
                     HashMapEqualFunc equal_func)
{
    HashMap *hashmap;

    /*
     * 建立哈希表
     */
    hashmap = (HashMap *) malloc(sizeof(HashMap));

    if (!hashmap) {
        return HASHMAP_NULL;
    }

    hashmap->hash_func  = hash_func;
    hashmap->equal_func = equal_func;
    hashmap->count = 0;
    hashmap->index = 0;     /* 初始的哈希表长度为哈希质数表中的第一个值 */
    /*
     * 给桶分配内存
     */
    if (!hashmap_alloc_buckets(hashmap)) {
        /* 分配失败 */
        free(hashmap);

        return HASHMAP_NULL;
    }
    /* 分配成功，则返回哈希表 */
    return hashmap;
}

void hashmap_free(HashMap *hashmap)
{
    HashMapEntry *walk;
    HashMapEntry *delete;

    for (int i = 0; i < hashmap->size; ++i) {
        walk = hashmap->buckets[i];

        /*
         * 释放桶中的所有链表
         */
        while (walk != NULL) {
            delete = walk;
            walk  = walk->next;

            free(delete);
        }
    }

    /*
     * 释放桶数组
     */
    free(hashmap->buckets);
    /*
     * 释放哈希表
     */
    free(hashmap);
}

/**
 * hashmap_resize       哈希表扩容函数
 *
 * @param hashmap       哈希表
 * @return              扩容成功，则返回非0值，
 *                      失败则返回0。
 */
static int hashmap_resize(HashMap *hashmap)
{
    HashMapEntry **old_buckets;
    unsigned int old_size;
    unsigned int old_index;
    HashMapEntry *walk;
    HashMapEntry *next;
    HashMapPair  *pair;
    unsigned int i;

    /*
     * 保存旧哈希表的重要信息
     */
    old_buckets = hashmap->buckets;
    old_size    = hashmap->size;
    old_index   = hashmap->index;

    /*
     * 更新哈希表
     */
    ++hashmap->index;
    if (!hashmap_alloc_buckets(hashmap)) {
        /*
         * 扩容失败，恢复现场
         */
        hashmap->buckets = old_buckets;
        hashmap->size    = old_size;
        hashmap->index   = old_index;
        return 0;
    }

    /*
     * 将旧哈希表的链表链接到新哈希表中
     */
    for (int j = 0; j < old_size; ++j) {
        walk = old_buckets[j];

        while (walk != NULL) {
            pair = &(walk->pair);
            /*
             * 每个键值对计算
             * 新哈希表的哈希值
             */
            i = hashmap->hash_func(pair->key) % hashmap->size;
            /*
             * 将节点链接到新的哈希表
             */
            next = walk->next;
            walk->next = hashmap->buckets[i];
            hashmap->buckets[i] = walk;
            /*
             * 继续下一个查找
             */
            walk = next;
        }
    }

    free(old_buckets);
    return 1;
}

int hashmap_put(HashMap      *hashmap,
                HashMapKey   key,
                HashMapValue value)
{
    HashMapEntry *new_entry;
    HashMapEntry *walk;
    HashMapPair  *pair;
    unsigned int i;
    
    /*
     * 判断当前哈希表内的键值对数量是否超过装填因子限制
     */
    if (hashmap->count > hashmap->size * LOAD_FACTOR) {
        /* 超过装填因子限制，自动扩容 */
        if (!hashmap_resize(hashmap)) {
            return 0;           /* 扩容失败 */
        }
    }
    
    /*
     * 生成哈希值，查找哈希表
     */
    i = hashmap->hash_func(key) % hashmap->size;
    walk = hashmap->buckets[i];

    while (walk != NULL) {
        pair = &(walk->pair);

        /*
         * 查找输入的key与哈希表中的键值对，
         * 若匹配，则更新原有键值对。
         */
        if (hashmap->equal_func(pair->key, key) != 0) {
            pair->key   = key;
            pair->value = value;

            return 1;
        }
        walk = walk->next;
    }

    /*
     * 该键值对不存在，则新建键值对，并插入哈希表
     */
    new_entry = (HashMapEntry *) malloc(sizeof(HashMapEntry));

    if (!new_entry) {
        return 0;
    }
    new_entry->pair.key   = key;
    new_entry->pair.value = value;

    /*
     * 新键值对插入哈希表
     */
    new_entry->next = hashmap->buckets[i];
    hashmap->buckets[i] = new_entry;
    /*
     * 维持哈希表的键值对总数
     */
    ++hashmap->count;

    return 1;
}

HashMapValue hashmap_get(HashMap *hashmap, HashMapKey key)
{
    unsigned int i;
    HashMapEntry *walk;

    /*
     * 计算哈希值
     */
    i = hashmap->hash_func(key) % hashmap->size;
    walk = hashmap->buckets[i];

    /*
     * 查找匹配的键值对
     */
    while (walk != NULL) {
        if (hashmap->equal_func(walk->pair.key, key) != 0) {
            return walk->pair.value;    /* 匹配 */
        }
        walk = walk->next;
    }

    /*
     * 没有匹配键值对，返回HASHMAP_NULL。
     */
    return HASHMAP_NULL;
}

int hashmap_del(HashMap *hashmap, HashMapKey key)
{
    HashMapEntry **walk;
    HashMapEntry *delete;
    HashMapPair  *pair;
    unsigned int i;

    /*
     * 计算哈希值
     */
    i = hashmap->hash_func(key) % hashmap->size;
    walk = &(hashmap->buckets[i]);

    /*
     * 查找匹配的键值对，并删除之
     */
    while (*walk != NULL) {
        pair = &((*walk)->pair);

        if (hashmap->equal_func(pair->key, key) != 0) {
            /*
             * 匹配，删除结点
             */
            delete = *walk;
            *walk = delete->next;
            free(delete);

            /*
             * 维持哈希表内键值对总数
             */
            --hashmap->count;

            return 1;
        }

        walk = &(*walk)->next;
    }

    /*
     * 没有匹配的键值对，无法删除。
     */
    return 0;
}