// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef NO_BINARIO_HPP
#define NO_BINARIO_HPP

#include <cstdlib>
#include <vector>
#include <stdexcept>

/**
 * @brief      Implementação de uma estrutura de Árvore Binária em C++
 */
template <typename T>
class NoBinario {
 protected:
	T* dado_;  //!< Dado genérico do nó
	NoBinario<T>* esquerda;  //!< Ponteiro para o nó a esquerda
	NoBinario<T>* direita;  //!< Ponteiro para o nó a direita
	std::vector<NoBinario<T>* > elementos;  //!< Elemento acessados durante
	                                        // o percurso realizado

 public:
	/**
	 * @brief      Construtor da classe NoBinario
	 *
	 * @param      dado  Dado do nó que será criado
	 *
	 * @details    Os ponteiros esquerda e direita apontam para nullptr
	 */
	NoBinario<T>(const T& dado) {
		esquerda = nullptr;
		direita = nullptr;
		dado_ = new T(dado);
	}
	/**
	 * @brief      Destrutor NoBinario
	 */
	virtual ~NoBinario() {
		delete dado_;
		if(esquerda != nullptr) {
			delete esquerda;
		}
		if(direita != nullptr) {
			delete direita;
		}
	}
	/**
	 * @brief      Get dado
	 *
	 * @return     T dado
	 */
	T* getDado() {
		return dado_;
	}
	/**
	 * @brief      Get elementos
	 *
	 * @return     Vector elementos
	 */
	std::vector< NoBinario<T>*> getElementos() {
		return elementos;
	}
	 /**
	 * @brief      Get esquerda
	 *
	 * @return     NoBinario a esquerda
	 */
	NoBinario<T>* getEsquerda() {
		return esquerda;
	}
	 /**
	 * @brief      Get direita
	 *
	 * @return     NoBinario a direita
	 */
	NoBinario<T>* getDireita() {
		return direita;
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
	T* busca(const T& dado, NoBinario<T>* arv) {
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
	 * @brief      Insere novo dado na árvore
	 *
	 * @param      dado  Dado a ser inserido
	 * @param      arv   Árvore a inserir o dado
	 *
	 * @return     Retorna árvore para recursão
	 */
	NoBinario<T>* inserir(const T& dado, NoBinario<T>* arv) { 
		if(dado < *(arv->getDado())) {
			if(arv->getEsquerda() == nullptr) {
				arv->esquerda = new NoBinario<T>(dado);
			} else {
				arv = inserir(dado, arv->getEsquerda());
			}
		} else {
			if(arv->getDireita() == nullptr) {
				arv->direita = new NoBinario<T>(dado);
			} else {
				arv = inserir(dado, arv->getDireita());
			}
		}
		return arv;
	}
	/**
	 * @brief      Remover um nó da árvore
	 *
	 * @param      arv   Árvore
	 * @param      dado  Dado a ser removido
	 *
	 * @return     Recursão para manter a estrutura da árvore após a exclusão
	 */
	NoBinario<T>* remover(NoBinario<T>* arv, const T& dado) {
		if(arv == nullptr) {
			return arv;
		} else {
			NoBinario<T> *tmp, *filho;
			if(dado < *(arv->getDado())) {
				arv->esquerda = remover(arv->getEsquerda(), dado);
				return arv;
			} else {
				if(dado > *(arv->getDado())) {
					arv->direita = remover(arv->getDireita(), dado);
					return arv;
				} else {
					tmp = arv;
					if(arv->getDireita() != nullptr &&
						arv->getEsquerda() != nullptr) {
						tmp = minimo(arv->getDireita());
						arv->dado_ = tmp->getDado();
						arv->direita = remover(arv->getDireita(),
											  *(arv->getDado()));
						return arv;
					} else {
						if(arv->getDireita() != nullptr) {
							filho = arv->getDireita();
							return filho;
						} else {
							if(arv->getEsquerda() != nullptr) {
								filho = arv->getEsquerda();
								return filho;
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

	/**
	 * @brief      Retorna o nó com o menor valor a partir de um determinado nó
	 *
	 * @param      nodo  Nó para início da busca
	 *
	 * @return     Nó que possuí o menor valor
	 */
	NoBinario<T>* minimo(NoBinario<T>* nodo) {
		if(nodo->getEsquerda() == nullptr) {
			return nodo;
		} else {
			nodo = minimo(nodo->getEsquerda());
			return nodo;
		}
	}
	/**
	 * @brief      Organiza os nós em um vetor começando pela raiz, depois pelos
	 *             nós a esquerda e depois pelos nós a direita
	 *
	 * @param      nodo  Nó para início da ordenação
	 */
	void preOrdem(NoBinario<T>* nodo) {
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
	void emOrdem(NoBinario<T>* nodo) {
		if(nodo != nullptr) {
			preOrdem(nodo->getEsquerda());
			elementos.push_back(nodo);
			preOrdem(nodo->getDireita());
		}
	}
	/**
	 * @brief      Organiza os nós em um vetor começando pelos nós a esquerda,
	 *             depois pelos nós a direita e a raiz
	 *
	 * @param      nodo  Nó para início da ordenação
	 */
	void posOrdem(NoBinario<T>* nodo) {
		if(nodo != nullptr) {
			posOrdem(nodo->getEsquerda());
			posOrdem(nodo->getDireita());
			elementos.push_back(nodo);
		}
	}
};

#endif  // NO_BINARIO_HPP
