//
// Created by Gabriel Ionescu on 14.05.2022.
//
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

node_t* init_node(float value)
{
    node_t *new= malloc(sizeof(node_t));
    new->val=value;
    new->next=NULL;
    return new;
}
stack* init_stack()
{
    stack *stackk= malloc(sizeof(stack));
    stackk->len=0;
    stackk->top=NULL;
    stackk->bottom=NULL;
    return stackk;
}
void add_stack(stack *stackk, float value)
{
    node_t *new= init_node(value);
    if(stackk->len==0)
    {
        stackk->top=new;
        stackk->bottom=new;
    }
    else
    {
        new->next=stackk->top;
        stackk->top=new;
    }
    stackk->len++;
}
node_t* remove_stack(stack *stackk)
{
    node_t *node;
    if(stackk->len==0)
        return 0;
    if(stackk->len==1)
    {
        node=stackk->top;
        stackk->top=NULL;
        stackk->bottom=NULL;
    }
    else
    {
        node = stackk->top;
        stackk->top = stackk->top->next;
    }
    stackk->len--;
    return node;
}
void delete_stack(stack *stackk)
{
    node_t *aux;
    if(stackk==NULL)
    {
        return;
    }
    while(stackk->len>0)
    {
        aux=remove_stack(stackk);
        free(aux);
    }
    free(stackk);
}
void print_stack(stack *path)
{
    if(path==NULL)
        return;
    node_t *current=path->top;
    while(current!=NULL)
    {
        printf("%.0f",current->val);
        if(current->next!=NULL)
            printf(" ");  
        current=current->next;
    }
    //printf("\n");
}
stack *copy(stack *a)
{
    stack *b=malloc(a->len*sizeof(node_t));
    stack *c=malloc(a->len*sizeof(node_t));
    node_t *aux;
    while(a->len>0)
    {
        aux=remove_stack(a);
        add_stack(b,aux->val);
        free(aux);
    }
    while(b->len>0)
    {
        aux=remove_stack(b);
        add_stack(c,aux->val);
        free(aux);
    }
    free(a);
    free(b);
}
stack *flip_stack(stack *a)
{
    stack *b=malloc(a->len*sizeof(node_t));
    node_t *aux;
    while(a->len>0)
    {
        aux=remove_stack(a);
        add_stack(b,aux->val);
        free(aux);
    }
    free(a);
    return b;
}
stack *sort(stack* a)
{
    stack *b=init_stack();
    node_t *aux,*aux2;
    while(a->len>0)
    {
        aux=remove_stack(a);
        while(b->len>0 && b->top->val < aux->val)
        {
            aux2=remove_stack(b);
            add_stack(a,aux2->val);
            free(aux2);
        }
        add_stack(b,aux->val);
        free(aux);
    }
    free(a);
    return b;
}