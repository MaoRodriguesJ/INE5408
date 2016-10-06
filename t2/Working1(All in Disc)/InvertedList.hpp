#ifndef INVERTED_LIST_HPP
#define INVERTED_LIST_HPP
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdexcept>

//!  Struct do elemento nó.
/*!  Implementação do nó AVL, que será inserido
 *   na árvore de palavras em arquivo.
 */
typedef struct Word {
	char word[100];
	int height, 
			 right, 
			 left;
	int occurrences[5642];
	int occurrenceIndex;

	bool operator==(const Word& rhs) const {
		if (strcmp(word, rhs.word) == 0) {
			return true;
		}
		return false;
	}

	bool operator<(const Word& rhs) const {
		if (strcmp(word, rhs.word) < 0)  {
			return true;
		}
		return false;
	}

	bool operator>(const Word& rhs) const {
		if (strcmp(word, rhs.word) > 0)  {
			return true;
		}
		return false;
	}

} Word;

//!  Classe do elemento da estrutura de dado: Arvore AVL.
/*!  Implementação do nó AVL com especialização para
 *   operações em disco, realizada na disciplina de 
 *   Estrutura de Dados - INE5408 como trabalho de implementação II do semestre.
 *   \author Bruno Marques Do Nascimento e Salomão Rodrigues Jacinto 
 *   \since 10/07/2016
 *   \version 1.0
 */
class InvertedList {
 private:
	FILE *invertedDat;  /*!< Ponteiro para o arquivo que possui a árvore */
	Word node;  /*!< Struct Word que contém as informações do nó */

 public:
//! Contrutor com argumentos.
/*! Sempre que usado, este construtor criará um 
 *  nó AVL, que possuirá filhos nulos, e seu dado conforme
 *  valor passado por parâmetro, além de altura 1;
 *  \param manPagePosition posição da palavra no manpage.dat.
 *  \param word nome da palavra a ser inserido.
 */
	InvertedList(int manPagePosition, const char word[100]) {
		node.height = 1;
		node.right = 0;
		node.left = 0;
		node.occurrenceIndex = 0;
		node.occurrences[node.occurrenceIndex] = manPagePosition;
		for(int j = 0; j < 100; j++) {
			node.word[j] = ' ';
		}
		strcpy(node.word, word);
		invertedDat = fopen("inverted.dat", "r+");
	}

//! Destrutor.
/*! Tem a função de destruir o nó AVL e fechar o arquivo da árvore.
 */
	~InvertedList() {
		fclose(invertedDat);
	}

//!  Função getHeight, informa a altura do nó.
/*!  
 *   \return um inteiro que informa a altura do nó.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	int getHeight() {
		return node.height;
	}

//!  Função getLeft, informa o ponteiro para o filho da esquerda.
/*!  
 *   \return um ponteiro que informa a posição do filho esquerdo no arquivo.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	int getLeft() {
		return node.left;
	}

//!  Função getRight, informa o ponteiro para o filho da direita.
/*!  
 *   \return um ponteiro que informa a posição do filho direito no arquivo.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	int getRight() {
		return node.right;
	}

//!  Função getWord, informa o nodo.
/*!  
 *   \return uma struct Word que foi criada.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	Word& getWord() {
		return node;
	}

//!  Função heightAVL, informa altura de um nó.
/*!  
 *   \param node posição do nó no arquivo
 *   \return o valo da altura do nó.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	int heightAVL(int node) {
		if (node == 0) {
			return 0;
		} else {
			fseek(invertedDat, node, SEEK_SET);
			Word nodeTmp;
			fread(&nodeTmp, sizeof(Word), 1, invertedDat);
			return nodeTmp.height;
		}
	}

//!  Função getBalance, calcula a diferença das alturas dos nós filhos.
/*!  
 *   \param nodo o nó pai.
 *   \return um inteiro que informa a diferença das alturas dos nós filhos.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	int getBalance(Word &node) {
		return heightAVL(node.left) - heightAVL(node.right);
	}

//!  Função rightRotation, realiza uma rotação simples para direita.
/*!  
 *   \param y o nó raiz da rotação.
 *   \param root a posição do nó no arquivo.
 *   \return um ponteiro para o nó raiz ao final da rotação.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	int rightRotation(Word y, int root) {
		Word x;

		fseek(invertedDat, y.left, SEEK_SET);
		fread(&x, sizeof(Word), 1, invertedDat);

		int rootNew = y.left;
		int aux = x.right;

		x.right = root;
		fseek(invertedDat, y.left, SEEK_SET);
		fwrite(&x, sizeof(Word), 1, invertedDat);

		y.left = aux;
		fseek(invertedDat, root, SEEK_SET);
		fwrite(&y, sizeof(Word), 1, invertedDat);

		//  Atualiza altura
		y.height = std::max(heightAVL(y.left), heightAVL(y.right))+1;
		fseek(invertedDat, root, SEEK_SET);
		fwrite(&y, sizeof(Word), 1, invertedDat);

		x.height = std::max(heightAVL(x.left), heightAVL(x.right))+1;
		fseek(invertedDat, rootNew, SEEK_SET);
		fwrite(&x, sizeof(Word), 1, invertedDat);

		// Retorna nova raiz
		return rootNew;
	}

//!  Função leftRotation, realiza uma rotação simples para esquerda.
/*!  
 *   \param x o nó raiz da rotação.
 *   \param root a posição do nó no arquivo.
 *   \return um ponteiro para o nó raiz ao final da rotação.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	int leftRotation(Word x, int root) {
		Word y;

		fseek(invertedDat, x.right, SEEK_SET);
		fread(&y, sizeof(Word), 1, invertedDat);

		int rootNew = x.right;
		int aux = y.left;

		y.left = root;
		fseek(invertedDat, x.right, SEEK_SET);
		fwrite(&y, sizeof(Word), 1, invertedDat);

		x.right = aux;
		fseek(invertedDat, root, SEEK_SET);
		fwrite(&x, sizeof(Word), 1, invertedDat);

		//  Atualiza altura
		x.height = std::max(heightAVL(x.left), heightAVL(x.right))+1;
		fseek(invertedDat, root, SEEK_SET);
		fwrite(&x, sizeof(Word), 1, invertedDat);

		y.height = std::max(heightAVL(y.left), heightAVL(y.right))+1;
		fseek(invertedDat, rootNew, SEEK_SET);
		fwrite(&y, sizeof(Word), 1, invertedDat);

		// Retorna nova raíz
		return rootNew;
	}

//!  Função insert, insere um dado em uma árvore AVL.
/*!  
 *   \param node o nó a ser inserido na árvore.
 *   \param root ponteiro para raiz da árvore.
 *   \return um ponteiro para o nó inserido.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	int insert(Word &node, int root) {
		if (root == 0) {
			fseek(invertedDat, 0, SEEK_END);
			root = ftell(invertedDat);
			fwrite(&node, sizeof(Word), 1, invertedDat);
			return root;
		}

		fseek(invertedDat, root, SEEK_SET);
		Word nodeTmp;
		fread(&nodeTmp, sizeof(Word), 1, invertedDat);

		if(node == nodeTmp) {
			if(node.occurrences[node.occurrenceIndex] != nodeTmp.occurrences[nodeTmp.occurrenceIndex]) {
					nodeTmp.occurrenceIndex++;
					nodeTmp.occurrences[nodeTmp.occurrenceIndex] = node.occurrences[node.occurrenceIndex];
					fseek(invertedDat, root, SEEK_SET);
					fwrite(&nodeTmp, sizeof(Word), 1, invertedDat);
					fflush(invertedDat);
			}
		} else {

			if (node < nodeTmp) {
				nodeTmp.left = insert(node, nodeTmp.left);
			} else {
				nodeTmp.right = insert(node, nodeTmp.right);
			}
			fseek(invertedDat, root, SEEK_SET);
			fwrite(&nodeTmp, sizeof(Word), 1, invertedDat);

			nodeTmp.height = std::max( heightAVL(nodeTmp.left), heightAVL(nodeTmp.right) ) +1;

			fseek(invertedDat, root, SEEK_SET);
			fwrite(&nodeTmp, sizeof(Word), 1, invertedDat);

			int balance = getBalance(nodeTmp);

			Word nodeTmpRight, nodeTmpLeft;

			if(nodeTmp.left != 0){
				fseek(invertedDat, nodeTmp.left, SEEK_SET);
				fread(&nodeTmpLeft, sizeof(Word), 1, invertedDat);
			}

			if(nodeTmp.right != 0){
				fseek(invertedDat, nodeTmp.right, SEEK_SET);
				fread(&nodeTmpRight, sizeof(Word), 1, invertedDat);
			}

			// Caso Esquerda-Esquerda
			if (balance > 1 && node < nodeTmpLeft) {
				return rightRotation(nodeTmp, root);
			}

			// Caso Esquerda-Direita
			if (balance > 1 && node > nodeTmpLeft) {
				nodeTmp.left = leftRotation(nodeTmpLeft, nodeTmp.left);
				fseek(invertedDat, root, SEEK_SET);
				fwrite(&nodeTmp, sizeof(Word), 1, invertedDat);
				return rightRotation(nodeTmp, root);
			}

			// Caso Direita-Direita
			if (balance < -1 && node > nodeTmpRight) {
				return leftRotation(nodeTmp, root);
			}

			// Caso Direita-Esquerda
			if (balance < -1 && node < nodeTmpRight) {
				nodeTmp.right = rightRotation(nodeTmpRight, nodeTmp.right);
				fseek(invertedDat, root, SEEK_SET);
				fwrite(&nodeTmp, sizeof(Word), 1, invertedDat);
				return leftRotation(nodeTmp, root);
			}
		}
		return root;
	}

//!  Função search, busca por um dado em uma árvore AVL.
/*!  
 *   \param node nó a ser buscado na árvore.
 *   \return o nó encontrado.
 *   \sa InvertedList(int manPagePosition, const char word[100])
 */
	Word search(Word node) {
		Word temp;
		int root;
		fseek(invertedDat, 0, SEEK_SET);
		fread(&root, sizeof(int), 1, invertedDat);

		fseek(invertedDat, root, SEEK_SET);
		fread(&temp, sizeof(Word), 1, invertedDat);


		while (root != 0 && !(node == temp)) {
			if (node < temp) {
				fseek(invertedDat, temp.left, SEEK_SET);
				root = temp.left;
				fread(&temp, sizeof(Word), 1, invertedDat);
			} else {
				fseek(invertedDat, temp.right, SEEK_SET);
				root = temp.right;
				fread(&temp, sizeof(Word), 1, invertedDat);
			}
		}

		if (root == 0) {
			temp.occurrenceIndex = -1;
			return temp;
		} else {
			return temp;
		}
	}

};

#endif /* INVERTED_LIST_HPP */
