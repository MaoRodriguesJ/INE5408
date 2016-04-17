// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

/**
 * @brief  		Elemento básico para Estruturas Encadeadas
 *
 * @param  		info		Ponteiro para o dado do elemento
 * @param  		_next		Ponteiro para o próximo elemento
 */
template<typename T>
class Elemento {
 private:
	T *info;
	Elemento<T> *_next;

 public:
	/**
	 * @brief  		Construtor da classe Elemento
	 *
	 * @param 		info	dado do elemento
	 * @param 		next	ponteiro para o próximo elemento
	 */
	Elemento(const T& info, Elemento<T> *next) : info(new T(info)), _next(next) {}
	/**
	 * @brief  		Destrutor da classe Elemento
	 */
	~Elemento() {
		delete info;
	}
	/**
	 * @brief  		Retorna o um ṕonteiro para o próximo elemento
	 */
	Elemento<T> *getProximo() const {
		return _next;
	}
	/**
	 * @brief  		Retorna o dado do elemento
	 */
	T getInfo() const {
		return *info;
	}
	/**
	 * @brief  		Altera qual é o próximo elemento
	 *
	 * @param 		next	Valor o qual será atríbuida a variável de próximo
	 * 						elemento
	 */
	void setProximo(Elemento<T> *next) {
		_next = next;
	}
};

#endif  // ELEMENTO_HPP
