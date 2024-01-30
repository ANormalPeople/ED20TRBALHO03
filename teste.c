#include <stdio.h>
#include <string.h>

void rotateAndKeepSelectedDigits(char *matricula) {
    char temp[3];
    int length = strlen(matricula);

    if (length >= 2) {
        strncpy(temp, matricula + length - 2, 2);  
        memmove(matricula + 2, matricula, length - 2); 
        strncpy(matricula, temp, 2);     

        char tempSelected[4];
        tempSelected[0] = matricula[1];
        tempSelected[1] = matricula[3];
        tempSelected[2] = matricula[5];
        tempSelected[3] = '\0';

        strcpy(matricula, tempSelected);  

        printf("A matrícula deve ter pelo menos 2 caracteres.\n");
    }
}

int main() {
    char a[] = "123456";
    rotateAndKeepSelectedDigits(a);
    printf("%s", a);
    return 0;
}  