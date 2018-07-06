/**
 * @file maxheap.h
 *
 * @brief 大顶堆（大根堆、最大堆）
 *
 * 大顶堆总是一颗二叉树，且满足以下性质：
 * （1）堆中任意节点的值总是不小于其子节点的值。
 * （2）堆总是一颗完全二叉树。
 */

#ifndef BULLET_MAXHEAP_H
#define BULLET_MAXHEAP_H

/**
 * 大顶堆
 */
typedef struct _MaxHeap MaxHeap;

/**
 * 大顶堆的元素类型
 */
typedef void *MaxHeapValue;

/**
 * 自定义大顶堆的空指针
 */
#define MAXHEAP_NULL ((void *) 0)

/**
 * MaxHeapCompareFunc   回调函数，用于节点元素比较大小
 *
 * @param value1        待比较元素1
 * @param value2        待比较元素2
 * @return              若value1  < value2，则返回值小于0，
 *                      若value1 == value2，则返回值等于0，
 *                      若value1  > value2，则返回值大于0。
 */
typedef int (*MaxHeapCompareFunc)(MaxHeapValue value1, MaxHeapValue value2);

/**
 * maxheap_new          新建最大堆
 *
 * @param n             最大堆的数组大小
 * @param cmp           节点元素比较函数
 * @return              创建最大堆成功，则返回最大堆，
 *                      若创建失败（内存分配失败），则返回MAXHEAP_NULL。
 */
extern MaxHeap *maxheap_new(unsigned int n, MaxHeapCompareFunc cmp);

/**
 * maxheap_add          向最大堆添加元素
 *
 * @param maxheap       最大堆
 * @param value         待添加元素
 * @return              添加成功，返回非0值，
 *                      若添加失败，返回0。
 * @note                插入失败的可能原因为：当最大堆已满，且value值小于堆顶。
 */
extern int maxheap_add(MaxHeap *maxheap, MaxHeapValue value);

/**
 * maxheap_find         在最大堆中查找元素
 *
 * @param maxheap       最大堆
 * @param value         待查找的元素
 * @return              若最大堆中存在该元素，则返回非0值，
 *                      若不存在，则返回0。
 */
extern int maxheap_find(MaxHeap *maxheap, MaxHeapValue value);

/**
 * maxheap_del          在最大堆中删除元素
 *
 * @param maxheap       最大堆
 * @param value         待删除元素
 * @return              删除成功，返回非0值，
 *                      若不存在该元素，则返回0。
 */
extern int maxheap_del(MaxHeap *maxheap, MaxHeapValue value);

/**
 * maxheap_pop_root     获取最大堆的堆顶
 *
 * @param maxheap       最大堆
 * @return              返回最大堆堆顶，并释放堆顶。
 *                      若堆为空，则返回MAXHEAP_NULL。
 */
extern MaxHeapValue maxheap_pop_root(MaxHeap *maxheap);

/**
 * maxheap_get_root     获取最大堆的堆顶
 *
 * @param maxheap       最大堆
 * @return              返回最大堆堆顶，
 *                      若堆为空，则返回MAXHEAP_NULL。
 * @note                与maxheap_pop_root不同，maxheap_get_root
 *                      并不释放堆顶。
 */
extern MaxHeapValue maxheap_get_root(MaxHeap *maxheap);

/**
 * maxheap_depth        获取堆的深度
 *
 * @param maxheap       最大堆
 * @return              返回堆的深度，若为空堆，则返回0。
 */
extern int maxheap_depth(MaxHeap *maxheap);

/**
 * maxheap_is_empty     判断是否为空堆
 *
 * @param maxheap       最大堆
 * @return              若堆不空，则返回非0值，
 *                      若为空堆，则返回0。
 */
extern int maxheap_is_empty(MaxHeap *maxheap);

/**
 * maxheap_is_full      判断堆是否为满
 *
 * @param maxheap       最大堆
 * @return              若堆为满，则返回非0值，
 *                      若堆未满，则返回0。
 */
extern int maxheap_is_full(MaxHeap *maxheap);

#endif /* BULLET_MAXHEAP_H */
