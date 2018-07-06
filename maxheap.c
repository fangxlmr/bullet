/*
 * 最大堆(maxheap)的代码实现。
 * 使用数组存储最大堆。
 */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "maxheap.h"

struct _MaxHeap {
    MaxHeapValue *array;        /* 堆数组 */
    unsigned int free;          /* 数组未使用的长度 */
    unsigned int used;          /* 数组已使用的长度 */
    MaxHeapCompareFunc cmp;
};

/**
 * swap             交换数组内元素
 *
 * @param v         数组
 * @param x         坐标x
 * @param y         坐标y
 */
static void swap(MaxHeapValue *v, int x, int y)
{
    MaxHeapValue temp;

    temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

/**
 * shiftdown        元素下沉函数
 *
 * @param maxheap   最大堆
 * @param n         最大堆的总大小，即数组的有效长度
 * @param i         待下沉的元素下标
 */
static void shiftdown(MaxHeap *maxheap, int i)
{
    int t;
    int n;                      /* 堆数组长度 */
    MaxHeapValue *h;            /* 堆数组 */
    int ileft, iright;          /* i的左、右孩子的坐标 */
    MaxHeapCompareFunc cmp;     /* 比较函数 */

    n = maxheap->used;
    h = maxheap->array;
    ileft  = 2 * i + 1;
    iright = 2 * i + 2;
    cmp = maxheap->cmp;

    /* 至少存在一个左孩子节点 */
    while (ileft < n) {
        /*
         * 与左孩子比较，取较大值
         */
        if (cmp(h[i], h[ileft]) < 0) {
            t = ileft;
        } else {
            t = i;
        }
        /*
         * 如果存在右孩子，则与右孩子比较，
         * 取较大值
         */
        if (iright < n && cmp(h[t], h[iright]) < 0) {
            t = iright;
        }

        /* 判断是否满足最大堆特性 */
        if (t != i) {
            /* 不满足最大堆特性，交换元素 */
            swap(h, t, i);

            /* 继续下沉操作 */
            i = t;
            ileft  = 2 * i + 1;
            iright = 2 * i + 2;

            /* 已满足最大堆，不需要继续下沉 */
        } else {
            break;
        }
    }
}

/**
 * shiftup          元素上浮函数
 *
 * @param maxheap   最大堆
 * @param n         最大堆的总大小，即数组的有效长度
 * @param i         待上浮的元素下标
 */
static void shiftup(MaxHeap *maxheap, int i)
{
    int n;                  /* 堆数组长度 */
    MaxHeapValue *h;        /* 堆数组 */
    int parent;             /* i的父节点坐标 */
    MaxHeapCompareFunc cmp; /* 比较函数 */

    n = maxheap->used;
    h = maxheap->array;
    parent = (int) floor((i - 1) / 2.0);
    cmp = maxheap->cmp;

    /* 下标不得超过堆数组长度 */
    if (i >= n) {
        return;
    }

    /* 存在父节点 */
    while (parent >= 0) {
        /*
         * 与父节点比较大小,
         * 当不满足最大堆特性时，
         * 交换父子节点元素。
         */
        if (cmp(h[i], h[parent]) > 0) {
            swap(h, i, parent);

            /* 继续上浮操作 */
            i = parent;
            parent = (int) floor((i - 1) / 2.0);

            /* 已满足最大堆特性 */
        } else {
            break;
        }
    }
}

MaxHeap *maxheap_new(unsigned int n, MaxHeapCompareFunc cmp)
{
    MaxHeapValue *array;
    MaxHeap *maxheap;

    maxheap = (MaxHeap *) malloc(sizeof(MaxHeap));
    if (!maxheap) {
        return NULL;
    } else {
        maxheap->cmp  = cmp;
        maxheap->free = n;
        maxheap->used = 0;
    }

    array = malloc(n * sizeof(MaxHeapValue));
    if (!array) {
        free(maxheap);
        return NULL;
    } else {
        memset(array, 0, n * sizeof(MaxHeapValue));
        maxheap->array = array;
    }

    return maxheap;
}

int maxheap_add(MaxHeap *maxheap, MaxHeapValue value) {
    MaxHeapCompareFunc cmp;

    cmp = maxheap->cmp;

    if (maxheap->free == 0) {
        /*
         * 堆已满。
         * （1）value值小于堆顶，则替代堆顶，
         * 并执行shiftdown函数，使之下沉到合适位置，
         * 继续满足最大堆特性。且返回1。
         */
        if (cmp(value, maxheap->array[0]) < 0) {
            maxheap->array[0] = value;
            shiftdown(maxheap, 0);      /* 下沉堆顶元素 */
            return 1;
            /*
             * （2）value值大于堆顶，忽略之，并返回0表示插入失败。
             */
        } else {
            return 0;
        }
    } else {
        /* 堆未满 */
        maxheap->array[maxheap->used] = value;

        /* 维持最大堆的结构信息 */
        ++maxheap->used;
        --maxheap->free;

        shiftup(maxheap, maxheap->used - 1);        /* 上浮新元素 */

        return 1;
    }
}

int maxheap_find(MaxHeap *maxheap, MaxHeapValue value) {
    MaxHeapValue *h;
    MaxHeapCompareFunc cmp;

    h = maxheap->array;
    cmp = maxheap->cmp;

    /* 空堆，不存在 */
    if (maxheap_is_empty(maxheap)) {
        return 0;
        /*
         * 堆不空，但value比大顶堆的堆顶还大，
         * 则堆内部也不可能存在值相同的元素。
         */
    } else if (cmp(value, h[0]) > 0) {
        return 0;

        /*
         * 堆不空，且value值不大于堆顶，
         * 则在最大堆内查找。
         */
    } else {
        for (int i = 0; i < maxheap->used; ++i) {

            /* 存在匹配值 */
            if (cmp(value, h[i]) == 0) {
                return 1;
            }
        }

        /* 未查找到匹配值 */
        return 0;
    }
}

int maxheap_del(MaxHeap *maxheap, MaxHeapValue value)
{
    MaxHeapValue *h;
    MaxHeapCompareFunc cmp;

    h = maxheap->array;
    cmp = maxheap->cmp;

    /* 空堆，不存在 */
    if (maxheap_is_empty(maxheap)) {
        return 0;
        /*
         * 堆不空，但value比大顶堆的堆顶还大，
         * 则堆内部也不可能存在值相同的元素。
         */
    } else if (cmp(value, h[0]) > 0) {
        return 0;

        /*
         * 堆不空，且value值不大于堆顶，
         * 则在最大堆内查找。
         */
    } else {
        for (int i = 0; i < maxheap->used; ++i) {
            /*
             * 查找到匹配元素，
             */
            if (cmp(value, h[i]) == 0) {
                --maxheap->used;
                ++maxheap->free;
                /*
                 * 复制堆尾元素到i位置上，
                 * 进行堆调整。
                 */
                h[i] = h[maxheap->used];
                shiftdown(maxheap, i);

                return 1;
            }
        }
    }
}

MaxHeapValue maxheap_pop_root(MaxHeap *maxheap)
{
    MaxHeapValue result;
    MaxHeapValue *h;

    h = maxheap->array;

    if (maxheap_is_empty(maxheap)) {
        result = MAXHEAP_NULL;

    } else {
        result = h[0];
        /*
         * 将堆尾最后一个元素复制到堆顶，
         * 相当于删除了堆顶元素，
         * 重新调整堆，使之满足大顶堆性质。
         */
        --maxheap->used;
        ++maxheap->free;
        h[0] = h[maxheap->used];
        shiftdown(maxheap, 0);
    }

    return result;
}

MaxHeapValue maxheap_get_root(MaxHeap *maxheap)
{
    if (maxheap_is_empty(maxheap)) {
        return MAXHEAP_NULL;
    } else {
        return maxheap->array[0];
    }
}

int maxheap_depth(MaxHeap *maxheap)
{
    if (maxheap_is_empty(maxheap)) {
        return 0;

    } else {
        double log2_n;
        /*
         * 节点数为n的完全二叉树的深度为
         * depth = [ log2(n)] + 1
         * 其中，[ log2(n) ]为不大于log2(n)的最大整数。
         */
        log2_n = log(maxheap->used) / log(2);   /* 对数换底公式 */
        return (int) floor(log2_n) + 1;
    }
}

int maxheap_is_empty(MaxHeap *maxheap)
{
    return maxheap->used == 0;
}

int maxheap_is_full(MaxHeap *maxheap)
{
    return maxheap->free == 0;
}
