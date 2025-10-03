#pragma once
#include "Librerias.h"
#include "NodoCliente.h"

class Cliente {
private:
    string nombres, apellidos, dni, pais, correo, contrasena;
public:
    Cliente(string n = "", string a = "", string d = "",
        string p = "", string c = "", string pass = "")
        : nombres(n), apellidos(a), dni(d), pais(p), correo(c), contrasena(pass) {
    }

    string getCorreo() const { return correo; }
    string getPassword() const { return contrasena; }

    void mostrar() {
        cout << "Cliente: " << nombres << " " << apellidos
            << " | DNI: " << dni << " | Pais: " << pais
            << " | Correo: " << correo << endl;
    }

    void guardarClienteTexto(ofstream& out) const {
        out << nombres << "|" << apellidos << "|" << dni << "|"
            << pais << "|" << correo << "|" << contrasena << "\n";
    }

    bool cargarClienteTexto(const string& linea) {
        stringstream ss(linea);
        string temp;

        if (!getline(ss, nombres, '|')) return false;
        if (!getline(ss, apellidos, '|')) return false;
        if (!getline(ss, dni, '|')) return false;
        if (!getline(ss, pais, '|')) return false;
        if (!getline(ss, correo, '|')) return false;
        if (!getline(ss, contrasena, '|')) return false;

        return true;
    }
};


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
            if (cliente.cargarClienteTexto(linea)) {
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