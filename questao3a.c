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


char* rotacao(char *matricula) {
    char temp[3];
    int length = strlen(matricula);

    if (length >= 2) {
        strncpy(temp, matricula + length - 2, 2);
        memmove(matricula + 2, matricula, length - 2);
        strncpy(matricula, temp, 2);
    } else {
        printf("A matricula precisa ter pelo menos 2 digitos");
    }

    return matricula;
}

char* extracao(char *matricula) {
    int length = strlen(matricula);
    char tempSelected[4];

    if (length >= 2) {
        tempSelected[0] = matricula[1];
        tempSelected[1] = matricula[3];
        tempSelected[2] = matricula[5];
        tempSelected[3] = '\0';

        strcpy(matricula, tempSelected);
    }
    return matricula;
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

int hashingA(char *matricula,int tamanhoVetor) {
    char posi[6];
    strcpy(posi, matricula);
    rotacao(posi);
    extracao(posi);
    return ((posi[0] - '0') * 100 + (posi[1] - '0') * 10 + (posi[2] - '0')) % tamanhoVetor;
}

void collisionHandlingA(Funcionario *funcionario, Hash *vetorDestino, int tamanhoVetor) {
    int hashValue = hashingA(funcionario->Matricula,tamanhoVetor);
    int primeiraMatriculaDigit = funcionario->Matricula[0] - '0';
    
    while (vetorDestino[hashValue].funcionarios != NULL && hashValue < tamanhoVetor)
        hashValue += primeiraMatriculaDigit;
    if(hashValue < tamanhoVetor)
        vetorDestino[hashValue].funcionarios = funcionario;
    else
        vetorDestino[0].funcionarios = funcionario;
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
        // Inserção nos vetores de destino usando a função de hashing A
        for (int i = 0; i < Total_fun; i++) {
            int hashValue = hashingA(funcionarios[i].Matricula, tamanhoVetor);
            // Tratamento de colisões
            if (vetorDestino[hashValue].funcionarios != NULL) {
                collisionHandlingA(&funcionarios[i], vetorDestino, tamanhoVetor);
                vetorDestino[hashValue].quant_coli++;
            } else {
                vetorDestino[hashValue].funcionarios = &funcionarios[i];
            }
        }

        for (int i = 0; i < tamanhoVetor; i++) 
            printf("%d-%d\n", i, vetorDestino[i].quant_coli);

        // Liberação de memória
        free(vetorDestino);
        free(funcionarios);
    }
    return 0;
}