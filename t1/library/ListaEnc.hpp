// Copyright Bruno Marques <2016.1>

#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include <stdexcept>
#include "Elemento.hpp"

//!  Classe da estrutura de dado: Lista Encadeada.
/*!  Implementação da estruturda de dado Lista Encadeada,
 *   realizada na disciplina de Estrutura de Dados - INE5408
 *   como quarto trabalho prático do semestre.
 *   \author Bruno Marques do Nascimento
 *   \since 13/04/2016
 *   \version 1.0
 */
template<typename T>
class ListaEnc {
 private:
	Elemento<T>* head;  /*!< Ponteiro para o primeiro elemento da estrutura */

	int size;  /*!< Inteiro que guarda o tamanho da Lista Encadeada */

 public:
//! Contrutor padrão.
/*! Sempre que usado, este construtor criará uma 
 *  lista encadeada de tamanho zero,
 *  e com o ponteiro "head" sendo um ponteiro nulo.
 */
	ListaEnc();

//! Destrutor.
/*! Tem a função de destruir todos
 *  os nós da lista encadeada.
 */
	~ListaEnc();

//!  Função adicionaNoInicio, insere um dado no inicio da lista encadeada.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista encadeada.
 *   \sa ListaEnc()
 */
	void adicionaNoInicio(const T& dado);

//!  Função retiraDoInicio, retira o dado da posição inicial da lista encadeada.
/*!  
 *   \return o dado retirado da lista encadeada do tipo T.
 *   \sa listaVazia() and ListaEnc()
 */
	T retiraDoInicio();

//!  Função eliminaDoInicio, elimina o dado do inicio da lista encadeada.
/*!  
 *   \sa listaVazia() and ListaEnc()
 */
	void eliminaDoInicio();

//!  Função adicionaNaPosicao, insere um dado na posicao definida.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista encadeada.
 *   \param pos posição de inserção desejada
 *   \sa ListaEnc()
 */
	void adicionaNaPosicao(const T& dado, int pos);

//!  Função posicao, informa a posição de um dado na lista encadeada.
/*!  
 *   \param dado argumento do tipo T, que será procurado na lista encadeada.
 *   \return um inteiro que informa a posição do dado na lista encadeada.
 *   \sa listaVazia() and ListaEnc()
 */
	int posicao(const T& dado) const;

//!  Função posicaoMem, informa a posição de memória de um dado da lista encad.
/*!  
 *   \param dado argumento do tipo T, que será procurado na lista encadeada.
 *   \return um ponteiro que informa a posição do dado na memória.
 *   \sa listaVazia() and ListaEnc()
 */
	T* posicaoMem(const T& dado) const;

//!  Função contem, informa a presença de um dado na lista encadeada.
/*!  
 *   \param dado argumento do tipo T, que será procurado na lista encadeada.
 *   \return um boolean que informa a presença do dado na lista encadeada.
 *   \sa listaVazia() and ListaEnc()
 */
	bool contem(const T& dado);

//!  Função retiraDaPosicao, retira um dado de uma posição escolhida.
/*!  
 *   \param pos posição de retirada de um dado.
 *   \return o dado retirado da lista encadeada do tipo T.
 *   \sa listaVazia() and ListaEnc()
 */
	T retiraDaPosicao(int pos);

//!  Função adiciona, insere um novo dado no fim da lista encadeada.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista encadeada.
 *   \sa ListaEnc()
 */
	void adiciona(const T& dado);

//!  Função retira, retira um dado do final da lista encadeada.
/*!  
 *   \return o dado retirado da lista encadeada do tipo T.
 *   \sa listaVazia() and ListaEnc()
 */
	T retira();

//!  Função retiraEspecifico, retira um dado específico da lista encadeada.
/*!  
 *   \param dado argumento do tipo T, que será retirado da lista encadeada.
 *   \return o dado retirado da lista encadeada do tipo T.
 *   \sa listaVazia() and ListaEnc()
 */
	T retiraEspecifico(const T& dado);

//!  Função adicionaEmOrdem insere o dado na lista encadeada em ordem crescente.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista encadeada.
 *   \sa ListaEnc()
 */
	void adicionaEmOrdem(const T& data);

//!  Função listaVazia, informa se a lista encadeada está vazia
/*!  
 *   \return um boolean que informa se a lista encadeada está vazia ou não.
 *   \sa ListaEnc()
 */
	bool listaVazia() const;

//!  Função igual, informa se os dados são iguais.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é igual ao dado2.
 *   \sa ListaEnc()
 */
	bool igual(T dado1, T dado2) const;

//!  Função maior, informa se um dado é maior que o outro.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é maior que dado2.
 *   \sa ListaEnc()
 */
	virtual bool maior(T dado1, T dado2);

//!  Função menor, informa se um dado é menor que o outro.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é menor que dado2.
 *   \sa ListaEnc()
 */
	bool menor(T dado1, T dado2);

//!  Função destroiLista, zera a lista encadeada descartando seus dados
/*!  
 *   \sa ListaEnc()
 */
	void destroiLista();

//!  Função getHead, retorna o ponteiro que aponta para primeiro elemento.
/*!  
 *   \return um ponteiro que aponta para o primeiro elemento.
 *   \sa ListaEnc()
 */
	Elemento<T>* getHead();

//!  Função tamanho, retorna o tamanho da lista encadeada.
/*!  
 *   \return um inteiro que informa o tamanho da lista encadeada.
 *   \sa ListaEnc()
 */
	int tamanho();

//!  Função mostra, mostra um dado em uma posição escolhida.
/*!  
 *   \param pos um inteiro com a posição desejada.
 *   \return um ponteiro que aponta para o primeiro elemento.
 *   \sa ListaEnc()
 */
	T mostra(int pos);
};

template<typename T>
ListaEnc<T>::ListaEnc() {
	size = 0;
	head = nullptr;
}

template<typename T>
ListaEnc<T>::~ListaEnc() {
	destroiLista();
}

template<typename T>
int ListaEnc<T>::tamanho() {
	return size;
}

template<typename T>
T ListaEnc<T>::mostra(int pos) {
	if (listaVazia()) {
		throw std::runtime_error("Lista Vazia");
	} else {
		if (pos > size-1 || pos < 0) {
			throw std::runtime_error("Erro Posição");
		} else {
			Elemento<T>* anterior = head;
			for (int i = 0; i < pos-1; i++) {
				anterior = anterior->getProximo();
			}
			return anterior->getInfo();
		}
	}
}

template<typename T>
void ListaEnc<T>::adicionaNoInicio(const T& dado) {
    Elemento<T>* novo = new Elemento<T>(dado, head);
    if (novo == nullptr) {
        throw std::runtime_error("Lista Vazia");
    } else {
        head = novo;
        ++size;
    }
}

template<typename T>
T ListaEnc<T>::retiraDoInicio() {
    if (listaVazia()) {
        throw std::runtime_error("Lista Vazia");
    } else {
        T info = head->getInfo();
        Elemento<T>* temp = getHead()->getProximo();
        delete head;
        head = temp;
        --size;
        return info;
    }
}

template<typename T>
void ListaEnc<T>::eliminaDoInicio() {
	if(listaVazia()) {
		throw std::runtime_error("Lista Vazia");
	} else {
		Elemento<T>* temp = head->getProximo();
		delete head;
		head = temp;
		--size;
	}
}

template<typename T>
void ListaEnc<T>::adicionaNaPosicao(const T& dado, int pos) {
	if (pos > size || pos < 0) {
		throw std::runtime_error("Erro Posição");
	} else {
		if (pos == 0) {
			adicionaNoInicio(dado);
			return;
		} else {
			Elemento<T>* novo = new Elemento<T>(dado, nullptr);
			if (novo == nullptr) {
				throw std::runtime_error("Lista Cheia");
			} else {
				Elemento<T>* anterior = head;
				for (int i = 0; i < pos-1; ++i) {
					anterior = anterior->getProximo();
				}
				novo -> setProximo(anterior->getProximo());
				anterior->setProximo(novo);
				++size;
			}
		}
	}
}

template<typename T>
int ListaEnc<T>::posicao(const T& dado) const {
	if (listaVazia()) {
		throw std::runtime_error("Lista Vazia");
	} else {
		Elemento<T>* aux = head;
		for (int i = 0; i < size; ++i) {
			if (igual(dado, (aux->getInfo()))) {
				return i;
			}
			aux = aux->getProximo();
		}
		throw std::runtime_error("Não Contém");
	}
}

template<typename T>
T* ListaEnc<T>::posicaoMem(const T& dado) const {
	if (listaVazia()) {
		throw std::runtime_error("Lista Vazia");
	} else {
		Elemento<T>* aux = head;
		for (int i = 0; i < size; ++i) {
			if (igual(dado, aux->getInfo())) {
				return aux;
			}
			aux = aux->getProximo();
		}
		throw std::runtime_error("Não Contém");
	}
}

template<typename T>
bool ListaEnc<T>::contem(const T& dado) {
	if (listaVazia()) {
		throw "ErroListaVazia";
	} else {
		Elemento<T>* aux = head;
		for (int i = 0; i < size; ++i) {
			if (igual(dado, aux->getInfo())) {
				return true;
			}
			aux = aux->getProximo();
		}
		return false;
	}
}

template<typename T>
T ListaEnc<T>::retiraDaPosicao(int pos) {
	if (listaVazia()) {
		throw std::runtime_error("Lista Vazia");
	} else {
		if (pos > size-1 || pos < 0) {
			throw std::runtime_error("Erro Posição");
		} else {
			if (pos == 0) {
				return retiraDoInicio();
			} else {
				Elemento<T>* anterior = head;
				Elemento<T>* eliminar;
				for (int i = 0; i < pos-1; ++i) {
					anterior = anterior->getProximo();
				}
				eliminar = anterior->getProximo();
				anterior->setProximo(eliminar->getProximo());
				--size;
				T dado = eliminar->getInfo();
				delete eliminar;
				return dado;
			}
		}
	}
}

template<typename T>
void ListaEnc<T>::adiciona(const T& dado) {
	adicionaNaPosicao(dado, size);
}

template<typename T>
T ListaEnc<T>::retira() {
	return retiraDaPosicao(size-1);
}

template<typename T>
T ListaEnc<T>::retiraEspecifico(const T& dado) {
	if (listaVazia()) {
		throw std::runtime_error("Lista Vazia");
	} else {
		return retiraDaPosicao(posicao(dado));
	}
}

template<typename T>
void ListaEnc<T>::adicionaEmOrdem(const T& data) {
	Elemento<T>* anterior = head;
	int posicao = 0;
    while (posicao < size && maior(data, anterior->getInfo())) {
    	    anterior = anterior->getProximo();
    	    ++posicao;
    }
    Elemento<T>* novo = new Elemento<T>(data, nullptr);
    if (posicao == 0) {
        adicionaNoInicio(data);
        ++size;
    } else {
        novo -> setProximo(anterior->getProximo());
	    anterior->setProximo(novo);
	    ++size;
    }
}


template<typename T>
bool ListaEnc<T>::listaVazia() const {
	return size == 0;
}

template<typename T>
bool ListaEnc<T>::igual(T dado1, T dado2) const {
	return dado1 == dado2;
}

template<typename T>
bool ListaEnc<T>::maior(T dado1, T dado2) {
	return dado1 > dado2;
}

template<typename T>
bool ListaEnc<T>::menor(T dado1, T dado2) {
	return dado1 < dado2;
}

template<typename T>
void ListaEnc<T>::destroiLista() {
	Elemento<T>* temp = head;
	while (head != nullptr) {
		temp = head->getProximo();
		delete head;
		head = temp;
	}
	size = 0;
}

template<typename T>
Elemento<T>* ListaEnc<T>::getHead() {
	return head;
}

#endif