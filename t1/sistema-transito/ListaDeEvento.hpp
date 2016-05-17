// Copyright Bruno Marques e Salomão Rodrigues Jacinto [2016.1]

#ifndef LISTADEEVENTO_HPP
#define LISTADEEVENTO_HPP

#include "Evento.hpp"

//!  Classe herdada da estrutura de dado: ListaEnc<T>.
/*!  Estrutura de dado do tipo Lista Encadeade com o método de
 *	 de comparação maior(T dado1, T dado2) alterado  para comparar
 *	 dados do tipo Evento, em função do seu tempo.
 * 	 \author Bruno Marques do Nascimento & Salomão Rodrigues Jacinto
 * 	 \since 10/05/2016
 * 	 \version 1.0
 */
class ListaDeEvento : public ListaCirc<Evento*> {
 public:
//!  Função maior, retorna se o tempo de um evento é maior que outro.
/*!  
 *   \param evento1 argumento do tipo Evento*, que será comparado com evento2.
 *   \param evento2 argumento do tipo Evento*, que será comparado com evento1.
 *   \return um boolean que informa se o tempo do evento1 é maior que evento2.
 */
 	bool maior(Evento* evento1, Evento* evento2);
};

bool ListaDeEvento::maior(Evento* evento1, Evento* evento2) {
	return evento1->tempo() > evento2->tempo(); 
}

#endif /* LISTADEEVENTO_HPP */ 