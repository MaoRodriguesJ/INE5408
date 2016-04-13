// Copyright [2016] <Salomão Rodrigues Jacinto>
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
		destroiLista();
	}
////////////////////////////////////////////////////////////////////////////
// INICIO
////////////////////////////////////////////////////////////////////////////
	void adicionaNoInicio(const T& dado) {
		Elemento<T> *novo = new Elemento<T>(dado, nullptr);
		head = novo;
		++size;
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
			--size;
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
			--size;
		}
	}
////////////////////////////////////////////////////////////////////////////
// POSICAO
////////////////////////////////////////////////////////////////////////////
	void adicionaNaPosicao(const T& dado, int pos) {
		Elemento<T> *novo = new Elemento<T>(dado, nullptr);
		Elemento<T> *anterior;
		if(pos > size + 1 || pos < 1) {
			throw "Posição inválida";
		} else {
			if(novo == nullptr) {
				throw "Lista Cheia";
			} else {
				if(pos == 0) {
					adicionaNoInicio(dado);
				} else {
					anterior = head;
					for(int i = 0; i < pos-2; ++i) {
						anterior = anterior->getProximo();
					}
					novo->setProximo(anterior->getProximo());
					anterior->setProximo(novo);
					++size;
				}
			}
		}
	}
	int posicao(const T& dado) const {
		if(listaVazia()) {
			throw "Lista Vazia";
		}
		Elemento<T> *atual;
		atual = head;
		for(int i = 0; i < size; ++i) {
			if(igual(dado, atual->getInfo())) {
				return i;
			}
			atual = atual->getProximo();
		}

		throw "Este dado não existe";
	}
	T* posicaoMem(const T& dado) const {
		if(listaVazia()) {
			throw "Lista Vazia";
		}
		int i = 0;
		Elemento<T> *proximo;
		proximo = head;
		while(i <= size) {
			if(igual(dado, proximo->getInfo())) {
				return proximo;
			}
			++i;
			proximo = proximo->getProximo();
		}
		throw "Este dado não existe";
	}
	bool contem(const T& dado) {
		if(listaVazia()) {
			return false;
		} else {
			Elemento<T> *proximo;
			proximo = head;
			for(int i = 0; i <= size; ++i) {
				if(igual(dado, proximo->getInfo())) {
					return true;
				}
			}
			return false;
		}
	}
	T retiraDaPosicao(int pos) {
		Elemento<T> *anterior, *eliminar;
		T volta;
		if(pos > size || pos < 1) {
			throw "Posição Inválida";
		}
		if(listaVazia()) {
			throw "Lista Vazia";
		} else {
			if(pos == 0) {
				return retiraDoInicio();
			}
			if(pos == size){
				retira();
			} else {
				anterior = head;
				for(int i = 0; i < pos-2; ++i) {
					anterior = anterior->getProximo();
				}
				eliminar = anterior->getProximo();
				volta = eliminar->getInfo();
				anterior = eliminar->getProximo();
				delete eliminar;
				--size;
				return  volta;
			}
		}
	}
////////////////////////////////////////////////////////////////////////////
// FIM
////////////////////////////////////////////////////////////////////////////
	void adiciona(const T& dado) {
		Elemento<T> *novo = new Elemento<T>(dado, nullptr);
		Elemento<T> *anterior;
		if(novo == nullptr) {
			throw "Lista Cheia";
		} else {
			anterior = head;
			while(anterior->getProximo() != nullptr) {
				anterior = anterior->getProximo();
			}
			anterior->setProximo(novo);
			++size;
		}
	}
	T retira() {
	    Elemento<T> *anterior, *eliminar;
		T volta;
		if(listaVazia()) {
			throw "Lista Vazia";
		} else {
			anterior = head;
			for(int i = 0; i <= size; ++i) {
				anterior = anterior->getProximo();
			}
			eliminar = anterior->getProximo();
			volta = eliminar->getInfo();
			anterior = eliminar->getProximo();
			delete eliminar;
			--size;
			return  volta;
		}
	}
////////////////////////////////////////////////////////////////////////////
// ESPECIFICO
////////////////////////////////////////////////////////////////////////////
	T retiraEspecifico(const T& dado) {
		return retiraDaPosicao(posicao(dado));
	}
	void adicionaEmOrdem(const T& data) {
		Elemento<T> *atual;
		if(listaVazia()) {
			throw "Lista Vazia";
		} else {
			atual = head;
			int i = 1;
			while(atual->getProximo() != nullptr && maior(data, atual->getInfo())) {
				atual = atual->getProximo();
				++i;
			}
			if(maior(data, atual->getInfo())) {
				adicionaNaPosicao(data, i+1);
			} else {
				adicionaNaPosicao(data, i);
			}
		}
	}
////////////////////////////////////////////////////////////////////////////
// TESTES
////////////////////////////////////////////////////////////////////////////
	bool listaVazia() const {
		return size == 0;
	}
	bool igual(T dado1, T dado2) const {
		return dado1 == dado2;
	}
	bool maior(T dado1, T dado2) const {
		return dado1 > dado2;
	}
	bool menor(T dado1, T dado2) const {
		return dado1 < dado2;
	}
	void destroiLista() {
		Elemento<T> *atual = head;
		while (atual != nullptr) {
			atual = atual->getProximo();
			eliminaDoInicio();
		}
		size = 0;
	}
};
