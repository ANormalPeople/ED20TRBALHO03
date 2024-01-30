#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_VETOR_DESTINO 101 // Defina o tamanho do vetor destino
#define TAMANHO_VETOR_DESTINO2 150 // Defina o tamanho do vetor destino
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
//////////////////////hash////////////////////////

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
        funcionarios[i].Salario = 5000;
    }
}
///////////////////////////////////////////////////////

int hashingA(char *matricula) {
    char posi[6];
    strcpy(posi, matricula);
    rotacao(posi);
    extracao(posi);
    return ((posi[0] - '0') * 100 + (posi[1] - '0') * 10 + (posi[2] - '0')) % TAMANHO_VETOR_DESTINO;
}

void collisionHandlingA(Funcionario *func, Hash *vetorDestinoA, int tamanhoVetor) {
    int jump = 7 + hashingA(func->Matricula);

    while (vetorDestinoA[jump].funcionarios != NULL && jump <= tamanhoVetor)
        jump += 7;
    
    if(jump <= tamanhoVetor)
        vetorDestinoA[jump].funcionarios = func;
    else
        vetorDestinoA[0].funcionarios = func;
}


// unsigned int hashingB(char *matricula) {
//     // Implemente a função de hashing conforme especificado no item (b)
// }

// unsigned int collisionHandlingB(unsigned int hashValue) {
//     // Implemente o tratamento de colisões conforme especificado no item (b)
// }

int main() {
    srand(time(NULL));
    Hash *vetorDestinoA = (Hash *)malloc(TAMANHO_VETOR_DESTINO * sizeof(Hash));
    Hash *vetorDestinoB = (Hash *)malloc(TAMANHO_VETOR_DESTINO2 * sizeof(Hash));

    // Inicialize os dados da base de funcionários
    Funcionario *funcionarios = (Funcionario *)malloc(Total_fun * sizeof(Funcionario));
    populando_funcionarios(funcionarios);

    // Inicialize a estrutura Hash no vetorDestinoA
    for (int i = 0; i < TAMANHO_VETOR_DESTINO; i++) {
        vetorDestinoA[i].funcionarios = NULL;
        vetorDestinoA[i].quant_coli = 0;
    }

    // Inserção nos vetores de destino usando a função de hashing A
    for (int i = 0; i < Total_fun; i++) {
        int hashValue = hashingA(funcionarios[i].Matricula);
        // printf("%d %d \n",i,hashValue);
        // Tratamento de colisões
        if(vetorDestinoA[hashValue].funcionarios != NULL){
            collisionHandlingA(&funcionarios[i], vetorDestinoA, TAMANHO_VETOR_DESTINO);   
            vetorDestinoA[hashValue].quant_coli++;         
        }else
            vetorDestinoA[hashValue].funcionarios = &funcionarios[i];
    }

    for (int i = 0; i < TAMANHO_VETOR_DESTINO; i++) {
        printf("%d-%d\n",i,vetorDestinoA[i].quant_coli);
    }

    // Restante do código...

    // Liberação de memória
    free(vetorDestinoA);
    free(vetorDestinoB);
    free(funcionarios);

    return 0;
}


