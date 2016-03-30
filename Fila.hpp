// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef FILA_HPP
#define FILA_HPP

template <typename T>
class Fila {
 private:
	const int MAXFILA = 100;
	T* m_dados;
	int fim;
	int tamanho;

 public:
	Fila() {  // construtor com o máximo definido
		fim = -1;
		m_dados = new T[MAXFILA];
		tamanho = MAXFILA;
	}
	explicit Fila<T>(int tam) {  // construtor com o valor desejado
		fim = -1;
		m_dados = new T[tam];
		tamanho = tam;
	}
	void inclui(T dado) {  // adiciona novo valor ao fim da fila
		if (filaCheia()) {
			throw "Fila Cheia!";
		} else {
			fim++;
			m_dados[fim] = dado;
		}
	}
	T retira() {  // retira o valor na primeira posição da fila
		if (filaVazia()) {
			throw "Fila Vazia!";
		} else {
			fim--;
			T dado = m_dados[0];
			for (int i = 0; i <= fim; i++) {  // reorganiza a fila
				m_dados[i] = m_dados[i+1];
			}
			return dado;
		}
	}
	T ultimo() {  // retorna o valor do último da fila
		if (filaVazia()) {
			throw "Fila Vazia!";
		} else {
			return m_dados[fim];
		}
	}
	int getUltimo() {  // retorna a posição do último da fila
		if (filaVazia()) {
			throw "Fila Vazia!";
		} else {
			return fim;
		}
	}
	bool filaCheia() {  // indica se a fila está cheia
		if (fim == tamanho-1) {
			return true;
		} else {
			return false;
		}
	}
	bool filaVazia() {  // indica se a fila está vazia
		if (fim == -1) {
			return true;
		} else {
			return false;
		}
	}
	void inicializaFila() {  // reinicia a fila
		fim = -1;
	}
};
#endif  // FILA_HPP
