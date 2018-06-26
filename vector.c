/*
 * 动态数组(vector)的代码实现
 */

#include <stdlib.h>
#include <string.h>
#include "vector.h"
#define RESIZE_FACTOR 2

/**
 * 动态数组
 */
struct _Vector {
    VectorValue *array;     /* 动态数组指针 */
    unsigned int capacity;  /* 动态数组当前容量 */
    unsigned int length;             /* 动态数组实际使用的长度 */
};

Vector *vector_new(unsigned int size)
{
    VectorValue *new_array;
    Vector *vector;

    new_array  = (VectorValue *) malloc(size * sizeof(VectorValue));
    vector = (Vector *) malloc(sizeof(Vector));

    if (!new_array || !vector) {
        return VECTOR_NULL;
    }

    vector->array    = new_array;
    vector->capacity = size;
    vector->length   = 0;

    return vector;
}

void vector_init(Vector *vector)
{
    VectorValue *array;
    unsigned int size;

    array = vector->array;
    size  = vector->capacity;

    /*
     * 初始化数组为0
     */
    memset(array, 0, size * sizeof(VectorValue));
    vector->length = 0;     /* 重置数组实际使用的长度 */
}

void vector_free(Vector *vector)
{
    free(vector->array);
    free(vector);
}

unsigned int vector_len(Vector *vector)
{
    return vector->length;
}

VectorValue vector_get(Vector *vector, int index)
{
    return (vector->array)[index];
}

/**
 * vector_resize        自动扩容动态数组
 *
 * @param vector        动态数组
 * @return              扩容成功，返回非0值，否则，返回0。
 * @note                新数组的大小是原数组的RESIZE_FACTOR倍。
 *                      RESIZE_FACTOR由#define定义
 */
static int vector_resize(Vector *vector)
{
    unsigned int old_capacity;
    unsigned int new_capacity;
    VectorValue *old_array;
    VectorValue *new_array;

    old_array = vector->array;
    old_capacity = vector->capacity;
    /*
     * 申请新的内存。
     */
    new_capacity = RESIZE_FACTOR * old_capacity;
    new_array = (VectorValue *) malloc(new_capacity * sizeof(VectorValue));

    /*
     * 扩容失败，返回0。
     */
    if (!new_array) {
        return 0;
    }

    /*
     * 扩容成功，则拷贝原始数组的数据，
     * 初始化新数组多出的部分为0，并释放旧的数组。
     */
    memcpy(new_array, old_array, old_capacity * sizeof(VectorValue));
    memset(new_array + old_capacity, 0,(new_capacity - old_capacity) * sizeof(VectorValue));

    vector->capacity = new_capacity;
    free(vector->array);
    vector->array = new_array;

    return 1;
}

int vector_set(Vector *vector, int index, VectorValue data)
{
    /*
     * 当index值不超过数组容量时，
     * 直接赋值。
     */
    if (index < vector->capacity) {
        (vector->array)[index] = data;
        /*
         * 判断动态数组已使用的长度
         */
        vector->length = (unsigned int) index + 1 > vector->length ?
                         (unsigned int) index + 1 : vector->length;
        return 1;

    } else {
        /*
         * 当index超过数组容量时，
         * 对数组扩容，并重新赋值。
         */
        if (vector_resize(vector)) {
            /* 扩容成功 */
            (vector->array)[index] = data;
            /*
             * 判断动态数组已使用的长度
             */
            vector->length = (unsigned int) index + 1 > vector->length ?
                             (unsigned int) index + 1 : vector->length;
            return 1;

        } else {
            /* 扩容失败 */
            return 0;
        }
    }
}
