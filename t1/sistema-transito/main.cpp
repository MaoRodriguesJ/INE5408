#include <iostream>
#include <stdlib.h>
#include "Sistema.hpp"

int main() {

	system("clear");

	int tempoSemaforoFicaraAberto, tempoDeSimulacao;

	std::cout << "Informe o tempo da simulação (s) : " << std::endl;
	std::cin >> tempoDeSimulacao;

	std::cout << "Informe o tempo que os semáforos ficam abertos (s) : " << std::endl;
	std::cin >> tempoSemaforoFicaraAberto;

	Sistema *sistema = new Sistema(tempoDeSimulacao, tempoSemaforoFicaraAberto);
	sistema->executar();

}