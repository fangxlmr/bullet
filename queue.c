#include "queue.h"

/**
 * @brief 新建队列，并初始化
 * @return 成功则返回队列指针，失败则返回nll
 *
 * 队列头尾指针保存在结构体 queue中
 */
pQueue queue_create (void) {
    pQueue queue = (pQueue) malloc(sizeof(Queue));
    if (!queue) {
        return NULL;
    }
    queue->front = queue->rear = NULL;
    return queue;
}


/**
 * @brief 入队操作
 * @param queue 队列指针
 * @param e     入队元素
 *
 * 入队，是将元素链接到尾结点后
 */
void queue_push (pQueue queue, QueueElemType e) {
    pQueueNode q = (pQueueNode) malloc(sizeof(QueueNode));
    if (!q){
        return;
    }
    q->e = e;
    q->next = NULL;
    if (!queue->front) {    /* 空队列 */
        queue->front = queue->rear = q;
    } else {         /* 队列非空 */
        queue->rear->next = q;
        queue->rear = q;
    }
}


/**
 * @brief 出队操作
 * @param queue 队列指针
 */
void queue_pop (pQueue queue) {
    pQueueNode node;
    if (queue->front == queue->rear) {
         /* 队列只有一个元素 */
        node = queue->rear;
        queue->rear = queue->front = NULL;
    } else {
        /* 队列有2个及以上的元素 */
        node  = queue->front;
        queue->front = node->next;
    }
    free(node);
}


/**
 * @brief 清空队列
 * @param queue 指针队列
 */
void queue_clear (pQueue queue) {
    /* 队列已经为空队列 */
    if (!queue->front) {
        return;
    }

    /* 队列不空，则清空队列 */
    pQueueNode q;
    while (!queue->front) {
        q = queue->front;
        queue->front = q->next;
        free(q);
    }
    queue->rear = queue->front = NULL;
}


/**
 * @brief 销毁队列
 */
void queue_destroy (pQueue queue) {
    queue_clear(queue);
    free(queue);
    queue = NULL;
}

/**
 * @brief 判断队列是否为空
 */
bool queue_empty (pQueue queue) {
    return (!queue->front) ? true : false;
}

/**
 * @brief 获取队列头
 */
QueueElemType queue_front (pQueue queue) {
    if (!queue_empty(queue)) {
        return queue->front->e;
    } else {
        printf("Warning: Queue is empty. NULL was returned.\n");
        return NULL;
    }
}


/**
 * @brief 查找队列长度
 */
size_t queue_size (pQueue queue) {
    size_t size = 0;
    if (!queue_empty(queue)) {
        pQueueNode walk = queue->front;
        while (walk) {
            ++size;
            walk = walk->next;
        }
    }
    return size;
}