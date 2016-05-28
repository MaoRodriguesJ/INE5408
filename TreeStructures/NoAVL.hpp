#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <stdexcept>

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
		altura = 0;
		esquerda = nullptr;
		direita = nullptr;
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
	NoAVL<T>* inserir(const T& data, NoAVL<T>* tree) {
		return insercaoAVL(data, tree);
	}
	int height(NoAVL<T>* node) {
		if(node == nullptr)
			return -1;
		else
			return node->getAltura();
	}
	int balanceFactor(NoAVL<T>* node) {
		if(node == nullptr)
			return 0;
		else
			return (height(node->getEsquerda()) -
				    height(node->getDireita()));
	}
	NoAVL<T>* rightRotation(NoAVL<T>* k2) {
		NoAVL<T> *k1;
		k1 = k2->getEsquerda();
		k2->esquerda = k1->getDireita();
		k1->direita = k2;

		k2->altura = std::max(height(k2->getEsquerda()), height(k2->getDireita()))+1;
		k1->altura = std::max(height(k1->getEsquerda()), height(k1->getDireita()))+1;
		return k1;
	}
	NoAVL<T>* leftRotation(NoAVL<T> *k2) {
		NoAVL<T> *k1;
		k1 = k2->getDireita();
		k2->direita = k1->getEsquerda();
		k1->esquerda = k2;

		k2->altura = std::max(height(k2->getEsquerda()), height(k2->getDireita()))+1;
		k1->altura = std::max(height(k1->getEsquerda()), height(k1->getDireita()))+1;
		return k1;
	}
	NoAVL<T>* doubleRotationAtLeft(NoAVL<T> *k3) {
		k3->esquerda = leftRotation(k3->getEsquerda());
		return rightRotation(k3->getEsquerda());
	}
	NoAVL<T>* doubleRotationAtRight(NoAVL<T> *k3) {
		k3->direita = rightRotation(k3->getDireita());
		return leftRotation(k3->getDireita());
	}
////////////////////////////////////////////////////////////////////////////////
// ROTAÇÕES NAO ESTAO FUNCIONANDO
////////////////////////////////////////////////////////////////////////////////
	NoAVL<T>* insercaoAVL(const T& data, NoAVL<T>* tree) {
		tree->altura = std::max(height(tree->getEsquerda()),
								height(tree->getDireita()))+2;

		if(data < *(tree->getDado())) {
			if(tree->getEsquerda() == nullptr) {
				tree->esquerda = new NoAVL<T>(data);
			} else {
				tree = insercaoAVL(data, tree->getEsquerda());
				int balance = balanceFactor(tree);
				if(balance > 1) {
					if(data > *(tree->esquerda->getDado())) {
						tree = rightRotation(tree);
					} else {
						tree = doubleRotationAtLeft(tree);
					}
				}
				if(balance < -1) {
					if(data < *(tree->direita->getDado())) {
						tree = leftRotation(tree);
					} else {
						tree = doubleRotationAtRight(tree);
					}
				}
			}
		} else {
			if(tree->getDireita() == nullptr) {
				tree->direita = new NoAVL<T>(data);
			} else {
				tree = insercaoAVL(data, tree->getDireita());
				int balance = balanceFactor(tree);
				if(balance > 1) {
					if(data > *(tree->esquerda->getDado())) {
						tree = rightRotation(tree);
					} else {
						tree = doubleRotationAtLeft(tree);
					}
				}
				if(balance < -1) {
					if(data < *(tree->direita->getDado())) {
						tree = leftRotation(tree);
					} else {
						tree = doubleRotationAtRight(tree);
					}
				}
			}
		}

		tree->altura = std::max(height(tree->getEsquerda()),
								height(tree->getDireita()))+1;

		return tree;
	}
////////////////////////////////////////////////////////////////////////////////
// SEM ROTAÇÕES
////////////////////////////////////////////////////////////////////////////////
	NoAVL<T>* remover(NoAVL<T>* tree, const T& data) {
		if(tree == nullptr) {
			return tree;
		} else {
			NoAVL<T> *tmp, *son;
			if(data < *(tree->getDado())) {
				tree->esquerda = remover(tree->getEsquerda(), data);
				return tree;
			} else {
				if(data > *(tree->getDado())) {
					tree->direita = remover(tree->getDireita(), data);
					return tree;
				} else {
					tmp = tree;
					if(tree->getDireita() != nullptr &&
					   tree->getEsquerda() != nullptr) {
						tmp = minimo(tree->getDireita());
						tree->dado = tmp->getDado();
						tree->direita = remover(tree->getDireita(),
											   *(tree->getDado()));
						return tree;
					} else {
						if(tree->getDireita() != nullptr) {
							son = tree->getDireita();
							return son;
						} else {
							if(tree->getEsquerda() != nullptr) {
								son = tree->getEsquerda();
								return son;
							} else {
								delete tmp;
								return nullptr;
							}
						}
					}
				}
			}
		}
	}

};

#endif  //NO_AVL_HPP