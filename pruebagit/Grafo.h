#pragma once
#include "Librerias.h"
#include "ListaAdyacencia.h"
#include "NodoGrafo.h"
#include "Arista.h"


template<typename T>
class Grafo {
private:
    static const int MAX_NODOS = 50;
    ListaAdyacencia<T>* adyacencias[MAX_NODOS];
    NodoGrafo<T>* nodos;
    int totalNodos;

    int buscarIdPorNombre(const string& nombre) const {
        NodoGrafo<T>* actual = nodos;
        while (actual) {
            if (actual->nombre == nombre) {
                return actual->id;
            }
            actual = actual->siguiente;
        }
        return -1;
    }

public:
    Grafo() : nodos(nullptr), totalNodos(0) {
        for (int i = 0; i < MAX_NODOS; i++) {
            adyacencias[i] = nullptr;
        }
    }

    vector<string> obtenerTodosLosNombres() const {
        vector<string> nombres;
        NodoGrafo<T>* actual = nodos; // 'nodos' es la cabeza de la lista de vertices
        while (actual) {
            nombres.push_back(actual->nombre);
            actual = actual->siguiente;
        }
        return nombres;
    }

    void agregarNodo(int id, const string& nombre) {
        NodoGrafo<T>* nuevo = new NodoGrafo<T>(id, nombre);
        nuevo->siguiente = nodos;
        nodos = nuevo;

        if (adyacencias[id] == nullptr) {
            adyacencias[id] = new ListaAdyacencia<T>();
        }
        totalNodos++;
    }

    void agregarAristaBidireccional(int origen, int destino, T peso) {
        if (adyacencias[origen] == nullptr) {
            adyacencias[origen] = new ListaAdyacencia<T>();
        }
        if (adyacencias[destino] == nullptr) {
            adyacencias[destino] = new ListaAdyacencia<T>();
        }

        adyacencias[origen]->agregarArista(destino, peso);
        adyacencias[destino]->agregarArista(origen, peso);
    }

    void agregarAristaBidireccionalPorNombre(const string& origen, const string& destino, T peso) {
        int idOrigen = buscarIdPorNombre(origen);
        int idDestino = buscarIdPorNombre(destino);

        if (idOrigen != -1 && idDestino != -1) {
            agregarAristaBidireccional(idOrigen, idDestino, peso);
        }
    }

    string obtenerNombrePorId(int id) const {
        NodoGrafo<T>* actual = nodos;
        while (actual) {
            if (actual->id == id) {
                return actual->nombre;
            }
            actual = actual->siguiente;
        }
        return "";
    }

    ListaAdyacencia<T>* obtenerAdyacencias(int id) const {
        if (id >= 0 && id < MAX_NODOS) {
            return adyacencias[id];
        }
        return nullptr;
    }

    int obtenerTotalNodos() const { return totalNodos; }

    NodoGrafo<T>* obtenerNodos() const { return nodos; }

    void mostrarGrafo() const {
        cout << "\n=== GRAFO DE RUTAS ===\n";
        NodoGrafo<T>* actual = nodos;
        while (actual) {
            cout << actual->nombre << " (" << actual->id << ") -> ";

            Arista<T>* arista = adyacencias[actual->id]->cabeza;
            while (arista) {
                string nombreDestino = obtenerNombrePorId(arista->destino);
                cout << nombreDestino << "(" << arista->peso << "km) ";
                arista = arista->siguiente;
            }
            cout << "\n";
            actual = actual->siguiente;
        }
    }

    ~Grafo() {
        for (int i = 0; i < MAX_NODOS; i++) {
            if (adyacencias[i]) {
                delete adyacencias[i];
            }
        }
        while (nodos) {
            NodoGrafo<T>* temp = nodos;
            nodos = nodos->siguiente;
            delete temp;
        }
    }
};