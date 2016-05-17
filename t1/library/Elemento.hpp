//  Copyright Bruno Marques <2016.1>

#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

//!  Classe que representa um elemento em estrutura de dado.
/*!  Implementação de um elemento em estrutura de dado encadeada,
 *   realizada na disciplina de Estrutura de Dados - INE5408
 *   como parte da implementação dos trabalhos práticos do semestre.
 *   \author Bruno Marques do Nascimento
 *   \since 13/04/2016
 *   \version 1.0
 */
template<typename T>
class Elemento {
 private:
    T *info; /*!< Ponteiro para a informação do elemento*/
    Elemento<T>* _next; /*!< Ponteiro para o proximo elemento da estrutura */

 public:
//! Contrutor
/*! Sempre que usado, este construtor criará um 
 *  novo elemento com os dados pré-definidos e 
 *  o próximo elemento da estrutura.
 *	\param info dado do elemento
 *  \param next ponteiro para o próximo elemento.
 */
    Elemento(const T& info, Elemento<T>* next);

//! Destrutor.
/*! Tem a função de destruir o
 *  elemento e seus dados
 */
	~Elemento();

//!  Função getProximo, informa a posição de memória do próximo elemento.
/*!  
 *   \return um ponteiro que iforma a posição na memória do próximo elemento.
 */
	Elemento<T>* getProximo() const;

//!  Função getInfo, informa o dado guardado pelo elemento.
/*!  
 *   \return o dado pertencente a este elemento.
 */
	T getInfo() const;

//!  Função setProximo, define quem será o próximo elemento da estrutura.
/*!  
 *   \param next o ponteiro para o próximo elemento.
 */
	void setProximo(Elemento<T>* next);
};

template<typename T>
Elemento<T>::Elemento(const T& info, Elemento<T>* next) :info(new T(info)),
                                                            _next(next) {}

template<typename T>
Elemento<T>::~Elemento() {
	delete info;
}

template<typename T>
Elemento<T>* Elemento<T>::getProximo() const {
	return _next;
}

template<typename T>
T Elemento<T>::getInfo() const {
	return *info;
}

template<typename T>
void Elemento<T>::setProximo(Elemento<T>* next) {
	_next = next;
}

#endif
