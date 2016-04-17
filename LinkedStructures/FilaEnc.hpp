// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef FILAENC_HPP
#define FILAENC_HPP

#include "ListaEnc.hpp"

/**
 * @brief  		Implementação de uma estrutura de Fila encadeada em C++
 *
 * @param  		fila	Uma instância da classe ListaEnc.hpp, pois a fila se
 * 						trata de uma lista com diferenças na ordem de entrada e
 * 						retirada de dados
 *
 * @details 	Os elementos são adicionado ao final da lista e retirados do
 * 				início, ou seja, mais rápido retirar um elemento da fila do que
 * 				adicionar
 */
template <typename T>
class FilaEnc{
 private:
	ListaEnc<T> *fila;

 public:
	 /**
	 * @brief  		Construtor da classe FilaEnc
	 *
	 * @details 		Uma instância da classe ListaEnc é inicializada
	 */
	FilaEnc<T>() {
		fila = new ListaEnc<T>();
	}
	/**
	 * @brief  		Destrutor da classe FilaEnc
	 */
	~FilaEnc() {
		limparFila();
	}
	/**
	 * @brief 		Adiciona um elemento ao fim da fila
	 *
	 * @param 		dado	O valor dado como parâmetro cria um novo objeto da
	 * 						classe elemento, dado = info (ver classe Elemento.hpp)
	 */
	void inclui(const T& dado) {
		fila->adiciona(dado);
	}
	/**
	 * @brief  		Retira  e retornar o primeiro valor adicionado a fila
	 *
	 * @details  	Retira por ordem de itens colocados na fila, primeiro a
	 * 				ser colocado é o primeiro a sair. A fila é reorganizada para
	 * 				o início do espaço armazenado.
	 */
	T retira() {
		return fila->retiraDoInicio();
	}
	/**
	 * @brief      Retorna o último valor adicionado a fila
	 */
	T ultimo() {
		T dado = fila->retira();
		inclui(dado);
		return dado;
	}
	/**
	 * @brief      Retorna o primeiro valor adicionado a fila
	 */
	T primeiro() {
		T dado = fila->retiraDoInicio();
		fila->adicionaNoInicio(dado);
		return dado;
	}
	/**
	 * @brief      Checa se a fila está cheia
	 *
	 * @return     Retorna true caso a fila esteja cheia
	 */
	bool filaVazia() {
		return fila->listaVazia();
	}
	/**
	 * @brief 		Limpa Fila
	 */
	void limparFila() {
		fila->destroiLista();
	}
};

#endif  // FILAENC_HPP
