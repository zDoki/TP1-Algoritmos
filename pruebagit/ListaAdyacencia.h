#pragma once
#include "Librerias.h"
#include "Arista.h"

// Lista de adyacencia para cada nodo se usa en el grafo 
template<typename T>
class ListaAdyacencia {
public:
    Arista<T>* cabeza;

    ListaAdyacencia() : cabeza(nullptr) {}

    void agregarArista(int destino, T peso) {
        Arista<T>* nueva = new Arista<T>(destino, peso);
        nueva->siguiente = cabeza;
        cabeza = nueva;
    }

    ~ListaAdyacencia() {
        while (cabeza) {
            Arista<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};