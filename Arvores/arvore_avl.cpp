#include <iostream>

using namespace std;

typedef struct no {
	int id;
	int altura;

	no* esquerda;
	no* direita;
	no* pai;
} No;

class AVL {
private:
	No* raiz;
public:
	AVL(No* no = NULL) {
		raiz = no;
	}
	No* busca_Arvore(No* no, int id);
	No* novoNo(int x);
	No* rotacaoEsquerda(No* r);
	No* rotacaoDireita(No* r);
	No* rotacaoDireitaEsquerda(No* r);
	No* rotacaoEsquerdaDireita(No* r);
	No* balancear(No* nos);
	No* inserir(No* nos, int x);
	int alturaNo(No* no);
	int maior(int a, int b);
	int fatorBalanceamento(No* no);
	void freeArvore();
};

No* AVL::busca_Arvore(No* no, int k) {
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

No* AVL::novoNo(int x) {
	No* novo = new No;
	if (novo == NULL) {
		cout << "Erro de alocacao";
		exit(1);
	}
	novo->id = x;
	novo->direita = novo->esquerda = novo->pai = NULL;
	novo->altura = 0;

	return novo;
}

No* AVL::rotacaoEsquerda(No* r) {
	No *y = NULL, *f = NULL;

	y = r->direita;
	f = y->esquerda;

	y->esquerda = r;
	r->direita = f;

	if (f != NULL) 
		f->pai = r;

	y->pai = r->pai;
	r->pai = y;


	r->altura = maior(alturaNo(r->esquerda), alturaNo(r->direita)) + 1;
	y->altura = maior(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

	return y;
}

No* AVL::rotacaoDireita(No* r) {
	No *y = NULL, *f = NULL;

	y = r->esquerda;
	f = y->direita;

	y->direita = r;
	r->esquerda = f;

	if (f != NULL)
		f->pai = r;
	y->pai = r->pai;
	r->pai = y;

	r->altura = maior(alturaNo(r->esquerda), alturaNo(r->direita)) + 1;
	y->altura = maior(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

	return y;
}

No* AVL::rotacaoDireitaEsquerda(No* r) {
	r->direita = rotacaoDireita(r->direita);
	return rotacaoEsquerda(r);
}

No* AVL::rotacaoEsquerdaDireita(No* r) {
	r->esquerda = rotacaoEsquerda(r->esquerda);
	return rotacaoDireita(r);
}

No* AVL::balancear(No* nos) {
	int fb, fb_esq, fb_dir;
	fb = fatorBalanceamento(nos);
	fb_esq = fatorBalanceamento(nos->esquerda);
	fb_dir = fatorBalanceamento(nos->direita);

	// rotacao a esquerada
	if (fb < -1 && fb_dir <= 0)
		nos = rotacaoEsquerda(nos);
	// rotacao a direita
	else if (fb > 1 && fb_esq >= 0)
		nos = rotacaoDireita(nos);
	// rotacao dupla a esquerda
	else if (fb > 1 && fb_esq < 0)
		nos = rotacaoEsquerdaDireita(nos);
	// rotacao dupla a direita
	else if (fb < -1 && fb_dir > 0)
		nos = rotacaoDireitaEsquerda(nos);

	return nos;
}

No* AVL::inserir(No* nos, int x) {
	if (nos == NULL) // Arvore vazia
		return novoNo(x);
	else { // insercao na direita ou esquerda
		if (x < nos->id) {
			nos->esquerda = inserir(nos->esquerda, x);
		}
		else if (x > nos->id) {
			nos->direita = inserir(nos->direita, x);
		}
		else
			cout << "O elemento" << nos->id << "ja existe \n";
	}

	// Recalcula a altura
	nos->altura = maior(alturaNo(nos->esquerda), alturaNo(nos->direita)) + 1;

	// Balancear
	nos = balancear(nos);
	return nos;
}

int AVL::alturaNo(No* no) {
	if (no == NULL)
		return -1;
	else
		return no->altura;
}

int AVL::fatorBalanceamento(No* no) {
	if (no != NULL)
		return (alturaNo(no->esquerda) - alturaNo(no->direita));
	else
		return 0;
}

int AVL::maior(int a, int b) {
	return (a > b) ? a : b;
}

void AVL::freeArvore() {
	if (raiz == NULL)
		return;

	No* nos = raiz;
	No* parent = NULL;

	while (nos != NULL) {
		if (nos->esquerda == NULL) {
			No* temp = nos->direita;
			delete nos;
			nos = temp;
		}
		else {
			No* predecessor = nos->esquerda;
			while (predecessor->direita != NULL && predecessor->direita != nos) {
				predecessor = predecessor->direita;
			}

			if (predecessor->direita == NULL) {
				predecessor->direita = nos;
				nos = nos->esquerda;
			}
			else {
				predecessor->direita = NULL;
				No* temp = nos->direita;
				delete nos;
				nos = temp;
			}
		}
	}
	raiz = NULL;
}