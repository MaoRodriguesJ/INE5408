// Copyright [2016] <Salomão Rodrigues Jacinto>
#include "ListaEnc.hpp"

template <typename T>
class PilhaEnc{
 private:
	ListaEnc<T> *pilha;

 public:
	PilhaEnc() {
		pilha = new ListaEnc<T>();
	}
	~PilhaEnc() {
		limparPilha();
	}
	void empilha(const T& dado) {
		pilha->adicionaNoInicio(dado);
	}
	T desempilha() {
		return pilha->retiraDoInicio();
	}
	T topo() {
		T dado = pilha->retiraDoInicio();
		empilha(dado);
		return dado;
	}
	void limparPilha() {
		pilha->destroiLista();
	}
	bool PilhaVazia() {
		return pilha->listaVazia();
	}
};
