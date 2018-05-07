#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashmap.h"

static int M = 0;  /* 求余散列法的模数 */

/* 散列函数hash(key) */
static int hash(ElemType);

/* 判断素数 */
static bool isprime(int);

/* 取模数为不大于表长n的最大素数 */
static int set_module(int n);


/* 散列函数hash(key) */
static int hash(ElemType key)
{
    return (key + OFFSET) % M;
}


/* 判断素数 */
static bool isprime(int n)
{
    int i;  
    for (i = 2; i * i <= n; ++i) {  
        if (n % i == 0)
            return false;  
    }  
    return true; 
}


/* 取模数为不大于表长n的最大素数 */
static int set_module(int n)    
{
    while(--n)
    {
        if(isprime(n))
            break;
        else
            continue;
    }
    return n;
}



/* 创建n个槽的哈希表 */
HashTable new(int n)
{
    if(n < 10)  /* 保证hash表长度至少为10 */
        n = 10;
    int i;
    HashTable hashtable = (HashTable) malloc(n*sizeof(Bucket));
    if(!hashtable)
    {
        printf("hashtable malloc faild,program exit...");
        return NULL;
    }
    /* 将哈希表置空 */
    for(i=0;i<n;i++)
        hashtable[i].first = NULL;
    
    M = set_module(n);    /* 将模数选取为不大于表长n 的最大素数 */
    return hashtable;
}


/*
 * 在哈希表中查找 key - value对
 * 查找成功，返回在哈希表中的位置
 * 查找不成功，返回NULL
*/
pNode get(HashTable hashtable, ElemType key)
{
    if(!hashtable)     /* 该hash 表不存在，返回NULL */
        return NULL;
    pNode pCur = hashtable[hash(key)].first;
    /* 需要判断key，相等，找到了匹配值 */
    while(pCur && pCur->key != key)
        pCur = pCur->next;
    return pCur;

}


/*
 * 在哈希表中插入key
 * 如果key存在，返回false
 * 如果不存在，则插入对应链表的最后并返回ture
 *  
 */
bool put(HashTable hashtable, ElemType key, ElemType value)
{
    if(!hashtable)     /* 该hash 表不存在，返回NULL */
        return false;

    pNode pCur = hashtable[hash(key)].first;
    pNode pPre = pCur;  /* 链表的末位，初始值与pCur相同 */
    /* 需要判断key相等，查看是否存在key值 */
    while(pCur && pCur->key != key){
        pPre = pCur;    /* 新结点的预备插入点 */
        pCur = pCur->next;
    }

    if(pCur != NULL)    /* 如果key已经存在，不需要再次插入，返回false */
        return false;
    /* 否则，key不存在，为新结点分配空间 */
    pNode pNew = (pNode) malloc(sizeof(Node));
    if(!pNew)
    {
        printf("pNew malloc faild,program exit...");
        exit(-1);
    }
    pNew->key = key;
    pNew->value = value;
    pNew->next = NULL;

      /* 将新结点插入到链表最后 */
    if(hashtable[hash(key)].first == NULL)  /* 当插入点为第一个点的情况 */
        hashtable[hash(key)].first = pNew;
    else
        pPre->next = pNew;  /* 插入点为第 n 点 (n>1) 的情况 */
    return true;
}


/*
 * 从哈希表中删除数据
 * 如果key不存在，则返回false
 * 若key存在，则删除key，且返回true
 */

bool del(HashTable hashtable, ElemType key)
{
    if(!hashtable)     /* 该hash 表不存在，返回false */
        return false;

    pNode pCur = hashtable[hash(key)].first;   /* 当前结点 */
    pNode pPre = pCur;   /* 存储被删结点的前一个结点，初始值与pCur相同 */

    if(pCur->key == key){    /* 被删结点是第一个结点 */
        hashtable[hash(key)].first = pCur->next;
    }
    else{   /* 被删结点不是第一个结点 */
        while(pCur && pCur->key != key){
            pPre = pCur;
            pCur = pCur->next;
        }
        pPre->next = pCur->next;
    }
    free(pCur);
    pCur = NULL;
    return true;
}


/* 销毁槽数为 n 的哈希表 */
void destroy(HashTable hashtable, int n)
{
    if(!hashtable)     /* 该hash 表不存在，不需要删除 */
        return;

    int i;
    /* 先逐个链表释放 */
    for(i=0; i<n; ++i)
    {
        pNode pCur = hashtable[i].first;
        pNode pDel = NULL;
        while(pCur)
        {
            pDel = pCur;
            pCur = pCur->next;
            free(pDel);
            pDel = NULL;
        }
    }
    /* 最后释放哈希表 */
    free(hashtable);
    hashtable = NULL;
    return;
}