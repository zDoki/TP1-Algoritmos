#pragma once
#include "Librerias.h"

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
        cout << "ID: " << id << " "
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


