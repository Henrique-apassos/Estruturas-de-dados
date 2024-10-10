#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int valor;
	struct lista *proximo;
}Lista;

void addInicio(Lista **lista, int add);
void addFim(Lista** lista, int add);
void addMeio(Lista** lista, int add, int ant);
void imprimir(Lista* lista);
Lista* remover(Lista** lista, int remov);
Lista* buscar(int id, Lista* listas);
void esvaziar(Lista** lista);

int main() {
	return 0;
}

void addInicio(Lista** lista, int add) {
	Lista* novo = NULL;
	novo = (Lista*)malloc(sizeof(Lista));
	if (novo == NULL) {
		printf("Erro de alocacao \n");
		exit(1);
	}
	novo->valor = add;
	novo->proximo = *lista;
	*lista = novo;
}

void addFim(Lista** lista, int add) {
	Lista* novo = NULL;
	novo = (Lista*)malloc(sizeof(Lista));
	if (novo == NULL) {
		printf("Erro de alocacao \n");
		exit(1);
	}
	novo->valor = add;
	novo->proximo = NULL;

	// eh o primeiro?
	if (*lista == NULL)
		*lista = novo;
	else {
		Lista* aux = *lista;
		while (aux->proximo != NULL)
			aux = aux->proximo;
		aux->proximo = novo;
	}
}

void addMeio(Lista** lista, int add, int ant) {
	Lista* novo = NULL;
	novo = (Lista*)malloc(sizeof(Lista));
	if (novo == NULL) {
		printf("Erro de alocacao \n");
		exit(1);
	}
	novo->valor = add;

	// eh o primeiro?
	if (*lista == NULL) {
		novo->proximo = NULL;
		*lista = novo;
	}
	else {
		Lista* aux = *lista;
		while (aux->valor != ant && aux->proximo != NULL)
			aux = aux->proximo;
		novo->proximo = aux->proximo;
		aux->proximo = novo;
	}
}

void imprimir(Lista* lista) {
	while (lista != NULL) {
		printf("%d", lista->valor);
		lista = lista->proximo;
	}
}

Lista* remover(Lista** lista, int remov) {
	Lista *aux, *del = NULL;
	if ((*lista)->valor == remov) { // Se for o primeiro
		del = *lista;
		*lista = del->proximo;
	}
	else {
		aux = *lista;
		while(aux->proximo != NULL && aux->proximo->valor != remov)
			aux = aux->proximo;
		if (aux->proximo != NULL) {
			del = aux->proximo;
			aux->proximo = del->proximo;
		}
	}
	return del;
}
Lista* buscar(int id, Lista* listas) {
	Lista* q = NULL;
	q = listas;
	while (q != NULL && q->valor != id) {
		q = q->proximo;
	}
	return q; // retorna nulo se nao encontrar
}

void esvaziar(Lista** lista) {
	Lista* aux = NULL, * temp = NULL;
	aux = *lista;

	while (aux != NULL) {
		temp = aux;
		aux = aux->proximo;
		free(temp);
	}

	*lista = NULL;
}