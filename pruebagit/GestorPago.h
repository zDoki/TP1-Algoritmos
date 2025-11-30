#pragma once
#include "NodoPago.h"
#include "Pago.h"

template <class T>
class GestorPago {
private:
    NodoPago<T>* cabeza;

public:
    GestorPago() : cabeza(nullptr) {}

    void registrarPago(T pago) {
        NodoPago<T>* nuevo = new NodoPago<T>(pago);
        if (!cabeza) {
            cabeza = nuevo;
        }
        else {
            NodoPago<T>* temp = cabeza;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = nuevo;
        }
    }

    void mostrarPagos() const {
        if (!cabeza) {
            cout << "No hay pagos registrados.\n";
            return;
        }
        NodoPago<T>* temp = cabeza;
        int contador = 1;
        cout << "\n===== LISTA DE PAGOS =====\n";
        while (temp) {
            cout << "\n--- Pago #" << contador++ << " ---\n";
            temp->dato.mostrarPagos();
            temp = temp->next;
        }
    }

    ~GestorPago() {
        NodoPago<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->next;
            delete temp;
        }
        cabeza = nullptr;
    }
};