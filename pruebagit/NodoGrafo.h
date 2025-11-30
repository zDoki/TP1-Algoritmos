#pragma once
#include "Librerias.h"

// Nodo del grafo que representa una ubicacion
template<typename T>
class NodoGrafo {
public:
    int id;
    string nombre;
    NodoGrafo<T>* siguiente;

    NodoGrafo(int _id, string _nombre) : id(_id), nombre(_nombre), siguiente(nullptr) {}
};
