#pragma once
#include "Grafo.h"

// ANALIZADOR DE RUTAS - Proporciona estadísticas sobre la red
template<typename T>
class AnalizadorRutas {
private:
    const Grafo<T>& grafo;

public:
    AnalizadorRutas(const Grafo<T>& _grafo) : grafo(_grafo) {}

    void mostrarEstadisticasRed() const {
        cout << "\n=== ESTADISTICAS DE LA RED ===\n";
        cout << "Total de ubicaciones: " << grafo.obtenerTotalNodos() << "\n";

        int totalAristas = 0;
        NodoGrafo<T>* actual = grafo.obtenerNodos();

        while (actual) {
            ListaAdyacencia<T>* lista = grafo.obtenerAdyacencias(actual->id);
            if (lista) {
                Arista<T>* arista = lista->cabeza;
                while (arista) {
                    totalAristas++;
                    arista = arista->siguiente;
                }
            }
            actual = actual->siguiente;
        }

        cout << "Total de conexiones: " << (totalAristas / 2) << "\n";
        cout << "================================\n";
    }
};