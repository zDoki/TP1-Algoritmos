#pragma once
#include "Librerias.h"

// Arista que conecta dos nodos con un peso (distancia)
template<typename T>
class Arista {
public:
    int destino;
    T peso;
    Arista<T>* siguiente;

    Arista(int _destino, T _peso) : destino(_destino), peso(_peso), siguiente(nullptr) {}
};