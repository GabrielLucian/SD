#ifndef TEMA3__STACK_H
#define TEMA3__STACK_H

#include <stddef.h>

typedef struct node{
    float val;
    struct node *next;
}node_t;
typedef struct stack{
    node_t *top;
    node_t *bottom;
    size_t len;
}stack;
node_t* init_node(float value);
stack* init_stack();
void add_stack(stack *stack, float value);
node_t* remove_stack(stack *stack);
void delete_stack(stack *stackk);
void print_stack(stack *path);
stack *copy(stack *a);
stack *flip_stack(stack *a);
stack *sort(stack* a);
#endif //TEMA3__STACK_H
