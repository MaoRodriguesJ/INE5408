// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef PILHAENC_HPP
#define PILHAENC_HPP

#include <stdexcept>

#include "ListaEnc.hpp"
#include "Elemento.hpp"

/**
 * @brief      Implementação de uma estrutura de Pilha encadeada em C++
 *
 * @details    Esta Pilha está implementada de forma inversa para se aproveitar
 *             do desempenho dos métodos adicionaNoInicio() e retiraDoInicio()
 *             da classe ListaEnc
 */
template <typename T>
class PilhaEnc: private ListaEnc<T> {
 private:

 public:
	/**
	 * @brief      Construtor da classe PilhaEnc
	 *
	 * @details    Uma instância da classe ListaEnc é inicializada
	 */
	PilhaEnc() {

	}
	/**
	 * @brief      Destrutor da classe PilhaEnc
	 */
	~PilhaEnc() {
		limparPilha();
	}
	/**
	 * @brief      Adiciona um elemento ao topo da pilha
	 *
	 * @param      dado  O valor dado como parâmetro cria um novo objeto da
	 *                   classe elemento, dado = info (ver classe Elemento.hpp)
	 */
	void empilha(const T& dado) {
		ListaEnc<T>::adicionaNoInicio(dado);
	}
	/**
	 * @brief      Retira o último valor colocado na pilha
	 */
	T desempilha() {
		return ListaEnc<T>::retiraDoInicio();
	}
	/**
	 * @brief      Apenas retorna o dado do último elemento da pilha sem
	 *             retirá-lo
	 */
	T topo() {
		if(PilhaVazia()) {
			throw std::runtime_error("Lista Vazia");
		} else {
			return ListaEnc<T>::head->getInfo();
		}
	}
	/**
	 * @brief      Limpa Pilha
	 */
	void limparPilha() {
		ListaEnc<T>::destroiLista();
	}
	/**
	 * @brief      Checa se a pilha está cheia
	 *
	 * @return     Retorna true caso a pilha esteja cheia
	 */
	bool PilhaVazia() {
		return ListaEnc<T>::listaVazia();
	}
};

#endif  // PILHAENC_HPP
