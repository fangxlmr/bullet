#ifndef BULLET_STACK_H
#define BULLET_STACK_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>

/* User defined StackElemType.
 * Here is int, you can redefine it.
 */
typedef int StackElemType;

typedef struct StackNode {    /* stack node */
    StackElemType e;
    struct StackNode *next;
}StackNode, *pStackNode;

typedef struct Stack {      /* stack info */
    pStackNode top;     /* top of the stack */
    /* Maybe some other info, say, count of stack nodes */
}Stack, *pStack;


/* Create a new stack and initialize it.
 * If malloc failed, return NULL,
 * or return the address of malloced stack.
 * */
pStack stack_new (void);

/* Push an Elem e into stack.
 * If NULL stack was used, print info, and program exits.
 * If malloced failed, return false,
 * or push the elem into stack and return true.
 * */
bool stack_push (pStack stack, StackElemType e);

/* Pop an Elem e out of stack.
 * If NULL stack was used, print info, and program exits.
 * If stack is already empty, then print info, and program exits.
 * Or pop the top of stack, and return true.
 * */
bool stack_pop (pStack stack);

/* Destroy a stack completely.
 * If NULL stack was used, print info, and program exits.
 * Or free all nodes (StackNodes and Stack), and return true.
 * */
bool stack_destroy (pStack stack);

/* Clear a stack.
 * If NULL stack was used, print info, and program exits.
 * Or clear all StackNodes in the stack, and return true.
 * */
pStack stack_clear (pStack stack);

/* Check the stack is empty or not.
 * If NULL stack was used, print info, and program exits.
 * Return true if empty, or return false.
 * */
bool stack_isempty (pStack stack);

/* Get the top of stack.
 * If NULL stack was used, print info, and program exits.
 * Print info if stack is empty, and program exits.
 * Or return the top value of stack.
 * */
StackElemType stack_gettop (pStack stack);


#endif /* BULLET_STACK_H */