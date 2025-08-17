#include <iostream>
#include "BinarySearchTree.h"

int main()
{
    // Creamos el BST pero con tipo de dato short
    BinarySearchTree<short> bst;

    // Insertamos valores pequeños (short es de 16 bits normalmente)
    bst.Add(50);
    bst.Add(30);
    bst.Add(70);
    bst.Add(20);
    bst.Add(40);
    bst.Add(60);
    bst.Add(80);

    std::cout << "InOrder Recursivo (short):" << std::endl;
    bst.InOrderWithRecursive();

    std::cout << "\nBusqueda de 40: "
        << (bst.Search(40) ? "Encontrado" : "No encontrado")
        << std::endl;

    std::cout << "\nPostOrder Iterativo (short):" << std::endl;
    bst.PostOrderIterative();

    std::cout << "\nBorrando todo el arbol (short)..." << std::endl;
    bst.Clear();

    std::cout << "\nAltura minima del arbol (ahora vacio): "
        << bst.MinimaAltura()
        << std::endl;

    return 0;
}
