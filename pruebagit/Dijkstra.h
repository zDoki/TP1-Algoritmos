#pragma once
#include "Librerias.h"
#include "Grafo.h"
#include "AnalizadorRutas.h"
#include "ResultadoDijkstra.h"

// Encuentra el camino mas corto entre dos nodos usando distancias minimas acumuladas
template<typename T>
class Dijkstra {
private:
    const Grafo<T>& grafo;
    static const int MAX_NODOS = 50;

    // Encuentra el nodo no visitado con menor distancia
    int encontrarMinimoNoVisitado(T* distancias, bool* visitado, int totalNodos) const {
        T minimo = 999999;
        int indiceMinimo = -1;

        for (int i = 0; i < totalNodos; i++) {
            if (!visitado[i] && distancias[i] < minimo) {
                minimo = distancias[i];
                indiceMinimo = i;
            }
        }
        return indiceMinimo;
    }

    int buscarIdPorNombre(const string& nombre) const {
        NodoGrafo<T>* actual = grafo.obtenerNodos();
        while (actual) {
            if (actual->nombre == nombre) {
                return actual->id;
            }
            actual = actual->siguiente;
        }
        return -1;
    }

public:
    Dijkstra(const Grafo<T>& _grafo) : grafo(_grafo) {}

    // Ejecuta Dijkstra desde un nodo origen a todos los demas
    ResultadoDijkstra<T> ejecutar(int idOrigen) const {
        ResultadoDijkstra<T> resultado;
        int totalNodos = MAX_NODOS;

        resultado.totalNodos = totalNodos;
        resultado.distancias = new T[totalNodos];
        resultado.predecesores = new int[totalNodos];
        bool* visitado = new bool[totalNodos];

        // Inicializacion
        for (int i = 0; i < totalNodos; i++) {
            resultado.distancias[i] = 999999;
            resultado.predecesores[i] = -1;
            visitado[i] = false;
        }

        resultado.distancias[idOrigen] = 0;

        // Algoritmo principal de Dijkstra
        for (int cont = 0; cont < totalNodos; cont++) {
            int u = encontrarMinimoNoVisitado(resultado.distancias, visitado, totalNodos);

            if (u == -1) break;

            visitado[u] = true;

            // Relajacion de aristas
            ListaAdyacencia<T>* lista = grafo.obtenerAdyacencias(u);
            if (lista) {
                Arista<T>* arista = lista->cabeza;
                while (arista) {
                    int v = arista->destino;
                    T peso = arista->peso;

                    if (!visitado[v] && resultado.distancias[u] + peso < resultado.distancias[v]) {
                        resultado.distancias[v] = resultado.distancias[u] + peso;
                        resultado.predecesores[v] = u;
                    }
                    arista = arista->siguiente;
                }
            }
        }

        delete[] visitado;
        resultado.exito = true;
        return resultado;
    }

    // Ejecuta Dijkstra usando nombres de ubicaciones
    ResultadoDijkstra<T> ejecutarPorNombre(const string& origen, const string& destino) const {
        int idOrigen = buscarIdPorNombre(origen);
        int idDestino = buscarIdPorNombre(destino);

        ResultadoDijkstra<T> resultado = ejecutar(idOrigen);

        if (idDestino != -1 && resultado.distancias[idDestino] < 999999) {
            resultado.distanciaTotal = resultado.distancias[idDestino];
            resultado.exito = true;
        }
        else {
            resultado.exito = false;
        }

        return resultado;
    }

    // Reconstruye la ruta desde origen hasta destino
    void reconstruirRuta(int destino, const ResultadoDijkstra<T>& resultado, int* ruta, int& longitudRuta) const {
        longitudRuta = 0;
        int actual = destino;

        int temp[MAX_NODOS];
        int tempLongitud = 0;

        while (actual != -1) {
            temp[tempLongitud++] = actual;
            actual = resultado.predecesores[actual];
        }

        // Invertir la ruta
        for (int i = 0; i < tempLongitud; i++) {
            ruta[i] = temp[tempLongitud - 1 - i];
        }
        longitudRuta = tempLongitud;
    }
};

