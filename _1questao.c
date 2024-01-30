#include "_1questao.h"

int primMST(lista_de_adjacência *g, int pai[], int weigth[]) {
  int i, imin, v, r=0, cor[g->nvert];
  Nodo *aux;
  int fsize=0, fringe[g->nvert]; // ORLA (stack de vértices)

  // Inicializações...
  for (i=0; i<g->nvert; i++) {
    pai[i] = -1;
    cor[i] = BLACK;
  }
  cor[0] = GREY;
  weigth[0] = 0;
  fringe[fsize++] = 0; //f = addV(f, 0, 0);
  
  //ciclo principal...
  while (fsize>1) {
    // Retirar melhor elemento da orla ("f = nextF(f, &v);"):
    // (1) encontrar mínimo
    imin = 0;
    for (i=1; i<fsize; i++)
      if (weigth[fringe[imin]] < weigth[fringe[i]]) imin = i;
    // (2) remover elemento
    v = fringe[imin];
    fringe[imin] = fringe[++fsize];
    // FIM DE "retirar"
    cor[v] = BLACK;
    r += weigth[v];
    for (aux=g->adj[v]; aux; aux=aux->prox)
      switch (cor[aux->dest])
	{
	case WHITE:
	  cor[aux->dest] = GREY;
	  fringe[fsize++] = aux->dest; //f = addV(f, aux->dest, aux->peso);
	  weigth[aux->dest] = aux->peso;
	  pai[aux->dest] = v;
	  break;
	case GREY:
	  if (aux->peso > weigth[aux->dest]) {
	    //f = updateV(f, aux->dest, aux->peso);
	    pai[aux->dest] = aux->peso;
	    weigth[aux->dest] = v;
	  }
	default:
	  break;
	}
  }
  return r;
}


#include <stdio.h>

int main() {
    //criando o grafo com 3 vertices que forme um triangulo
     int grafo[24][24]={0};
    grafo[0][1] = 1;
    grafo[0][2] = 1;
    grafo[1][0] = 1;
    grafo[1][2] = 1;
    grafo[2][0] = 1;
    grafo[2][2] = 1;
    return 0;
}

#include <stdio.h>

int main() {
    //criando o grafo dado
    int grafo[24][24]={0};

    //1 vertice
    grafo[1][2] = 1;
    grafo[1][3] = 1;
    grafo[1][4] = 1;
    grafo[1][5] = 1;

    //2 vertice
    grafo[2][6] = 1;
    grafo[2][3] = 1;

    //3 vertice
    grafo[3][7] = 1;    
    grafo[3][4] = 1;
    //4 vertice
    grafo[4][8] = 1;
    grafo[4][5] = 1;
    //5 vertice
    grafo[5][9] = 1;
    //6 vertice
    grafo[6][10] = 1;
    grafo[6][7] = 1;
    //7 vertice
    grafo[7][8] = 1;
    grafo[7][11] = 1;
    //8 vertice
    grafo[8][9] = 1;
    grafo[8][15] = 1;
    //9 vertice
    grafo[9][10] = 1;
    //10 vertice
    grafo[10][16] = 1;
    //11 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //12 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //13 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //14 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //15 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //16 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //17 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //18 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //19 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //20 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //21 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //22 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //23 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
    //24 vertice
    grafo[8][9] = 1;
    grafo[8][14] = 1;
        
    
    
    return 0;
}
