// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef LISTA_HPP
#define LISTA_HPP

/**
 * @brief  		Implementação de uma estrutura de Lista em C++
 *
 * @tparam  	T			Ponteiro para o início da Lista
 *
 * @param  		topo		Armazena o último da Lista
 * @param  		tamanho		Armazena o tamanho da Lista
 */
template <typename T>
class Lista {
 private:
	const int MAXLISTA = 100;
	T* m_dados;
	int topo;
	int tamanho;

 public:
	/**
	 * @brief  		Construtor da classe Lista
	 *
	 * @details  	Valor do tamanho definido em uma constante como 100
	 */
	Lista() {
		topo = -1;
		m_dados = new T[MAXLISTA];
		tamanho = MAXLISTA;
	}
	/**
	 * @brief  		Construtor da classe Fila
	 *
	 * @param  		tam		Valor para o tamanho da lista
	 */
	explicit Lista(int tam) {
		topo = -1;
		m_dados = new T[tam];
		tamanho = tam;
	}
	/**
	 * @brief  		Adiciona um dado ao último da lista
	 *
	 * @param  		dado  Dado genérico, podendo ser um inteiro, float...
	 */
	void adiciona(T dado) {
		adicionaNaPosicao(dado, topo+1);
	}
	/**
	 * @brief  		Adiciona um dado ao início da lista
	 *
	 * @param  		dado  Dado genérico, podendo ser um inteiro, float...
	 */
	void adicionaNoInicio(T dado) {
		adicionaNaPosicao(dado, 0);
	}
	/**
	 * @brief  		Adiciona um dado na posição desejada da lista
	 *yaourt
	 * @param  		dado  Dado genérico, podendo ser um inteiro, float...
	 * @param 		posicao  Inteiro para posição desejada
	 */
	void adicionaNaPosicao(T dado, int posicao) {
		if(listaCheia()) {
			throw "Lista cheia";
		} else {
			if(posicao > topo + 1 || posicao < 0) {
				throw "Posição inválida";
			} else {
				topo++;
				int i = topo;
				while(i > posicao) {
					m_dados[i] = m_dados[i-1];
					i--;
				}
				m_dados[posicao] = dado;
			}
		}
	}
	/**
	 * @brief  		Adiciona um dado na lista acima do que possuí uma valor
	 * 				inferior ao seu e abaixo do que possuí um valor superior
	 *
	 * @param  		dado  Dado genérico, podendo ser um inteiro, float...
	 */
	void adicionaEmOrdem(T dado) {
		if(listaCheia()) {
			throw "Lista Cheia";
		} else {
			int i = 0;
			while(i <= topo && maior(dado, m_dados[i])) {
				i++;
			}
			adicionaNaPosicao(dado, i);
		}
	}
	/**
	 * @brief      Retira o último dado colocado na lista
	 */
	T retira() {
		return retiraDaPosicao(topo);
	}
	/**
	 * @brief      Retira o dado que ocupe a posição 0 da lista
	 */
	T retiraDoInicio() {
		return retiraDaPosicao(0);
	}
	/**
	 * @brief 		Retira o dado que ocupe a posição desejada na lista
	 *
	 * @param 		posicao  Inteiro para posição desejada
	 */
	T retiraDaPosicao(int posicao) {
		if(posicao > topo || posicao < 0) {
			throw "Posição inválidaa";
		} else {
			if(listaVazia()) {
				throw "Lista Vazia";
			} else {
				topo--;
				T dadoaux = m_dados[posicao];
				int i = posicao;
				while(i <= topo) {
					m_dados[i] = m_dados[i+1];
					i++;
				}
				return dadoaux;
			}
		}
	}
	/**
	 * @brief 		Retira um dado específico da lista
	 *
	 * @param 		dado  Dado a ser pesquisado na lista, e retirado caso
	 * 				encontrado
	 */
	T retiraEspecifico(T dado) {
		return retiraDaPosicao(posicao(dado));
	}

	/**
	 * @brief 		Retorna a posição do dado desejado
	 *
	 * @param 		dado  Dado genérico, podendo ser um inteiro, float...
	 *
	 * @return 		Inteiro para posição do dado
	 */
	int posicao(T dado) {
		int i = 0;
		while(i <= topo && !(igual(dado, m_dados[i]))) {
			i++;
		}
		if(i > topo) {
			throw "Este dado não existe";
		} else {
			return i;
		}
	}
	/**
	 * @brief 		Pesquisa se a lista contém um determinado dado
	 *
	 * @param 		dado  Dado genérico, podendo ser um inteiro, float...
	 *
	 * @return 		Retorna true caso exista o dado desejado na lista e
	 * 				false caso contrário
	 */
	bool contem(T dado) {
		if(listaVazia()) {
			return false;
		} else {
			for(int i = 0; i <= topo; i++) {
				if(igual(m_dados[i], dado)) {
					return true;
				}
			}
			return false;
		}
	}
	/**
	 * @brief      Checa se dois determinados dados são iguais
	 */
	bool igual(T dado1, T dado2) {
		return dado1 == dado2;
	}
	/**
	 * @brief      Checa se o dado1 é maior que o dado2
	 */
	bool maior(T dado1, T dado2) {
		return dado1 > dado2;
	}
	/**
	 * @brief      Checa se o dado1 é menor que o dado2
	 */
	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}
	/**
	 * @brief      Checa se a lista está cheia
	 *
	 * @return     Retorna true caso a lista esteja cheia
	 */
	bool listaCheia() {
		if (topo == tamanho-1) {
			return true;
		} else {
			return false;
		}
	}
	/**
	 * @brief      Checa se a lista está vazia
	 *
	 * @return     Retorna true caso a lista esteja vazia
	 */
	bool listaVazia() {
		if (topo == -1) {
			return true;
		} else {
			return false;
		}
	}
	/**
	 * @brief      Reinicia a lista sem apagar os dados, apenas reinicia o
	 * 			   indexador, ou seja, os dados serão sobrescritos
	 */
	void destroiLista() {
		topo = -1;
	}
};
#endif  // LISTA_HPP
