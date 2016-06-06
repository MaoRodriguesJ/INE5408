#include <iostream>
#include <iomanip>
#include "NoAVL.hpp"

void postorder(NoAVL<int>* p, int indent) {
	if(p != nullptr) {
		if(p->getDireita()) {
			postorder(p->getDireita(), indent+4);
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (p->getDireita()) std::cout<<" /\n" << std::setw(indent) << ' ';
		std::cout<< *(p->getDado()) << "\n ";
		if(p->getEsquerda()) {
			std::cout << std::setw(indent) << ' ' <<" \\\n";
			postorder(p->getEsquerda(), indent+4);
		}
	}
}

int main() {
	NoAVL<int>* root = new NoAVL<int>(10);
	root = root->inserir(15, root);
	root = root->inserir(20, root);
	root = root->inserir(12, root);
	root = root->inserir(21, root);
	root = root->inserir(22, root);
	root = root->inserir(9, root);

	std::cout << root->getAltura() << "\n";

	// root = root->inserir(20, root);
	// AVL<int>* root = new AVL<int>();
	// root->Insert(15);
	// root->Insert(20);
	// root->Insert(25);

	// root->PrintPreOrderTraversal(std::cout);

	postorder(root, 0);
	return 0;
}