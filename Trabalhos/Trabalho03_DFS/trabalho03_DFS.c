#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../GrafosListaAdjacencias/grafos_lista_adjacencias.h"
#include "../../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../../EstruturasDeDados/Lista/lista_encadeada.h"
#include "../../ReadPajek/read_pajek.h"

typedef struct node_v_{
    int vertex;
    int value;
    struct node_v_ *next;
    struct node_v_ *prev;
}NodeV;

typedef struct grafo_{
    NodeV *Adj;
    char colour; //W -> white; B -> black; G -> grey
    int n_vertices;
    int dist;
}Graph;

/* Funções criadas para a resolução do trabalho 03
*/
void quicksort(int number[25],int first,int last){
    int i, j, pivot, temp;

    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(number[i]<=number[pivot]&&i<last) i++;
            while(number[j]>number[pivot]) j--;
            if(i<j){
                temp=number[i];
                number[i]=number[j];
                number[j]=temp;
            }
        }
        
        temp=number[pivot];
        number[pivot]=number[j];
        number[j]=temp;
        quicksort(number,first,j-1);
        quicksort(number,j+1,last);
    }
}

void Trab03_A_RecursiveDFS(Graph *G, int cur_index, Stack *B_Stack, List *W_List){

    if(G[cur_index].colour != 'W') return;

    int aux_e;
    SearchRemoveElem(W_List, &cur_index, &aux_e);

    if(G[cur_index].Adj != NULL){
        G[cur_index].colour = 'G';

        NodeV* aux_node = G[cur_index].Adj;
        while (aux_node != NULL){
            Trab03_A_RecursiveDFS(G, aux_node->vertex, B_Stack, W_List);
            aux_node = aux_node->next;
        }

    }

    G[cur_index].colour = 'B';
    AddElemStack(B_Stack, cur_index);

    return;
}


int Trab03_B_RecursiveDFS(Graph *G, int cur_index, Stack *B_Stack, List *W_List){

    if(G[cur_index].colour != 'W') return 1;

    int aux_e;
    SearchRemoveElem(W_List, &cur_index, &aux_e);

    if(G[cur_index].Adj != NULL){
        G[cur_index].colour = 'G';

        NodeV* aux_node = G[cur_index].Adj;
        while (aux_node != NULL){
            return Trab03_B_RecursiveDFS(G, aux_node->vertex, B_Stack, W_List);
            aux_node = aux_node->next;
        }

    }

    G[cur_index].colour = 'B';
    AddElemStack(B_Stack, cur_index);

    return 0;
}

//Parte A: retorna o número de componentes e a quantidade de vetores em cada um
void PartA_DFS(Graph *G){

    Stack *B_Stack = CreateStack();
    List *W_List = CreateList();

    for(int i=0; i<G->n_vertices; i++){
        G[i].colour = 'W';    
        AddLastElem(W_List,i);
    }

    int root;
    int *n_vertices = (int *) malloc(sizeof(int) * 1);

    int i=0;

    while(!IsEmptyList(W_List)){
        root = GetFirstElem(W_List);

        Trab03_A_RecursiveDFS(G, root, B_Stack, W_List);

        n_vertices[i] = GetNumElem(B_Stack);

        i++;
        n_vertices = (int *) realloc(n_vertices, sizeof(int)*(i+1));

        FreeStack(B_Stack);
        B_Stack = CreateStack();
    }

    quicksort(n_vertices, 0, i-1);
    printf("%d\n",i);
    for (int j=i-1; j >= 0; j--){
        printf("%d\n",n_vertices[j]);
    }

    FreeStack(B_Stack);
    free(B_Stack);

    FreeList(W_List);
    free(n_vertices);

    return;
}

//Parte B: checa se o grafo possui ciclo ou não
void PartB_DFS(Graph *G){

    Stack *B_Stack = CreateStack();
    List *W_List = CreateList();

    for(int i=0; i<G->n_vertices; i++){
        G[i].colour = 'W';    
        AddLastElem(W_List,i);
    }

    int root;

    while(!IsEmptyList(W_List)){
        root = GetFirstElem(W_List);

        if(Trab03_B_RecursiveDFS(G, root, B_Stack, W_List)){
            printf("S\n");

            FreeStack(B_Stack);
            free(B_Stack);

            FreeList(W_List);
            return;
        }

        for(int i=0; i<G->n_vertices; i++){
            G[i].colour = 'W';    
        }

        FreeStack(B_Stack);
        B_Stack = CreateStack();
    }

    FreeStack(B_Stack);
    free(B_Stack);

    FreeList(W_List);

    printf("N\n");

    return;
}
