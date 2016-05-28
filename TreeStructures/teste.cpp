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
    std::cout << root->getAltura() << "\n";
    root->inserir(15, root);
    std::cout << root->getAltura() << " ";
    std::cout << root->getDireita()->getAltura() << "\n";

    root->inserir(20, root);
    std::cout << root->getAltura() << " ";
    std::cout << root->getDireita()->getAltura() << " ";
    std::cout << root->getDireita()->getDireita()->getAltura() << "\n";

    root->inserir(25, root);
    std::cout << root->getAltura() << " ";
    std::cout << root->getDireita()->getAltura() << " ";
    std::cout << root->getDireita()->getDireita()->getAltura() << "\n";

    root->inserir(30, root);
    std::cout << root->getAltura() << " ";
    std::cout << root->getDireita()->getAltura() << " ";
    std::cout << root->getDireita()->getDireita()->getAltura() << "\n";

    root->inserir(35, root);
    std::cout << root->getAltura() << " ";
    std::cout << root->getDireita()->getAltura() << " ";
    std::cout << root->getDireita()->getDireita()->getAltura() << "\n";

	postorder(root, 0);
	return 0;
}