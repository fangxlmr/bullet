/*
 * 该自定义库文件实现了 hashmap 功能。
 * 在 hashmap 中，存储键值对。
 * 支持创建、查找、删除、销毁 hashmap 的功能函数
 * 
 */

#ifndef _HASHMAP_H_
#define _HASHMAP_H_

/* 定义求余hash函数中的偏置值。 hash(key) = (key + OFFSET) % M 
 * M 为static。且：M = n, n 为hash表长度
 **/
#define OFFSET 1000
typedef int ElemType;


/* 采用链接发解决冲突问题 */
typedef struct Node     /* Node为链表节点的数据结构 */
{
    ElemType key;
    ElemType value;
    struct Node *next;
}Node, *pNode;


/* Hash表每个槽的数据结构 */
typedef struct Bucket
{
    pNode first;    /* 指向Bucket内链表的第一个节点 */
}Bucket, *HashTable;


/*
 * 创建 n 个槽的Hash表，成功返回hash表的HashTable型指针，并将散列法的模数设置为 n.
 * n < 10时，将 n = 10
 * 不成功程序 打印"hashtable malloc faild,program exit..."
 * 再返回 NULL
 */
HashTable new(int);


/*
 * 在给定Hash表中查找数据
 * 成功返回该键值对的链表地址
 * 失败则返回 NULL
 */
pNode get(HashTable, ElemType);


/*
 * 插入键值对到哈希表
 * 插入成功，返回true
 * hash表不存在，或键值对已存在，返回false
 * 若插入失败，打印"pNew malloc faild,program exit...",再返回false
 */
bool put(HashTable, ElemType, ElemType);


/* 
 * 从哈希表删除数据
 * 成功，则返回true
 * 若给定的hash表不存在，返回false
 */
bool del(HashTable, ElemType);


/*
 * 销毁哈希表
 * 若该 hash 表不存在，返回false
 * 若销毁成功，返回true
 */
void destroy(HashTable, int);

#endif