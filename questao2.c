#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define BLACK 0
#define GREY 1
#define WHITE 2

typedef struct Nodo Nodo;
typedef struct lista_de_adjacencia lista_de_adjacencia;

struct Nodo {
    int dest;
    float confiabilidade;
    Nodo* prox;
};

struct lista_de_adjacencia {
    int nvert;
    Nodo** adj;
};

Nodo* novoNodo(int dest, float confiabilidade) {
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    novo->dest = dest;
    novo->confiabilidade = confiabilidade;
    novo->prox = NULL;
    return novo;
}

lista_de_adjacencia* novaListaAdj(int nvert) {
    lista_de_adjacencia* grafo = (lista_de_adjacencia*)malloc(sizeof(lista_de_adjacencia));
    grafo->nvert = nvert;
    grafo->adj = (Nodo**)malloc(nvert * sizeof(Nodo*));

    for (int i = 0; i < nvert; ++i)
        grafo->adj[i] = NULL;

    return grafo;
}

void adicionarAresta(lista_de_adjacencia* grafo, int origem, int destino, float confiabilidade) {
    Nodo* novo = novoNodo(destino, confiabilidade);
    novo->prox = grafo->adj[origem];
    grafo->adj[origem] = novo;

    novo = novoNodo(origem, confiabilidade); //caminho inverso para ser bilateral ou seja la qual for o nome
    novo->prox = grafo->adj[destino];
    grafo->adj[destino] = novo;
}

void liberarGrafo(lista_de_adjacencia* grafo) {
    for (int i = 0; i < grafo->nvert; ++i) {
        Nodo* atual = grafo->adj[i];
        while (atual != NULL) {
            Nodo* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    free(grafo->adj);
    free(grafo);
}


// Função para imprimir o caminho adequado de um vértice inicial para o vértice final
void imprimirCaminho(float dist[], int pai[], int vert_final) {
    printf(" Chance de dar certo \t\t Caminho\n");
    printf(" %.2f \t\t\t\t", dist[vert_final]*100);
    int j = vert_final;
    while (j != -1) {
        printf("%d <- ", j);
        j = pai[j];
    }
    printf("\n");
}


// Função auxiliar para encontrar o vértice com melhor confiabilidade no conjunto de vértices não processados
int encontrarConfiabilidade(float dist[], int processado[], int nvert) {
    float max_conf = -1.0;
    int max_index = -1;

    for (int v = 0; v < nvert; v++) {
        if (!processado[v] && dist[v] >= max_conf) {
            max_conf = dist[v];
            max_index = v;
        }
    }

    return max_index;
}


void dijkstra(lista_de_adjacencia* g, int vert_inicial, int vert_final) {
    float dist[g->nvert];    
    int processado[g->nvert]; 
    int pai[g->nvert];     

    for (int i = 0; i < g->nvert; i++) {
        dist[i] = 0.0;  
        processado[i] = 0;
        pai[i] = -1;
    }

    dist[vert_inicial] = 1.0;  

    for (int count = 0; count < g->nvert - 1; count++) {
        int u = encontrarConfiabilidade(dist, processado, g->nvert);
        processado[u] = 1;

        for (Nodo* aux = g->adj[u]; aux; aux = aux->prox) {
            int v = aux->dest;
            if (!processado[v] && dist[u] * aux->confiabilidade > dist[v]) {
                dist[v] = dist[u] * aux->confiabilidade;
                pai[v] = u;
            }
        }
    }

    imprimirCaminho(dist, pai, vert_final);
}

// Função para calcular a média dos valores das arestas
float calcularMediaArestas(lista_de_adjacencia* grafo) {
    float soma = 0;
    int arestas = 0;

    for (int i = 0; i < grafo->nvert; i++) {
        for (Nodo* aux = grafo->adj[i]; aux; aux = aux->prox) {
            soma += aux->confiabilidade;
            arestas++;
        }
    }

    return (arestas > 0) ? (soma / arestas) : 0;
}

// Função para normalizar os valores das arestas
void normalizarArestas(lista_de_adjacencia* grafo) {
    float mediaArestas = calcularMediaArestas(grafo);

    for (int i = 0; i < grafo->nvert; i++) {
        for (Nodo* aux = grafo->adj[i]; aux; aux = aux->prox) {
            aux->confiabilidade /= mediaArestas;
            if (aux->confiabilidade > 1.0) {
                aux->confiabilidade = 1.0;
            }
        }
    }
}

int main() {
    int numVertices = 24;
    lista_de_adjacencia* meuGrafo = novaListaAdj(numVertices);

    //CRIANDO GRAFO DADO NA QUESTÃO

    //vertice 1
    adicionarAresta(meuGrafo, 0, 1, 15);
    adicionarAresta(meuGrafo, 0, 2, 15);
    adicionarAresta(meuGrafo, 0, 3, 6);
    adicionarAresta(meuGrafo, 0, 4, 6);
    
    //primeiro valor é o vertice de origem, segundo o vertice de destino e o ultimo é o valor da 
    //aresta
    
    //vertice 2
    adicionarAresta(meuGrafo, 1, 5, 27);
    adicionarAresta(meuGrafo, 1, 2, 10);

    //vertice 3
    adicionarAresta(meuGrafo, 2, 6, 27);
    adicionarAresta(meuGrafo, 2, 3, 7);

    //vertice 4
    adicionarAresta(meuGrafo, 3, 7, 18);
    adicionarAresta(meuGrafo, 3, 4, 8);

    //vertice 5
    adicionarAresta(meuGrafo, 4, 8, 15);

    //vertice 6
    adicionarAresta(meuGrafo, 5, 10, 6);
    adicionarAresta(meuGrafo, 5, 6, 8);

    //vertice 7
    adicionarAresta(meuGrafo, 6, 11, 6);
    adicionarAresta(meuGrafo, 6, 7, 8);

    //vertice 8
    adicionarAresta(meuGrafo, 7, 14, 24);
    adicionarAresta(meuGrafo, 7, 8, 4);

    //vertice 9
    adicionarAresta(meuGrafo, 8, 9, 9);

    //vertice 10
    adicionarAresta(meuGrafo, 9, 15, 21);

    //vertice 11
    adicionarAresta(meuGrafo, 10, 12, 7.5);

    //vertice 12
    adicionarAresta(meuGrafo, 11, 13, 7.5);

    //vertice 13
    adicionarAresta(meuGrafo, 12, 16, 7.5);
    adicionarAresta(meuGrafo, 12, 13, 5);

    //vertice 14
    adicionarAresta(meuGrafo, 13, 17, 7.5);
    adicionarAresta(meuGrafo, 13, 14, 4);

    //vertice 15
    adicionarAresta(meuGrafo, 14, 18, 12);
    adicionarAresta(meuGrafo, 14, 15, 6);

    //vertice 16
    adicionarAresta(meuGrafo, 15, 22, 27);

    //vertice 17
    adicionarAresta(meuGrafo, 16, 19, 15);

    //vertice 18
    adicionarAresta(meuGrafo, 17, 20, 9);

    //vertice 19
    adicionarAresta(meuGrafo, 18, 21, 7.5);
    
    //vertice 20,21,22,23
    adicionarAresta(meuGrafo, 19, 20, 8);
    adicionarAresta(meuGrafo, 20, 21, 5.5);
    adicionarAresta(meuGrafo, 21, 22, 17.5);

    //vertice 24
    adicionarAresta(meuGrafo, 23, 19, 15);
    adicionarAresta(meuGrafo, 23, 20, 9);
    adicionarAresta(meuGrafo, 23, 21, 7.5);
    adicionarAresta(meuGrafo, 23, 22, 15);
    /////////////////////////////////////////////////////



    // Normalizando as arestas
    normalizarArestas(meuGrafo);

    while(1){
        int a,b;
        printf("Diga o vertice de inicio e o vertice final(digite -1 para sair):");
        scanf("%d",&a);
        if(a == -1)
            return 1;
        scanf("%d",&b);
        if(a >= 0 && b < numVertices)
            dijkstra(meuGrafo, a, b);
        else
            printf("Valores invalidos!!!\n");
    }

    // Libere a memória no final
    liberarGrafo(meuGrafo);

    return 0;
}
