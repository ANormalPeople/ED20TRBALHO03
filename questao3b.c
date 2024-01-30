#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_VETOR_DESTINO 101 // Defina o tamanho do vetor destino

typedef struct Funcionario Funcionario;

struct Funcionario {
    char Matricula[7];
    char Nome[20];
    char Funcao[20];
    float Salario;
};

unsigned int hashFunctionB(char *matricula, int tamanhoVetor) {
    // Fole shift com 3 dígitos
    int shift1 = atoi(matricula) % 10;
    int shift2 = (atoi(matricula + 2) * 10 + atoi(matricula + 5)) % 10;
    
    int hashValue = (shift1 * shift2) % tamanhoVetor;

    return hashValue;
}

unsigned int collisionHandlingB(unsigned int hashValue) {
    // Tratamento de colisões somando 7 ao valor obtido
    return (hashValue + 7) % TAMANHO_VETOR_DESTINO;
}

int main() {
    Funcionario *vetorDestino = (Funcionario *)malloc(TAMANHO_VETOR_DESTINO * sizeof(Funcionario));

    // Inicialize os dados da base de funcionários

    // Implemente a função de hashing e colisão conforme especificado no item (b)

    free(vetorDestino);
    return 0;
}
