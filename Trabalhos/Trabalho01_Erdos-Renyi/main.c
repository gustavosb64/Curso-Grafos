#include <stdio.h>
#include <stdlib.h>
#include "erdos_renyi.h"

int main(int argc, char *argv[]){
    int n;
    float p;

    scanf(" %d",&n);
    scanf(" %f",&p);
    printf("n: %d\tp: %f\n", n,p);

    Grafo G = CriarGrafo(n, p);
    PrintGrafo(G, n);
    printf("Grau do vertice: %d\n",GrauVertice(G, n, 3));

    int *lista = ListaAdjacencias(G, n, 3);
    int i = 0;
    while (lista[i] != -1){
        printf("Adjacência com vértice: %d\n",lista[i++]);
    }

    int a = 0, b = 1;
    printf("Numero de arestas entre %d e %d: %d\n",a,b,ExisteAresta(G, n, a,b));

    free(lista);
    free(G);
    return 0;
}



