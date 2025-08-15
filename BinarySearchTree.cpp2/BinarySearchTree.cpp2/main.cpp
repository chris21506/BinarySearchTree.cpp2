#include <iostream>
#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int> bst;

    // Insertar valores
    bst.Add(50);
    bst.Add(30);
    bst.Add(70);
    bst.Add(20);
    bst.Add(40);
    bst.Add(60);
    bst.Add(80);

    std::cout << "InOrder Recursivo:" << std::endl;
    bst.InOrderWithRecursive();

    std::cout << "\nBusqueda de 40: " << (bst.Search(40) ? "Encontrado" : "No encontrado") << std::endl;

    std::cout << "\nPostOrder Iterativo:" << std::endl;
    bst.PostOrderIterative();

    std::cout << "\nBorrando todo el arbol..." << std::endl;
    bst.Clear();

    std::cout << "\nAltura minima del arbol (ahora vacio): " << bst.MinimaAltura() << std::endl;

    return 0;
}
