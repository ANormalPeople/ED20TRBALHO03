#include <stdlib.h>

#ifndef _1QUESTAO_H

#define _1QUESTAO_H

typedef struct lista_de_adjacência lista_de_adjacência;
typedef struct Nodo Nodo;

// Estrutura para um nó da lista encadeada
struct Nodo {
    int dest;        // Vértice de destino da aresta
    int peso;        // Peso associado à aresta
    struct Nodo* prox; // Ponteiro para o próximo nó na lista
};

// Estrutura para a lista de adjacência de um vértice
struct LAdj {
    int nvert;       // Número de vértices no grafo
    Nodo** adj;      // Array de ponteiros para listas encadeadas
};

// nome das funçoes

#endif



// Função para criar um novo nó
Nodo* novoNodo(int dest, int peso) {
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    novo->dest = dest;
    novo->peso = peso;
    novo->prox = NULL;
    return novo;
}

// Função para criar uma nova lista de adjacência
LAdj* novaLAdj(int nvert) {
    LAdj* grafo = (LAdj*)malloc(sizeof(LAdj));
    grafo->nvert = nvert;
    grafo->adj = (Nodo**)malloc(nvert * sizeof(Nodo*));
    
    // Inicializa todas as listas como vazias
    for (int i = 0; i < nvert; ++i)
        grafo->adj[i] = NULL;

    return grafo;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(LAdj* grafo, int origem, int destino, int peso) {
    Nodo* novo = novoNodo(destino, peso);
    novo->prox = grafo->adj[origem];
    grafo->adj[origem] = novo;
    
}

// Função para liberar a memória ocupada pelo grafo
void liberarGrafo(LAdj* grafo) {
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

// Exemplo de uso
int main() {
    int numVertices = 24;
    LAdj* meuGrafo = novaLAdj(numVertices);



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
    adicionarAresta(meuGrafo, 19, 20, 7.5);
    adicionarAresta(meuGrafo, 20, 21, 7.5);
    adicionarAresta(meuGrafo, 21, 22, 7.5);

    //vertice 24
    adicionarAresta(meuGrafo, 23, 19, 15);
    adicionarAresta(meuGrafo, 23, 20, 9);
    adicionarAresta(meuGrafo, 23, 21, 7.5);
    adicionarAresta(meuGrafo, 23, 22, 15);
    /////////////////////////////////////////////////////

    // Libere a memória no final
    liberarGrafo(meuGrafo);

    return 0;
}