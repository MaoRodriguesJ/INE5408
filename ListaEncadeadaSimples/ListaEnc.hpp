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
		if(novo == 0) {
			throw "Lista Cheia";
		} else {
			size++;
			novo = new Elemento<T>(dado, head);
			head = novo;
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
			delete saiu;
			size--;
			return volta;
		}
	}
	////////////////////////////////////////////////////////////////////////////
	// POSICAO
	////////////////////////////////////////////////////////////////////////////
	void adicionaNaPosicao(const T& dado, int pos) {

	}
	int posicao(const T& dado) const {

	}
	T* posicaoMem(const T& dado) const {

	}
	bool contem(const T& dado) {

	}
	T retiraDaPosicao(int pos) {

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