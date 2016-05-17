// Copyright Bruno Marques <2016.1>

#ifndef LISTA_HPP
#define LISTA_HPP

#include <stdexcept>

//!  Classe da estrutura de dado: Lista.
/*!  Implementação da estruturda de dado Lista,
 *   realizada na disciplina de Estrutura de Dados - INE5408
 *   como segundo terceiro prático do semestre.
 *   \author Bruno Marques do Nascimento
 *   \since 05/04/2016
 *   \version 1.0
 */
template <typename T>
class Lista {
 private:
  T* dados;  /*!< Ponteiro para o array de T */
  int maxLista;  /*!< Tamanho máximo que a lista deve assumir */
  int ultimo = -1;  /*!< Posição do último elemento */

 public:
//!  Contrutor padrão.
/*!  Sempre que usado, este construtor criará uma 
 *   lista, com tamanho definido pela variável maxLista.
 */
	Lista() {
    dados = new T[maxLista];
  }

//!  Contrutor com paramêtro.
/*!  Sempre que usado, este construtor criará uma 
 *   lista, com tamanho definido pela variável inteira "tam".
 */
	explicit Lista(int tam): maxLista(tam) {
    dados = new T[maxLista];
  }


  T mostra (int posicao) {
    if (listaVazia()) {
      throw std::runtime_error("Erro Lista Vazia");
    } else if (posicao < 0 || posicao > maxLista-1) {
      throw std::runtime_error("Posição inválida");
    } else {
      return dados[posicao];
    }
  }
//!  Função adiciona, insere um novo dado no fim da lista, e retorna vazio.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista.
 *   \sa listaCheia() and Lista()
 */
  void adiciona(T dado) {
    adicionaNaPosicao(dado, ultimo+1);
  }

//!  Função adicionaNoInicio, insere um dado no inicio da lista e retorna vazio.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista.
 *   \sa listaCheia() and Lista()
 */
	void adicionaNoInicio(T dado) {
    adicionaNaPosicao(dado, 0);
  }

//!  Função adicionaNaPosicao, insere um dado em uma posicao definida da lista.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista.
 *   \param posicao posição de inserção desejada
 *   \sa listaCheia() and Lista()
 */
	void adicionaNaPosicao(T dado, int posicao) {
    if (listaCheia()) {
      throw std::runtime_error("Lista Cheia");
    } else if (posicao < 0 || posicao > ultimo+1) {
      throw std::runtime_error("Posição Inválida");
    } else {
      ++ultimo;
      int cont = ultimo;
      while (cont > posicao) {
        dados[cont] = dados[cont-1];
        --cont;
      }
      dados[posicao] = dado;
    }
  }

//!  Função adicionaEmOrdem insere um dado na lista em ordem crescente.
/*!  
 *   \param dado argumento do tipo T, que será adicionado na lista.
 *   \sa listaCheia() and Lista()
 */
	void adicionaEmOrdem(T dado) {
		if ( listaCheia() ) {
	        throw std::runtime_error("Erro Lista Cheia");
	    } else {
	        int posicao = 0;
	        while (posicao <= ultimo && dado > dados[posicao]) {
	          ++posicao;
	        }
	        adicionaNaPosicao(dado, posicao);
	    }
  	}

//!  Função retira, retira um dado da lista, e retorna um tipo T.
/*!  
 *   \return o dado retirado da lista do tipo T.
 *   \sa listaVazia() and Lista()
 */
	T retira() {
    return retiraDaPosicao(ultimo);
  }

//!  Função retiraDoInicio, retira um dado da posição inicial da lista.
/*!  
 *   \return o dado retirado da lista do tipo T.
 *   \sa listaVazia() and Lista()
 */
	T retiraDoInicio() {
    return retiraDaPosicao(0);
  }

//!  Função retiraDaPosicao, retira um dado da lista, de uma posição escolhida.
/*!  
 *   \param posicao posição de retirada de um dado.
 *   \return o dado retirado da lista do tipo T.
 *   \sa listaVazia() and Lista()
 */
	T retiraDaPosicao(int posicao) {
    if (listaVazia()) {
      throw std::runtime_error("Erro Lista Vazia");
    } else if (posicao < 0 || posicao > maxLista-1) {
      throw std::runtime_error("Posição inválida");
    } else {
      T temp = dados[posicao];
      for (int i = 0; i < ultimo-posicao; i++) {
        dados[posicao] = dados[posicao+1];
      }
      --ultimo;
      return temp;
    }
  }

//!  Função retiraEspecifico, retira um dado específico da lista.
/*!  
 *   \param dado argumento do tipo T, que será retirado da lista.
 *   \return o dado retirado da lista do tipo T.
 *   \sa listaVazia() and Lista()
 */
	T retiraEspecifico(T dado) {
    if (contem(dado)) {
      int temp;
      for (int i = 0; i < ultimo+1; i++) {
        if (dado == dados[i]) {
          temp = i;
          break;
        }
      }
      return retiraDaPosicao(temp);
    } else {
      throw std::runtime_error("Não Contém");
    }
  }

//!  Função posicao, informa a posição de um dado na lista.
/*!  
 *   \param dado argumento do tipo T, que será procurado na lista.
 *   \return um inteiro que iforma a posição do dado na lista.
 *   \sa listaVazia() and Lista()
 */
	int posicao(T dado) {
    if (contem(dado)) {
      int temp, i;
      for (i = 0; i < ultimo+1; i++) {
        if (dado == dados[i]) {
          temp = i;
          break;
        }
      }
      return temp;
    } else {
      throw std::runtime_error("Não Contém");
    }
  }

//!  Função contem, informa a presença de um dado na lista.
/*!  
 *   \param dado argumento do tipo T, que será procurado na lista.
 *   \return um boolean que iforma a presença do dado na lista.
 *   \sa listaVazia() and Lista()
 */
	bool contem(T dado) {
    if (listaVazia()) {
      return false;
    } else {
      for (int i = 0; i < ultimo+1; i++) {
        if (dado == dados[i]) return true;
      }
      return false;
    }
  }

//!  Função igual, informa se os dados são iguais.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é igual ao dado2.
 */
	bool igual(T dado1, T dado2) {
      return dado1 == dado2;
  }

//!  Função maior, informa se um dado é maior que o outro.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é maior que dado2.
 */
	bool maior(T dado1, T dado2) {
      return dado1 > dado2;
  }

//!  Função menor, informa se um dado é menor que o outro.
/*!  
 *   \param dado1 argumento do tipo T, que será comparado com dado2.
 *   \param dado2 argumento do tipo T, que será comparado com dado1.
 *   \return um boolean que informa se dado1 é menor que dado2.
 */
	bool menor(T dado1, T dado2) {
      return dado1 < dado2;
  }

//!  Função listaCheia, informa se um a lista está cheia
/*!  
 *   \return um boolean que informa se a lista está cheia ou não.
 */
	bool listaCheia() {
    return ultimo == (maxLista - 1);
  }

//!  Função listaVazia, informa se um a lista está vazia
/*!  
 *   \return um boolean que informa se a lista está vazia ou não.
 */
	bool listaVazia() {
    return ultimo == -1;
  }

//!  Função destroiLista, zera a lista descartando seus dados
/*!  
 */
	void destroiLista() {
    ultimo = -1;
  }
};

#endif