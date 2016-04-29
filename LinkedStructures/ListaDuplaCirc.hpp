// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef LISTADUPLACIRC_HPP
#define LISTADUPLACIRC_HPP

#include <stdexcept>

#include "ElementoDuplaEnc.hpp"

/**
 * @brief  		Implementação de uma estrutura de Lista circular duplamente
 * 				encadeada em C++
 *
 * @param  		head		Ponteiro para o header da Lista encadeada
 * @param  		size		Armazena a quantidade de elementos na Lista encadeada
 */
template <typename T>
class ListaDuplaCirc {
 private:
	ElementoDuplaEnc<T> *head = nullptr;
	int size = 0;

 public:
	/**
	 * @brief  		Construtor da classe ListaDuplaCirc
	 *
	 * @details		O header aponta para null e o size está em zero
	 */
	ListaDuplaCirc() = default;
	/**
	 * @brief 		Destrutor da classe ListaDuplaCirc
	 *
	 * @details 	Chama o método destroiListaDuplo() para destruir elemento por
	 * 				elemento
	 */
	~ListaDuplaCirc() {
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
			if(size == 0) {
				head = novo;
				novo->setProximo(novo);
				novo->setAnterior(novo);
				++size;
				return;
			} else {
				ElementoDuplaEnc<T> *atual = head;
				while(atual->getProximo() != head) {
					atual = atual->getProximo();
				}
				head->setAnterior(novo);
				atual->setProximo(novo);
				head = novo;
				++size;
			}

		}
	}
	/**
	 * @brief      Retira e retorna um elemento do início da lista e retorna seu
	 *             dado
	 *
	 * @details    O objeto da classe elemento apontada pelo head é retirado da
	 *             lista e seu dado é retornado
	 */
	T retiraDoInicioDuplo() {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		} else {
			ElementoDuplaEnc<T> *atual = head;
			T volta = atual->getInfo();
			head = atual->getProximo();
			--size;

			if(listaVazia()) {
				delete atual;
				return volta;
			} else {
				ElementoDuplaEnc<T> *teste = head;
				while(teste->getProximo() != atual) {
					teste = teste->getProximo();
				}
				teste->setProximo(head);
				head->setAnterior(teste);
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
	void eliminaDoInicioDuplo() {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		} else {
			ElementoDuplaEnc<T> *atual = head;
			head = atual->getProximo();
			--size;

			if(listaVazia()) {
				delete atual;
				return;
			} else {
				ElementoDuplaEnc<T> *teste = head;
				while(teste->getProximo() != atual) {
					teste = teste->getProximo();
				}
				teste->setProximo(head);
				head->setAnterior(teste);
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
	 *                   classe ElementoDuplaEnc, dado = info (ver classe
	 *                   ElementoDuplaEnc.hpp)
	 * @param      pos   Posição desejada para o elemento ser colocado
	 *
	 * @details    Caso a posição seja 0 chama o método adicionaNoInicioDuplo(),
	 *             pois é um caso epecífico Uma explicação de como é feito os
	 *             índices de posição desta lista podem ser encontrada na
	 *             descrição do método posicaoDuplo()
	 */
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
		if(pos > size || pos < 0) {
			throw std::runtime_error("Posição Inválida");
		}
		if(pos == 0) {
			adicionaNoInicioDuplo(dado);
		} else {
			ElementoDuplaEnc<T> *atual = head;
			ElementoDuplaEnc<T> *novo =
			new ElementoDuplaEnc<T>(dado, nullptr, nullptr);

			if(novo == nullptr) {
				throw std::runtime_error("Sem Espaço na Memória");
			} else {
				for(int i = 0; i < (pos-1); i++) {
					atual = atual->getProximo();
				}
				novo->setProximo(atual->getProximo());
				atual->getProximo()->setAnterior(novo);
				novo->setAnterior(atual);
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
	int posicaoDuplo(const T& dado) const {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		}
		ElementoDuplaEnc<T> *atual = head;
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
	T* posicaoMemDuplo(const T& dado) const {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		}
		ElementoDuplaEnc<T> *atual = head;
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
	bool contemDuplo(const T& dado) {
		if(listaVazia()) {
			return false;
		} else {
			ElementoDuplaEnc<T> *atual = head;
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
	 * @details 	Caso a posição seja 0, chama o metódo retiraDoInicioDuplo(), pois
	 * 				é um caso específico
	 */
	T retiraDaPosicaoDuplo(int pos) {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		}
		if(pos > size-1 || pos < 0) {
			throw std::runtime_error("Posição Inválida");
		} else {
			if(pos == 0) {
				return retiraDoInicioDuplo();
			} else {
				ElementoDuplaEnc<T> *anterior = head;
				ElementoDuplaEnc<T> *eliminar;
				for(int i = 0; i < (pos-1); i++) {
					anterior = anterior->getProximo();
				}
				eliminar = anterior->getProximo();
				T volta = eliminar->getInfo();
				eliminar->getProximo()->setAnterior(anterior);
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
	 * @brief      Adicona um elemento ao final da lista
	 *
	 * @param      dado  O valor dado como parâmetro cria um novo objeto da
	 *                   classe ElementoDuplaEnc, dado = info (ver classe
	 *                   ElementoDuplaEnc.hpp)
	 *
	 * @details    Utiliza o método adicionaNaPosicaoDuplo()
	 */
	void adicionaDuplo(const T& dado) {
		adicionaNaPosicaoDuplo(dado, size);
	}
	/**
	 * @brief 		Retira um elemento do final da lista e retorna seu dado
	 *
	 * @details 	Utiliza o método retiraNaPosicao()
	 */
	T retiraDuplo() {
		return retiraDaPosicaoDuplo(size-1);
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
	 * @details 	Utiliza o método retiraDaPosicaoDuplo() com paramêtro o método
	 * 				posicaoDuplo()
	 */
	T retiraEspecificoDuplo(const T& dado) {
		return retiraDaPosicaoDuplo(posicaoDuplo(dado));
	}

	/**
	 * @brief      Retorna o dado de uma determinada posição da lista
	 *
	 * @param      pos   Posição desejada
	 */
	T mostra(int pos) {
		if(listaVazia()) {
			throw std::runtime_error("Lista Vazia");
		}
		if(pos > size-1 || pos < 0) {
			throw std::runtime_error("Posição Inválida");
		} else {
			ElementoDuplaEnc<T> *atual = head;
			for(int i = 0; i < pos; i++) {
				atual = atual->getProximo();
			}
			return atual->getInfo();
		}
	}
	/**
	 * @brief      Adicona um elemento em ordem crescente
	 *
	 * @param      data  O valor dado como parâmetro cria um novo objeto da
	 *                   classe ElementoDuplaEnc, dado = info (ver classe
	 *                   ElementoDuplaEnc.hpp)
	 *
	 * @details    Percorre elemento por elemento checando o dado de parâmetro é
	 *             maior que o dado da lista, caso seja vai para o próximo
	 *             elemento, caso não seja utiliza o método adicionaNaPosicao()
	 *             com o contador que é utilizado na iteração de cada elemento
	 *             percorrido
	 */
	void adicionaEmOrdem(const T& data) {
		if(listaVazia()) {
			adicionaNoInicioDuplo(data);
		} else {
			ElementoDuplaEnc<T> *atual = head;
			int pos = 0;
			do {
				if(maior(data, atual->getInfo())) {
					atual = atual->getProximo();
					++pos;
				} else {
					break;
				}
			} while (atual->getProximo() != head);
			adicionaNaPosicaoDuplo(data, pos);
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
	void destroiListaDuplo() {
		while (size != 0) {
			eliminaDoInicioDuplo();
		}
	}
};

#endif  // LISTADUPLACIRC_HPP
