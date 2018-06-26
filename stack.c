/*
 * 栈(stack)的代码实现
 */

#include <stdlib.h>
#include "stack.h"

/*
 * 栈结点结构
 */
typedef struct _StackEntry StackEntry;

struct _StackEntry {
    StackValue data;
    StackEntry *next;
};

/*
 * 栈
 */
struct _Stack {
    StackEntry *top;    /* 栈顶 */
};

Stack *stack_new(void)
{
    Stack *stack;

    stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) {
        return STACK_NULL;
    }
    stack->top = NULL;
    return stack;
}

void stack_free(Stack *stack)
{
    /*
     * 释放栈结点
     */
    while (!stack_is_empty(stack)) {
        stack_pop(stack);
    }
    /*
     * 释放栈表
     */
    free(stack);
}

int stack_push(Stack *stack, StackValue data)
{
    StackEntry *new_entry;

    /*
     * 新建栈结点，并写入数据
     */
    new_entry = (StackEntry *) malloc(sizeof(StackEntry));

    if (!new_entry) {
        return 0;
    }

    new_entry->data = data;
    new_entry->next = stack->top;
    /*
     * 压栈
     */
    stack->top = new_entry;

    return 1;
}

StackValue stack_pop(Stack *stack)
{
    StackEntry *entry;
    StackValue result;

    /*
     * 判断是否空栈
     */
    if (stack_is_empty(stack)) {
        return STACK_NULL;
    }
    /*
     * 元素弹出栈
     */
    entry = stack->top;
    stack->top = entry->next;
    result = entry->data;
    free(entry);

    return result;
}

StackValue stack_get_top(Stack *stack)
{
    StackValue result;

    if (!stack_is_empty(stack)) {
        return STACK_NULL;
    }

    return stack->top->data;
}


int stack_is_empty (Stack *stack) {
    return stack->top == NULL;
}
