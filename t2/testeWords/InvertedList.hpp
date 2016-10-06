#ifndef INVERTED_LIST_HPP
#define INVERTED_LIST_HPP
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdexcept>

typedef struct Word {
	char word[100];
	long int height, right, left;
	long int occurrences[5642];
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

class InvertedList {
 private:
	FILE *invertedDat;
	Word node;

 public:
	InvertedList(long int manPagePosition, const char word[100]) {
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

	~InvertedList() {
		fclose(invertedDat);
	}

	long int getHeight() {
		return node.height;
	}

	long int getLeft() {
		return node.left;
	}

	long int getRight() {
		return node.right;
	}

	Word& getWord() {
		return node;
	}

	long int heightAVL(long int node) {
		if (node == 0) {
			return 0;
		} else {
			fseek(invertedDat, node, SEEK_SET);
			Word nodeTmp;
			fread(&nodeTmp, sizeof(Word), 1, invertedDat);
			return nodeTmp.height;
		}
	}

	long int getBalance(Word &node) {
		return heightAVL(node.left) - heightAVL(node.right);
	}

	long int rightRotation(Word y, long int root) {
		Word x;

		fseek(invertedDat, y.left, SEEK_SET);
		fread(&x, sizeof(Word), 1, invertedDat);

		long int rootNew = y.left;
		long int aux = x.right;

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

	long int leftRotation(Word x, long int root) {
		Word y;

		fseek(invertedDat, x.right, SEEK_SET);
		fread(&y, sizeof(Word), 1, invertedDat);

		long int rootNew = x.right;
		long int aux = y.left;

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

	long int insert(Word &node, long int root) {
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

	Word search(Word node) {
		Word temp;
		long int root;
		fseek(invertedDat, 0, SEEK_SET);
		fread(&root, 8, 1, invertedDat);

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
