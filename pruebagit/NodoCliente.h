#pragma once

template <typename T>
class NodoCliente {
public:
    T dato;
    NodoCliente<T>* siguiente;

    NodoCliente(T d) : dato(d), siguiente(nullptr) {}
    ~NodoCliente() { siguiente = nullptr; }
};