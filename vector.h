/**
 * @file    vector.h
 *
 * @brief   动态数组(vector)
 *
 * 动态数组是C语言原生数组的一种扩展。
 *
 * C语言原生数组，一旦确定大小，那么久不可变动。而动态数组
 * 支持自动扩容机制。当所需的空间超过了原本分配的空间大小时，
 * 动态数组可以自动将原先的数组扩容，以满足需要。
 *
 * 使用vector_new创建动态数组，使用vector_free销毁动态数组。
 * 使用vector_init初始化动态数组的所有元素为“0”。
 *
 * 使用vector_len获取当前动态数组已使用的长度。
 *
 * 使用vector_get获取指定下标位置的元素值。
 * 使用vector_set重置或修改指定下标位置的元素值。
 */

#ifndef BULLET_VECTOR_H
#define BULLET_VECTOR_H

/**
 * 动态数组
 */
typedef struct _Vector Vector;

/**
 * 数组元素类型
 */
typedef void *VectorValue;

/**
 * 动态数组空指针
 */
#define VECTOR_NULL ((void *) 0)

/**
 * vector_new       新建动态数组
 *
 * @param size      新建动态数组的容量大小
 * @return          创建动态数组成功，返回动态数组指针，
 *                  内存分配失败，则返回VECTOR_NULL。
 */
extern Vector *vector_new(unsigned int size);

/**
 * vector_init      初始化动态数组
 *
 * @param vector    待初始化的动态数组
 * @note            将数组所有字节初始化为0
 */
extern void vector_init(Vector *vector);

/**
 * vector_free      销毁动态数组
 *
 * @param vector    待销毁的动态数组
 */
extern void vector_free(Vector *vector);

/**
 * vector_size      查询动态数组的长度
 *
 * @param vector    动态数组
 * @return          返回动态数组长度
 */
extern unsigned int vector_len(Vector *vector);

/**
 * vector_get       获取动态数组的元素值
 *
 * @param vector    动态数组
 * @param index     动态数组对应下标
 * @return          成功，则返回动态数组对应下标的值，
 *                  否则，返回VECTOR_NULL。
 */
extern VectorValue vector_get(Vector *vector, int index);

/**
 * vector_set       修改动态数组元素值
 *
 * @param vector    动态数组
 * @param index     待修改元素下标
 * @param data      重新设定的参数
 * @return          修改成功，返回非0值，修改失败，则返回0。
 * @note            1). 扩容后的数组地址可能是变化的；
 *                  2). 扩容后，超出原数组长度，且没有被赋值的部分，
 *                  会被初始化为0。
 */
extern int vector_set(Vector *vector, int index, VectorValue data);

#endif /* BULLET_VECTOR_H */
