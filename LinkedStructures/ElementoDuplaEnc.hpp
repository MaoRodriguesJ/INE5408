// Copyright [2016] <Salomão Rodrigues Jacinto>
#ifndef ELEMENTODUPLAENC_HPP
#define ELEMENTODUPLAENC_HPP

/**
 * @brief      Elemento básico para Estruturas Encadeadas
 *
 * @param      info       Ponteiro para o dado do elemento
 * @param      _next      Ponteiro para o próximo elemento
 * @param      _previous  Ponteiro para o elemento anterior
 */
template<typename T>
class ElementoDuplaEnc {
 private:
	T *info;
	Elemento<T> *_next;
	Elemento<T> *_previous;

 public:
	/**
	 * @brief      Construtor da classe Elemento
	 *
	 * @param      info      Dado do elemento
	 * @param      next      Ponteiro para o próximo elemento
	 * @param      previous  Ponteiro para o elemento anterior
	 */
	Elemento(const T& info, Elemento<T> *next, Elemento<T> *previous)
	: info(new T(info)), _next(next), _previous(previous) {}
	/**
	 * @brief      Destrutor da classe Elemento
	 */
	~Elemento() {
		delete info;
	}
	/**
	 * @brief      Retorna o um ponteiro para o próximo elemento
	 */
	Elemento<T> *getProximo() const {
		return _next;
	}
	/**
	 * @brief      Retorna o um ponteiro para o elemento anterior
	 */
	Elemento<T> *getAnterior() const {
		return _previous;
	}
	/**
	 * @brief      Retorna o dado do elemento
	 */
	T getInfo() const {
		return *info;
	}
	/**
	 * @brief      Altera qual é o próximo elemento
	 *
	 * @param      next  Valor o qual será atríbuida a variável de próximo
	 *                   elemento
	 */
	void setProximo(Elemento<T> *next) {
		_next = next;
	}
	/**
	 * @brief      Altera qual é o elemento anterior
	 *
	 * @param      previous  Valor o qual será atríbuida a variável de elemento
	 *                       anterior
	 */
	void setAnterior(Elemento<T> *previous) {
		_previous = previous;
	}
};

#endif  // ELEMENTODUPLAENC_HPP
