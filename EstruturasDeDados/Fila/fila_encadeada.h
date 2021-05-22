#ifndef FILA_ENCADEADA_H
#define FILA_ENCADEADA_H

typedef int elem;

typedef struct node_ Node;
typedef struct queue_ Queue;

Queue* CreateQueue();
int IsEmpty(Queue *queue);
int AddElem(Queue *queue, elem e);
int OutQueue(Queue *queue, elem *e);
Node* SearchElem(Queue *queue, elem e, int *error);
int PrintQueue(Queue *queue);

#endif
