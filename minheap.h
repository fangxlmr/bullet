/**
 * @file minheap.h
 *
 * @brief 小顶堆（小根堆、最小堆）
 *
 * 小顶堆总是一颗二叉树，且满足以下性质：
 * （1）堆中任意节点的值总是不大于其子节点的值。
 * （2）堆总是一颗完全二叉树。
 */

#ifndef BULLET_MINHEAP_H
#define BULLET_MINHEAP_H

/**
 * 小顶堆
 */
typedef struct _MinHeap MinHeap;

/**
 * 小顶堆的元素类型
 */
typedef void *MinHeapValue;

/**
 * 自定义小顶堆的空指针
 */
#define MINHEAP_NULL ((void *) 0)

/**
 * MinHeapCompareFunc   回调函数，用于节点元素比较大小
 *
 * @param value1        待比较元素1
 * @param value2        待比较元素2
 * @return              若value1  < value2，则返回值小于0，
 *                      若value1 == value2，则返回值等于0，
 *                      若value1  > value2，则返回值大于0。
 */
typedef int (*MinHeapCompareFunc)(MinHeapValue value1, MinHeapValue value2);

/**
 * minheap_new          新建最小堆
 *
 * @param n             最小堆的数组大小
 * @param cmp           节点元素比较函数
 * @return              创建最小堆成功，则返回最小堆，
 *                      若创建失败（内存分配失败），则返回MINHEAP_NULL。
 */
extern MinHeap *minheap_new(unsigned int n, MinHeapCompareFunc cmp);

/**
 * minheap_add          向最小堆添加元素
 *
 * @param minheap       最小堆
 * @param value         待添加元素
 * @return              添加成功，返回非0值，
 *                      若添加失败（内存分配失败），返回0。
 */
extern int minheap_add(MinHeap *minheap, MinHeapValue value);

/**
 * minheap_fin          在最小堆中查找元素
 *
 * @param minheap       最小堆
 * @param value         待查找的元素
 * @return              若最小堆中存在该元素，则返回非0值，
 *                      若不存在，则返回0。
 */
extern int minheap_find(MinHeap *minheap, MinHeapValue value);

/**
 * minheap_del          在最小堆中删除元素
 *
 * @param minheap       最小堆
 * @param value         待删除元素
 * @return              删除成功，返回非0值，
 *                      若不存在该元素，则返回0。
 */
extern int minheap_del(MinHeap *minheap, MinHeapValue value);

/**
 * minheap_pop_root     获取最小堆的堆顶
 *
 * @param minheap       最小堆
 * @return              返回最小堆堆顶，并释放堆顶。
 *                      若堆为空，则返回MINHEAP_NULL。
 */
extern MinHeapValue minheap_pop_root(MinHeap *minheap);

/**
 * minheap_get_root     获取最小堆的堆顶
 *
 * @param minheap       最小堆
 * @return              返回最小堆堆顶，
 *                      若堆为空，则返回MINHEAP_NULL。
 * @note                与minheap_pop_root不同，minheap_get_root
 *                      并不释放堆顶。
 */
extern MinHeapValue minheap_get_root(MinHeap *minheap);

/**
 * minheap_depth        获取堆的深度
 *
 * @param minheap       最小堆
 * @return              返回堆的深度，若为空堆，则返回0。
 */
extern int minheap_depth(MinHeap *minheap);

/**
 * minheap_is_empty     判断是否为空堆
 *
 * @param minheap       最小堆
 * @return              若堆不空，则返回非0值，
 *                      若为空堆，则返回0。
 */
extern int minheap_is_empty(MinHeap *minheap);

/**
 * minheap_is_full      判断堆是否为满
 *
 * @param minheap       最小堆
 * @return              若堆为满，则返回非0值，
 *                      若堆未满，则返回0。
 */
extern int minheap_is_full(MinHeap *minheap);

#endif /* BULLET_MINHEAP_H */
