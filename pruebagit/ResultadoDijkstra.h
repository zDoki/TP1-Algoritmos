#pragma once
#include "Librerias.h"



template<typename T>
class ResultadoDijkstra {
public:
    bool exito;
    T distanciaTotal;
    int* predecesores;
    T* distancias;
    int totalNodos;

    ResultadoDijkstra() : exito(false), distanciaTotal(0), predecesores(nullptr),
        distancias(nullptr), totalNodos(0) {
    }

   
    ResultadoDijkstra(const ResultadoDijkstra& otro) {
        exito = otro.exito;
        distanciaTotal = otro.distanciaTotal;
        totalNodos = otro.totalNodos;

        if (otro.predecesores && totalNodos > 0) {
            predecesores = new int[totalNodos];
            for (int i = 0; i < totalNodos; i++) {
                predecesores[i] = otro.predecesores[i];
            }
        }
        else {
            predecesores = nullptr;
        }

        if (otro.distancias && totalNodos > 0) {
            distancias = new T[totalNodos];
            for (int i = 0; i < totalNodos; i++) {
                distancias[i] = otro.distancias[i];
            }
        }
        else {
            distancias = nullptr;
        }
    }

    ResultadoDijkstra& operator=(const ResultadoDijkstra& otro) {
        if (this != &otro) {
            if (predecesores) delete[] predecesores;
            if (distancias) delete[] distancias;

            exito = otro.exito;
            distanciaTotal = otro.distanciaTotal;
            totalNodos = otro.totalNodos;

            if (otro.predecesores && totalNodos > 0) {
                predecesores = new int[totalNodos];
                for (int i = 0; i < totalNodos; i++) {
                    predecesores[i] = otro.predecesores[i];
                }
            }
            else {
                predecesores = nullptr;
            }

            if (otro.distancias && totalNodos > 0) {
                distancias = new T[totalNodos];
                for (int i = 0; i < totalNodos; i++) {
                    distancias[i] = otro.distancias[i];
                }
            }
            else {
                distancias = nullptr;
            }
        }
        return *this;
    }

    ~ResultadoDijkstra() {
        if (predecesores) delete[] predecesores;
        if (distancias) delete[] distancias;
    }
};