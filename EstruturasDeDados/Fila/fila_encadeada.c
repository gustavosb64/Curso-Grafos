#include <stdio.h>
#include <stdlib.h>
#include "fila_encadeada.h"

struct node_{
    elem val;
    struct node_ *next;
};

struct queue_{
    Node *first;
    Node *last;
    int n_elem;
};

Queue* CreateQueue(){
    Queue *queue = (Queue *) malloc(sizeof(Queue)); 
    
    queue->first = NULL; 
    queue->last = queue->first; 

    queue->n_elem = 0; 

    return queue;
}

int IsEmptyQueue(Queue *queue){
    if (queue->n_elem == 0) return 1;
    else return 0;
}

int AddElemQueue(Queue *queue, elem e){
    Node *aux_node = (Node *) malloc(sizeof(Node));
    if (aux_node == NULL) return 1;

    if (IsEmptyQueue(queue)){
        queue->first = aux_node;
    }
    else {
        queue->last->next = aux_node; 
    }

    queue->last = aux_node;

    queue->last->val = e;
    queue->last->next = NULL;

    queue->n_elem++;

    return 0;
}

int OutQueue(Queue *queue, elem *e){

    if(IsEmptyQueue(queue)) return 1;

    *e = queue->first->val;
    
    Node *aux_node = queue->first->next;

    free(queue->first);
    queue->first = aux_node;

    queue->n_elem--;

    return 0;
}

Node* SearchElemQueue(Queue *queue, elem e, int *error){

    if(IsEmptyQueue(queue)){
        *error = 1;
        return NULL;
    }

    Node *dest_node;
    dest_node = queue->first;

    while (dest_node != NULL){
        if (dest_node->val == e){
            return dest_node;
        }
        dest_node = dest_node->next;
    }
    
    *error = 2;
    return NULL;
}

int PrintQueue(Queue *queue){

    if(IsEmptyQueue(queue)) return 1;
    
    Node *aux_node = queue->first;
    
    while(aux_node!=NULL){
        printf("%d\n",aux_node->val+1);
        aux_node = aux_node->next;
    }

    return 0;
}

int FreeQueue(Queue *queue){

    if(IsEmptyQueue(queue)){
        free(queue->first);
        free(queue);
        return 1;
    }
    
    elem e;
    Node *aux_node = queue->first;
    Node *aux_node2;
    while(aux_node != NULL){
        aux_node2 = aux_node;
        aux_node = aux_node->next;
        free(aux_node2);
    }
    free(aux_node);
    free(queue);

    return 0;
}
