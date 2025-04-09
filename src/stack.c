#include <stdio.h>
#include <stdlib.h>
#include <stack.h>
#include <string.h>


stack_t stack_new(size_t _s){
    stack_t stack;
    stack.len = 0;
    stack.allocated_len = 64;
    stack.stack = malloc(stack.allocated_len * _s);
    if(stack.stack == NULL){perror("realloc failed\n"), exit(1);}
    return stack;
}

void stack_destroy(stack_t *stack){
    free(stack->stack);
}

void stack_push(stack_t *stack, void *val, size_t _s){
    stack->len++;
    if(stack->len >= stack->allocated_len){
        stack->allocated_len += 64;
        stack->stack = realloc(stack->stack, stack->allocated_len * _s);
        if(stack->stack == NULL){perror("stack realloc failed\n"), exit(1);}
    }
    memcpy((stack->stack + _s*(stack->len-1)), val, _s);
}

void stack_pop(stack_t *stack, void *dest, size_t _s){
    if(stack->len <= 0){
        perror("popping from emty stack is not allowed\n");
        return;
    }
    stack->len--;
    memcpy(dest, (stack->stack + _s*(stack->len)), _s);
}
