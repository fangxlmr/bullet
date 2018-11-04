/* 
 * stack.c
 *
 * Copyright (C) 2018 by Xiaoliang Fang (fangxlmr@foxmail.com).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
    while (! stack_isempty(stack)) {
        stack_pop(stack);
    }
    free(stack);
}

int stack_push(stack_t *stack, void *x)
{
    struct entry *e;

    e = (struct entry *) malloc(sizeof(*e));
    if (e == NULL) {
        return -1;
    } else {
        e->x = x;
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
    if (stack_isempty(stack)) {
        return NULL;
    } else {
        return stack->top->x;
    }
}

int stack_isempty(stack_t *stack) {
    return stack->top == NULL;
}

size_t stack_size(stack_t *stack)
{
    return stack->size;
}
