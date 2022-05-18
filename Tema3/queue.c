#include "queue.h"
#include "graph_adj_matrix.h"
#include <stdlib.h>

Pair *init_pair(int node, int size, int *mask)
{
    pair=malloc(sizeof(Pair));
    pair->node=node;
    pair->size=size;
    pair->mask=malloc(size*sizeof(int));
    for(int i=0;i<size;i++)
        pair->mask[i]=mask[i];
    pair->next=NULL;
    pair->prev=NULL;
    return pair;
}
Queue *init_queue()
{
    Queue *queue=malloc(sizeof(Queue));
    queue->head=NULL;
    queue->tail=NULL;
    queue->len=0;
    return queue;
}
void add_queue(Queue *queue, Pair *pair)
{
    if(queue->len==0)
    {
        queue->head=pair;
        queue->tail=pair;
    }
    else
    {
        pair->prev=queue->tail;
        queue->tail=pair;
    }
    queue->len++;
}
Pair *remove_queue(Queue *queue)
{
    Pair *pair;
    if(queue->len==0)
        return 0;
    if(queue->len==1)
    {
        pair=queue->head;
        queue->head=NULL;
        queue->tail=NULL;
    }
    else
    {
        pair=queue->head;
        queue->head=queue->head->next;
        queue->head->prev=NULL;
    }
    queue->len--;
    return pair;
}
void delete_queue(Queue *queue)
{
    Pair *aux;
    if(queue==NULL)
        return;
    while(queue->len>0)
    {
        aux=remove_queue(queue);
        free(aux);
    }
    free(queue);
}
void print_queue(Queue *queue)
{
    if(queue==NULL)
        return;
    Path *current=queue->head;
    while(current!=NULL)
    {
        printf("%d - ",current->node);
        for(int i=0;i<current->size;i++)
            printf("%d ", current->mask[i]);
    }
}
