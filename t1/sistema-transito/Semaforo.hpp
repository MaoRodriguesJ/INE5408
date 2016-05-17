// Copyright Bruno Marques e Salomão Rodrigues Jacinto [2016.1]

#ifndef SEMAFORO_HPP
#define SEMAFORO_HPP

#include <stdexcept> 
#include "../library/Lista.hpp"
#include "Pista.hpp"

//!  Classe Semaforo.
/*!  Classe representativa de um semáforo de trânsito.
 * 	 \author Bruno Marques do Nascimento & Salomão Rodrigues Jacinto
 * 	 \since 10/05/2016
 * 	 \version 1.0
 */
class Semaforo {
 private:
 	Lista<Pista*>* _pistasDeSaida;  /*!< Um ponteiro Lista<Pista*>* que guarda 
 									 *   as pistas de destino referentes
 									 * 	 a este semáforo.
 									 */
 	Pista* _pistaControlada;  /*!< Um ponteiro Pista* que guarda a pista
 							   *   controlada pelo semáforo.
 							   */

 	int _tempoAberto;  /*!< Inteiro com o tempo de abertura do semaforo */

 	int* _probabilidades;  /*!< Inteiro com as probabilidades de saída para
 						    *   as pistas de destino deste semáforo
 						    */

 	int	_proximaAbertura;  /*!< Inteiro com o tempo da 
 							*   proxima mudança do semaforo */

 	bool _fechado;  /*!< Inteiro que informa se o semáforo está fechado */
 
 public:
//! Contrutor com parâmetros.
/*! Sempre que usado, este construtor criará um semáforo.
 *
 *  \param fechado boolean que informa se ele está fechado.
 *  \param pistasDeSaida[] um array com as pistas de destino.
 *  \param pistaControlada um ponteiro Pista* que informa a pista controlada.
 *  \param probabilidade um ponteiro inteiro com as probabilidades de destino.
 *  \param tempoAberto um inteiro que informa o tempo de abertura do semáforo.
 */
 	Semaforo(bool fechado, Pista* pistasDeSaida[], 
 				   Pista* pistaControlada, int* probabilidade, int tempoAberto);

//!  Função trocaCarroDePista, realiza a tentativa de trocar um carro de pista.
/*!  
 *   \return ponteiro Pista* que informa a pista de destino do carro retirado.
 *   \sa Semaforo(bool fechado, Pista* pistasDeSaida[], 
 *				   Pista* pistaControlada, int* probabilidade, int tempoAberto)
 */
 	Pista* trocaCarroDePista();

//!  Função trocarEstado, realiza a troca de estado do semáforo.
/*!  
 *   \param tempoAtual utilizado para calcular a próxima troca de estado.
 *   \sa Semaforo(bool fechado, Pista* pistasDeSaida[], 
 *				   Pista* pistaControlada, int* probabilidade, int tempoAberto)
 */
 	void trocarEstado(int tempoAtual);

//!  Função setProximoEvento, retorna o tempo do proximo evento.
/*!  
 *   \param tempoAtual utilizado para calcular o próximo evento.
 *   \param fechado boolean para informar se o semáforo está fechado.
 *   \sa Semaforo(bool fechado, Pista* pistasDeSaida[], 
 *				   Pista* pistaControlada, int* probabilidade, int tempoAberto)
 */
 	int setProximoEvento(int tempoAtual, bool fechado);

//!  Função tempoAberto, retorna o tempo de abertura do semáforo.
/*!  
 *   \return um inteiro que informa o tempo de abertura do semáforo.
 *   \sa Semaforo(bool fechado, Pista* pistasDeSaida[], 
 *				   Pista* pistaControlada, int* probabilidade, int tempoAberto)
 */
 	int tempoAberto();

//!  Função pistaControlada, retorna a pista controlada pelo semáforo.
/*!  
 *   \return um ponteiro Pista* que informa a pista controlada pelo semáforo.
 *   \sa Semaforo(bool fechado, Pista* pistasDeSaida[], 
 *				   Pista* pistaControlada, int* probabilidade, int tempoAberto)
 */
 	Pista* pistaControlada();

//!  Função proximaAbertura, retorna o tempo da próxima mudança de estado.
/*!  
 *   \return um inteiro que informa o tempo da proxima mudança de estado.
 *   \sa Semaforo(bool fechado, Pista* pistasDeSaida[], 
 *				   Pista* pistaControlada, int* probabilidade, int tempoAberto)
 */
 	int proximaAbertura();

};

Semaforo::Semaforo(bool fechado, Pista* pistasDeSaida[],
				 Pista* pistaControlada, int* probabilidades, int tempoAberto) {

	_fechado = fechado;

	_pistasDeSaida = new Lista<Pista*>(3);

	for (int i = 0; i < 3; i++)
		_pistasDeSaida->adiciona(pistasDeSaida[i]);

	_pistaControlada = pistaControlada;

	_probabilidades = probabilidades;

	_tempoAberto = tempoAberto;

	_proximaAbertura = 0;
}

Pista* Semaforo::trocaCarroDePista() {

	if (_fechado) {
		throw std::runtime_error("Semaforo Fechado");
	}

	Carro* carro = _pistaControlada->primeiro();

	int pistaDestino = carro->pistaDestino();
	Pista* destino;

	if (pistaDestino <= _probabilidades[0]) {

		destino = _pistasDeSaida->mostra(0);

		if (destino->pistaCheia(carro) == false){
			return destino;
		} else {
			destino = _pistaControlada;
			return destino;
		}
	} else {
		int random = (rand() % 2) + 1 ;
		destino = _pistasDeSaida->mostra(random);
		if(destino->pistaCheia(carro) == false) {
			return destino;
		} else {
			destino = _pistaControlada;
			return destino;
		}
	}
}

void Semaforo::trocarEstado(int tempoAtual) {
	if (!_fechado) {
		_proximaAbertura = tempoAtual + _tempoAberto * 3;
	} 
	if (_fechado) {
		_proximaAbertura = tempoAtual;
	}
	_fechado = !_fechado;
}

int Semaforo::setProximoEvento(int tempoAtual, bool fechado) {
	if (fechado == false) {
		return tempoAtual + _tempoAberto * 3;
	}
	return tempoAtual + _tempoAberto;
}

int Semaforo::tempoAberto() {
	return _tempoAberto;
}

Pista* Semaforo::pistaControlada() {
	return _pistaControlada;
}

int Semaforo::proximaAbertura() {
	return _proximaAbertura;
}

#endif /* SEMAFORO_HPP */
