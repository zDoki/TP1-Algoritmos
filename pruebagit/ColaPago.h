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
        if (!frente) final = nullptr;
        delete temp;
        return true;
    }

    void mostrarCola() const {
        if (estaVacia()) {
            cout << "\nLa cola esta vacia. No hay pagos pendientes.\n";
            return;
        }
        NodoPago<T>* temp = frente;
        int contador = 1;
        cout << "\n========================================\n";
        cout << "      COLA DE PAGOS PENDIENTES         \n";
        cout << "========================================\n\n";

        while (temp) {
            cout << "--- Pago #" << contador++ << " ---\n";
            temp->dato.mostrarPagos();
            cout << "\n";
            temp = temp->next;
        }
        cout << "Total de pagos en cola: " << (contador - 1) << "\n";
        cout << "========================================\n";
    }


    void guardarColaPagos(const string& nombreArchivo) const {
        ofstream out(nombreArchivo, ios::app);
        if (!out.is_open()) {
            cout << "Error: No se pudo abrir el archivo para guardar pagos.\n";
            return;
        }

        NodoPago<T>* temp = frente;
        while (temp) {
            //  producto|cantidad|precio|metodo
            out << temp->dato.getProducto() << "|"
                << temp->dato.getCantidad() << "|"
                << fixed << setprecision(2) << temp->dato.getPrecioUnitario() << "|"
                << temp->dato.metodo.getTipoPago() << "\n";
            temp = temp->next;
        }
        out.close();
    }

    void cargarColaPagos(const string& nombreArchivo) {
        ifstream in(nombreArchivo);
        if (!in.is_open()) {
            cout << "No hay pagos previos registrados.\n";
            return;
        }

        string linea;
        int contador = 0;

        while (getline(in, linea)) {
            if (linea.empty()) continue;

            stringstream ss(linea);
            string producto, campo, metodoPago;
            int cantidad;
            double precio;

            try {
               
                getline(ss, producto, '|');

                getline(ss, campo, '|');
                cantidad = stoi(campo);

                getline(ss, campo, '|');
                precio = stod(campo);

                getline(ss, metodoPago, '|');

           
                T pago(producto, cantidad, precio);
                pago.metodo.setTipoPago(metodoPago);

                encolar(pago);
                contador++;
            }
            catch (...) {
                continue;
            }
        }
        in.close();

        if (contador > 0) {
            cout << "Se cargaron " << contador << " pagos desde " << nombreArchivo << endl;
        }
    }

  
    int contarElementos() const {
        int cuenta = 0;
        NodoPago<T>* temp = frente;
        while (temp) {
            cuenta++;
            temp = temp->next;
        }
        return cuenta;
    }

    ~ColaPago() {
        while (!estaVacia()) {
            desencolar();
        }
    }
};