// Copyright Bruno Marques e Salomão Rodrigues Jacinto [2016.1]

#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "../library/ListaCirc.hpp"

//!  Classe Evento.
/*!  Classe representativa de um evento que possui
 *   tempo de ocorrencia, categoria, calsse e atributo.
 *   \author Bruno Marques do Nascimento & Salomão Rodrigues Jacinto
 *   \since 10/05/2016
 *   \version 1.0
 */
class Evento {
 private:
 	int _tempo;  /*!< Inteiro que guarda o tempo de ocorrência do evento */

 	int _categoria;  /*!< Um inteiro que guarda a categoria do evento:
                    *   0-MudarSemafaro
 					          *   1-CriarCarro
 					          *   2-DeletarCarro
 					          *   3-ChegadaNoSemafaro 
                    */
 	void* _classe; /*!< Um ponteiro void que guardará a classe do evento */

 	void* _atributo; /*!< Um ponteiro void que guardará um atributo do evento */

 public:
//! Contrutor com parâmetros.
/*! Sempre que usado, este construtor criará um 
 *  evento com um tempo definido, categoria, classe e atributo.
 *
 *  \param tempo um inteiro que informa o tempo de ocorrência do evento.
 *  \param categoria um inteiro que informa a categoria do evento.
 *  \param classe um inteiro que informa a classe do evento.
 *  \param atributo um inteiro que informa um atributo do evento.
 */
 	Evento(int tempo, int categoria, void* classe, void* atributo);

//!  Função tempo, retorna o tempo de ocorrência do evento.
/*!  
 *   \return um inteiro que informa o tempo de ocorrência do evento.
 *   \sa Evento(int tempo, int categoria, void* classe, void* atributo)
 */
	int tempo();

//!  Função categoria, retorna a categoria do evento.
/*!  
 *   \return um inteiro que informa a categoria do evento.
 *   \sa Evento(int tempo, int categoria, void* classe, void* atributo)
 */
	int categoria();

//!  Função classe, retorna a classe do evento.
/*!  
 *   \return um void* que informa a classe do evento.
 *   \sa Evento(int tempo, int categoria, void* classe, void* atributo)
 */
	void* classe();

//!  Função classe, retorna um atributo do evento.
/*!  
 *   \return um void* que informa um atributo do evento.
 *   \sa Evento(int tempo, int categoria, void* classe, void* atributo)
 */
	void* atributo();
};

Evento::Evento(int tempo, int categoria, void* classe, void* atributo) {
    _tempo = tempo;
    _categoria = categoria;
    _classe = classe;
    _atributo = atributo;
}

int Evento::tempo() {
  return _tempo;
}

int Evento::categoria() {
  return _categoria;
}

void* Evento::classe() {
  return _classe;
}

void* Evento::atributo() {
  return _atributo;
}

#endif /* EVENTO_HPP */
