
typedef struct pair{
    int node;
    int size;
    int *mask;
    struct pair *prev;
    struct pair *next;
}Pair;

typedef struct queue{
    Pair *head;
    Pair *tail;
    size_t len;
}Queue;
Pair *init_pair(int node, int size, int *mask);
Queue *init_queue();
void add_queue(Queue *queue, Pair *pair);
Pair *remove_queue(Queue *queue);
void delete_queue(Queue *queue);
void print_queue(Queue *queue);