// Copyright Bruno Marques e Salomão Rodrigues Jacinto [2016.1]

#ifndef CARRO_HPP
#define CARRO_HPP

#include <cstdlib>

//!  Classe Carro.
/*!  Classe representativa de um automóvel.
 * 	 \author Bruno Marques do Nascimento & Salomão Rodrigues Jacinto
 * 	 \since 10/05/2016
 * 	 \version 1.0
 */
class Carro {
 private:
	int _tamanho;  /*!< Inteiro que guarda o tamanho do carro */

 	int _pistaDestino;  /*!< Inteiro que guarda a pista destino
 							 em função da probabilidade calculada */
 public:
//! Contrutor padrão.
/*! Sempre que usado, este construtor criará um 
 *  carro com um tamanho aleatório, e com uma probabilidade
 *  de pista destino.
 */
 	Carro();

//!  Função geraTamanho, gera um tamanho de carro entre 2 e 6 mais afastamentos.
/*!  
 *   \sa Carro()
 */
 	void geraTamanho();

//!  Função geraPistaDestino, calcula a probabilidade do carro escolher uma rua.
/*!  
 *   \sa Carro()
 */
 	void geraPistaDestino();

//!  Função tamanho, retorna o tamanho do carro.
/*!  
 *   \return um inteiro que informa o tamanho do carro.
 *   \sa Carro()
 */
 	int tamanho();

//!  Função pistaDestino, retorna a probabilidade da pista destino do carro.
/*!  
 *   \return um inteiro que informa a probabilidade da pista destino do carro.
 *   \sa Carro()
 */
 	int pistaDestino();
};

 	Carro::Carro() {
 		geraTamanho();
 		geraPistaDestino();
 	}

 	void Carro::geraTamanho() {
 		
 		_tamanho = (int) (rand() % 5) + 2 + 3;
 	}
 	
 	void Carro::geraPistaDestino() {
 		_pistaDestino = (rand() % 100) + 1;
 	}
 	
 	int Carro::tamanho() {
 		return _tamanho;
 	}
 	
 	int Carro::pistaDestino() {
 		return _pistaDestino;
 	}

#endif /* CARRO_HPP */
