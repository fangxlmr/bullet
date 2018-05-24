#include <stdlib.h>
#include <assert.h> /* 待自己实现的assert.h */
#include "stack.h"

#define T Stack_T

typedef struct elem {
    void *x;
    struct elem *next;
}elem;

struct T {
    int count;     /* 栈深度 */
    elem *top;        /* 栈顶 */
};

/* 新建并初始化栈 */
T stack_new (void) {
    T stk;

    stk = (T) malloc(sizeof(struct T));
    stk->count = 0;
    stk->top = NULL;
    return stk;
}


/* 判断栈是否为空，空返回0，不空返回1 */
int stack_empty (T stk) {
    assert(stk);
    return stk->count == 0;
}


/* 栈深度 */
int stack_size (T stk) {
    assert(stk);
    return stk->count;
}


/* 元素入栈 */
void stack_push (T stk, void *x) {
    elem *t;

    assert(stk);
    t = (elem *) malloc(sizeof(elem));
    t->x = x;
    t->next = stk->top;
    stk->top = t;
    stk->count++;
}


/* 元素出栈 */
void *stack_pop (T stk) {
    void *x;
    elem *t;

    assert(stk);
    assert(stk->count > 0);
    t = stk->top;
    stk->top = t->next;
    stk->count--;
    x = t->x;
    free(t);
    return x;
}


/* 释放栈 */
void stack_free (T *stk) {
    elem *t, *u;

    assert(stk && *stk);
    for (t = (*stk)->top; t ; t = u) {
        u = t->next;
        free(t);
    }
    free(*stk);
    *stk = NULL;
}