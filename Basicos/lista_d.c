#include <stdio.h>
#include <stdlib.h>

typedef struct listad {
    int valor;

    struct listad* proximo;
    struct listad* anterior;
}Listad;

void addInicio(Listad** lista, int add);
void addFim(Listad** lista, int add);
void addMeio(Listad** lista, int add, int ant);
void imprimir(Listad* lista);
Listad* remover(Listad** lista, int remov);
Listad* buscar(int id, Listad* listas);
void esvaziar(Listad** lista);

int main() {
    return 0;
}

void addInicio(Listad** lista, int add) {
    Listad* novo = NULL;
    novo = (Listad*)malloc(sizeof(Listad));
    if (novo == NULL) {
        printf("Erro de alocacao\n");
        exit(1);
    }
    novo->valor = add;
    novo->proximo = *lista;
    novo->anterior = NULL;
    if (*lista != NULL)
        (*lista)->anterior = novo;
    *lista = novo;
}

void addFim(Listad** lista, int add) {
    Listad* aux, * novo = NULL;
    novo = (Listad*)malloc(sizeof(Listad));
    if (novo == NULL) {
        printf("Erro de alocacao\n");
        exit(1);
    }
    novo->valor = add;
    novo->proximo = NULL;

    //primeiro da lista
    if (*lista == NULL) {
        novo->anterior = NULL;
        *lista = novo;
    }
    else {
        aux = *lista;
        while (aux->proximo != NULL)
            aux = aux->proximo;
        aux->proximo = novo;
        novo->anterior = aux;
    }
}

void addMeio(Listad** lista, int add, int ant) {
    Listad* aux, * novo = (Listad*)malloc(sizeof(Listad));
    if (novo == NULL) {
        printf("Erro de alocacao\n");
        exit(1);
    }
    novo->valor = add;

    // Primeiro da lista
    if (*lista == NULL) {
        novo->proximo = NULL;
        novo->anterior = NULL;
        *lista = novo;
    }
    else {
        aux = *lista;
        while (aux->valor != ant && aux->proximo != NULL)
            aux = aux->proximo;

        if (aux->valor == ant) {
            novo->proximo = aux->proximo;
            if (aux->proximo != NULL)
                aux->proximo->anterior = novo;
            novo->anterior = aux;
            aux->proximo = novo;
        }
        else {
            free(novo);
        }
    }
}
void imprimir(Listad* lista) {
    while (lista != NULL) {
        printf("%d ", lista->valor);
        lista = lista->proximo;
    }
    printf("\n");
}

Listad* remover(Listad** lista, int remov) {
    Listad* aux, * del = NULL;
    if (*lista != NULL) {
        if ((*lista)->valor == remov) {
            del = *lista;
            *lista = del->proximo;
            if (*lista != NULL)
                (*lista)->anterior = NULL;
        }
        else {
            aux = *lista;
            while (aux->proximo != NULL && aux->proximo->valor != remov)
                aux = aux->proximo;
            if (aux->proximo != NULL) {
                del = aux->proximo;
                aux->proximo = del->proximo;
                if (aux->proximo != NULL)
                    aux->proximo->anterior = aux;
            }
        }
    }
    return del;
}
Listad* buscar(int id, Listad* listas) {
    Listad* q = NULL;
    q = listas;
    while (q != NULL && q->valor != id) {
        q = q->proximo;
    }
    return q;
}
void esvaziar(Listad** lista) {
    Listad* aux = NULL, * temp = NULL;
    aux = *lista;
    while (aux != NULL) {
        temp = aux;
        aux = aux->proximo;
        free(temp);
    }
    *lista = NULL;
}