	// Copyright Bruno Marques 2016.1
#ifndef LISTACIRC_HPP
#define LISTACIRC_HPP

#include "Elemento.hpp"

//!  Classe da estrutura de dado: Lista Circular.
/*!  Implementação da estruturda de dado Lista Circular,
 *   realizada na disciplina de Estrutura de Dados - INE5408
 *   como trabalho prático do semestre.
 *   \author Bruno Marques do Nascimento
 *   \since 26/04/2016
 *   \version 1.0
 */
template <typename T>
class ListaCirc {
 public:
    Elemento<T>* nodoSentinela; /*!< Ponteiro para o sentinela da lista */
	Elemento<T>* head;  /*!< Ponteiro para o nodoSentinela */
	int size;  /*!< Inteiro que guarda o tamanho da Lista circular */

 public:
//! Contrutor padrão.
/*! Sempre que usado, este construtor criará uma 
 *  lista circular de tamanho zero,
 *  e com o ponteiro "head" sendo um ponteiro para o nodoSentinela,
 *. e o nodoSentinela sendo um elemento neutro, que aponta para si mesmo.
 */
	ListaCirc();

//! Destrutor.
/*! Tem a função de destruir todos
 *  os nós da lista circular.
 */
	~ListaCirc();

//!  Função adicionaNoInicio, insere um dado no inicio da lista circular.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista circular.
 *   \sa ListaCirc()
 */
	void adicionaNoInicio(const T& dado);

//!  Função retiraDoInicio, retira o dado da posição inicial da lista circular.
/*!  
 *   \return o dado retirado da lista circular do tipo T.
 *   \sa listaVazia() and ListaCirc()
 */
	T retiraDoInicio();

//!  Função eliminaDoInicio, elimina o dado do inicio da lista circular.
/*!  
 *   \sa listaVazia() and ListaCirc()
 */
	void eliminaDoInicio();

//!  Função adicionaNaPosicao, insere um dado na posicao definida.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista circular.
 *   \param pos posição de inserção desejada
 *   \sa ListaCirc()
 */
	void adicionaNaPosicao(const T& dado, int pos);

//!  Função posicao, informa a posição de um dado na lista circular.
/*!  
 *   \param dado argumento do tipo T, que será procurado na lista circular.
 *   \return um inteiro que informa a posição do dado na lista circular.
 *   \sa listaVazia() and ListaCirc()
 */
	int posicao(const T& dado) const;

//!  Função posicaoMem, informa a posição de memória de um dado da lista circ.
/*!  
 *   \param dado argumento do tipo T, que será procurado na lista circular.
 *   \return um ponteiro que informa a posição do dado na memória.
 *   \sa listaVazia() and ListaCirc()
 */
	T* posicaoMem(const T& dado) const;

//!  Função contem, informa a presença de um dado na lista circular.
/*!  
 *   \param dado argumento do tipo T, que será procurado na lista circular.
 *   \return um boolean que informa a presença do dado na lista circular.
 *   \sa listaVazia() and ListaCirc()
 */
	bool contem(const T& dado);

//!  Função retiraDaPosicao, retira um dado de uma posição escolhida.
/*!  
 *   \param pos posição de retirada de um dado.
 *   \return o dado retirado da lista circular do tipo T.
 *   \sa listaVazia() and ListaCirc()
 */
	T retiraDaPosicao(int pos);

//!  Função adiciona, insere um novo dado no fim da lista circular.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista circular.
 *   \sa ListaCirc()
 */
	void adiciona(const T& dado);

//!  Função retira, retira um dado do final da lista circular.
/*!  
 *   \return o dado retirado da lista circular do tipo T.
 *   \sa listaVazia() and ListaCirc()
 */
	T retira();

//!  Função retiraEspecifico, retira um dado específico da lista circular.
/*!  
 *   \param dado argumento do tipo T, que será retirado da lista circular.
 *   \return o dado retirado da lista circular do tipo T.
 *   \sa listaVazia() and ListaCirc()
 */
	T retiraEspecifico(const T& dado);

//!  Função adicionaEmOrdem insere o dado na lista circular em ordem crescente.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista circular.
 *   \sa ListaCirc()
 */
	void adicionaEmOrdem(const T& data);

//!  Função listaVazia, informa se a lista circular está vazia
/*!  
 *   \return um boolean que informa se a lista circular está vazia ou não.
 */
	bool listaVazia() const;

//!  Função igual, informa se os dados são iguais.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é igual ao dado2.
 */
	bool igual(T dado1, T dado2) const;

//!  Função maior, informa se um dado é maior que o outro.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é maior que dado2.
 */
	virtual bool maior(T dado1, T dado2);

//!  Função menor, informa se um dado é menor que o outro.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é menor que dado2.
 */
	bool menor(T dado1, T dado2);

//!  Função destroiLista, zera a lista circular descartando seus dados
/*!  
 */
	void destroiLista();

//!  Função tamanho, retorna o tamanho da lista circular.
/*!  
 *   \return um inteiro que informa o tamanho da lista circular.
 *   \sa ListaCirc()
 */
	int tamanho();

//!  Função mostra, mostra um dado em uma posição escolhida.
/*!  
 *   \param pos um inteiro com a posição desejada.
 *   \return um ponteiro que aponta para o primeiro elemento.
 *   \sa ListaCirc()
 */
	T mostra(int pos);

};

template<typename T>
ListaCirc<T>::ListaCirc() {
	size = 0;
	head = nodoSentinela;
	nodoSentinela = new Elemento<T>(0, head);
}

template<typename T>
ListaCirc<T>::~ListaCirc() {
	destroiLista();
}

template<typename T>
int ListaCirc<T>::tamanho() {
	return size; 
}

template<typename T>
T ListaCirc<T>::mostra(int pos) {
	if (listaVazia()) {
		throw "ErroListaVazia";
	} else {
		if (pos > size-1 || pos < 0) {
			throw "ErroPosição";
		} else {
			Elemento<T>* anterior = nodoSentinela->getProximo();
			for (int i = 0; i < pos; i++) {
				anterior = anterior->getProximo();
			}
			return anterior->getInfo();
		}
	}
}

template<typename T>
void ListaCirc<T>::adicionaNoInicio(const T& dado) {
	Elemento<T>* novo = new Elemento<T>(dado, head);
    if (novo == nullptr) {
        throw "ErroListaCheia";
    } else {
    	novo->setProximo(nodoSentinela->getProximo());
        nodoSentinela->setProximo(novo);
        ++size;
    }
}

template<typename T>
T ListaCirc<T>::retiraDoInicio() {
    if (listaVazia()) {
        throw "ErroListaVazia";
    } else {
        T info = nodoSentinela->getProximo()->getInfo();
        Elemento<T>* temp = nodoSentinela->getProximo()->getProximo();
        delete nodoSentinela->getProximo();
        nodoSentinela->setProximo(temp);
        --size;
        return info;
    }
}

template<typename T>
void ListaCirc<T>::eliminaDoInicio() {
    if (listaVazia()) {
        throw "ErroListaVazia";
    } else {
        Elemento<T>* temp = nodoSentinela->getProximo()->getProximo();
        delete nodoSentinela->getProximo();
        nodoSentinela->setProximo(temp);
        --size;
    }
}

template<typename T>
void ListaCirc<T>::adicionaNaPosicao(const T& dado, int pos) {
	if (pos > size || pos < 0) {
		throw "ErroPosição";
	} else {
		if (pos == 0) {
			adicionaNoInicio(dado);
			return;
		} else {
			Elemento<T>* novo = new Elemento<T>(dado, nullptr);
			if (novo == nullptr) {
				throw "ErroListaCheia";
			} else {
				Elemento<T>* anterior = nodoSentinela->getProximo();
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
int ListaCirc<T>::posicao(const T& dado) const {
	if (listaVazia()) {
		throw "ErroListaVazia";
	} else {
		Elemento<T>* aux = nodoSentinela->getProximo();
		for (int i = 0; i < size; ++i) {
			if (igual(dado, (aux->getInfo()))) {
				return i;
			}
			aux = aux->getProximo();
		}
		throw "ErroNãoContem";
	}
}

template<typename T>
T* ListaCirc<T>::posicaoMem(const T& dado) const {
	if (listaVazia()) {
		throw "ErroListaVazia";
	} else {
		Elemento<T>* aux = nodoSentinela->getProximo();
		for (int i = 0; i < size; ++i) {
			if (igual(dado, aux->getInfo())) {
				return aux;
			}
			aux = aux->getProximo();
		}
		throw "ErroNãoContem";
	}
}

template<typename T>
bool ListaCirc<T>::contem(const T& dado) {
	if (listaVazia()) {
		throw "ErroListaVazia";
	} else {
		Elemento<T>* aux = nodoSentinela->getProximo();
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
T ListaCirc<T>::retiraDaPosicao(int pos) {
	if (listaVazia()) {
		throw "ErroListaVazia";
	} else {
		if (pos > size-1 || pos < 0) {
			throw "ErroPosição";
		} else {
			if (pos == 0) {
				return retiraDoInicio();
			} else {
				Elemento<T>* anterior = nodoSentinela->getProximo();
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
void ListaCirc<T>::adiciona(const T& dado) {
	adicionaNaPosicao(dado, size);
}

template<typename T>
T ListaCirc<T>::retira() {
	return retiraDaPosicao(size-1);
}

template<typename T>
T ListaCirc<T>::retiraEspecifico(const T& dado) {
	if (listaVazia()) {
		throw "ErroListaVazia";
	} else {
		return retiraDaPosicao(posicao(dado));
	}
}

template<typename T>
void ListaCirc<T>::adicionaEmOrdem(const T& data) {

	Elemento<T>* anterior = nodoSentinela->getProximo();
	int posicao = 0;
    while (posicao < size && maior(data, anterior->getInfo())) {
    	    anterior = anterior->getProximo();
    	    ++posicao;
    }
    if (posicao == 0) {
    	return adicionaNoInicio(data);
    }
//    Elemento<T>* novo = new Elemento<T>(data, nullptr);
    adicionaNaPosicao(data, posicao);
//   novo -> setProximo(anterior->getProximo());
//	anterior->setProximo(novo);
//	++size;
}

template<typename T>
bool ListaCirc<T>::listaVazia() const {
	return size == 0;
}

template<typename T>
bool ListaCirc<T>::igual(T dado1, T dado2) const {
	return dado1 == dado2;
}

template<typename T>
bool ListaCirc<T>::maior(T dado1, T dado2) {
	return dado1 > dado2;
}

template<typename T>
bool ListaCirc<T>::menor(T dado1, T dado2) {
	return dado1 < dado2;
}

template<typename T>
void ListaCirc<T>::destroiLista() {
	Elemento<T>* temp = nodoSentinela->getProximo();
	while (size > 0) {
		temp = nodoSentinela->getProximo()->getProximo();
		delete nodoSentinela->getProximo();
		nodoSentinela->setProximo(temp);
		--size;
	}
}

#endif