#ifndef BULLET_STACK_H
#define BULLET_STACK_H

/**
 * 栈
 */
typedef struct _Stack Stack;

/**
 * 栈内部数据类型
 */
typedef void *StackValue;

/**
 * 空指针
 */
#define STACK_NULL ((void *) 0)

/**
 * stack_new        新建并初始化栈
 *
 * @return          新建栈成功，返回新栈地址
 *                  否则，返回STACK_NULL。
 */
extern Stack *stack_new(void);

/**
 * stack_free       销毁栈
 *
 * @param           待销毁的栈
 */
extern void stack_free(Stack *stack);

/**
 * stack_push       入栈
 *
 * @param stack     栈
 * @param data      待入栈数据
 * @return          数据入栈成功返回非0值，
 *                  若失败，则返回0。
 */
extern int stack_push(Stack *stack, StackValue data);

/**
 * stack_pop        出栈
 *
 * @param stack     栈
 * @return          返回栈顶元素，若栈空，则返回STACK_NULL。
 */
extern StackValue stack_pop(Stack *stack);

/**
 * stack_get_top    获取栈顶元素值
 *
 * @param stack     栈
 * @return          返回栈顶元素值，若栈空，则返回STACK_NULL。
 */
extern StackValue stack_get_top(Stack *stack);

/**
 * stack_is_empty   判断栈是否为空
 *
 * @return          空栈返回非0值，非空返回0。
 */
extern int stack_is_empty (Stack *stack);

#endif /* BULLET_STACK_H */