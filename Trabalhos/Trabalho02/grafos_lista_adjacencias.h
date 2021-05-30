#ifndef GRAFO_LISTA_ADJACENCIAS_H
#define GRAFO_LISTA_ADJACENCIAS_H
#include "../../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../../EstruturasDeDados/Lista/lista_encadeada.h"

typedef int elem;
typedef struct node_v_ NodeV;
typedef struct grafo_ Graph;

Graph* CreateGraph(int);
int IsEmpty(NodeV *Adj);
int Insert(Graph *, int, int, int);
int RemoveEdge(Graph *, int, int);
void PrintGraph(Graph*);
void FreeGraph(Graph*);
void BFS(Graph*, elem);
void PrintBFS(Graph*);

#endif
