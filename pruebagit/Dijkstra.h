#pragma once
#include "Librerias.h"
#include "Grafo.h"
#include "AnalizadorRutas.h"
#include "ResultadoDijkstra.h"

// Nodo del grafo que representa una ubicaci�n
template<typename T>
class NodoGrafo {
public:
    int id;
    string nombre;
    NodoGrafo<T>* siguiente;

    NodoGrafo(int _id, string _nombre) : id(_id), nombre(_nombre), siguiente(nullptr) {}
};

// Arista que conecta dos nodos con un peso (distancia)
template<typename T>
class Arista {
public:
    int destino;
    T peso;
    Arista<T>* siguiente;

    Arista(int _destino, T _peso) : destino(_destino), peso(_peso), siguiente(nullptr) {}
};

// Lista de adyacencia para cada nodo
template<typename T>
class ListaAdyacencia {
public:
    Arista<T>* cabeza;

    ListaAdyacencia() : cabeza(nullptr) {}

    void agregarArista(int destino, T peso) {
        Arista<T>* nueva = new Arista<T>(destino, peso);
        nueva->siguiente = cabeza;
        cabeza = nueva;
    }

    ~ListaAdyacencia() {
        while (cabeza) {
            Arista<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

// Grafo implementado con lista de adyacencia
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
        NodoGrafo<T>* actual = nodos; // 'nodos' es la cabeza de la lista de v�rtices
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

// Estructura para almacenar resultados de Dijkstra 
// Esta estructura gestiona la memoria de los arrays din�micos
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

    // Constructor de copia para evitar problemas de memoria
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

    // Operador de asignaci�n
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

// IMPLEMENTACI�N DEL ALGORITMO DE DIJKSTRA
// Encuentra el camino m�s corto entre dos nodos usando distancias m�nimas acumuladas
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

    // Ejecuta Dijkstra desde un nodo origen a todos los dem�s
    ResultadoDijkstra<T> ejecutar(int idOrigen) const {
        ResultadoDijkstra<T> resultado;
        int totalNodos = MAX_NODOS;

        resultado.totalNodos = totalNodos;
        resultado.distancias = new T[totalNodos];
        resultado.predecesores = new int[totalNodos];
        bool* visitado = new bool[totalNodos];

        // Inicializaci�n
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

            // Relajaci�n de aristas
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

// ANALIZADOR DE RUTAS - Proporciona estad�sticas sobre la red
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