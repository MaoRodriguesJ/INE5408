// Copyright Bruno Marques <2016.1>

#ifndef FILAENC_HPP
#define FILAENC_HPP

#include <stdexcept> 
#include "Elemento.hpp"
#include "ListaEnc.hpp"

template <typename T>
class FilaEnc :private ListaEnc<T>{
 private:
    Elemento<T>* fim;  /*!< Ponteiro para o fim da estrutura de dado */

 public:
//!  Contrutor padrão.
/*!  Sempre que usado, este construtor criará uma 
 * 	 fila encadeada, com tamanho zero.
 */
	FilaEnc();

//! Destrutor.
/*! Tem a função de destruir todos
 *  os nós da fila encadeada.
 */
	~FilaEnc();

//!  Função inclui, realiza a inserção de um novo dado na fila encadeada.
/*!  
 *	 \param dado argumento do tipo T, que será adicionado na fila encadeada.
 *	 \sa FilaEnc()
 */
	void inclui(const T& dado);

//!  Função retira, realiza a retirada de um dado da fila encadeada.
/*!  
 *	 \return o dado retirado da fila encadeada, do tipo T.
 *	 \sa filaVazia() and FilaEnc()
 */
	T retira();

//!  Função ultimo, informa o último dado inserido na fila encadeada, do tipo T.
/*!
 *	 \return o último dado adicionado na fila encadeada, do tipo T.
 *	 \sa filaVazia() and FilaEnc()
 */	
	T ultimo();

//!  Função primeiro, informa o primeiro dado da fila encadeada, do tipo T.
/*!
 *	 \return o primeiro dado da fila encadeada, do tipo T.
 *	 \sa filaVazia() and FilaEnc()
 */	
	T primeiro();

//!  Função filaVazia, verifica se a fila encadeada está vazia.
/*!
 *	 \return um booleano, true se a fila estiver vazia, caso contrário false.
 *	 \sa FilaEnc()
 */	
	bool filaVazia();

//!  Função limparFila, zera a fila encadeada descartando seus dados
/*!  
 */
	void limparFila();
};

template <typename T>
FilaEnc<T>::FilaEnc() : ListaEnc<T>::ListaEnc() {}

template <typename T>
FilaEnc<T>::~FilaEnc() {
    ListaEnc<T>::destroiLista();
}

template <typename T>
void FilaEnc<T>::inclui(const T& dado) {
    ListaEnc<T>::adiciona(dado);
    if (ListaEnc<T>::tamanho() == 1) {
        fim = ListaEnc<T>::getHead();
    } else {
        fim = fim->getProximo();
    }
}

template <typename T>
T FilaEnc<T>:: retira() {
    T dado = ListaEnc<T>::retiraDoInicio();
    if (ListaEnc<T>::tamanho() == 0) {
        fim = ListaEnc<T>::getHead();
    }
    return dado;
}

template <typename T>
T FilaEnc<T>::ultimo() {
    if (filaVazia()) {
        throw std::runtime_error("Fila Vazia");
    } else {
        return fim->getInfo();
    }
}

template <typename T>
T FilaEnc<T>::primeiro() {
    if (filaVazia()) {
        throw std::runtime_error("Fila Vazia");
    } else {
        return ListaEnc<T>::getHead()->getInfo();
    }
}

template <typename T>
bool FilaEnc<T>::filaVazia() {
    return ListaEnc<T>::listaVazia();
}
template <typename T>
void FilaEnc<T>::limparFila() {
    ListaEnc<T>::destroiLista();
}

#endif