#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>
#include <stdexcept>

//ALTURA CAGADA
//REMOVER CAGADO
//TESTE DO JEAN COMPLETAMENTE CAGADO

template <typename T>
class NoAVL {
 private:
	int altura;  //!< Representa a altura do nó AVL
	T* dado;  //!< Dado genérico do nó
	NoAVL<T>* esquerda;  //!< Ponteiro para o nó a esquerda
	NoAVL<T>* direita;  //!< Ponteiro para o nó a direita
	std::vector<NoAVL<T>* > elementos;  //!< Elemento acessados durante
										// o percurso realizado

 public:
	explicit NoAVL(const T& data) {
		altura = 1;
		esquerda = 0;
		direita = 0;
		dado = new T(data);
	}
	virtual ~NoAVL() {
		delete dado;
		if(esquerda != nullptr)
			delete esquerda;
		if(direita != nullptr)
			delete direita;
	}
	int getAltura() {
		return altura;
	}
	NoAVL<T>* getEsquerda() {
		return esquerda;
	}
	NoAVL<T>* getDireita() {
		return direita;
	}
	NoAVL<T>* minimo(NoAVL<T>* node) {
		if(node->getEsquerda() == nullptr)
			return node;
		else {
			node = minimo(node->getEsquerda());
			return node;
		}
	}
	NoAVL<T>* removerMinimo(NoAVL<T>* nodo) {
		if (nodo->esquerda == 0) {
			return nodo->direita;
		}
		nodo->esquerda = removerMinimo(nodo->esquerda);
		return balancear(nodo);
	}
	T* getDado() {
		return dado;
	}
	std::vector<NoAVL<T>* > getElementos() {
		return elementos;
	}
	T* busca(const T& data, NoAVL<T>* tree) {
		while(tree != nullptr && *(tree->getDado()) != data) {
			if(*(tree->getDado()) < data)
				tree = tree->getDireita();
			else
				tree = tree->getEsquerda();
		}
		if(tree == nullptr)
			throw std::runtime_error("Dado não encontrado");
		else
			return tree->getDado();
	}
	void preOrdem(NoAVL<T>* node) {
		if(node != nullptr) {
			elementos.push_back(node);
			preOrdem(node->getEsquerda());
			preOrdem(node->getDireita());
		}
	}
	void emOrdem(NoAVL<T>* node) {
		if(node != nullptr) {
			preOrdem(node->getEsquerda());
			elementos.push_back(node);
			preOrdem(node->getDireita());
		}
	}
	void posOrdem(NoAVL<T>* node) {
		if(node != nullptr) {
			posOrdem(node->getEsquerda());
			posOrdem(node->getDireita());
			elementos.push_back(node);
		}
	}
	int height(NoAVL<T>* nodo) {
		return nodo ? nodo->altura : 0;
	}
	int fator(NoAVL<T>* nodo) {
		return (height(nodo->direita) - height(nodo->esquerda));
	}
	void arrumarAltura(NoAVL<T>* nodo) {
		int hL = height(nodo->esquerda);
		int hR = height(nodo->direita);
		nodo->altura = (hL > hR ? hL : hR) + 1;
	}
	NoAVL<T>* rotacao_direita(NoAVL<T>* raiz) {
		NoAVL<T>* auxiliar = raiz->esquerda;
		raiz->esquerda = 0;
		auxiliar->direita = raiz;
		raiz = auxiliar;
		arrumarAltura(raiz);
		arrumarAltura(auxiliar);
		return raiz;
	}
	NoAVL<T>* rotacao_esquerda(NoAVL<T>* raiz) {
		NoAVL<T>* auxiliar = raiz->direita;
		raiz->direita = 0;
		auxiliar->esquerda = raiz;
		raiz = auxiliar;
		arrumarAltura(raiz);
		arrumarAltura(auxiliar);
		return raiz;
	}
	NoAVL<T>* rotacao_dupla_esquerda(NoAVL<T>* raiz) {
		raiz->esquerda = rotacao_direita(raiz->esquerda);
		return rotacao_esquerda(raiz);
	}
	NoAVL<T>* rotacao_dupla_direita(NoAVL<T>* raiz) {
		raiz->direita = rotacao_esquerda(raiz->direita);
		return rotacao_direita(raiz);
	}
	NoAVL<T>* balancear(NoAVL<T>* raiz) {
		arrumarAltura(raiz);
		if (fator(raiz) == 2) {
			if (fator(raiz->direita) < 0) {
				// return rotacao_dupla_direita(raiz);
				raiz->direita = rotacao_direita(raiz->direita);
			}
			raiz = rotacao_esquerda(raiz);
			return raiz;
		}
		if (fator(raiz) == -2) {
			if (fator(raiz->esquerda) > 0) {
				// return rotacao_dupla_esquerda(raiz);
				raiz->esquerda = rotacao_esquerda(raiz->esquerda);
			}
			raiz = rotacao_direita(raiz);
			return raiz;
		}
		return raiz;
	}
	NoAVL<T>* inserir(const T& dado, NoAVL<T>* nodo) {
		if (nodo == 0) {
			return nodo = new NoAVL<T>(dado);
		}
		if (dado < *(nodo->dado)) {
			nodo->esquerda = inserir(dado, nodo->esquerda);
		} else {
			nodo->direita = inserir(dado, nodo->direita);
		}
		nodo = balancear(nodo);
		return nodo;
	}
	NoAVL<T>* remover(NoAVL<T>* nodo, const T& dado) {
		if (!nodo) {
			throw 0;
		}
		if (dado < *(nodo->dado)) {
			nodo->esquerda = remover(nodo->esquerda, dado);
		} else if (dado > *(nodo->dado)) {
			nodo->direita = remover(nodo->direita, dado);
		} else {
			NoAVL<T>* esq = nodo->esquerda;
			NoAVL<T>* dir = nodo->direita;
			delete nodo;
			if (!dir) {
				return esq;
			}
			NoAVL<T>* min = minimo(dir);
			min->direita = removerMinimo(dir);
			min->esquerda = esq;
			return balancear(min);
		}
		return balancear(nodo);
	}

};

#endif  //NO_AVL_HPP