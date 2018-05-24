#ifndef BULLET_QUEUE_H
#define BULLET_QUEUE_H

#define T Queue_T
typedef struct T *T;

/* 新建队列，并初始化 */
extern T queue_new (void);

/* 判断队列是否为空 */
extern int queue_empty (T que);

/* 队列长度 */
extern int queue_size (T que);

/* 元素入队 */
extern void enqueue (T que, void *x);

/* 元素出队 */
extern void *dequeue (T que);

/* 释放队列，并置NULL */
extern void queue_free (T *que);

#undef T
#endif /* BULLET_QUEUE_H */