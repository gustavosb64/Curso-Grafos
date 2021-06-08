#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Retorna grafo modelo Erdos-Renyi com os parâmetros n e p
Grafo CriarGrafo(int n, float p){
    Grafo G = (int **) calloc(n, sizeof(int*));
    for (int i=0; i < n; i++) G[i] = (int *) calloc (n, sizeof(int));

    srand(time(NULL)); //seed para gerar numero randomico
    float r;
    int m = n-1;

    for (int i=0; i<n; i++){
        for(int j = 0; j < n-m; j++){
            r = rand() / ((double) RAND_MAX);
            if(r > p){
                G[i][j]++;
                G[j][i]++;
            }
        }
        m--;
    }

    return G;
}

//Retorna o grau do vertice
int GrauVertice(Grafo G, int n, int v){
    n--;

    if (v > n){
        printf("Entrada invalida!\n");
        return 0;
    }

    //A cada iteração é somado ao contador cont o numero de arestas com cada vertice
    int cont = 0;
    for (int i = 0; i < n; i++){
        cont += G[v][i];
    }

    return cont;
}

//Retorna lista com o índice dos vértices adjacentes
int* ListaAdjacencias(Grafo G, int n, int v){
    n--;

    if (v > n){
        printf("Entrada invalida!\n");
        return 0;
    }

    int *lista_adj = (int *) malloc(n * sizeof(int));
    int j = 0;
    for (int i = 0; i < n; i++){
        if (G[v][i]){
            lista_adj[j] = i+1;
            j++;
        }
    }
    lista_adj = (int *) realloc(lista_adj, sizeof(int) * (j));

    return lista_adj;
}

//Checa se ha aresta entre Vi e Vj. Caso exista, retorno = 1; caso contrario, retorno = 0
int ExisteAresta(Grafo G, int n, int i, int j){
    n--;

    if (i > n || j > n){
        printf("Entrada invalida!\n");
        return 0;
    }

    //O proprio valor da matriz contem 0 ou 1
    return (G[i][j]);
}
