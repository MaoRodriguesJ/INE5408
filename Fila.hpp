// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef FILA_HPP
#define FILA_HPP

/**
 * @brief  		{ Implementação de uma estrutura de Fila em C++ }
 *
 * @tparam  	T		{ Ponteiro para o início da Fila }
 *
 * @param  		fim			{ Armazena o fim da FIla}
 * @param  		tamanho		{ Armazena o tamanho da Fila }
 */
template <typename T>
class Fila {
 private:
	const int MAXFILA = 100;
	T* m_dados;
	int fim;
	int tamanho;

 public:
	/**
	 * @brief  		{ Construtor da classe Fila }
	 *
	 * @param  		tam		{ Valor para o tamanho da fila }
	 */
	Fila() {
		fim = -1;
		m_dados = new T[MAXFILA];
		tamanho = MAXFILA;
	}
	explicit Fila<T>(int tam) {
		fim = -1;
		m_dados = new T[tam];
		tamanho = tam;
	}
	/**
	 * @brief  		{ Adiciona um dado a fila }
	 *
	 * @param  		dado  { Dado genérico, podendo ser um inteiro, float... }
	 */
	void inclui(T dado) {
		if (filaCheia()) {
			throw "Fila Cheia!";
		} else {
			fim++;
			m_dados[fim] = dado;
		}
	}
	/**
	 * @brief  		{ Retira o primeiro valor adicionado a fila }
	 *
	 * @details  	{ Retira por ordem de itens colocados na fila, primeiro a
	 * 				ser colocado é o primeiro a sair. A fila é reorganizada para
	 * 				o início do espaço armazenado. }
	 */
	T retira() {
		if (filaVazia()) {
			throw "Fila Vazia!";
		} else {
			fim--;
			T dado = m_dados[0];
			for (int i = 0; i <= fim; i++) {
				m_dados[i] = m_dados[i+1];
			}
			return dado;
		}
	}
	/**
	 * @brief      { Retira o último valor adicionado a fila }
	 */
	T ultimo() {
		if (filaVazia()) {
			throw "Fila Vazia!";
		} else {
			return m_dados[fim];
		}
	}
	/**
	 * @brief      { Retorna a posição do último valor }
	 */
	int getUltimo() {
		if (filaVazia()) {
			throw "Fila Vazia!";
		} else {
			return fim;
		}
	}
	/**
	 * @brief      { Checa se a fila está cheia }
	 *
	 * @return     { Retorna true caso a fila esteja cheia }
	 */
	bool filaCheia() {
		if (fim == tamanho-1) {
			return true;
		} else {
			return false;
		}
	}
	/**
	 * @brief      { Checa se a fila está vazia }
	 *
	 * @return     { Retorna true caso a fila esteja vazia }
	 */
	bool filaVazia() {
		if (fim == -1) {
			return true;
		} else {
			return false;
		}
	}
	/**
	 * @brief      { Inicializa a fila }
	 */
	void inicializaFila() {
		fim = -1;
	}
};
#endif  // FILA_HPP
