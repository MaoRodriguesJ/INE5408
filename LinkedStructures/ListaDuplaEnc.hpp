// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef LISTADUPLAENC_HPP
#define LISTADUPLAENC_HPP

#include <stdexcept>

#include "ElementoDuplaEnc.hpp"

/**
 * @brief  		Implementação de uma estrutura de Lista duplamente
 * 				encadeada em C++
 *
 * @param  		head		Ponteiro para o header da Lista encadeada
 * @param  		size		Armazena a quantidade de elementos na Lista encadeada
 */
template <typename T>
class ListaDupla {
 private:
	ElementoDuplaEnc<T> *head;
	int size;

 public:
	/**
	 * @brief  		Construtor da classe ListaDuplaEnc
	 *
	 * @details		O header aponta para null e o size está em zero
	 */
	ListaDupla() {
		size = 0;
		head = nullptr;
	}
	/**
	 * @brief 		Destrutor da classe ListaDuplaEnc
	 *
	 * @details 	Chama o método destroiLista() para destruir elemento por
	 * 				elemento
	 */
	~ListaDupla() {
		destroiListaDuplo();
	}
	/**
	* INICIO
	*/
	/**
	 * @brief 		Adicona um elemento ao início da lista
	 *
	 * @details 	O valor dado como parâmetro cria um novo objeto da classe
	 * 				ElementoDuplaEnc, dado = info, head = _next,
	 * 				nullptr = _previous (ver classe ElementoDuplaEnc.hpp)
	 *
	 * @param  		dado  Dado genérico, podendo ser um inteiro, float...
	 */
	void adicionaNoInicioDuplo(const T& dado) {
		ElementoDuplaEnc<T> *novo = new ElementoDuplaEnc<T>(dado, head, nullptr);
		if(novo == nullptr) {
			throw std::runtime_error("Sem Espaço na Memória");
		} else {
			head = novo;
			if(novo->getProximo() ! nullptr) {
				novo->getProximo()->setAnterior(novo);
			}
			++size;
		}
	}
	T retiraDoInicioDuplo() {

	}
	void eliminaDoInicioDuplo() {

	}
	/**
	* POSIÇÃO
	*/
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {

	}
	int posicaoDuplo(const T& dado) const {

	}
	T* posicaoMemDuplo(const T& dado) const {

	}
	bool contemDuplo(const T& dado) {

	}
	T retiraDaPosicaoDuplo(int pos) {

	}
	/**
	* FIM
	*/
	void adicionaDuplo(const T& dado) {

	}
	T retiraDuplo() {

	}
	int verUltimo() {

	}
	/**
	* ESPECÍFICO
	*/
	T retiraEspecificoDuplo(const T& dado) {

	}
	T mostra(int pos) {

	}
	void adicionaEmOrdem(const T& data) {

	}
	/**
	* TESTES
	*/
	/**
	 * @brief      Checa se a lista está vazia
	 *
	 * @return     Retorna true caso a lista esteja vazia
	 */
	bool listaVazia() const {
		return size == 0;
	}
	/**
	 * @brief      Checa se dois determinados dados são iguais
	 */
	bool igual(T dado1, T dado2) const {
		return dado1 == dado2;
	}
	/**
	 * @brief      Checa se o dado1 é maior que o dado2
	 */
	bool maior(T dado1, T dado2) const {
		return dado1 > dado2;
	}
	/**
	 * @brief      Checa se o dado1 é menor que o dado2
	 */
	bool menor(T dado1, T dado2) const {
		return dado1 < dado2;
	}
	void destroiListaDuplo() {

	}
};

#endif  // LISTADUPLAENC_HPP
