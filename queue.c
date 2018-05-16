#include "queue.h"

/**
 * @brief 判断队列是否为 null
 * @param queue 待检测队列
 */
static void isnull (pQueue queue) {
    if (!queue) {
        printf("Queue of null is used.\n"
               "Program exits with code -1.");
    }
}


/**
 * @brief 新建队列，并初始化
 * @return 成功则返回队列指针，失败则返回nll
 *
 * 队列头尾指针保存在结构体 queue中，并且，队列含有一个头结点
 */
pQueue queue_create (void) {
    pQueueNode q = (pQueueNode) malloc(sizeof(QueueNode));
    if (!q) {
        return NULL;
    }
    memset(q, 0, sizeof(QueueNode));
    pQueue queue = (pQueue) malloc(sizeof(Queue));
    if (!queue) {
        return NULL;
    }
    queue->front = queue->rear = q;
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
    isnull(queue);
    pQueueNode q = (pQueueNode) malloc(sizeof(QueueNode));
    if (!q){
        return false;
    }
    q->e = e;
    q->next = NULL;
    queue->rear->next = q;
    queue->rear = q;
}


/**
 * @brief 出队操作
 * @param queue 队列指针
 * @return 空队列，返回null。队列不空，返回队头元素
 */
QueueElemType queue_pop (pQueue queue) {
    isnull(queue);
    pQueueNode head;
    if (queue->front->next == queue->rear) {
        /*
         * 队列只有一个元素
         */
        head = queue->rear;
        queue->rear = queue->front;
        queue->front->next = NULL;
    } else {
        /*
         * 队列有2个及以上的元素
         */
        head  = queue->front->next;
        queue->front->next = head->next;
    }
    return head->e;
}


/**
 * @brief 清空队列
 * @param queue 指针队列
 * @return
 */
void queue_clear (pQueue queue) {
    isnull(queue);

    /*
     * 队列为 null 或已经为空队列
     */
    if (queue->front == queue->rear) {
        return;
    }

    /*
     * 队列不空，则清空队列
     */
    pQueueNode q;
    while (queue->front->next) {
        q = queue->front->next;
        queue->front->next = q->next;
        free(q);
    }
    queue->rear = queue->front;
    queue->front->next = NULL;
}


/**
 * @brief 销毁队列
 * @param queue 队列指针
 */
void queue_destroy (pQueue queue) {
    isnull(queue);
    queue_clear(queue);
    free(queue);
    queue = NULL;
}

/**
 * @brief 判断队列是否为空
 */
bool queue_isempty (pQueue queue) {
    isnull(queue);
    return (queue->front == queue->rear) ? true : false;
}

/**
 * @brief 获取队列头
 * @param queue
 * @return
 */
QueueElemType queue_get_head (pQueue queue) {
    isnull(queue);
    if (!queue_isempty(queue)) {
        return queue->front->next->e;
    } else {
        printf("Warning: Queue is empty. NULL was returned.\n");
        return NULL;
    }
}