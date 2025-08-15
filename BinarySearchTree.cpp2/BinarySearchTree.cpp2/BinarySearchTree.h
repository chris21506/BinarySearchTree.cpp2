#pragma once

// PASO 0: Cabeceras necesarias para impresión, pilas y logaritmos
#include <iostream>
#include <stack>
#include <cmath>

// PASO 1: Funciones auxiliares pedidas (altura mínima teórica de un árbol m-ario)
double log_base_n(double x, double base);
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo);

// PASO 2: Plantilla del BST
// NOTA DE CORRECCIÓN IMPORTANTE:
//   En el código original, 'TreeNode' estaba templado de nuevo dentro del template,
//   sombreando 'T' y complicando su uso. Aquí lo CORREGIMOS haciendo que TreeNode
//   use el 'T' del árbol (NO vuelve a templarse).
template <typename T>
class BinarySearchTree {
private:
    // PASO 3: Nodo interno: guarda dato y enlaces a padre/izq/der
    struct TreeNode {
        T data;
        TreeNode* parent;
        TreeNode* leftChild;
        TreeNode* rightChild;
        // Constructores simples
        TreeNode() : data{}, parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
        TreeNode(const T& value) : data(value), parent(nullptr), leftChild(nullptr), rightChild(nullptr) {}
    };

    // PASO 4: Estado del árbol
    TreeNode* root;   // raíz del árbol
    int count;        // número de nodos

    // PASO 5: Helpers de inserción y búsqueda
    void InsertarNode(TreeNode* currentNode, bool isLeftChild, const T& value);
    void AddRecursive(const T& value, TreeNode* currentNode);
    TreeNode* SearchRecursive(TreeNode* currentNode, const T& value) const;

    // PASO 6: Mínimo/Máximo, sucesor
    TreeNode* Minimum(TreeNode* node) const;
    TreeNode* Maximum(TreeNode* node) const;
    TreeNode* Successor(TreeNode* node) const;

    // PASO 7: Recorridos recursivos de apoyo
    void InOrderRecursive(TreeNode* node) const;
    void PreOrderRecursive(TreeNode* node) const;
    void PostOrderRecursive(TreeNode* node) const;

    // PASO 8: Borrado por postorden (lo que pide el punto 3)
    void DeleteSubtreeRecursive(TreeNode* node);

public:
    // PASO 9: Ciclo de vida
    BinarySearchTree();
    ~BinarySearchTree();

    // PASO 10: Altas (iterativa y usando recursión interna)
    void Add(const T& value);              // iterativa
    void AddWithAddRecursive(const T& value);

    // PASO 11: Búsquedas
    bool Search(const T& value) const;     // iterativa (punto 2)
    bool SearchWithRecursive(const T& value) const;

    // PASO 12: Borrado de una clave (con correcciones de seguridad)
    void Delete(const T& value);

    // PASO 13: Borrado total por postorden (recursivo)
    void Clear();

    // PASO 14: API de recorridos solicitados
    void InOrderWithRecursive() const;
    void PostOrderIterative() const;       // iterativa (punto 4)

    // PASO 15: Altura mínima teórica según cantidad de nodos y nodos
    int MinimaAltura() const;
};
