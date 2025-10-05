#pragma once
#include "Pago.h"

template <class T>
class ColaPago {
private:
    NodoPago<T>* frente;
    NodoPago<T>* final;
public:

    ColaPago() : frente(nullptr), final(nullptr) {}

    bool estaVacia() const { return frente == nullptr; }

    void encolar(T valor) {
        NodoPago<T>* nuevoNodo = new NodoPago<T>(valor);
        if (estaVacia()) {
            frente = final = nuevoNodo;
        }
        else {
            final->next = nuevoNodo;
            final = nuevoNodo;
        }
    }
    bool desencolar() {
        if (estaVacia()) return false;
        NodoPago<T>* temp = frente;
        frente = frente->next;
        if (!frente) final = nullptr; // Si la cola queda vacía
        delete temp;
        return true;
    }

    void mostrarCola() const {
        if (estaVacia()) {
            cout << "La cola esta vacia.\n";
            return;
        }
        NodoPago<T>* temp = frente;
        cout << "\n------ COLA DE PAGOS ------\n";
        while (temp) {
            temp->dato.mostrarPagos();
            temp = temp->next;
        }
    }


    ~ColaPago() {
        while (!estaVacia()) {
            desencolar();
        }
    }




};
