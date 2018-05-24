#ifndef BULLET_STACK_H
#define BULLET_STACK_H

#define T Stack_T
typedef struct T *T;

/* 新建并初始化栈 */
extern T stack_new (void);

/* 判断栈是否为空，空返回0，不空返回1 */
extern int stack_empty (T stk);

/* 栈深度 */
extern int stack_size (T stk);

/* 元素入栈 */
extern void stack_push (T stk, void *x);

/* 元素出栈 */
extern void *stack_pop (T stk);

/* 释放栈，并置NULL */
extern void stack_free (T *stk);

#undef T
#endif /* BULLET_STACK_H */