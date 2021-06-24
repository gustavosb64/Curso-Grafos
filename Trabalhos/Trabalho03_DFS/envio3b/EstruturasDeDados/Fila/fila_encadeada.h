#ifndef FILA_ENCADEADA_H
#define FILA_ENCADEADA_H

typedef int elem;

typedef struct node_ Node;
typedef struct queue_ Queue;

Queue* CreateQueue();
int IsEmptyQueue(Queue *queue);
int AddElemQueue(Queue *queue, elem e);
int OutQueue(Queue *queue, elem *e);
Node* SearchElemQueue(Queue *queue, elem e, int *error);
int PrintQueue(Queue *queue);
int FreeQueue(Queue *queue);

#endif
