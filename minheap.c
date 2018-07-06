/*
 * 最小堆(minheap)的代码实现。
 * 使用数组存储最小堆。
 */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "minheap.h"

struct _MinHeap {
    MinHeapValue *array;        /* 堆数组 */
    unsigned int free;          /* 数组未使用的长度 */
    unsigned int used;          /* 数组已使用的长度 */
    MinHeapCompareFunc cmp;
};

/**
 * swap             交换数组内元素
 *
 * @param v         数组
 * @param x         坐标x
 * @param y         坐标y
 */
static void swap(MinHeapValue *v, int x, int y)
{
    MinHeapValue temp;

    temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

/**
 * shiftdown        元素下沉函数
 *
 * @param minheap   最小堆
 * @param n         最小堆的总大小，即数组的有效长度
 * @param i         待下沉的元素下标
 */
static void shiftdown(MinHeap *minheap, int i)
{
    int t;
    int n;                      /* 堆数组长度 */
    MinHeapValue *h;            /* 堆数组 */
    int ileft, iright;          /* i的左、右孩子的坐标 */
    MinHeapCompareFunc cmp;     /* 比较函数 */

    n = minheap->used;
    h = minheap->array;
    ileft  = 2 * i + 1;
    iright = 2 * i + 2;
    cmp = minheap->cmp;

    /* 至少存在一个左孩子节点 */
    while (ileft < n) {
        /*
         * 与左孩子比较，取较小值
         */
        if (cmp(h[i], h[ileft]) > 0) {
            t = ileft;
        } else {
            t = i;
        }
        /*
         * 如果存在右孩子，则与右孩子比较，
         * 取较小值
         */
        if (iright < n && cmp(h[t], h[iright]) > 0) {
            t = iright;
        }

        /* 判断是否满足最小堆特性 */
        if (t != i) {
            /* 不满足最小堆特性，交换元素 */
            swap(h, t, i);

            /* 继续下沉操作 */
            i = t;
            ileft  = 2 * i + 1;
            iright = 2 * i + 2;

            /* 已满足最小堆，不需要继续下沉 */
        } else {
            break;
        }
    }
}

/**
 * shiftup          元素上浮函数
 *
 * @param minheap   最小堆
 * @param n         最小堆的总大小，即数组的有效长度
 * @param i         待上浮的元素下标
 */
static void shiftup(MinHeap *minheap, int i)
{
    int n;                  /* 堆数组长度 */
    MinHeapValue *h;        /* 堆数组 */
    int parent;             /* i的父节点坐标 */
    MinHeapCompareFunc cmp; /* 比较函数 */

    n = minheap->used;
    h = minheap->array;
    parent = (int) floor((i - 1) / 2.0);
    cmp = minheap->cmp;

    /* 下标不得超过堆数组长度 */
    if (i >= n) {
        return;
    }

    /* 存在父节点 */
    while (parent >= 0) {
        /*
         * 与父节点比较大小,
         * 当不满足最小堆特性时，
         * 交换父子节点元素。
         */
        if (cmp(h[i], h[parent]) < 0) {
            swap(h, i, parent);

            /* 继续上浮操作 */
            i = parent;
            parent = (int) floor((i - 1) / 2.0);

            /* 已满足最小堆特性 */
        } else {
            break;
        }
    }
}

MinHeap *minheap_new(unsigned int n, MinHeapCompareFunc cmp)
{
    MinHeapValue *array;
    MinHeap *minheap;

    minheap = (MinHeap *) malloc(sizeof(MinHeap));
    if (!minheap) {
        return NULL;
    } else {
        minheap->cmp  = cmp;
        minheap->free = n;
        minheap->used = 0;
    }

    array = malloc(n * sizeof(MinHeapValue));
    if (!array) {
        free(minheap);
        return NULL;
    } else {
        memset(array, 0, n * sizeof(MinHeapValue));
        minheap->array = array;
    }

    return minheap;
}

int minheap_add(MinHeap *minheap, MinHeapValue value) {
    MinHeapCompareFunc cmp;

    cmp = minheap->cmp;

    if (minheap->free == 0) {
        /*
         * 堆已满。
         * （1）value值大于堆顶，则替代堆顶，
         * 并执行shiftdown函数，使之下沉到合适位置，
         * 继续满足最小堆特性。且返回1。
         */
        if (cmp(value, minheap->array[0]) > 0) {
            minheap->array[0] = value;
            shiftdown(minheap, 0);      /* 下沉堆顶元素 */
            return 1;
            /*
             * （2）value值小于堆顶，忽略之，并返回0表示插入失败。
             */
        } else {
            return 0;
        }
    } else {
        /* 堆未满 */
        minheap->array[minheap->used] = value;

        /* 维持最小堆的结构信息 */
        ++minheap->used;
        --minheap->free;

        shiftup(minheap, minheap->used - 1);        /* 上浮新元素 */

        return 1;
    }
}

int minheap_find(MinHeap *minheap, MinHeapValue value) {
    MinHeapValue *h;
    MinHeapCompareFunc cmp;

    h = minheap->array;
    cmp = minheap->cmp;

    /* 空堆，不存在 */
    if (minheap_is_empty(minheap)) {
        return 0;
        /*
         * 堆不空，但value比小顶堆的堆顶还小，
         * 则堆内部也不可能存在值相同的元素。
         */
    } else if (cmp(value, h[0]) < 0) {
        return 0;

        /*
         * 堆不空，且value值大于堆顶，
         * 则在最小堆内查找。
         */
    } else {
        for (int i = 0; i < minheap->used; ++i) {

            /* 存在匹配值 */
            if (cmp(value, h[i]) == 0) {
                return 1;
            }
        }

        /* 未查找到匹配值 */
        return 0;
    }
}

int minheap_del(MinHeap *minheap, MinHeapValue value)
{
    MinHeapValue *h;
    MinHeapCompareFunc cmp;

    h = minheap->array;
    cmp = minheap->cmp;

    /* 空堆，不存在 */
    if (minheap_is_empty(minheap)) {
        return 0;
        /*
         * 堆不空，但value比小顶堆的堆顶还小，
         * 则堆内部也不可能存在值相同的元素。
         */
    } else if (cmp(value, h[0]) < 0) {
        return 0;

        /*
         * 堆不空，且value值大于堆顶，
         * 则在最小堆内查找。
         */
    } else {
        for (int i = 0; i < minheap->used; ++i) {
            /*
             * 查找到匹配元素，
             */
            if (cmp(value, h[i]) == 0) {
                --minheap->used;
                ++minheap->free;
                /*
                 * 复制堆尾元素到i位置上，
                 * 进行堆调整。
                 */
                h[i] = h[minheap->used];
                shiftdown(minheap, i);

                return 1;
            }
        }
    }
}

MinHeapValue minheap_pop_root(MinHeap *minheap)
{
    MinHeapValue result;
    MinHeapValue *h;

    h = minheap->array;

    if (minheap_is_empty(minheap)) {
        result = MINHEAP_NULL;

    } else {
        result = h[0];
        /*
         * 将堆尾最后一个元素复制到堆顶，
         * 相当于删除了堆顶元素，
         * 重新调整堆，使之满足小顶堆性质。
         */
        --minheap->used;
        ++minheap->free;
        h[0] = h[minheap->used];
        shiftdown(minheap, 0);
    }

    return result;
}

MinHeapValue minheap_get_root(MinHeap *minheap)
{
    if (minheap_is_empty(minheap)) {
        return MINHEAP_NULL;
    } else {
        return minheap->array[0];
    }
}

int minheap_depth(MinHeap *minheap)
{
    if (minheap_is_empty(minheap)) {
        return 0;

    } else {
        double log2_n;
        /*
         * 节点数为n的完全二叉树的深度为
         * depth = [ log2(n)] + 1
         * 其中，[ log2(n) ]为不大于log2(n)的最大整数。
         */
        log2_n = log(minheap->used) / log(2);   /* 对数换底公式 */
        return (int) floor(log2_n) + 1;
    }
}

int minheap_is_empty(MinHeap *minheap)
{
    return minheap->used == 0;
}

int minheap_is_full(MinHeap *minheap)
{
    return minheap->free == 0;
}
