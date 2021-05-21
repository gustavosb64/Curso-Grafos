#ifndef ERDOS_RENYI_H
#define ERDOS_RENYI_H

typedef int** Grafo;

Grafo CriarGrafo(int, float);
int ExisteAresta(Grafo G, int n, int i, int j);
int* ListaAdjacencias(Grafo G, int n, int i);
int GrauVertice(Grafo G, int n, int v);

#endif
