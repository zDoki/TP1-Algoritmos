
#pragma once
#include "Librerias.h"
#include "Paquete.h" 


template<typename T>
class NodoArbol {
public:
    Paquete<T> dato;
    NodoArbol<T>* izquierda;
    NodoArbol<T>* derecha;

    NodoArbol(const Paquete<T>& p) : dato(p), izquierda(nullptr), derecha(nullptr) {}
};

//  arbol binario de busquera 
template<typename T>
class ArbolPaquete {
private:
    NodoArbol<T>* raiz;
    int numElementos;

   
    NodoArbol<T>* insertarRecursivo(NodoArbol<T>* nodo, const Paquete<T>& paquete) {
        if (nodo == nullptr) {
            numElementos++;
            return new NodoArbol<T>(paquete);
        }

      
        if (paquete.peso < nodo->dato.peso) {
            nodo->izquierda = insertarRecursivo(nodo->izquierda, paquete);
        }
        else if (paquete.peso > nodo->dato.peso) {
            nodo->derecha = insertarRecursivo(nodo->derecha, paquete);
        }
        else {
            
            if (paquete.id < nodo->dato.id) {
                nodo->izquierda = insertarRecursivo(nodo->izquierda, paquete);
            }
            else if (paquete.id > nodo->dato.id) {
                nodo->derecha = insertarRecursivo(nodo->derecha, paquete);
            }
           
        }
        return nodo;
    }

    void mostrarEnOrdenRecursivo(NodoArbol<T>* nodo, int& contador) const {
        if (nodo) {
            mostrarEnOrdenRecursivo(nodo->izquierda, contador);

            cout << "--- Paquete #" << (contador++) << " ---\n";
            cout << "  ID Paquete:  " << nodo->dato.id << "\n";
            cout << "  ID Cliente:  " << nodo->dato.clienteID << "\n";
            cout << "  Descripcion: " << nodo->dato.descripcion << "\n";
            cout << "  Peso:        " << fixed << setprecision(2) << nodo->dato.peso << " kg\n";
            cout << "  Ruta:        " << nodo->dato.sedeOrigen << " -> " << nodo->dato.destino << "\n";
            cout << "----------------------------------------\n";

            mostrarEnOrdenRecursivo(nodo->derecha, contador);
        }
    }

    void liberarNodos(NodoArbol<T>* nodo) {
        if (nodo) {
            liberarNodos(nodo->izquierda);
            liberarNodos(nodo->derecha);
            delete nodo;
        }
    }

public:
    ArbolPaquete() : raiz(nullptr), numElementos(0) {}
    ~ArbolPaquete() {
        liberarNodos(raiz);
    }

    void insertar(const Paquete<T>& paquete) {
        raiz = insertarRecursivo(raiz, paquete);
    }
    
    void mostrarEnOrdenConEstadisticas() const {
        system("cls");
        cout << "========================================\n";
        cout << "   PAQUETES ORDENADOS POR PESO (BST)   \n";
        cout << "   (Menor a Mayor)                     \n";
        cout << "========================================\n\n";

        if (raiz == nullptr) {
            cout << "No hay paquetes en el arbol.\n";
            return;
        }

        int contador = 1;
        mostrarEnOrdenRecursivo(raiz, contador);

        cout << "\n========================================\n";
        cout << "  Total de paquetes: " << numElementos << "\n";
        cout << "========================================\n";
    }


    void mostrarEnOrden() const {
        system("cls");
        cout << "========================================\n";
        cout << "   PAQUETES ORDENADOS POR PESO (BST)   \n";
        cout << "   (Menor a Mayor)                     \n";
        cout << "========================================\n\n";

        if (raiz == nullptr) {
            cout << "No hay paquetes en el arbol.\n";
            return;
        }

        int contador = 1;
        mostrarEnOrdenRecursivo(raiz, contador);

        cout << "\n========================================\n";
        cout << "  Total de paquetes: " << numElementos << "\n";
        cout << "========================================\n";
    }

    // En pruebagit/ArbolPaquete.h

    void cargarDesdeArchivo(const string& nombreArchivo) {
        // Limpiar el árbol existente antes de cargar
        liberarNodos(raiz);
        raiz = nullptr;
        numElementos = 0;

        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo: " << nombreArchivo << " para cargar el BST.\n";
            return;
        }

        int cargados = 0;
        string linea;

        // LEER UNA LÍNEA POR ITERACIÓN
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            string campo;
            Paquete<T> paquete; 
            try {
               
               
                stringstream ss_carga(linea);

     
                getline(ss_carga, campo, '|');
                if (!campo.empty()) paquete.id = stoi(campo);

    
                getline(ss_carga, campo, '|');
                if (!campo.empty()) paquete.clienteID = stoi(campo);

        
                getline(ss_carga, paquete.descripcion, '|');

            
                getline(ss_carga, campo, '|');
                if (!campo.empty()) paquete.peso = stod(campo);

           
                getline(ss_carga, paquete.sedeOrigen, '|');
                getline(ss_carga, paquete.destino, '|');

               
                insertar(paquete);
                cargados++;
            }
            catch (...) {
                continue;
            }
        }

        archivo.close();
        cout << "Se cargaron " << cargados << " paquetes en el Arbol Binario de Busqueda.\n";
    }


};
