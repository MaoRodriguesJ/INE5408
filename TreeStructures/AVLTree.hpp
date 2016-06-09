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
	/**
	 * @brief      Uma função para atualizar a altura de um nó
	 *
	 * @param      nodo  Nó o qual quer se atualizar a altura
	 */
	void updateHeight(NoAVL<T>* node) {
		node->altura = std::max(height(node->getDireita()),
								height(node->getEsquerda()))+1;
	}
	/**
	 * @brief      Rotação para direita (ou rotação à esquerda)
	 *
	 * @param      k2  nó desbalanceado
	 *
	 * @return         k2         k1
	 * 			      /    	     /  \
	 * 			     k1    ->   x    k2
	 * 			    /
	 *			   x
	 */
	NoAVL<T>* rightRotate(NoAVL<T> *k2) {
		NoAVL<T> *k1;
		k1 = k2->getEsquerda();
		k2->esquerda = k1->getDireita();
		k1->direita = k2;

		updateHeight(k2);
		updateHeight(k1);

		return k1;
	}
	/**
	 * @brief      Rotação para esquerda (ou rotação à direita)
	 *
	 * @param      k2  nó desbalanceado
	 *
	 * @return     k2              k1
	 * 			     \    	      /  \
	 * 			      k1    ->   k2   x
	 * 			       \
	 *			        x
	 */
	NoAVL<T>* leftRotate(NoAVL<T> *k2) {
		NoAVL<T> *k1;
		k1 = k2->getDireita();
		k2->direita = k1->getEsquerda();
		k1->esquerda = k2;

		updateHeight(k2);
		updateHeight(k1);

		return k1;
	}
	/**
	 * @brief      Dupla rotação à esquerda
	 *
	 * @param      k3  nó desbalanceado
	 *
	 * @return       k3            k3			 y			Onde o y inicial é
	 * 			    /    	      /			    / \   	    maior que x e menor
	 * 			   x      ->     y      ->     x   k3  		que k3.
	 * 			    \			/
	 *	             y		   x
	 */
	NoAVL<T>* doubleRotateAtLeft(NoAVL<T> *k3) {
		k3->esquerda = leftRotate(k3->getEsquerda());
		return rightRotate(k3);
	}
	/**
	 * @brief      Dupla rotação à direita
	 *
	 * @param      k3  nó desbalanceado
	 *
	 * @return     k3          k3			   y		Onde o y inicial é maior
	 * 			     \ 	      	 \		      / \   	que k3 e menor que x.
	 * 			      x    ->     y     ->   k3  x
	 * 			     /			   \
	 *	            y		        x
	 */
	NoAVL<T>* doubleRotateAtRight(NoAVL<T> *k3) {
		k3->direita = rightRotate(k3->getDireita());
		return leftRotate(k3);
	}
	/**
	 * @brief      Teste de balanceamento
	 *
	 * @return     int altura nó esquerdo - altura nó direito
	 */
	int balanceFactor(NoAVL<T>* node) {
		if(node == nullptr)
			return 0;
		return height(node->getEsquerda()) - height(node->getDireita());
	}
	/**
	 * @brief      Insere novo dado na árvore
	 *
	 * @param      dado  Dado a ser inserido
	 * @param      arv   Árvore a inserir o dado
	 *
	 * @return     Recursão e rotações para manter a estrutura e balanceamento
	 *             da árvore após a exclusão
	 */
	NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
		if(arv == nullptr) {
			return new NoAVL<T>(dado);
		} else {
			if(dado < *arv->getDado())
				arv->esquerda = inserir(dado, arv->getEsquerda());
			else
				arv->direita = inserir(dado, arv->getDireita());
		}

		updateHeight(arv);
		int balance = balanceFactor(arv);

		if(balance > 1) {
			if(dado > *arv->esquerda->getDado())
				arv->esquerda = leftRotate(arv->getEsquerda());
			return rightRotate(arv);
		}
		if(balance < -1) {
			if(dado < *arv->direita->getDado())
				arv->direita = rightRotate(arv->getDireita());
			return leftRotate(arv);
		}
		return arv;
	}
	/**
	 * @brief      Remover um nó da árvore
	 *
	 * @param      arv   Árvore
	 * @param      dado  Dado a ser removido
	 *
	 * @return     Recursão e rotações para manter a estrutura e balanceamento
	 *             da árvore após a exclusão
	 */
	NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
		if(arv == nullptr) {
			return arv;
		}
		if(dado < *arv->getDado()) {
			arv->esquerda = remover(arv->getEsquerda(), dado);
		} else if (dado > *arv->getDado()) {
			arv->direita = remover(arv->getDireita(), dado);
		} else {
			NoAVL<T>* tmp;
			if(arv->getEsquerda() != nullptr && arv->getDireita() != nullptr) {
				tmp = minimo(arv->getDireita());
				*arv->dado = *tmp->getDado();
				arv->direita = remover(arv->getDireita(), *arv->getDado());
			} else {
				if(arv->getDireita() != nullptr) {
					tmp = arv->getDireita();
					return tmp;
				} else {
					if(arv->getEsquerda() != nullptr) {
						tmp = arv->getEsquerda();
						return tmp;
					} else {
						delete arv;
						return nullptr;
					}
				}
			}
		}
		if(arv == nullptr)
			return arv;

		updateHeight(arv);
		int balance = balanceFactor(arv);

		if(balance > 1) {
			if(balanceFactor(arv->getEsquerda()) < 0)
				arv->esquerda = leftRotate(arv->getEsquerda());
			return rightRotate(arv);
		}
		if(balance < -1) {
			if(balanceFactor(arv->getDireita()) > 0)
				arv->direita = rightRotate(arv->getDireita());
			return leftRotate(arv);
		}

		return arv;
	}
};

#endif /* NO_AVL_HPP */