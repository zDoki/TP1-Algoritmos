#pragma once
#include "NodoCliente.h"
#include "Cliente.h"

template <typename T>
class GestoCliente {
private:
    NodoCliente<T>* cabeza;
public:
    GestoCliente() : cabeza(nullptr) {}

    void insertar(T valor) {
        NodoCliente<T>* nuevo = new NodoCliente<T>(valor);
        if (!cabeza) {
            cabeza = nuevo;
        }
        else {
            NodoCliente<T>* temp = cabeza;
            while (temp->siguiente) temp = temp->siguiente;
            temp->siguiente = nuevo;
        }
    }

    void mostrar() {
        NodoCliente<T>* temp = cabeza;
        while (temp) {
            temp->dato.mostrar();
            temp = temp->siguiente;
        }
    }

    T* buscarPorID(int id) {
        NodoCliente<T>* temp = cabeza;
        while (temp) {
            if (temp->dato.getID() == id) {
                return &(temp->dato);
            }
            temp = temp->siguiente;
        }
        return nullptr;
    }

    T* buscarPorCorreo(const string& correo) {
        NodoCliente<T>* temp = cabeza;
        while (temp) {
            if (temp->dato.getCorreo() == correo) {
                return &(temp->dato);
            }
            temp = temp->siguiente;
        }
        return nullptr;
    }

    void guardarClientes(const string& nombreArchivo) const {
        ofstream out(nombreArchivo, ios::app);
        if (!out) {
            cerr << "No se pudo abrir el archivo para guardar.\n";
            return;
        }
        NodoCliente<T>* temp = cabeza;
        while (temp) {
            temp->dato.guardarClienteTexto(out);
            temp = temp->siguiente;
        }
        out.close();
    }

    void cargarClientes(const string& nombreArchivo) {
        ifstream in(nombreArchivo);
        if (!in) {
            cout << "No hay datos previos.\n";
            return;
        }

        string linea;
        while (getline(in, linea)) {
            T cliente;
            if (cliente.leerArchivoCliente(linea)) {
                insertar(cliente);
            }
        }
        in.close();
    }

    bool ingresoCuenta(const string& correo, const string& password) const {
        NodoCliente<T>* temp = cabeza;
        while (temp) {
            if (temp->dato.getCorreo() == correo &&
                temp->dato.getPassword() == password) {
                return true;
            }
            temp = temp->siguiente;
        }
        return false;
    }


};