// Copyright Bruno Marques e Salomão Rodrigues Jacinto [2016.1]

#ifndef PISTA_HPP
#define PISTA_HPP

#include "Carro.hpp"
#include "../library/FilaEnc.hpp"
#include <cstdio>

//!  Classe Pista.
/*!  Classe representativa de uma pista de trânsito.
 * 	 \author Bruno Marques do Nascimento & Salomão Rodrigues Jacinto
 * 	 \since 10/05/2016
 * 	 \version 1.0
 */
class Pista : public FilaEnc<Carro*> {
 private:
 	int _velocidade;  /*!< Inteiro que guarda a velocidade da pista */

 	int _tamanho;  /*!< Inteiro que guarda o tamanho da pista */

 	int _espacoUsado;  /*!< Inteiro que guarda o espaço usado da pista */

 	int _frequenciaBase;  /*!< Inteiro com a freq. base de criação de carro */

 	int _frequenciaVariacao;  /*!< Inteiro com a variação da freq. base */

 	int _carrosPassantes;  /*!< Inteiro com o número de carros passantes,
 							*   nas pistas centrais */

 	int _carrosCriados;  /*!< Inteiro com o número de carros criados,
 						  *   nas pistas fontes */

 	int _carrosDeletados;  /*!< Inteiro com o número de carros deletados,
 							*   nas pistas sumidouro */

 	int _tempoChegada;  /*!< Inteiro com tempo de travessia da pista */

 	bool _sumidouro;  /*!< Boolean que informa se a pista é sumidouro */

 	bool _fonte;  /*!< Boolean que informa se a pista é fonte */

 public:
//! Contrutor com parâmetros.
/*! Sempre que usado, este construtor criará uma pista.
 *
 *  \param velocidade define a velocidade da pista.
 *  \param tamanho define o tamanho da pista.
 *  \param frequenciaBase define a frequência base de criação de carros.
 *  \param frequenciaVariacao define a variação da frequência base.
 */
 	Pista (int velocidade, int tamanho, int frequenciaBase, 
 										int frequenciaVariacao);

//!  Função calculaTempoDeslocamento, calcula o tempo de travessia da pista.
/*!  
 *   \param velocidade que possui a velocidade da pista.
 * 	 \param tamanho que possui o tamanho da pista.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	void calculaTempoDeslocamento(int velocidade, int tamanho);

//!  Função calculaProximoSpawn, calcula o tempo da próxima criação de carro.
/*!  
 *   \param tempoAtual informa o tempo atual para calcular próximo spawn.
 *	 \return um inteiro com o tempo de criação do próximo carro.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	int calculaProximoSpawn(int tempoAtual);

//!  Função adicionarCarro, adiciona um carro na pista.
/*!  
 *   \param carro informa o carro que seerá adicionado na pista.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	void adicionarCarro(Carro* carro);

//!  Função removerCarro, remove um carro na pista.
/*!  
 *   \return o carro que foi removido da pista.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	Carro* removerCarro();

//!  Função tempoChegada, calcula o tempo em que o carro chegará no semáforo.
/*!  
 *   \param tempoCriado informa o tempo que o carro foi criado.
 *	 \return um inteiro com o tempo de chegada do carro no semáforo.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	int tempoChegada(int tempoCriado);

//!  Função pistaCheia, verifica se a pista está cheia.
/*!  
 *   \param carro informa o carro que seria adicionado na pista.
 *	 \return um boolean que informa se é possível adicionar o carro na pista.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	bool pistaCheia(Carro* carro);

//!  Função fonte, informa se a pista é uma fonte.
/*!  
 *   \return um boolean que informa se a pista é fonte.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	bool fonte();

//!  Função sumidouro, informa se a pista é um sumidouro.
/*!  
 *   \return um boolean que informa se a pista é sumidouro.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	bool sumidouro();

//!  Função carrosCriados, informa o número de carros criados na fonte.
/*!  
 *   \return um inteiro que informa o número de carros criados na fonte.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	int carrosCriados();

//!  Função carrosPassantes, informa quantidade de carros passantes.
/*!  
 *   \return inteiro informando o número de carros passantes na pista central.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	int carrosPassantes();

//!  Função carrosDeletados, informa quantidade de carros deletados.
/*!  
 *   \return inteiro informando o número de carros deletados no sumidouro.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	int carrosDeletados();

//!  Função espacoUsado, informa quantidade de espaco ocupado na pista.
/*!  
 *   \return inteiro informando a quantidade de espaço usado na pista.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	int espacoUsado();

//!  Função getTamanho, informa o tamanho da pista.
/*!  
 *   \return inteiro informando o tamanho da pista.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	int getTamanho();

};

Pista::Pista(int velocidade, int tamanho, int frequenciaBase, int frequenciaVariacao) {

	FilaEnc<Carro*>();

	_velocidade = velocidade;
	_tamanho = tamanho;

	_tempoChegada = (int) tamanho / (velocidade / 3.6);
	_frequenciaVariacao = frequenciaVariacao;
	_frequenciaBase = frequenciaBase;

	_espacoUsado = 0 ;
	_carrosPassantes = 0 ;
	_carrosCriados = 0;
	_carrosDeletados = 0 ;

	if(frequenciaBase > 0) { //fonte
		_fonte = true;
		_sumidouro = false;

	} else if (frequenciaBase == 0) { //central
		_sumidouro = false;
		_fonte = false;	

	} else {	//sumidouro
		_sumidouro = true;
		_fonte = false;	
	}
}

int Pista::calculaProximoSpawn(int tempoAtual) {
	return (tempoAtual + (_frequenciaBase - _frequenciaVariacao) + (rand() % (_frequenciaVariacao * 2)) + 1);
}

void Pista::adicionarCarro(Carro* carro) {

	if ((_espacoUsado + carro->tamanho()) <= _tamanho ) {
		inclui(carro);
		_espacoUsado += carro->tamanho();
		if (fonte()) {
			_carrosCriados++;
		} 
		if (!fonte() && !sumidouro()) {
			_carrosPassantes++;
		}	
	}
}

Carro* Pista::removerCarro() {

	Carro* carro =	retira();
	_espacoUsado -= carro->tamanho();
	if (sumidouro()) {
		_carrosDeletados++;
	}
	return carro;
}

int Pista::tempoChegada(int tempoAtual) {
	return _tempoChegada + tempoAtual;
}

bool Pista::pistaCheia(Carro* carro) {
	return _espacoUsado + carro->tamanho() > _tamanho;
}

bool Pista::fonte() {
	return _fonte;
}

bool Pista::sumidouro() {
	return _sumidouro;
}

int Pista::carrosPassantes() {
	return _carrosPassantes;
}

int Pista::carrosDeletados() {
	return _carrosDeletados;
}

int Pista::espacoUsado() {
	return _espacoUsado;
}

int Pista::getTamanho() {
	return _tamanho;
}

int Pista::carrosCriados() {
	return _carrosCriados;
}

#endif /* PISTA_HPP */
