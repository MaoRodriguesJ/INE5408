// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef PILHA_HPP
#define PILHA_HPP

#include <stdexcept>

/**
 * @brief  		Implementação de uma estrutura de Pilha em C++
 *
 * @param  		m_dados		Ponteiro para o início da Pilha
 * @param  		top			Armazena o topo da Pilha
 * @param  		tamanho		Armazena o tamanho da Pilha
 */
template<typename T>
class Pilha {
 private:
	const int MAXPILHA = 100;
	T* m_dados;
	int top;
	int tamanho;

 public:
	/**
	 * @brief  		Construtor da Classe Pilha
	 *
 	 * @details  	Valor do tamanho definido em uma constante como 100
	 */
	Pilha() {
		top = -1;
		m_dados = new T[MAXPILHA];
		tamanho = MAXPILHA;
	}
	/**
	 * @brief  		Construtor da Classe Pilha
	 *
	 * @param  		t		Valor para o tamanho da pilha
	 */
	explicit Pilha<T>(int t) {
		top = -1;
		m_dados = new T[t];
		tamanho = t;
	}
	/**
	 * @brief  		Retorna o valor armazenado no topo da pilha
	 */
	T topo() {
		if (PilhaVazia()) {
			throw std::runtime_error("Pilha Vazia");
		} else {
			return m_dados[top];
		}
	}
	/**
	 * @brief      Retorna a posição do topo
	 */
	int getPosTopo() {
		if (PilhaVazia()) {
			throw std::runtime_error("Pilha Vazia");
		} else {
			return top;
		}
	}
	/**
	 * @brief      Limpa a pilha
	 */
	void limparPilha() {
		top = -1;
	}
	/**
	 * @brief      Checa se a pilha está vazia
	 *
	 * @return     Retorna true caso a pilha esteja vazia
	 */
	bool PilhaVazia() {
		if (top == -1) {
			return true;
		} else {
			return false;
		}
	}
	/**
	 * @brief      Checa se a pilha está cheia
	 *
	 * @return     Retorna true caso a pilha esteja cheia
	 */
	bool PilhaCheia() {
		if (top == tamanho-1) {
			return true;
		} else {
			return false;
		}
	}
	/**
	 * @brief      Adiciona um dado a pilha
	 *
	 * @param  		dado  Dado genérico, podendo ser um inteiro, float...
	 */
	void empilha(T dado) {
		if (PilhaCheia()) {
			throw std::runtime_error("Pilha Cheia");
		} else {
			top++;
			m_dados[top] = dado;
		}
	}
	/**
	 * @brief      Retira o último valor colocado na pilha
	 */
	T desempilha() {
		if (PilhaVazia()) {
			throw std::runtime_error("Pilha Vazia");
		} else {
			top--;
			return m_dados[top+1];
		}
	}
};
#endif  // PILHA_HPP
