#include <iostream>

using namespace std;

class heap {
private:
	int tam;
	int compr;
	int* elem;
public:
	heap(int t = 0, int c = 0, int* el = NULL) {
		tam = t;
		compr = c;
		elem = el;
	}
	int pai(int);
	int esquerda(int);
	int direita(int);
	void max_Heapfy(int*, int);
	void cria_maxHeap();
	void min_Heapfy(int*, int);
	void cria_minHeap();
	void insert(int);
	void printa();
	int tira_max();
	void freeHeap();
};

 int main() {
	heap H;
	H.insert(1);
	H.insert(10);
	H.insert(25);
	H.insert(9);
	H.insert(5);
	H.cria_maxHeap();
	H.printa();
	H.tira_max();
	H.printa();

	H.freeHeap();
	return 0;
}

int heap::pai(int pos) {
	return (pos - 1) / 2;
}
int heap::esquerda(int pos) {
	return 2 * pos + 1;
}

int heap::direita(int pos) {
	return (2 * pos) + 2;
}

void heap::max_Heapfy(int* vet, int pos) {
	int l = esquerda(pos);
	int r = direita(pos);
	int pMaior = pos;

	if (l <= tam && vet[l] > vet[pMaior]) {
		pMaior = l;
	}
	if (r <= tam && vet[r] > vet[pMaior]) {
		pMaior = r;
	}

	if (pMaior != pos) {
		int temp = vet[pos];
		vet[pos] = vet[pMaior];
		vet[pMaior] = temp;
		max_Heapfy(vet, pMaior);
	}
}


void heap::cria_maxHeap() {
	tam = compr;
	for (int i = (tam / 2) - 1; i >= 0; i--) {
		max_Heapfy(elem, i);
	}
}

void heap::min_Heapfy(int* vet, int pos) {
	int l = esquerda(pos);
	int r = direita(pos);
	int pMenor = pos;
	if (l < tam && vet[l] < vet[pMenor]) {
		pMenor = l;
	}
	if (r < tam && vet[r] < vet[pMenor]) {
		pMenor = r;
	}
	if (pMenor != pos) {
		int temp = vet[pos];
		vet[pos] = vet[pMenor];
		vet[pMenor] = temp;
		min_Heapfy(vet, pos);
	}
}
void heap::cria_minHeap() {
	tam = compr;
	for (int i = (tam / 2) - 1; i >= 0; i--) {
		min_Heapfy(elem, i);
	}
}

void heap::insert(int ins) {
	if (elem == nullptr) {
		compr = 1;
		elem = new int[1];
		if (elem == nullptr) {
			cout << "Erro de alocacao";
			exit(1);
		}
		elem[0] = ins;
	}
	else {
		compr++;
		int* temp = new int[compr];
		if (temp == nullptr) {
			cout << "Erro de alocacao";
			exit(1);
		}
		for (int i = 0; i < compr - 1; i++) {
			temp[i] = elem[i];
		}
		temp[compr - 1] = ins;
		delete[] elem;
		elem = temp;
	}
}

void heap::printa() {
	for (int i = 0; i < tam; i++) {
		cout << elem[i] << " ";
	}
	cout << "\n";
}

int heap::tira_max() {
	if (tam < 1) {
		cout << "Erro underflow" << "\n";
		return -1;
	}
	int max = elem[0];
	elem[0] = elem[tam - 1];
	tam--;
	max_Heapfy(elem, 0);
	return max;
}

void heap::freeHeap() {
	delete[] elem;
}