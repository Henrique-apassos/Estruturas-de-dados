#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int topo;
    int tam;
    int* elementos;
} Pilha;

bool pilhaVazia(Pilha conj);
Pilha push(Pilha conj, int elem);
Pilha pop(Pilha conj);
Pilha inserir(Pilha conj, int elem);

bool pilhaVazia(Pilha conj) {
    return conj.tam == 0 ? true : false;
}

Pilha push(Pilha conj, int elem) {
    if (pilhaVazia(conj) == true) {
        conj.tam = 1;
        conj.elementos = (int*)calloc(1, sizeof(int));
        if (conj.elementos == NULL) {
            printf("Erro de alcacao \n");
            exit(1);
        }
        conj.elementos[0] = elem;
        conj.topo = elem;
        return conj;
    }
    else {
        conj.tam++;
        int* temp = realloc(conj.elementos, conj.tam * sizeof(int));
        if (temp == NULL) {
            printf("Erro de alcocacao \n");
            exit(1);
        }
        conj.elementos = temp;
        conj.elementos[conj.tam - 1] = elem;
        conj.topo = elem;
        return conj;
    }
}

Pilha pop(Pilha conj) {
    if (pilhaVazia(conj)) {
        return conj;
    }
    else {
        if (conj.tam > 1) {
            conj.tam--;
            int* temp = realloc(conj.elementos, conj.tam * sizeof(int));
            if (temp == NULL) {
                printf("Erro de alocação!\n");
                exit(1);
            }
            conj.elementos = temp;
            conj.topo = conj.elementos[conj.tam - 1];
        }
        else {
            conj.tam = 0;
            free(conj.elementos);
            conj.elementos = NULL;
            conj.topo = 0;
        }
        return conj;
    }
}

Pilha inserir(Pilha conj, int elem) {
    if (elem % 2 == conj.topo % 2 && elem != conj.topo) {
        elem = abs(conj.topo - elem);
        conj = pop(conj);
        return pilhaVazia(conj) ? push(conj, elem) : inserir(conj, elem);
    }
    else if (elem == 0) {

        return conj;
    }
    else if (elem == conj.topo) {
        return pop(conj);
    }
    else {
        return push(conj, elem);
    }
}
