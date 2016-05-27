#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>
#include <stdlib.h>
#include <algorithm>

#include "NoBinario.hpp"

template <typename T>
class NoAVL: private NoBinario<T> {
 private:
    int altura;  //!< Representa a altura do nó AVL
    T* dado;
    NoAVL<T>* esquerda;
    NoAVL<T>* direita;
    std::vector<NoAVL<T>* > elementos;

 public:
    explicit NoAVL(const T& dado): NoBinario<T>(dado), altura(0) {}
    virtual ~NoAVL();
    int getAltura() {return altura;}
    std::vector<NoAVL<T>* > getElementos() {return NoBinario<T>::getElementos()}
    NoAVL<T>* getEsquerda() {return NoBinario<T>::getEsquerda()}
    NoAVL<T>* getDireita() {return NoBinario<T>::getDireita()}
    NoAVL<T>* minimo(NoAVL<T>* nodo) {return NoBinario<T>::minimo(nodo)}
    T* getDado() {return NoBinario<T>::getDado()}
    T* busca(const T& dado, NoAVL<T>* arv) {return NoBinario<T>::busca(dado, arv)}
    void preOrdem(NoAVL<T>* nodo) {return NoBinario<T>::preOrdem()}
    void emOrdem(NoAVL<T>* nodo) {return NoBinario<T>::emOrdem()}
    void posOrdem(NoAVL<T>* nodo) {return NoBinario<T>::posOrdem()}

    int height(NoAVL<T> *nodo) {
      if(nodo == nullptr)
        return -1;
      else
        return nodo->getAltura();
    }
    int balanceFactor(NoAVL<T> *nodo) {
      return abs(nodo->height(nodo->getEsquerda()) -
                 nodo->height(nodo->getDireita()));
    }
    NoAVL<T>* rightRotation(NoAVL<T> *k2) {
      NoAVL<T> *k1;
      k1 = k2->getEsquerda();
      k2->esquerda = k1->getDireita();
      k1->direita = k2;

      k2->altura = max(height(k2->getEsquerda()), height(k2->getDireita()))+1;
      k1->altura = max(height(k1->getEsquerda()), height(k1->getDireita()))+1;
    }
    NoAVL<T>* leftRotation(NoAVL<T> *k2) {
      NoAVL<T> *k1;
      k1 = k2->getDireita();
      k2->direita = k1->getEsquerda();
      k1->esquerda = k2;

      k2->altura = max(height(k2->getEsquerda()), height(k2->getDireita()))+1;
      k1->altura = max(height(k1->getEsquerda()), height(k1->getDireita()))+1;
    }
    NoAVL<T>* doubleRotationAtLeft(NoAVL<T> *k3) {
      k3->esquerda = leftRotation(k3->getEsquerda());
      return rightRotation(k3->getEsquerda());
    }
    NoAVL<T>* doubleRotationAtRight(NoAVL<T> *k3) {
      k3->direita = rightRotation(k3->direita());
      return leftRotation(k3->getDireita());
    }

    NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv);
    NoAVL<T>* remover(NoAVL<T>* arv, const T& dado);
};

#endif /* NO_AVL_HPP */