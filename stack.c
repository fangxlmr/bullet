#include "stack.h"

/* Static functions */
/* Stack_isnull function
 * Return true if stack is null,
 * or return false
 * */
static void stack_isnull (pStack stack);


/* External functions */
/* Create a new stack and initialize it */
pStack stack_new (void){
    pStackNode s = (pStackNode) malloc(sizeof(StackNode));
    if (!s)
        return NULL;
    memset(s, 0, sizeof(StackNode));
    pStack stack = (pStack) malloc(sizeof(Stack));
    if (!stack) {
        return NULL;
    }
    stack->top = s;
    return stack;
}


/* Push an Elem e into stack */
bool stack_push (pStack stack, StackElemType e) {
    stack_isnull(stack);
    pStackNode s = (pStackNode) malloc(sizeof(StackNode));
    if (!s) {
        return false;
    }
    s->e = e;
    s->next = stack->top;
    stack->top = s;
    return true;
}


/* Pop an Elem e out of stack */
bool stack_pop (pStack stack) {
    stack_isnull(stack);
    if (stack_isempty(stack)) {
        printf("Stack is already empty, and can't be popped.\n");
        printf("Program exits.\n");
        exit(-1);
    }
    pStackNode s = stack->top;
    stack->top = stack->top->next;
    free(s);
    return true;
}


/* Destroy a stack completely */
bool stack_destroy (pStack stack) {
    stack_isnull(stack);
    while (stack->top->next) {
        pStackNode s = stack->top;
        stack->top = stack->top->next;
        free(s);
    }
    free(stack->top);
    free(stack);
    return true;
}


/* Clear a stack */
pStack stack_clear (pStack stack) {
    stack_isnull(stack);
    while (stack->top->next) {
        pStackNode s = stack->top;
        stack->top = stack->top->next;
        free(s);
    }
    return stack;
}


/* Stack is empty or not */
bool stack_isempty (pStack stack) {
    stack_isnull(stack);
    if (!stack->top->next) {
        return true;
    } else {
        return false;
    }
}


/* Get the top of stack */
StackElemType stack_gettop (pStack stack) {
    stack_isnull(stack);
    if (stack_isempty(stack)) {
        printf("Stack is empty, no top value. Program exits.\n");
        exit(-1);
    }
    return stack->top->e;
}


static void stack_isnull (pStack stack) {
    if (!stack) {
        printf("NULL stack was used. Program exits.\n");
        exit(-1);
    }
}