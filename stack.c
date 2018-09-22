/* Implementation of stack  */

#include <assert.h>
#include "stack.h"

struct entry {
    void *x;
    struct entry *next;
};

struct _stack {
    struct entry *top;
    size_t size;
};

stack_t *stack_new(void)
{
    stack_t *stack;

    stack = (stack_t *) malloc(sizeof(*stack));
    if (stack == NULL) {
        return NULL;
    } else {
        stack->top = NULL;
        stack->size = 0;
        return stack;
    }
}

void stack_free(stack_t *stack)
{
    assert(stack);
    while (! stack_isempty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}

int stack_push(stack_t *stack, const void *x)
{
    struct entry *e;

    assert(stack);
    assert(x);
    e = (struct entry *) malloc(sizeof(*e));

    if (e == NULL) {
        return -1;

    } else {
        e->x = (void *) x;
        e->next = stack->top;
        stack->top = e;
        stack->size++;
        return 0;
    }
}

void *stack_pop(stack_t *stack)
{
    struct entry *e;
    void *x;

    assert(stack);
    if (stack_isempty(stack)) {
        return NULL;

    } else {
        e = stack->top;
        stack->top = e->next;
        stack->size--;

        x = e->x;
        free(e);
        return x;
    }
}

void *stack_peek(stack_t *stack)
{
    assert(stack);
    if (stack_isempty(stack)) {
        return NULL;

    } else {
        return stack->top->x;
    }
}

int stack_isempty(stack_t *stack) {
    assert(stack);
    return stack->top == NULL;
}

size_t stack_size(stack_t *stack)
{
    assert(stack);
    return stack->size;
}
