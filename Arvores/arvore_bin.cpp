#include <iostream>

using namespace std;

typedef struct no{
	int id;

	no *esquerda;
	no *direita;
	no *pai;
} No;

class Arvore {
private:
	No* raiz;

public:
	Arvore(No* no = NULL) {
		raiz = no;
	}
	No* busca_Arvore(No* no, int id);
	No* minimo_Arvore(No* no);
	No* maximo_Arvore(No* no);
	No* sucessor(No* no);
	No* antecessor(No* no);
	void inserir(No* add);
	void transplante(No* u, No* v);
	void deletar_Arvore(No* apaga);
	void freeArvore();
};

/*int main() {
	Arvore tree;
	No* novo = NULL;
	novo = new No;
	if (novo == NULL) {
		cout << "Erro de alocacao \n";
		exit(1);
	}
	novo->id = 1;
	novo->esquerda = novo->direita = novo->pai = NULL;
	tree.inserir(novo);
	novo = new No;
	if (novo == NULL) {
		cout << "Erro de alocacao \n";
		exit(1);
	}
	novo->id = 2;
	novo->esquerda = novo->direita = novo->pai = NULL;
	tree.inserir(novo);
	novo = tree.antecessor(novo);
	cout << "Valor: " << novo->id << endl;
	
	tree.freeArvore();
	return 0;
}*/

No* Arvore::busca_Arvore(No* no, int k) {
	if (no == NULL || k == no->id) {
		return no;
	}
	else if (no->id > k) {
		return busca_Arvore(no->esquerda, k);
	}
	else {
		return busca_Arvore(no->direita, k);
	}
}

No* Arvore::minimo_Arvore(No* no) {
	while (no->esquerda != NULL) {
		no = no->esquerda;
	}
	return no;
}

No* Arvore::maximo_Arvore(No* no) {
	while (no->direita != NULL) {
		no = no->direita;
	}
	return no;
}

No* Arvore::sucessor(No* no) {
	if (no->direita != NULL)
		return minimo_Arvore(no->direita);
	else {
		No* aux = no->pai;
		while (aux != NULL && no == aux->direita) {
			no = aux;
			aux = aux->pai;
		}
		return aux;
	}
}

No* Arvore::antecessor(No* no) {
	if (no->esquerda != NULL)
		return maximo_Arvore(no->esquerda);
	else {
		No* aux = no->pai;
		while (aux != NULL && no == aux->esquerda) {
			no = aux;
			aux = aux->pai;
		}
		return aux;
	}
}

void Arvore::inserir(No *add) {
	No *x = raiz, *y = NULL;
	
	while (x != nullptr) {
		y = x;
		if (add->id < x->id) {
			x = x->esquerda;
		}
		else {
			x = x->direita;
		}
	}
	add->pai = y;
	if (y == NULL)
		raiz = add; // Arvore era vazia
	else if (add->id < y->id)
		y->esquerda = add;
	else
		y->direita = add;
}

void Arvore::transplante(No* u, No* v) {
	if (u->pai == NULL) {
		raiz = v;
	}
	else if(u == u->pai->esquerda){
		u->pai->esquerda = v;
	}
	else {
		u->pai->direita = v;
	}
	if (v != NULL) {
		v->pai = u->pai;
	}
}
void Arvore::deletar_Arvore(No* apaga) {
	if (apaga == NULL)
		return;
	if (apaga->esquerda == NULL)
		transplante(apaga, apaga->direita);
	else if (apaga->direita == NULL)
		transplante(apaga, apaga->esquerda);
	else {
		No* y = minimo_Arvore(apaga->direita);
		if (y->pai != apaga) {
			transplante(y, y->direita);
			y->direita = apaga->direita;
			y->direita->pai = y;
		}
		transplante(apaga, y);
		y->esquerda = apaga->esquerda;
		y->esquerda->pai = y;
	}

}

void Arvore::freeArvore() {
	if (raiz == NULL)
		return;

	No* nos = raiz;
	No* parent = NULL;

	while (nos != NULL) {
		if (nos->esquerda == NULL) {
			// Se não há filho esquerdo, deletamos o nó atual e movemos para o direito
			No* temp = nos->direita;
			delete nos;
			nos = temp;
		}
		else {
			// Encontramos o predecessor in-order do nó atual
			No* predecessor = nos->esquerda;
			while (predecessor->direita != NULL && predecessor->direita != nos) {
				predecessor = predecessor->direita;
			}

			if (predecessor->direita == NULL) {
				// Estabelecemos um link temporário do predecessor para nos
				predecessor->direita = nos;
				nos = nos->esquerda;
			}
			else {
				// Removemos o link temporário e deletamos o nó atual
				predecessor->direita = NULL;
				No* temp = nos->direita;
				delete nos;
				nos = temp;
			}
		}
	}
	raiz = NULL; // Certificamos que a raiz é NULL após deletar todos os nós
}