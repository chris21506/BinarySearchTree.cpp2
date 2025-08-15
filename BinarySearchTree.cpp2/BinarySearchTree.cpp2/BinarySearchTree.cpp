#include "BinarySearchTree.h"

// ==============================
// PASO A: funciones auxiliares
// ==============================
double log_base_n(double x, double base) {
    // PASO A1: Cambio de base   log_base(x) = ln(x) / ln(base)
    return std::log(x) / std::log(base);
}

int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo) {
    // PASO A2: Fórmula dada: ceil( log_base ( (m-1)*N + 1 ) ) - 1
    int term = (maximoDeHijosPorNodo - 1) * numeroDeNodos + 1;
    int altura = std::ceil(log_base_n(term, maximoDeHijosPorNodo)) - 1;
    return altura;
}

// ==============================
// PASO B: ctor/dtor
// ==============================
template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr), count(0) {}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    // PASO B1: Liberar memoria de todos los nodos con Clear()
    Clear();
}

// ==============================
// PASO C: inserciones
// ==============================
template <typename T>
void BinarySearchTree<T>::InsertarNode(TreeNode* currentNode, bool isLeftChild, const T& value) {
    // PASO C1: Crear el nuevo nodo y enlazarlo al lado correcto
    TreeNode* newNode = new TreeNode(value);
    newNode->parent = currentNode;
    if (isLeftChild) currentNode->leftChild = newNode;
    else             currentNode->rightChild = newNode;
    count++;
}

template <typename T>
void BinarySearchTree<T>::AddRecursive(const T& value, TreeNode* currentNode) {
    // PASO C2: Recorrer hacia izq/der según la comparación
    if (value > currentNode->data) {
        if (!currentNode->rightChild) InsertarNode(currentNode, /*isLeft=*/false, value);
        else AddRecursive(value, currentNode->rightChild);
    }
    else if (value < currentNode->data) {
        if (!currentNode->leftChild)  InsertarNode(currentNode, /*isLeft=*/true, value);
        else AddRecursive(value, currentNode->leftChild);
    }
    else {
        // PASO C3: Valor duplicado -> no insertamos (política simple)
        return;
    }
}

template <typename T>
void BinarySearchTree<T>::Add(const T& value) {
    // PASO C4: Inserción iterativa
    if (!root) {
        root = new TreeNode(value);
        count++;
        return;
    }
    TreeNode* cur = root;
    while (cur) {
        if (value > cur->data) {
            if (!cur->rightChild) { InsertarNode(cur, false, value); return; }
            cur = cur->rightChild;
        }
        else if (value < cur->data) {
            if (!cur->leftChild) { InsertarNode(cur, true, value); return; }
            cur = cur->leftChild;
        }
        else {
            // duplicado
            return;
        }
    }
}

template <typename T>
void BinarySearchTree<T>::AddWithAddRecursive(const T& value) {
    // PASO C5: Inserción “envoltura” que delega a la versión recursiva
    if (!root) {
        root = new TreeNode(value);
        count++;
        return;
    }
    AddRecursive(value, root);
}

// ==============================
// PASO D: búsqueda
// ==============================
template <typename T>
bool BinarySearchTree<T>::Search(const T& value) const {
    // PASO D1 (punto 2): Búsqueda ITERATIVA
    TreeNode* cur = root;
    while (cur) {
        if (cur->data == value) return true;
        cur = (value < cur->data) ? cur->leftChild : cur->rightChild;
    }
    return false;
}

template <typename T>
typename BinarySearchTree<T>::TreeNode*
BinarySearchTree<T>::SearchRecursive(TreeNode* currentNode, const T& value) const {
    // PASO D2: Búsqueda recursiva de apoyo (para otras funciones)
    if (!currentNode) return nullptr;
    if (currentNode->data == value) return currentNode;
    if (value < currentNode->data) return SearchRecursive(currentNode->leftChild, value);
    return SearchRecursive(currentNode->rightChild, value);
}

template <typename T>
bool BinarySearchTree<T>::SearchWithRecursive(const T& value) const {
    // PASO D3: Envoltura de la versión recursiva
    return (SearchRecursive(root, value) != nullptr);
}

// ==============================
// PASO E: mínimo/máximo/sucesor
// ==============================
template <typename T>
typename BinarySearchTree<T>::TreeNode*
BinarySearchTree<T>::Minimum(TreeNode* node) const {
    // PASO E1: Ir todo a la izquierda
    TreeNode* m = node;
    while (m && m->leftChild) m = m->leftChild;
    return m;
}

template <typename T>
typename BinarySearchTree<T>::TreeNode*
BinarySearchTree<T>::Maximum(TreeNode* node) const {
    // PASO E2: Ir todo a la derecha
    TreeNode* m = node;
    while (m && m->rightChild) m = m->rightChild;
    return m;
}

template <typename T>
typename BinarySearchTree<T>::TreeNode*
BinarySearchTree<T>::Successor(TreeNode* node) const {
    // PASO E3: Si hay hijo derecho, el sucesor es el mínimo del subárbol derecho
    if (node->rightChild) return Minimum(node->rightChild);
    // Si no, subir por padres hasta que el nodo sea hijo izquierdo
    TreeNode* anc = node->parent;
    while (anc && node == anc->rightChild) {
        node = anc;
        anc = anc->parent;
    }
    return anc;
}

// ==============================
// PASO F: recorridos
// ==============================
template <typename T>
void BinarySearchTree<T>::InOrderRecursive(TreeNode* node) const {
    if (!node) return;
    InOrderRecursive(node->leftChild);
    std::cout << node->data << " ";
    InOrderRecursive(node->rightChild);
}

template <typename T>
void BinarySearchTree<T>::PreOrderRecursive(TreeNode* node) const {
    if (!node) return;
    std::cout << node->data << " ";
    PreOrderRecursive(node->leftChild);
    PreOrderRecursive(node->rightChild);
}

template <typename T>
void BinarySearchTree<T>::PostOrderRecursive(TreeNode* node) const {
    if (!node) return;
    PostOrderRecursive(node->leftChild);
    PostOrderRecursive(node->rightChild);
    std::cout << node->data << " ";
}

template <typename T>
void BinarySearchTree<T>::InOrderWithRecursive() const {
    // PASO F1: Envoltura para imprimir InOrder recursivo
    InOrderRecursive(root);
}

// (punto 4) — PostOrder ITERATIVO con 2 pilas: pila1 hace “preorder inverso”, pila2 invierte al final.
template <typename T>
void BinarySearchTree<T>::PostOrderIterative() const {
    if (!root) return;
    std::stack<TreeNode*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        TreeNode* n = s1.top(); s1.pop();
        s2.push(n);
        if (n->leftChild)  s1.push(n->leftChild);
        if (n->rightChild) s1.push(n->rightChild);
    }
    while (!s2.empty()) {
        std::cout << s2.top()->data << " ";
        s2.pop();
    }
}

// ==============================
// PASO G: borrado de clave
// ==============================
// NOTA DE CORRECCIÓN IMPORTANTE (punto 1):
//   - El código original en “caso 3” (dos hijos) podía desreferenciar punteros nulos
//     al hacer 'successor->rightChild->parent = ...' sin verificar nulo.
//   - Aquí adoptamos el enfoque CLÁSICO Y SEGURO:
//       1) Encontrar el sucesor (mínimo del subárbol derecho).
//       2) Copiar su 'data' al nodo a eliminar.
//       3) Eliminar el sucesor (que tendrá 0 o 1 hijo).
//     Así evitamos re-enlazar demasiados punteros y reducimos errores.
template <typename T>
void BinarySearchTree<T>::Delete(const T& value) {
    // PASO G1: Localizar el nodo objetivo
    TreeNode* node = SearchRecursive(root, value);
    if (!node) {
        std::cout << "No existe el valor en el arbol.\n";
        return;
    }

    // PASO G2: Si el nodo tiene dos hijos, reemplazar por el sucesor y
    //          continuar la eliminación sobre el sucesor (que ahora será más simple).
    if (node->leftChild && node->rightChild) {
        TreeNode* succ = Successor(node);               // existe por tener hijo derecho
        node->data = succ->data;                        // copiar dato
        node = succ;                                    // eliminar el sucesor “real”
    }

    // PASO G3: Ahora node tiene 0 o 1 hijo
    TreeNode* child = (node->leftChild) ? node->leftChild : node->rightChild;

    // PASO G4: Re-enlazar child con el padre del node
    if (child) child->parent = node->parent;

    if (!node->parent) {
        // node era la raíz
        root = child;
    }
    else if (node == node->parent->leftChild) {
        node->parent->leftChild = child;
    }
    else {
        node->parent->rightChild = child;
    }

    // PASO G5: Eliminar y actualizar contador
    delete node;
    count--;
}

// ==============================
// PASO H: borrado total (punto 3)
// ==============================
// Requisito: “viaja izq, viaja der, borra actual” -> postorden recursivo
template <typename T>
void BinarySearchTree<T>::DeleteSubtreeRecursive(TreeNode* node) {
    if (!node) return;
    DeleteSubtreeRecursive(node->leftChild);   // 1) sub-árbol izquierdo
    DeleteSubtreeRecursive(node->rightChild);  // 2) sub-árbol derecho
    delete node;                               // 3) borrar actual
    count--;
}

template <typename T>
void BinarySearchTree<T>::Clear() {
    // PASO H1: Eliminar todo el árbol en postorden
    DeleteSubtreeRecursive(root);
    root = nullptr;
}

// ==============================
// PASO I: altura mínima teórica
// ==============================
template <typename T>
int BinarySearchTree<T>::MinimaAltura() const {
    return MinimaAlturaDeArbol(count, /*m = binario*/ 2);
}

// ======================================================
// NOTA final (plantillas separadas): instanciaciones guía
// ======================================================
template class BinarySearchTree<int>;
template class BinarySearchTree<double>;
template class BinarySearchTree<std::string>;
