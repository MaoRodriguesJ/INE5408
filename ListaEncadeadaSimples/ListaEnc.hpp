// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef LISTAENC_HPP
#define LISTAENC_HPP

#include "Elemento.hpp"

template<typename T>
class ListaEnc {
 private:
	Elemento<T> *head;
	int size;

 public:
	ListaEnc() {
		size = 0;
		head = nullptr;
	}
	~ListaEnc() {

	}
////////////////////////////////////////////////////////////////////////////
// INICIO
////////////////////////////////////////////////////////////////////////////
	void adicionaNoInicio(const T& dado) {
		Elemento<T> *novo;
		if(novo == NULL) {
			throw "Lista Cheia";
		} else {
			novo = new Elemento<T>(dado, head);
			head = novo;
			size++;
		}
	}
	T retiraDoInicio() {
		Elemento<T> *saiu;
		T volta;
		if(listaVazia()) {
			throw "Lista Vazia";
		} else {
			saiu = head;
			volta = saiu->getInfo();
			head = saiu->getProximo();
			saiu->~Elemento();
			delete saiu;
			size--;
			return volta;
		}
	}
	void eliminaDoInicio() {
		Elemento<T> *saiu;
		if(listaVazia()) {
			throw "Lista Vazia";
		} else {
			saiu = head;
			head = saiu->getProximo();
			saiu->~Elemento();
			delete saiu;
			size--;
			return volta;
		}
	}
////////////////////////////////////////////////////////////////////////////
// POSICAO
////////////////////////////////////////////////////////////////////////////
	void adicionaNaPosicao(const T& dado, int pos) {
		Elemento<T> *novo, *anterior;
		if(pos > size + 1) {
			throw "Posição inválida";
		} else {
			if(novo == NULL) {
				throw "Lista Cheia";
			} else {
				if(pos == 1) {
					adicionaNoInicio(dado);
				} else {
					anterior = head;
					for(int i = 0; i < pos-2; i++) {
						anterior = anterior->getProximo();
					}
					novo = new Elemento(dado, anterior->getProximo());
					anterior.setProximo(novo);
					size++;
				}
			}
		}
	}
	int posicao(const T& dado) const {
		int i = 0;
		Elemento<T> *proximo;
		proximo = head;
		while(i <= size && !(igual(dado->getInfo(), proximo->getInfo())) {
			i++;
			proximo = proximo->getProximo();
		}
		if(i > size) {
			throw "Este dado não existe";
		} else {
			return i;
		}
	}
	T* posicaoMem(const T& dado) const {

	}
	bool contem(const T& dado) {

	}
	T retiraDaPosicao(int pos) {
		Elemento<T> *anterior, *eliminar;
		T volta;
		if(pos > size) {
			throw "Posição Inválida";
		else if(listaVazia()) {
			throw "Lista Vazia";
		} else {
			if(pos == 1) {
				return retiraDoInicio();
			} else {
				anterior = head;
				for(int i = 0; i < pos-2; i++) {
					anterior = anterior->getProximo();
				}
				eliminar = anterior->getProximo();
				volta = eliminar->getInfo();
				anterior.setProximo(eliminar.getProximo());
				eliminar->~Elemento();
				delete eliminar;
				size--;
				return  volta;
			}
		}
	}
////////////////////////////////////////////////////////////////////////////
// FIM
////////////////////////////////////////////////////////////////////////////
	void adiciona(const T& dado) {

	}
	T retira() {

	}
////////////////////////////////////////////////////////////////////////////
// ESPECIFICO
////////////////////////////////////////////////////////////////////////////
	T retiraEspecifico(const T& dado) {

	}
	void adicionaEmOrdem(const T& data) {

	}
////////////////////////////////////////////////////////////////////////////
// TESTES
////////////////////////////////////////////////////////////////////////////
	bool listaVazia() const {
		return size == 0;
	}
	bool igual(T dado1, T dado2) {
		return dado1 == dado2;
	}
	bool maior(T dado1, T dado2) {
		return dado1 > dado2;
	}
	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}
	void destroiLista() {

	}
};

#endif  // LISTAENC_HPP
