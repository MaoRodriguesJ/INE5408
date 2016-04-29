// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef LISTACIRC_HPP
#define LISTACIRC_HPP

#include <stdexcept>
#include "Elemento.hpp"

/**
 * @brief  		Implementação de uma estrutura de Lista Encadeada Circular em C++
 *
 * @param  		head		Ponteiro para o header da Lista
 * @param  		size		Armazena a quantidade de elementos na Lista
 */
template<typename T>
class ListaCirc {
 private:
	Elemento<T> *head = nullptr;
	int size = 0;

 public:
	/**
	 * @brief  		Construtor da classe ListaCirc
	 *
	 * @details		O header aponta para null e o size está em zero
	 */
	ListaCirc() = default;
	/**
	 * @brief 		Destrutor da classe ListaCirc
	 *
	 * @details 	Chama o método destroiLista() para destruir elemento por
	 * 				elemento
	 */
	~ListaCirc() {
		destroiLista();
	}
	/**
	* INICIO
	*/
	/**
	 * @brief 		Adicona um elemento ao início da lista
	 *
	 * @details 	O valor dado como parâmetro cria um novo objeto da classe
	 * 				elemento, dado = info, head = _next (ver classe Elemento.hpp)
	 *
	 * @param  		dado  Dado genérico, podendo ser um inteiro, float...
	 */
	void adicionaNoInicio(const T& dado) {
		Elemento<T> *novo = new Elemento<T>(dado, nullptr);
		if(novo == nullptr) {
			throw std::runtime_error("Sem Espaço na Memória");
		} else {
			if(size == 0) {
				head = novo;
				novo->setProximo(novo);
				++size;
				return;
			} else {
				Elemento<T> *atual = head;
				while(atual->getProximo() != head) {
					atual = atual->getProximo();
				}
				atual->setProximo(novo);
				novo->setProximo(head);
				head = novo;
				++size;
			}
		}
	}
	/**
	 * @brief 		Retira um elemento do início da lista e retorna seu dado
	 *
	 * @details 	O objeto da classe elemento apontada pelo head é retirado da
	 * 				lista e seu dado é retornado
	 */
	T retiraDoInicio() {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		} else {
			Elemento<T> *atual = head;
			T volta = atual->getInfo();
			head = atual->getProximo();
			--size;

			if(listaVazia()) {
				delete atual;
				return volta;
			} else {
				Elemento<T> *teste = head;
				while(teste->getProximo() != atual) {
					teste = teste->getProximo();
				}
				teste->setProximo(head);
				delete atual;
				return volta;
			}
		}
	}
	/**
	 * @brief 		Retira um elemento do início da lista
	 *
	 * @details 	O objeto da classe elemento apontada pelo head é retirado da
	 * 				lista
	 */
	void eliminaDoInicio() {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		} else {
			Elemento<T> *atual = head;
			head = atual->getProximo();
			--size;

			if(listaVazia()) {
				delete atual;
				return;
			} else {
				Elemento<T> *teste = head;
				while(teste->getProximo() != atual) {
					teste = teste->getProximo();
				}
				teste->setProximo(head);
				delete atual;
			}
		}
	}
	/**
	* POSIÇÃO
	*/
	/**
	 * @brief      Adiciona um elemento na posição desejada
	 *
	 * @param      dado  O valor dado como parâmetro cria um novo objeto da
	 *                   classe elemento, dado = info (ver classe Elemento.hpp)
	 *
	 * @param      pos   Posição desejada para o elemento ser colocado
	 *
	 * @details    Caso a posição seja 0 chama o método adicionaNoInicio(), pois
	 *             é um caso epecífico Uma explicação de como é feito os índices
	 *             de posição desta lista podem ser encontrada na descrição do
	 *             método posicao()
	 */
	void adicionaNaPosicao(const T& dado, int pos) {
		if(pos > size || pos < 0) {
			throw std::runtime_error("Posição Inválida");
		}
		if(pos == 0) {
			adicionaNoInicio(dado);
		} else {
			Elemento<T> *atual = head;
			Elemento<T> *novo = new Elemento<T>(dado, nullptr);
			if(novo == nullptr) {
				throw std::runtime_error("Sem Espaço na Memória");
			} else {
				for(int i = 0; i < (pos-1); i++) {
					atual = atual->getProximo();
				}
				novo->setProximo(atual->getProximo());
				atual->setProximo(novo);
				++size;
			}
		}
	}
	/**
	 * @brief 		Retorna a posição de um dado específico
	 *
	 * @param 		dado  Dado a ser pesquisado
	 *
	 * @details 	Os índices de posição começam em 0 e vão até size-1, ou seja,
	 * 				com uma lista de 10 elementos as posições estão numeradas de
	 * 				0 a 9
	 */
	int posicao(const T& dado) const {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		}
		Elemento<T> *atual = head;
		for(int i = 0; i < size; i++) {
			if(igual(dado, atual->getInfo())) {
				return i;
			}
			atual = atual->getProximo();
		}
		throw std::runtime_error("Este dado não existe");
	}
	/**
	 * @brief 		Retorna o ponteiro para posição de um dado específico
	 *
	 * @param 		dado  Dado a ser pesquisado
	 */
	T* posicaoMem(const T& dado) const {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		}
		Elemento<T> *atual = head;
		for(int i = 0; i < size; i++) {
			if(igual(dado, atual->getInfo())) {
				return atual;
			} else {
				atual = atual->getProximo();
			}
		}
		throw std::runtime_error("Este dado não existe");
	}
	/**
	 * @brief 		Verifica se a lista contém um dado específico, retornando
	 * 				true caso exista um elemento com esse dado
	 *
	 * @param 		dado  Dado a ser pesquisado
	 */
	bool contem(const T& dado) const {
		if(listaVazia()) {
			return false;
		} else {
			Elemento<T> *atual = head;
			for(int i = 0; i < size; i++) {
				if(igual(dado, atual->getInfo())) {
					return true;
				} else {
					atual = atual->getProximo();
				}
			}
			return false;
		}
	}
	/**
	 * @brief 		Retira um elemento de uma posição deseja e retorna seu dado
	 *
	 * @param 		Posição do elemento a ser retirado
	 *
	 * @details 	Caso a posição seja 0, chama o metódo retiraDoInicio(), pois
	 * 				é um caso específico
	 */
	T retiraDaPosicao(int pos) {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		}
		if(pos > size-1 || pos < 0) {
			throw std::runtime_error("Posição Inválida");
		} else {
			if(pos == 0) {
				return retiraDoInicio();
			} else {
				Elemento<T> *anterior = head;
				Elemento<T> *eliminar;
				for(int i = 0; i < (pos-1); i++) {
					anterior = anterior->getProximo();
				}
				eliminar = anterior->getProximo();
				T volta = eliminar->getInfo();
				anterior->setProximo(eliminar->getProximo());
				delete eliminar;
				--size;
				return volta;
			}
		}
	}
	/**
	* FIM
	*/
	/**
	 * @brief 		Adicona um elemento ao final da lista
	 *
	 * @param 		dado	O valor dado como parâmetro cria um novo objeto da
	 * 						classe elemento, dado = info (ver classe Elemento.hpp)
	 *
	 * @details 	Utiliza o método adicionaNaPosicao()
	 */
	void adiciona(const T& dado) {
		adicionaNaPosicao(dado, size);
	}
	/**
	 * @brief 		Retira um elemento do final da lista e retorna seu dado
	 *
	 * @details 	Utiliza o método retiraNaPosicao()
	 */
	T retira() {
		return retiraDaPosicao(size-1);
	}
	/**
	 * @brief      Retorna o último elemento da lista
	 */
	T mostra() {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		}
		Elemento<T> *atual = head;
		while(atual->getProximo() != head) {
			atual = atual->getProximo();
		}
		return atual->getInfo();
	}
	/**
	 * @brief      Retorna o tamanho da lista
	 */
	int verUltimo() {
		return size;
	}
	/**
	* ESPECÍFICO
	*/
	/**
	 * @brief 		Retira um elemento que tenha um dado específico e retorna
	 * 				seu dado
	 *
	 * @details 	Utiliza o método retiraDaPosicao() com paramêtro o método
	 * 				posicao()
	 */
	T retiraEspecifico(const T& dado) {
		return retiraDaPosicao(posicao(dado));
	}
	/**
	 * @brief 		Adicona um elemento em ordem crescente
	 *
	 * @param 		data	O valor dado como parâmetro cria um novo objeto da
	 * 						classe elemento, dado = info (ver classe Elemento.hpp)
	 *
	 * @details 	Percorre elemento por elemento checando o dado de parâmetro
	 * 				é maior que o dado da lista, caso seja vai para o próximo
	 * 				elemento, caso não seja utiliza o método adicionaNaPosicao()
	 * 				com o contador que é utilizado na iteração de cada elemento
	 * 				percorrido
	 */
	void adicionaEmOrdem(const T& data) {
		if(listaVazia()) {
			adicionaNoInicio(data);
		} else {
			Elemento<T> *atual = head;
			int pos = 0;
			do {
				if(maior(data, atual->getInfo())) {
					atual = atual->getProximo();
					++pos;
				} else {
					break;
				}
			} while (atual->getProximo() != head);
			adicionaNaPosicao(data, pos);
		}
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
	/**
	 * @brief 		Destrói a lista elemento por elemento
	 */
	void destroiLista() {
		while (size != 0) {
			eliminaDoInicio();
		}
	}
};

#endif  // LISTACIRC_HPP
