// Copyright Bruno Marques e Salomão Rodrigues Jacinto [2016.1]

#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include "ListaDeEvento.hpp"
#include "Semaforo.hpp"
#include "../library/ListaCirc.hpp"

//!  Classe Sistema.
/*!  Classe representativa de um sistema, que possui tempo discreto,
 *   esta classe é responsável por todo o programa, ela é que controlará
 *   a crição e tratamento de eventos.
 * 	 \author Bruno Marques do Nascimento & Salomão Rodrigues Jacinto
 * 	 \since 10/05/2016
 * 	 \version 1.0
 */
class Sistema {
 private:
 	int _carrosPassantes;  /*!< Inteiro com o número de carros passantes,
 							*   nas pistas centrais 
 							*/

 	int _carrosCriados;  /*!< Inteiro com o número de carros criados,
 						  *   nas pistas fontes 
 						  */

 	int _carrosDeletados;  /*!< Inteiro com o número de carros deletados,
 							*   nas pistas sumidouro 
 							*/

 	int _tempoDeSimulacao;  /*!< Inteiro com o tempo de simulação do sistema */

 	int _tempoSemaforo;   /*!< Tempo que os semáforos ficarão abertos */

 	int _tempoAtual;   /*!< Inteiro que guarda o tempo atual do sistema */

 	ListaCirc<Pista*>* _pistas;  /*!< Uma lista que guarda todas as pistas
 							   	  *   controlada pelo sistema.
 							      */

 	ListaCirc<Semaforo*>* _semaforos;  /*!< Uma lista que guarda todos semáforos
 							   	 	    *   controlados pelo sistema.
 							     	    */
 	ListaDeEvento* _eventos;  /*!< Uma lista que guarda todos os eventos
 							   *   controlados pelo sistema.
 							   */
 public:
//! Contrutor com parâmetros.
/*! Sempre que usado, este construtor criará um sistema.
 *
 *  \param tempoDeSimulacao informa o tempo total de simulação do sistema.
 *  \param tempoSemaforo informa o tempo de abertura dos semáforos.
 */
 	Sistema(int tempoDeSimulacao, int tempoSemaforo);

//!  Função inicializarComponentes, inicializa os componentes do sistema, sendo
/*!  eles pistas e semáforos.
 *  
 *   \sa Sistema(int tempoDeSimulacao, int tempoSemaforo)()
 */
 	void inicializarComponentes();

//!  Função criaEventoCriarCarro, cria todos os eventos de criação de carro.
/*!
 *   \sa Sistema(int tempoDeSimulacao, int tempoSemaforo)()
 */
 	void criaEventoCriarCarro();

//!  Função criaEventoChegarNoSemafaro, cria todos os eventos
/*!  de chegada em semáforo.
 *
 *   \sa Sistema(int tempoDeSimulacao, int tempoSemaforo)()
 */
 	void criaEventoChegarNoSemaforo();

//!  Função criaEventoAberturaSemafaro, cria todos os eventos
/*!  de mudança de estado do semáforo.
 * 
 *   \sa Sistema(int tempoDeSimulacao, int tempoSemaforo)()
 */
 	void criaEventoAberturaSemaforo ();

//!  Função tratarEventoTrocaDePista, irá tratar dos eventos que irão trocar
/*!  carros de pistas.
 *
 *   \param eventoChegouSemafaro evento que deverá ser tratado.
 *   \sa Sistema(int tempoDeSimulacao, int tempoSemaforo)()
 */
 	void tratarEventoTrocaDePista(Evento* eventoChegouSemaforo);

//!  Função localizarSemaforo, localiza o semáforo responsável pela pista.
/*!  
 *	 \param pista pista que queremos encontrar o semáforo contolador.
 *   \return o controlador da pista em questão.
 *   \sa Pista (int velocidade, int tamanho, int frequenciaBase, 
 *											 int frequenciaVariacao)
 */
 	Semaforo* localizarSemaforo(Pista* pista);

//!  Função tratarEventos, irá tratar todos os eventos criados no sistema.
/*!  
 *   \sa Sistema(int tempoDeSimulacao, int tempoSemaforo)()
 */
 	void tratarEventos();

//!  Função executar, irá inicializar a execução do sistema.
/*!  
 *   \sa Sistema(int tempoDeSimulacao, int tempoSemaforo)()
 */
 	void executar();

//!  Função exit, informa os dados gerados pelo sistema e encerra o sistema.
/*!  
 *   \sa Sistema(int tempoDeSimulacao, int tempoSemaforo)()
 */
 	void exit();

};

Sistema::Sistema(int tempoDeSimulacao, int tempoSemaforo) {
	
	_tempoDeSimulacao = tempoDeSimulacao;
	_tempoSemaforo = tempoSemaforo;

	_pistas = new ListaCirc<Pista*>();
	_semaforos = new ListaCirc<Semaforo*>();
	_eventos = new ListaDeEvento();
	_tempoAtual = 0;
	_carrosDeletados = 0;
	_carrosCriados = 0;

	inicializarComponentes();
}

void Sistema::inicializarComponentes() {

	Pista* s1sul = new Pista(60, 500, -1, 0);
	Pista* s1norte = new Pista(60, 500, 30, 7);

	Pista* s2sul = new Pista(40, 500, -1, 0);
	Pista* s2norte = new Pista(40, 500, 60, 15);

	Pista* l1leste = new Pista(30, 400, -1, 0);
	Pista* l1oeste = new Pista(30, 400, 10, 2);

	Pista* n2sul = new Pista(40, 500, 20, 5);
	Pista* n2norte = new Pista(40, 500, -1, 0);

	Pista* n1sul = new Pista(60, 500, 20, 5);
	Pista* n1norte = new Pista(60, 500, -1, 0);

	Pista* o1leste = new Pista(80, 2000, 10, 2);
	Pista* o1oeste = new Pista(80, 2000, -1, 0);

	Pista* c1leste = new Pista(60, 300, 0, 0);
	Pista* c1oeste = new Pista(60, 300, 0, 0);


	_pistas->adiciona(l1leste);
	_pistas->adiciona(l1oeste);
	
	_pistas->adiciona(s2sul);
	_pistas->adiciona(s2norte);

	_pistas->adiciona(n2sul);
	_pistas->adiciona(n2norte);

	_pistas->adiciona(c1leste);
	_pistas->adiciona(c1oeste);

	_pistas->adiciona(n1sul);
	_pistas->adiciona(n1norte);

	_pistas->adiciona(s1sul);
	_pistas->adiciona(s1norte);

	_pistas->adiciona(o1leste);
	_pistas->adiciona(o1oeste);


	int probabilidades1[3] = {40, 30, 30};
	Pista* pistasDeSaida1[3] = {l1leste, n2norte, s2sul};
	Semaforo* semaforoC1leste = new Semaforo(true, pistasDeSaida1, c1leste, probabilidades1, _tempoSemaforo);


	int probabilidades2[3] = {80, 10, 10};
	Pista* pistasDeSaida2[3] = {c1leste, n1norte, s1sul};
	Semaforo* semaforoO1leste = new Semaforo(true, pistasDeSaida2, o1leste, probabilidades2, _tempoSemaforo);

	int probabilidades3[3] = {40, 30, 30};
	Pista* pistasDeSaida3[3] = {l1leste, c1oeste, s2sul};
	Semaforo* semaforoN2sul = new Semaforo(true, pistasDeSaida3, n2sul, probabilidades3, _tempoSemaforo);

	int probabilidades4[3] = {80, 10, 10};
	Pista* pistasDeSaida4[3] = {c1leste, o1oeste, s1sul};
	Semaforo* semaforoN1sul = new Semaforo(true, pistasDeSaida4, n1sul, probabilidades4, _tempoSemaforo);

	int probabilidades5[3] = {40, 30, 30};
	Pista* pistasDeSaida5[3] = {l1leste, s2sul, c1oeste};
	Semaforo* semaforoS2norte = new Semaforo(true, pistasDeSaida5, s2norte, probabilidades5, _tempoSemaforo);

	int probabilidades6[3] = {80, 10, 10};
	Pista* pistasDeSaida6[3] = {c1leste, n1norte, o1oeste};
	Semaforo* semaforoS1norte = new Semaforo(true, pistasDeSaida6, s1norte, probabilidades6, _tempoSemaforo);

	int probabilidades7[3] = {40, 30, 30};
	Pista* pistasDeSaida7[3] = {n2norte, c1leste, s2sul};
	Semaforo* semaforoL1oeste = new Semaforo(true, pistasDeSaida7, l1oeste, probabilidades7, _tempoSemaforo);
	
	int probabilidades8[3] = {40, 30, 30};
	Pista* pistasDeSaida8[3] = {o1oeste, n1norte, s1sul};
	Semaforo* semaforoC1oeste = new Semaforo(true, pistasDeSaida8, c1oeste, probabilidades8, _tempoSemaforo);


	_semaforos->adiciona(semaforoC1leste);
	_semaforos->adiciona(semaforoO1leste);

	_semaforos->adiciona(semaforoN2sul);
	_semaforos->adiciona(semaforoN1sul);

	_semaforos->adiciona(semaforoS2norte);
	_semaforos->adiciona(semaforoS1norte);

	_semaforos->adiciona(semaforoL1oeste);
	_semaforos->adiciona(semaforoC1oeste);

}

void Sistema::criaEventoCriarCarro() {

	Pista* pista;
	Evento* novoEvento;

	int tempoControleInterno;
	int tempoProximoEvento;
	
	for (int i = 0; i < _pistas->tamanho(); i++) {
		pista = _pistas->mostra(i);	

		if(pista->fonte()) { 

			tempoControleInterno = _tempoAtual;

			while (tempoControleInterno < _tempoDeSimulacao) {

				tempoProximoEvento = pista->calculaProximoSpawn(tempoControleInterno);
				if(tempoProximoEvento <= _tempoDeSimulacao) {

					novoEvento = new Evento(tempoProximoEvento, 1, new Carro(), pista);
					_eventos->adicionaEmOrdem(novoEvento);
					tempoControleInterno = tempoProximoEvento;

				} else {
					break;  // break do while
				}
			}
		}
	}
}

void Sistema::criaEventoChegarNoSemaforo() {
	
	Evento* novoEvento;
	Pista* pista;
	Semaforo* semaforo;

	int tempoProximoEvento;
	int tempoCriado;

	for (int i = 0; i < _eventos->tamanho(); i++) {
		
		Evento* eventoAux = _eventos->mostra(i);
		if(eventoAux->categoria() == 1) {
			tempoCriado = eventoAux->tempo();
			pista = (Pista*) eventoAux->atributo();
			semaforo = (Semaforo*) localizarSemaforo(pista);

			tempoProximoEvento = pista->tempoChegada(tempoCriado);

			if (tempoProximoEvento <= _tempoDeSimulacao) {
				novoEvento = new Evento(tempoProximoEvento, 3, semaforo, 0);
				_eventos->adicionaEmOrdem(novoEvento);
			} 
		}
	}

}

Semaforo* Sistema::localizarSemaforo(Pista* pista) {
    
    Semaforo* semaforo;
    for(int i = 0; i < _semaforos->tamanho(); i++){   

    	semaforo = _semaforos->mostra(i);

    	if (semaforo->pistaControlada() == pista) {
        	return semaforo;
    	}
	}
	return 0;
}

void Sistema::criaEventoAberturaSemaforo () {
	int tempoControleInterno, tempoProximoEvento;
	Semaforo* semaforoAbrira1; 
	Semaforo* semaforoAbrira2;

	Evento* novoEvento1;
	Evento* novoEvento2;


	for(int i = 0; i < _semaforos->tamanho(); i += 2) {

		tempoControleInterno = _tempoAtual + (i/2*_tempoSemaforo);
		bool fechado = false;

		semaforoAbrira1 = _semaforos->mostra(i);
		semaforoAbrira2 = _semaforos->mostra(i+1);

		semaforoAbrira1->trocarEstado(tempoControleInterno); // abriu
		semaforoAbrira2->trocarEstado(tempoControleInterno); // abriu

		while(tempoControleInterno < _tempoDeSimulacao) {


			tempoProximoEvento = semaforoAbrira1->setProximoEvento(tempoControleInterno, fechado);

			if (tempoProximoEvento <= _tempoDeSimulacao) {

				novoEvento1 = new Evento(tempoProximoEvento, 0, semaforoAbrira1, 0);
				novoEvento2 = new Evento(tempoProximoEvento, 0, semaforoAbrira2, 0);

				_eventos->adicionaEmOrdem(novoEvento1);
				_eventos->adicionaEmOrdem(novoEvento2);
			}

			fechado = !fechado;
			tempoControleInterno = tempoProximoEvento;
		}
	}
}

void Sistema::tratarEventoTrocaDePista(Evento* eventoGerado) {
	Evento* evento;
	Semaforo* semaforo = (Semaforo*) eventoGerado->classe();
	_tempoAtual =  eventoGerado->tempo();

	int tempoProximoEvento;
    try {
        Pista* pistaDestino = semaforo->trocaCarroDePista();

        if (pistaDestino == semaforo->pistaControlada()) {

            if (_tempoAtual + 1 < semaforo->proximaAbertura()) {
                tempoProximoEvento = _tempoAtual + 1;
                evento = new Evento(tempoProximoEvento, 3, semaforo, 0);
            } else {
                tempoProximoEvento = semaforo->proximaAbertura() + 1;
                evento = new Evento(tempoProximoEvento, 3, semaforo, 0);
            }

        } else {

            if (pistaDestino->sumidouro()) {
            	Carro* carro = ((Pista*)semaforo->pistaControlada())->removerCarro();
            	//Carro* carro = (Carro*) ((Pista*)semaforo->pistaControlada())->retira();
            	//semaforo->pistaControlada()->liberaEspaco(carro);

            	pistaDestino->adicionarCarro(carro);
            	//pistaDestino->inclui( carro );
            	//pistaDestino->encheEspaco(carro);

                tempoProximoEvento = pistaDestino->tempoChegada(_tempoAtual);
                evento = new Evento(tempoProximoEvento, 2, pistaDestino, 0);

            } else {
				Carro* carro = ((Pista*)semaforo->pistaControlada())->removerCarro();
				//Carro* carro = (Carro*) ((Pista*)semaforo->pistaControlada())->retira();
            	//semaforo->pistaControlada()->liberaEspaco(carro);

            	pistaDestino->adicionarCarro(carro);
            	//pistaDestino->inclui( carro );
            	//pistaDestino->encheEspaco(carro);
            	//pistaDestino->addCarrosPassantes();

                tempoProximoEvento = pistaDestino->tempoChegada(_tempoAtual);
                evento = new Evento(tempoProximoEvento, 3, localizarSemaforo(pistaDestino), 0);
            }
        }

    } catch (std::exception& e) {

        tempoProximoEvento = semaforo->proximaAbertura()+1;
        evento = new Evento(tempoProximoEvento, 3, semaforo, 0);
    }
    if (tempoProximoEvento < _tempoDeSimulacao && tempoProximoEvento > _tempoAtual) {
        _eventos->adicionaEmOrdem(evento);
    }
}

void Sistema::tratarEventos() {

	Evento* evento;
	for (int i = 0; i < _eventos->tamanho(); ++i) {

		evento = _eventos->mostra(i);

		if (_tempoAtual >= _tempoDeSimulacao) {
			break;
		}
		switch (evento->categoria()){

			case 0: {  //Mudar Semáforo
				//std::cout << "Semaforo Troca Cor -> Tempo [" << evento->tempo() << "]" << std::endl;
				Semaforo* semaforoDoEvento = (Semaforo*) evento->classe();
				semaforoDoEvento->trocarEstado(_tempoAtual);
				_tempoAtual = evento->tempo();
				break;

			} case 1: {  //Criar Carro
				//std::cout << "Carro Criado -> Tempo [" << evento->tempo() << "]" << std::endl;
				Pista* pistaDoEvento = (Pista*) evento->atributo();
				Carro* carroDoEvento = (Carro*) evento->classe();

				pistaDoEvento->adicionarCarro(carroDoEvento);

				_tempoAtual = evento->tempo();
				break;

			} case 2: {  //Deletar Carro
				//std::cout << "Carro Deletado -> Tempo [" << evento->tempo() << "]" << std::endl;
				Pista* pistaDoEvento = (Pista*) evento->classe();
				pistaDoEvento->removerCarro();
				_tempoAtual = evento->tempo();
				break;

			} case 3: {  //Chegada no semaforo
				//std::cout << "Chegada no Smafaro -> Tempo [" << evento->tempo() << "]" << std::endl;

				tratarEventoTrocaDePista(evento);
				break;
			} default: {}
		}
	}
}

void Sistema::exit() {
	Pista* pista;
	int espacoCarros = 0;
	for(int i = 0; i < _pistas->tamanho(); ++i) {
		pista = _pistas->mostra(i);

		std::cout << "---- Pista [" << i << "] ---- " << std::endl;
		std::cout << "Tamanho :" << pista->getTamanho() << std::endl;
		std::cout << "Carros deletados :" << pista->carrosDeletados() << std::endl;
		std::cout << "Carros criados :" << pista->carrosCriados() << std::endl;
		std::cout << "Carros passantes :" << pista->carrosPassantes() << std::endl;
		std::cout << "Espaco usado :" << pista->espacoUsado() << std::endl;
		espacoCarros = 0;

		for (int j = 0; j < pista->getTamanho(); j++) {
			if(!pista->filaVazia()) {
				Carro* carro2 = ((Carro*)pista->retira());
				std::cout << "Carro [" << j << "] tamanho = " << carro2->tamanho() << std::endl;
				espacoCarros += carro2->tamanho();
			}
		}
		_carrosDeletados += pista->carrosDeletados();
		_carrosCriados += pista->carrosCriados();
		_carrosPassantes += pista->carrosPassantes();

	}
	
	std::cout << "Carros deletados :" << _carrosDeletados << std::endl;
	std::cout << "Carros passantes :" << _carrosPassantes << std::endl;
	std::cout << "Carros criados :" << _carrosCriados << std::endl;
}

void Sistema::executar() {
	criaEventoCriarCarro();

	int x = _eventos->tamanho();
	std::cout << "Eventos criação carro: " << x << std::endl;

	criaEventoChegarNoSemaforo();

	int y = _eventos->tamanho();
	std::cout << "Eventos chegada no semáforo " << _eventos->tamanho() - x << std::endl;

	criaEventoAberturaSemaforo();

	std::cout << "Eventos abertura semáforo " << _eventos->tamanho() - y << std::endl;
	
	tratarEventos();
	
	exit();
}

#endif
