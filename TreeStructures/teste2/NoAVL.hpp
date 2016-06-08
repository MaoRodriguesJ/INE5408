// Copyright [2016] <Salomão Rodrigues Jacinto>

#ifndef NO_AVL_HPP
#define NO_AVL_HPP

#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

/**
 * @brief      Implementação de uma estrutura de Árvore AVL em C++
 */
template <typename T>
class NoAVL  {
 private:
	int altura;  //!< Representa a altura do nó AVL
	T* dado;  //!< Dado genérico do nó
	NoAVL<T>* esquerda;  //!< Ponteiro para o nó a esquerda
	NoAVL<T>* direita;  //!< Ponteiro para o nó a direita
	std::vector<NoAVL<T>* > elementos;  //!< Elemento acessados durante
										// o percurso realizado

 public:
	/**
	 * @brief      Construtor da classe NoAVL
	 *
	 * @param      dado  Dado do nó que será criado
	 *
	 * @details    Os ponteiros esquerda e direita apontam para nullptr e a
	 *             altura é colocada em 0
	 */
	explicit NoAVL(const T& dado) {
		altura = 0;
		esquerda = nullptr;
		direita = nullptr;
		this->dado = new T(dado);
		elementos.clear();
	}
	/**
	 * @brief      Destrutor NoAVL
	 */
	virtual ~NoAVL() {
		delete dado;
		if(esquerda != nullptr) {
			delete esquerda;
		}
		if(direita != nullptr) {
			delete direita;
		}
	}
	/**
	 * @brief      Get Altura
	 *
	 * @return     int altura
	 */
	int getAltura() {
		return altura;
	}
	/**
	 * @brief      teste de altura caso o nó seja nulo
	 *
	 * @return     int altura
	 */
	int height(NoAVL<T>* node) {
		if(node == nullptr)
			return -1;
		else
			return node->getAltura();
	}
	/**
	 * @brief      teste de altura caso o nó da esquerda seja nulo e tente
	 * 			   retornar sua altura
	 *
	 * @return     int altura
	 */
	int heightAtLeft(NoAVL<T>* node) {
		if(node == nullptr)
			return -1;
		else
			return height(node->getEsquerda());
	}
	/**
	 * @brief      teste de altura caso o nó da direita seja nulo e tente
	 * 			   retornar sua altura
	 *
	 * @return     int altura
	 */
	int heightAtRight(NoAVL<T>* node) {
		if(node == nullptr)
			return -1;
		else
			return height(node->getDireita());
	}
	/**
	 * @brief      Get elementos
	 *
	 * @return     Vector elementos
	 */
	std::vector<NoAVL<T>* > getElementos() {
		return elementos;
	}
	 /**
	 * @brief      Get esquerda
	 *
	 * @return     NoAVL a esquerda
	 */
	NoAVL<T>* getEsquerda() {
		return esquerda;
	}
	 /**
	 * @brief      Get direita
	 *
	 * @return     NoAVL a direita
	 */
	NoAVL<T>* getDireita() {
		return direita;
	}
	/**
	 * @brief      Retorna o nó com o menor valor a partir de um determinado nó
	 *
	 * @param      nodo  Nó para início da busca
	 *
	 * @return     Nó que possuí o menor valor
	 */
	NoAVL<T>* minimo(NoAVL<T>* nodo) {
		if(nodo->getEsquerda() == nullptr) {
			return nodo;
		} else {
			nodo = minimo(nodo->getEsquerda());
			return nodo;
		}
	}
	/**
	 * @brief      Get dado
	 *
	 * @return     T dado
	 */
	T* getDado() {
		return dado;
	}
	/**
	 * @brief      Busca Binária
	 *
	 * @param      dado  Dado a ser pesquisado
	 * @param      arv   Árvore para pesquisar o dado
	 *
	 * @return     Retorna o nó que contém o dado, retornadndo um nullptr caso o
	 *             dado não exista na árvore
	 */
	T* busca(const T& dado, NoAVL<T>* arv) {
		while(arv != nullptr && *(arv->getDado()) != dado) {
			if(*(arv->getDado()) < dado) {
				arv = arv->getDireita();
			} else {
				arv = arv->getEsquerda();
			}
		}
		if(arv == nullptr) {
			throw std::runtime_error("Dado não encontrado");
		} else {
			return arv->getDado();
		}
	}
	/**
	 * @brief      Organiza os nós em um vetor começando pela raiz, depois pelos
	 *             nós a esquerda e depois pelos nós a direita
	 *
	 * @param      nodo  Nó para início da ordenação
	 */
	void preOrdem(NoAVL<T>* nodo) {
		if(nodo != nullptr) {
			elementos.push_back(nodo);
			preOrdem(nodo->getEsquerda());
			preOrdem(nodo->getDireita());
		}
	}
	/**
	 * @brief      Organiza os nós em um vetor começando pelos nós a esquerda,
	 *             depois pela raiz e pelos nós a direita
	 *
	 * @param      nodo  Nó para início da ordenação
	 */
	void emOrdem(NoAVL<T>* nodo) {
		if(nodo != nullptr) {
			emOrdem(nodo->getEsquerda());
			elementos.push_back(nodo);
			emOrdem(nodo->getDireita());
		}
	}
	/**
	 * @brief      Organiza os nós em um vetor começando pelos nós a esquerda,
	 *             depois pelos nós a direita e a raiz
	 *
	 * @param      nodo  Nó para início da ordenação
	 */
	void posOrdem(NoAVL<T>* nodo) {
		if(nodo != nullptr) {
			posOrdem(nodo->getEsquerda());
			posOrdem(nodo->getDireita());
			elementos.push_back(nodo);
		}
	}
////////////////////////////////////////////////////////////////////////////////
//  FALTA DOCUMENTAR
////////////////////////////////////////////////////////////////////////////////
	NoAVL<T>* rightRotate(NoAVL<T> *k2) {
		NoAVL<T> *k1;
		k1 = k2->getEsquerda();
		k2->esquerda = k1->getDireita();
		k1->direita = k2;

		k2->altura = std::max(height(k2->getDireita()),
							  height(k2->getEsquerda()))+1;
		k1->altura = std::max(height(k1->getDireita()),
							  height(k1->getEsquerda()))+1;
		return k1;
	}
	NoAVL<T>* leftRotate(NoAVL<T> *k2) {
		NoAVL<T> *k1;
		k1 = k2->getDireita();
		k2->direita = k1->getEsquerda();
		k1->esquerda = k2;

		k2->altura = std::max(height(k2->getDireita()),
							  height(k2->getEsquerda()))+1;
		k1->altura = std::max(height(k1->getDireita()),
							  height(k1->getEsquerda()))+1;
		return k1;
	}
	NoAVL<T>* doubleRotateAtLeft(NoAVL<T> *k3) {
		k3->esquerda = leftRotate(k3->getEsquerda());
		return rightRotate(k3);
	}
	NoAVL<T>* doubleRotateAtRight(NoAVL<T> *k3) {
		k3->direita = rightRotate(k3->getDireita());
		return leftRotate(k3);
	}
	NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
		NoAVL<T>* arv_rodada;
		if(arv == nullptr) {
			arv = new NoAVL<T>(dado);
		} else {
			 if (dado < *arv->getDado()) {
				arv->esquerda = inserir(dado, arv->getEsquerda());
				if ((height(arv->getEsquerda()) -
					 height(arv->getDireita())) > 1) {
					if (dado < *arv->esquerda->getDado()) {
						arv_rodada = rightRotate(arv);
					} else {
						arv_rodada = doubleRotateAtLeft(arv);
					}
					return arv_rodada;
				} else {
					arv->altura = std::max(height(arv->getEsquerda()),
										   height(arv->getDireita())) + 1;
				}
			} else {
				arv->direita = inserir(dado, arv->getDireita());
				if ((height(arv->getDireita()) -
					 height(arv->getEsquerda())) > 1) {
					if (dado > *arv->direita->getDado()) {
						arv_rodada = leftRotate(arv);
					} else {
						arv_rodada = doubleRotateAtRight(arv);
					}
					return arv_rodada;
				} else {
					arv->altura = std::max(height(arv->getDireita()),
										   height(arv->getEsquerda())) + 1;
				}
			}
		}
		return arv;
	}
	NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
		NoAVL<T> *tmp, *filho;
		if (arv == NULL) {
			return arv;
		} else {
			if (dado < *arv->getDado()) {
				arv->esquerda = remover(arv->getEsquerda(), dado);
				if (height(arv->getEsquerda()) > height(arv->getDireita())) {
					if (heightAtLeft(arv->getEsquerda()) >=
						heightAtRight(arv->getEsquerda())) {
						arv = rightRotate(arv);
					} else {
						arv = doubleRotateAtLeft(arv);
					}
				} else if (height(arv->getEsquerda()) < height(arv->getDireita())) {
					if (heightAtRight(arv->getDireita()) >=
						heightAtLeft(arv->getDireita())) {
						arv = leftRotate(arv);
					} else {
						arv = doubleRotateAtRight(arv);
					}
				}

				arv->altura = std::max(height(arv->getEsquerda()),
									   height(arv->getDireita())) + 1;
				return arv;
			} else {
				if (dado > *arv->getDado()) {
					arv->direita = remover(arv->getDireita(), dado);
				if (height(arv->getEsquerda()) > height(arv->getDireita())) {
					if (heightAtLeft(arv->getEsquerda()) >=
						heightAtRight(arv->getEsquerda())) {
						arv = rightRotate(arv);
					} else {
						arv = doubleRotateAtLeft(arv);
					}
				} else if (height(arv->getEsquerda()) < height(arv->getDireita())) {
					if (heightAtRight(arv->getDireita()) >=
						heightAtLeft(arv->getDireita())) {
						arv = leftRotate(arv);
					} else {
						arv = doubleRotateAtRight(arv);
					}
				}
				arv->altura = std::max(height(arv->getEsquerda()),
									   height(arv->getDireita())) + 1;


					return arv;
				} else {
					if (arv->getDireita() != NULL &&
												arv->getEsquerda() != NULL) {
						tmp = minimo(arv->getDireita());
						*arv->dado = *tmp->getDado();
						arv->direita = remover(arv->getDireita(),
						*arv->getDado());
						arv->altura = std::max(height(arv->getEsquerda()),
											   height(arv->getDireita())) + 1;

						return arv;
					} else {
						tmp = arv;
						if (arv->getDireita() != NULL) {
							filho = arv->getDireita();
							return filho;
						} else {
							if (arv->getEsquerda() != NULL) {
								filho = arv->getEsquerda();
								return filho;
							} else {
								delete arv;
								return NULL;
							}
						}
					}
				}
			}
		}
	}
};

#endif /* NO_AVL_HPP */
