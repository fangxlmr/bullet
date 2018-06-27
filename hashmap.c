/*
 * 哈希表的代码实现
 */

#include <stdlib.h>
#include "hashmap.h"

/*
 * 哈希表的元素
 */
typedef struct _HashMapEntry HashMapEntry;

struct _HashMapEntry {
    /*
     * HashMapPair为哈希表的键值对，
     * 定义在hashmap.h中。
     */
    HashMapPair  pair;
    HashMapEntry *next;
};

/*
 * 哈希表结构
 */
struct _HashMap {
    HashMapEntry        **table;       /* 哈希表元素的数组 */
    unsigned int        table_size;    /* 哈希表的大小 */
    HashMapHashFunc     hash_func;     /* 哈希函数 */
    HashMapEqualFunc    equal_func;    /* 键比较函数 */
    unsigned int        count;         /* 哈希表内的键值对数量 */

};

HashMap *hashmap_new(HashMapHashFunc  hash_fun,
                     HashMapEqualFunc equal_func)
{
}

void hashmap_free(HashMap *hashmap)
{

}

int hashmap_put(HashMap      *hashmap,
                HashMapKey   key,
                HashMapValue value)
{

}

HashMapValue hashmap_get(HashMap *hashmap, HashMapKey key)
{

}

int hashmap_del(HashMap *hashmap, HashMapKey key)
{

}