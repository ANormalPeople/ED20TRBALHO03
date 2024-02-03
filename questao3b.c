#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// tamanhos utilizados
#define TAMANHO_VETOR_DESTINO 101 
#define TAMANHO_VETOR_DESTINO2 150 
#define Total_fun 1000

typedef struct Funcionario Funcionario;
typedef struct Hash Hash;

struct Funcionario {
    char Matricula[7];
    char Nome[20];
    char Funcao[20];
    float Salario;
};

struct Hash {
    Funcionario *funcionarios;
    int quant_coli;
};

//////////////////////hash////////////////////////

int fold_shift(char *matricula,int tamanhoVetor) {
    int parte1 = (matricula[0] - '0') * 100 + (matricula[2] - '0') * 10 + (matricula[5] - '0');
    int parte2 = (matricula[1] - '0') * 100 + (matricula[3] - '0') * 10 + (matricula[4] - '0');

    return (parte1 + parte2) % tamanhoVetor;
}

//////////////////////////////////////////////

////////////////////populando////////////////////

void gerar_matricula(char *matricula) {
    matricula[0] = '1' + rand() % 9;
    for (int i = 1; i < 6; i++) {
        matricula[i] = '0' + rand() % 10;
    }
    matricula[6] = '\0';
}

void populando_funcionarios(Funcionario *funcionarios) {
    for (int i = 0; i < Total_fun; i++) {
        gerar_matricula(funcionarios[i].Matricula);
        sprintf(funcionarios[i].Nome, "Funcionario%d", i);
        sprintf(funcionarios[i].Funcao, "Cargo%d", i);
        funcionarios[i].Salario = 1000;
    }
}
///////////////////////////////////////////////////////

int hashingB(char *matricula,int tamanhoVetor){
    int a = fold_shift(matricula,tamanhoVetor);
    return a;
}


void collisionHandlingB(Funcionario *func, Hash *vetorDestino, int tamanhoVetor) {
    int jump = 7 + hashingB(func->Matricula,tamanhoVetor);

    while (vetorDestino[jump].funcionarios != NULL && jump < tamanhoVetor)
        jump += 7;
    
    if(jump < tamanhoVetor)
        vetorDestino[jump].funcionarios = func;
    else
        vetorDestino[0].funcionarios = func;
}

void limpar(Hash *vetorDestino, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetorDestino[i].funcionarios = NULL;
        vetorDestino[i].quant_coli = 0;
    }
}

int main() {
    srand(time(NULL));
    int esc;

    while (1) {
        Hash *vetorDestino;

        printf("1 para o vetor com 101\n2 para o vetor com 150\n-1 para sair\n");
        scanf("%d", &esc);

        // Inicialize os dados da base de funcionários
        Funcionario *funcionarios = (Funcionario *)malloc(Total_fun * sizeof(Funcionario));
        populando_funcionarios(funcionarios);

        int tamanhoVetor = 0;
        if (esc == 1) {
            vetorDestino = (Hash *)malloc(TAMANHO_VETOR_DESTINO * sizeof(Hash));
            tamanhoVetor = TAMANHO_VETOR_DESTINO;
        } else if (esc == 2) {
            vetorDestino = (Hash *)malloc(TAMANHO_VETOR_DESTINO2 * sizeof(Hash));
            tamanhoVetor = TAMANHO_VETOR_DESTINO2;
        } else if (esc == -1) {
            return 0;
        } else {
            printf("Escolha uma opcao valida!\n");
            continue;
        }
        limpar(vetorDestino,tamanhoVetor);
        // Inserção nos vetores de destino usando a função de hashing B
        for (int i = 0; i < Total_fun; i++) {
            int hashValue = hashingB(funcionarios[i].Matricula, tamanhoVetor);
            // Tratamento de colisões
            if (vetorDestino[hashValue].funcionarios != NULL) {
                vetorDestino[hashValue].quant_coli++;
                collisionHandlingB(&funcionarios[i], vetorDestino, tamanhoVetor);
            }else 
                vetorDestino[hashValue].funcionarios = &funcionarios[i];
            
        }

        for (int i = 0; i < tamanhoVetor; i++) 
            printf("%d-%d\n", i, vetorDestino[i].quant_coli);
        

        // Liberação de memória
        free(vetorDestino);
        free(funcionarios);
    }
    return 0;
}