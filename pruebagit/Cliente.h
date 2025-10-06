#pragma once
#include "Librerias.h"
#include "NodoCliente.h"

class Cliente {
private:
    int id;
    string nombres, apellidos, dni, pais, correo, contrasena;
public:
    Cliente(int _id = 0, string n = "", string a = "", string d = "",
        string p = "", string c = "", string pass = "")
        : id(_id), nombres(n), apellidos(a), dni(d),
        pais(p), correo(c), contrasena(pass) {
    }

    int getID() const { return id; }
    string getCorreo() const { return correo; }
    string getPassword() const { return contrasena; }

    static int generarIDUnico(const string& archivo) {
        int nuevoID;
        bool repetido;

        do {
            
            nuevoID = rand() % 999 + 100;//100-999
            repetido = false;

            // Verificar si el id ya existe en el archivo
            ifstream in(archivo);
            string linea;
            while (getline(in, linea)) {
                if (linea.empty()) continue;

                stringstream ss(linea);
                string campo;
                getline(ss, campo, '|'); 
                if (stoi(campo) == nuevoID) {
                    repetido = true;
                    break;
                }
            }
            in.close();

        } while (repetido); 

        return nuevoID;
    }

    void mostrar() {
        cout << "ID: " << id
            << "Cliente: " << nombres << " " << apellidos
            << " | DNI: " << dni << " | Pais: " << pais
            << " | Correo: " << correo << endl;
    }

    void guardarClienteTexto(ofstream& out) const {
        out << id << "|" << nombres << "|" << apellidos << "|" << dni << "|"
            << pais << "|" << correo << "|" << contrasena << "\n";
    }

    bool leerArchivoCliente(const string& linea) {

        stringstream ss(linea);
        string campo;

        getline(ss, campo, '|');
        id = stoi(campo);
        getline(ss, nombres, '|');
        getline(ss, apellidos, '|');
        getline(ss, dni, '|');
        getline(ss, pais, '|');
        getline(ss, correo, '|');
        getline(ss, contrasena, '|');
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