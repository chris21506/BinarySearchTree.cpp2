#pragma once
#include <vector>
#include <list>
#include <iostream>

template <typename T>
class HashSet {
private:
    std::vector<std::list<T>> tabla;
    int capacidad;
    int cantidad;

    int Hash(const T& valor) const {
        return std::hash<T>{}(valor) % capacidad; // función hash de C++
    }

public:
    // Constructor
    HashSet(int capacidadInicial = 10) {
        capacidad = capacidadInicial;
        cantidad = 0;
        tabla.resize(capacidad);
    }

    // Insertar un elemento (sin duplicados)
    void Agregar(const T& valor) {
        int indice = Hash(valor);

        for (const auto& elem : tabla[indice]) {
            if (elem == valor) {
                return; // Ya existe, no insertamos duplicados
            }
        }

        tabla[indice].push_back(valor);
        cantidad++;
    }

    // Verificar si contiene un valor
    bool Contiene(const T& valor) const {
        int indice = Hash(valor);
        for (const auto& elem : tabla[indice]) {
            if (elem == valor) return true;
        }
        return false;
    }

    // Eliminar un valor si existe
    void Eliminar(const T& valor) {
        int indice = Hash(valor);
        auto& lista = tabla[indice];

        for (auto it = lista.begin(); it != lista.end(); ++it) {
            if (*it == valor) {
                lista.erase(it);
                cantidad--;
                return;
            }
        }
    }

    // Imprimir todo el HashSet
    void Imprimir() const {
        for (int i = 0; i < capacidad; i++) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& elem : tabla[i]) {
                std::cout << elem << " ";
            }
            std::cout << "\n";
        }
    }
};

