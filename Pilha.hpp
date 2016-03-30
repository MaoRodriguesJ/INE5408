// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef PILHA_HPP
#define PILHA_HPP

template<typename T>
class Pilha {
 private:
	const int MAXPILHA = 100;
	T* m_dados;
	int top;
	int tamanho;

 public:
	Pilha() {  // construtor com o máximo definido
		top = -1;
		m_dados = new T[MAXPILHA];
		tamanho = MAXPILHA;
	}
	explicit Pilha<T>(int t) {  // construtor com o valor desejado
		top = -1;
		m_dados = new T[t];
		tamanho = t;
	}
	T topo() {  // retorna dados do topo da pilha
		if (PilhaVazia()) {
			throw "Pilha Vazia";
		} else {
			return m_dados[top];
		}
	}
	int getPosTopo() {  // retorna posição do topo
		if (PilhaVazia()) {
			throw "Pilha Vazia";
		} else {
			return top;
		}
	}
	void limparPilha() {  // limpa a pilha
		top = -1;
	}
	bool PilhaVazia() {  // checa se a pilha está vazia
		if (top == -1) {
			return true;
		} else {
			return false;
		}
	}
	bool PilhaCheia() {  // checa se a pilha está cheia
		if (top == tamanho-1) {
			return true;
		} else {
			return false;
		}
	}
	void empilha(T dado) {  // adiciona um dado a pilha
		if (PilhaCheia()) {
			throw "Pilha Cheia!";
		} else {
			top++;
			m_dados[top] = dado;
		}
	}
	T desempilha() {  // retira um dado da pilha
		if (PilhaVazia()) {
			throw "Pilha Vazia!";
		} else {
			top--;
			return m_dados[top+1];
		}
	}
};
#endif  // PILHA_HPP
