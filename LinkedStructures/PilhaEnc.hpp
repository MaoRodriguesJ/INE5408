// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef PILHAENC_HPP
#define PILHAENC_HPP

#include "ListaEnc.hpp"

/**
 * @brief      Implementação de uma estrutura de Pilha encadeada em C++
 *
 * @details    Esta Pilha está implementada de forma inversa para se aproveitar
 *             do desempenho dos métodos adicionaNoInicio() e retiraDoInicio()
 *             da classe ListaEnc
 *
 * @tparam     pilha  Uma instância da classe ListaEnc.hpp, pois a pilha se
 *                    trata de uma lista com diferenças na ordem de entrada e
 *                    retirada de dados
 */
template <typename T>
class PilhaEnc{
 private:
	ListaEnc<T> *pilha;

 public:
	/**
	 * @brief      Construtor da classe PilhaEnc
	 *
	 * @details    Uma instância da classe ListaEnc é inicializada
	 */
	PilhaEnc() {
		pilha = new ListaEnc<T>();
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
		pilha->adicionaNoInicio(dado);
	}
	/**
	 * @brief      Retira o último valor colocado na pilha
	 */
	T desempilha() {
		return pilha->retiraDoInicio();
	}
	/**
	 * @brief      Apenas retorna o dado do último elemento da pilha sem
	 *             retirá-lo
	 */
	T topo() {
		T dado = pilha->retiraDoInicio();
		empilha(dado);
		return dado;
	}
	/**
	 * @brief      Limpa Pilha
	 */
	void limparPilha() {
		pilha->destroiLista();
	}
	/**
	 * @brief      Checa se a pilha está cheia
	 *
	 * @return     Retorna true caso a pilha esteja cheia
	 */
	bool PilhaVazia() {
		return pilha->listaVazia();
	}
};

#endif  // PILHAENC_HPP
