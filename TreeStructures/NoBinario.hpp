// Copyright [2016] <Salomão Rodrigues Jacinto>
//
// Did some changes to the original: Created set methods and changed dado to a
// 									 non-pointer (as well as the method getDado()).
#ifndef NO_BINARIO_HPP
#define NO_BINARIO_HPP

#include <cstdlib>
#include <vector>
#include <stdexcept>

/**
 * @brief      Implementação de uma estrutura de Árvore Binária em C++
 *
 * @param      dado_      Dado genérico do nó
 * @param      esquerda   Ponteiro para o nó a esquerda
 * @param      direita    Ponteiro para o nó a direita
 * @param      elementos  Elemento acessados durante o percurso realizado
 */
template <typename T>
class NoBinario {
 protected:
	T dado_;
	NoBinario<T>* esquerda;
	NoBinario<T>* direita;
	std::vector<NoBinario<T>* > elementos;

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
		dado_ = dado;
	}
	/**
	 * @brief      Destrutor NoBinario
	 */
	virtual ~NoBinario() {
		// posOrdem(this);
		// for(unsigned i = 0; i < elementos.size(); i++) {
		// 	remover(elementos[elementos.size()], elementos[i]->getDado());
		// }
	}
	/**
	 * @brief      Get dado
	 *
	 * @return     T dado
	 */
	T getDado() {
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
	void setEsquerda(NoBinario<T>* node) {
		esquerda = node;
	}
	void setDireita(NoBinario<T>* node) {
		direita = node;
	}
	void setDado(const T& dado) {
		dado_ = dado;
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
	T busca(const T& dado, NoBinario<T>* arv) {
		while(arv != nullptr && arv->getDado() != dado) {
			if(arv->getDado() < dado) {
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
		NoBinario<T> *novo = new NoBinario<T>(dado);
		if(novo == nullptr) {
			throw std::runtime_error("Sem Espaço na Memória");
		} else {
			if(dado < arv->getDado()) {
				if(arv->getEsquerda() == nullptr) {
					arv->setEsquerda(novo);
				} else {
					arv = inserir(dado, arv->getEsquerda());
				}
			} else {
				if(arv->getDireita() == nullptr) {
					arv->setDireita(novo);
				} else {
					arv = inserir(dado, arv->getDireita());
				}
			}
			return arv;
		}
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
			if(dado < arv->getDado()) {
				arv->setEsquerda(remover(arv->getEsquerda(), dado));
				return arv;
			} else {
				if(dado > arv->getDado()) {
					arv->setDireita(remover(arv->getDireita(), dado));
					return arv;
				} else {
					tmp = arv;
					if(arv->getDireita() != nullptr &&
						arv->getEsquerda() != nullptr) {

						tmp = minimo(arv->getDireita());
						arv->setDado(tmp->getDado());
						arv->setDireita(remover(arv->getDireita(),
										arv->getDado()));

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
	NoBinario<T>* minimo(NoBinario<T>* nodo) {
		if(nodo->getEsquerda() == nullptr) {
			return nodo;
		} else {
			nodo = minimo(nodo->getEsquerda());
			return nodo;
		}
	}
	void preOrdem(NoBinario<T>* nodo) {
		if(nodo != nullptr) {
			elementos.push_back(nodo);
			preOrdem(nodo->getEsquerda());
			preOrdem(nodo->getDireita());
		}
	}
	void emOrdem(NoBinario<T>* nodo) {
		if(nodo != nullptr) {
			preOrdem(nodo->getEsquerda());
			elementos.push_back(nodo);
			preOrdem(nodo->getDireita());
		}
	}
	void posOrdem(NoBinario<T>* nodo) {
		if(nodo != nullptr) {
			posOrdem(nodo->getEsquerda());
			posOrdem(nodo->getDireita());
			elementos.push_back(nodo);
		}
	}
};

#endif // NO_BINARIO_HPP
