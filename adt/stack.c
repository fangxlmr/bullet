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
    stackElem x;
    struct entry *next;
};

struct _stack {
    struct entry *top;
    size_t size;
};

int stack_new(_stack_t *stack)
{
    _stack_t new_stack;

    new_stack = (_stack_t) malloc(sizeof(*new_stack));
    if (new_stack == NULL) {
        return -1;
    } else {
        new_stack->top = NULL;
        new_stack->size = 0;
        *stack = new_stack;
        return 0;
    }
}

void stack_free(_stack_t *stack)
{
    stackElem x;
    while (stack_isempty(*stack) == 0) {
        stack_pop(*stack, &x);
    }
    free(*stack);
    *stack = NULL;
}

int stack_push(_stack_t stack, stackElem x)
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

int stack_pop(_stack_t stack, stackElem *x)
{
    struct entry *e;

    if (stack_isempty(stack)) {
        return -1;
    } else {
        e = stack->top;
        stack->top = e->next;
        stack->size--;

        *x = e->x;
        free(e);
        return 0;
    }
}

int stack_peek(_stack_t stack, stackElem *x)
{
    if (stack_isempty(stack)) {
        return -1;
    } else {
        *x = stack->top->x;
        return 0;
    }
}

int stack_isempty(_stack_t stack)
{
    return stack->top == NULL;
}

size_t stack_get_size(_stack_t stack)
{
    return stack->size;
}
