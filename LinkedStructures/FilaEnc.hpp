// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef FILAENC_HPP
#define FILAENC_HPP

#include <stdexcept>

#include "ListaEnc.hpp"
#include "Elemento.hpp"

/**
 * @brief      Implementação de uma estrutura de Fila encadeada em C++
 *
 * @details    Os elementos são adicionado ao final da lista e retirados do
 *             início, ou seja, mais rápido retirar um elemento da fila do que
 *             adicionar
 *
 * @param      tail  Um ponteiro para o fim da fila
 */
template <typename T>
class FilaEnc: private ListaEnc<T> {
 private:
	Elemento<T> *tail;

 public:
	/**
	 * @brief  		Construtor da classe FilaEnc
	 *
	 * @details 		Uma instância da classe ListaEnc é inicializada
	 */
	FilaEnc() {
		tail = nullptr;
	}
	/**
	 * @brief      Destrutor da classe FilaEnc
	 */
	~FilaEnc() {
		limparFila();
	}
	/**
	 * @brief      Adiciona um elemento ao fim da fila
	 *
	 * @param      dado  O valor dado como parâmetro cria um novo objeto da
	 *                   classe elemento, dado = info (ver classe Elemento.hpp)
	 */
	void inclui(const T& dado) {
		Elemento<T> *novo = new Elemento<T>(dado, nullptr);
		if(novo == nullptr) {
			throw std::runtime_error("Sem Espaço na Memória");
		} else {
			if(filaVazia()) {
				ListaEnc<T>::setHead(novo);
				tail = novo;
			} else {
				tail->setProximo(novo);
				tail = novo;
			}
			ListaEnc<T>::addSize();
		}
	}
	/**
	 * @brief      Retira  e retornar o primeiro valor adicionado a fila
	 *
	 * @details    Retira por ordem de itens colocados na fila, primeiro a ser
	 *             colocado é o primeiro a sair. A fila é reorganizada para o
	 *             início do espaço armazenado.
	 */
	T retira() {
		return ListaEnc<T>::retiraDoInicio();
	}
	/**
	 * @brief      Retorna o último valor adicionado a fila
	 */
	T ultimo() {
		if(filaVazia()) {
			throw std::runtime_error("Lista Vazia");
		} else {
			return tail->getInfo();
		}
	}
	/**
	 * @brief      Retorna o primeiro valor adicionado a fila
	 */
	T primeiro() {
		if(filaVazia()) {
			throw std::runtime_error("Lista Vazia");
		} else {
			return ListaEnc<T>::getHead()->getInfo();
		}
	}
	/**
	 * @brief      Checa se a fila está cheia
	 *
	 * @return     Retorna true caso a fila esteja cheia
	 */
	bool filaVazia() {
		return ListaEnc<T>::listaVazia();
	}
	/**
	 * @brief      Limpa Fila
	 */
	void limparFila() {
		ListaEnc<T>::destroiLista();
		tail = nullptr;
	}
};

#endif  // FILAENC_HPP
