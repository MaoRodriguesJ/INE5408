// Copyright [2016] <Salomão Rodrigues Jacinto>
#include "ListaEnc.hpp"

template <typename T>
class FilaEnc{
 private:
 	ListaEnc<T> *fila;

 public:
	FilaEnc<T>() {
		fila = new ListaEnc<T>();
	}
	~FilaEnc() {
		limparFila();
	}
	void inclui(const T& dado) {
		fila->adiciona(dado);
	}
	T retira() {
		return fila->retiraDoInicio();
	}
	T ultimo() {
		T dado = fila->retira();
		inclui(dado);
		return dado;
	}
	T primeiro() {
		T dado = fila->retiraDoInicio();
    	fila->adicionaNoInicio(dado);
    	return dado;
	}
	bool filaVazia() {
		return fila->listaVazia();
	}
	void limparFila() {
		fila->destroiLista();
	}
};
