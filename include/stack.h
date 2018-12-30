/* 
 * stack.h
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

#ifndef BULLET_STACK_H
#define BULLET_STACK_H

#include <stdlib.h>

/**
 * Define a new data type: _stack_t
 */
typedef struct _stack *_stack_t;

/**
 * Define a new stackElem type
 */
typedef void *stackElem;

/**
 * stack_new - Create a new stack
 *
 * @stack[out]: the stack
 *
 * Return 0 if create a new stack successfully,
 * -1 if failed to alloc memory.
 */
extern int stack_new(_stack_t *stack);

/**
 * stack_free - Destroy a stack
 *
 * @stack[in]: the stack
 */
extern void stack_free(_stack_t *stack);

/**
 * stack_push - Push an entry on top of a stack
 *
 * @stack[in]: the stack
 * @x[in]: input entry value
 *
 * Return 0 if success, -1 if failed to alloc memory.
 */
extern int stack_push(_stack_t stack, stackElem x);

/**
 * stack_pop - Pop out an entry
 *
 * @stack[in]: the stack
 * @x[out]: output entry value
 *
 * Return 0 if success, -1 if stack is already empty.
 */
extern int stack_pop(_stack_t stack, stackElem *x);

/**
 * stack_peek - Peek top entry of a stack
 *
 * @stack[in]: the stack
 * @x[out]: peeked value
 *
 * Return 0 if success, -1 if stack is already empty.
 */
extern int stack_peek(_stack_t stack, stackElem *x);

/**
 * stack_isempty - Check stack is empty or not
 *
 * @stack[in]: the stack
 *
 * Return non-zero value if the stack is empty, 0 otherwise.
 */
extern int stack_isempty(_stack_t stack);

/**
 * stack_get_size - Get size of the stack
 *
 * @stack[in]: the stack
 *
 * Return size of the stack, 0 if stack is empty.
 */
extern size_t stack_get_size(_stack_t stack);

#endif /* BULLET_STACK_H */
