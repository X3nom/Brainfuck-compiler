#pragma once
#include <stddef.h>

// Generates wrapper around generic stack
#define GENERATE_STACK_WRAPPER(_T, _sT)\
    typedef struct{ \
    _T *stack; \
    int len; \
    int allocated_len; \
    } _sT; \
    static inline _sT _sT##_new(){ \
        stack_t _tmp_stack = stack_new(sizeof(_T)); \
        return *(_sT*)&_tmp_stack; \
    } \
    static inline void _sT##_destroy(_sT *stack){ stack_destroy((void*)stack); } \
    static inline void _sT##_push(_sT *stack, _T val){ \
        _T tmp = val; \
        stack_push((void*)stack, &tmp, sizeof(_T)); \
    } \
    static inline _T _sT##_pop(_sT *stack){ \
        _T tmp; \
        stack_pop((void*)stack, &tmp, sizeof(_T)); \
        return tmp; \
    }




typedef struct{
    void *stack;
    int len;
    int allocated_len;
} stack_t;


stack_t stack_new(size_t _s);

void stack_destroy(stack_t *stack);

void stack_push(stack_t *stack, void *val, size_t _s);

void stack_pop(stack_t *stack, void *dest, size_t _s);




GENERATE_STACK_WRAPPER(int, intStack);
