#pragma once
#include "Librerias.h"
#include "NodoPago.h"


class MetodoPago {
private:
    string tipoPago;
public:
    MetodoPago() : tipoPago("Sin definir") {}

    void PagoYape() {
        tipoPago = "Yape";
    }

    void PagoTarjeta() {
        tipoPago = "Tarjeta";
    }

    void PagoEfectivo() {
        tipoPago = "Efectivo";
    }

    string getTipoPago() const {
        return tipoPago;
    }

    void setTipoPago(const string& tipo) {
        tipoPago = tipo;
    }
};


template <class T>
class Pago {
private:
    T producto;
    int cantidad;
    double precioUnitario;

public:
    MetodoPago metodo;

    Pago(T prod = T(), int cant = 0, double precio = 0.0)
        : producto(prod), cantidad(cant), precioUnitario(precio) {}

    T getProducto() const { return producto; }
    int getCantidad() const { return cantidad; }
    double getPrecioUnitario() const { return precioUnitario; }
    double calcularTotal() const { return cantidad * precioUnitario; }

    void setProducto(T prod) { producto = prod; }
    void setCantidad(int cant) { cantidad = cant; }
    void setPrecioUnitario(double precio) { precioUnitario = precio; }


    void mostrarPagos() const {
        cout << "|-------------------------------------------|\n";
        cout << "| PRODUCTO: " << producto << "\n";
        cout << "| CANTIDAD: " << cantidad << "\n";
        cout << "| PRECIO UNIT: S/ " << precioUnitario << "\n";
        cout << "| METODO PAGO: " << metodo.getTipoPago() << "\n";
        cout << "| TOTAL: S/ " << calcularTotal() << "\n";
        cout << "|-------------------------------------------|\n";
    }



    void cargarPagoTexto(const string& pagoStr) {
        istringstream ss(pagoStr);
        string campo, metodoPagoStr;

        if (!getline(ss, campo, '|')) return;
        producto = campo;

        if (!getline(ss, campo, '|')) return;
        cantidad = stoi(campo);

        if (!getline(ss, campo, '|')) return;
        precioUnitario = stod(campo);

        if (!getline(ss, metodoPagoStr, '|')) return;
        metodo.setTipoPago(metodoPagoStr);
    }
};


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
        while (cabeza) {
            NodoPago<T>* temp = cabeza;
            cabeza = cabeza->next;
            delete temp;
        }
    }
};