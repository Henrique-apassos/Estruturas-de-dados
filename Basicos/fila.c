#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int tamanho;
    int base;
    int* elementos;
} Fila;

bool filaVazia(Fila fila);
Fila fpush(Fila fila, int add);
Fila fpop(Fila fila);

/*int main() {
	return 0;
}*/

bool filaVazia(Fila fila) {
    return fila.tamanho == 0 ? true : false;
}

Fila fpush(Fila fila, int add) {
    if (filaVazia(fila) == true) {
        fila.tamanho = 1;
        // Adicionar a primeira int (base)
        fila.elementos = (int*)malloc(sizeof(int));
        if (fila.elementos == NULL) {
            printf("Erro de Alocacao ");
            exit(1);
        }
        fila.elementos[0] = add;
        fila.base = add;
        return fila;
    }
    else {
        fila.tamanho++;
        int* temp = realloc(fila.elementos, fila.tamanho * sizeof(int));
        if (temp == NULL) {
            printf("Erro de alocacao ");
            exit(1);
        }
        fila.elementos = temp;
        fila.elementos[fila.tamanho - 1] = add;
        return fila;
    }
}

Fila fpop(Fila fila) {
    if (filaVazia(fila)) {
        return fila;
    }
    else if (fila.tamanho == 1) {
        free(fila.elementos);
        fila.tamanho--;
        fila.base = 0;
        return fila;
    }
    else {
        int* temp = NULL;
        fila.tamanho--;
        fila.base = fila.elementos[1];

        temp = (int*)malloc(fila.tamanho * sizeof(int));
        if (temp == NULL) {
            printf("Erro de Alocacao");
            exit(1);
        }
        for (int i = 0; i < fila.tamanho; i++) {
            temp[i] = fila.elementos[i + 1];
        }
        free(fila.elementos);
        fila.elementos = temp;

        return fila;
    }
}
