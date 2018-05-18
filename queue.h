#ifndef BULLET_QUEUE_H
#define BULLET_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

/**
 * @brief 用户自定义队列元素类型
 */
typedef int QueueElemType;

/**
 * @brief 队列结点结构
 *
 * 用户可以根据自己的需要，增加新的数据
 */
typedef struct QueueNode {
    QueueElemType e;
    struct QueueNode *next;
}QueueNode, *pQueueNode;


/**
 * @brief 队列信息，包括头尾结点
 *
 * 这实际上是对外的接口，引用队列时，都使用 pQueue
 * 用户可以根据自己的需要，增加新的数据
 */
typedef struct Queue {
    pQueueNode front, rear;
}Queue, *pQueue;

/**
 * @brief 生成队列并初始化
 */
extern pQueue queue_create (void);

/**
 * @brief 入队操作
 * @param queue 队列指针
 * @param e     入队元素
 *
 * 入队，是将元素链接到尾结点后
 */
extern void queue_push (pQueue queue, QueueElemType e);

/**
 * @brief 出队操作
 * @param queue 队列指针
 * @return 空队列，返回null。队列不空，返回队头元素
 */
extern void queue_pop (pQueue queue);

/**
 * @brief 销毁队列
 * @param queue 队列指针
 */
extern void queue_destroy (pQueue queue);

/**
 * @brief 清空队列
 * @param queue 指针队列
 */
extern void queue_clear (pQueue queue);

/**
 * @brief 判断队列是否为空
 * @return 空队列返回0.
 */
extern bool queue_empty (pQueue queue);

/**
 * @brief 求队列的长度
 * @param queue
 * @return 空队列返回0。
 */
extern size_t queue_size (pQueue queue);

/**
 * @brief 获取队列头
 */
extern QueueElemType queue_front (pQueue queue);

#endif /* BULLET_QUEUE_H */
