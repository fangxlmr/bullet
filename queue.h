/**
 * @file    queue.h
 *
 * @brief   队列(queue)
 *
 * 队列是一种数据结构，遵循先进先出(FIFO)的原则。
 *
 * 使用queue_new创建新队列，使用queue_free销毁队列。
 *
 * 使用queue_push将元素入队尾，使用queue_pop弹出队头元素。
 *
 * 使用queue_get_head获取队头元素，使用queue_get_tail获取队尾元素，
 * 注意，queue_get_head与queue_get_tail并不释放元素。
 *
 * 使用queue_is_empty判断队列是否为空。
 */

#ifndef BULLET_QUEUE_H
#define BULLET_QUEUE_H

/**
 * 单向队列
 */
typedef struct _Queue Queue;

/**
 * 队列元素类型
 */
typedef void *QueueValue;

/**
 * 队列内部空指针
 */
#define QUEUE_NULL ((void *) 0)

/**
 * queue_new        新建队列，并初始化
 *
 * @return          新建队列成功，返回新队列地址。
 *                  否则，返回QUEUE_NULL。
 */
extern Queue *queue_new(void);

/**
 * queue_free       释放队列
 *
 * @param queue     待销毁队列
 */
extern void queue_free(Queue *queue);

/**
 * queue_push       入队
 *
 * @param queue     队列
 * @param data      待入队元素
 * @return          元素入队成功，返回非0值，
 *                  失败（内存分配失败），返回0。
 */
extern int queue_push(Queue *queue, QueueValue data);

/**
 * queue_pop        出队
 *
 * @param queue     队列
 * @return          若队列不空，则返回队头元素，
 *                  若队列为空，则返回QUEUE_NULL。
 */
extern QueueValue queue_pop(Queue *queue);

/**
 * queue_get_head   获取队头元素
 *
 * @param queue     队列
 * @return          队列不空，返回队头元素，
 *                  若为空队列，则返回QUEUE_NULL。
 */
extern QueueValue queue_get_head(Queue *queue);

/**
 * queue_get_tail   获取队尾元素
 * @param queue     队列
 * @return          队列不空，则返回队尾元素，
 *                  若为空队列，则返回QUEUE_NULL。
 */
extern QueueValue queue_get_tail(Queue *queue);

/**
 * queue_empty      判断队列是否为空
 *
 * @param queue     队列
 * @return          空队列，返回非0值。
 *                  队列不空，则返回0。
 */
extern int queue_is_empty(Queue *queue);

#endif /* BULLET_QUEUE_H */