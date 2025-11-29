#pragma once
#include "Librerias.h"

using namespace std;

template<typename T>
class Arista {
private:
    int destino;
    T peso;

public:
    Arista(int _destino = 0, T _peso = T())
        : destino(_destino), peso(_peso) {
    }

    int getDestino() const { return destino; }
    T getPeso() const { return peso; }

    void setDestino(int d) { destino = d; }
    void setPeso(T p) { peso = p; }

    void mostrar() const {
        cout << "-> Destino: " << destino
            << " | Peso: " << peso << endl;
    }
};

template<typename T>
class NodoArista {
public:
    Arista<T> arista;
    NodoArista<T>* siguiente;

    NodoArista(const Arista<T>& a)
        : arista(a), siguiente(nullptr) {
    }

    ~NodoArista() { siguiente = nullptr; }
};

template<typename T>
class Vertice {
private:
    int id;
    string nombre;
    NodoArista<T>* listaAdyacencia;

public:
    Vertice(int _id = 0, string _nombre = "")
        : id(_id), nombre(_nombre), listaAdyacencia(nullptr) {
    }

    ~Vertice() {
        while (listaAdyacencia) {
            NodoArista<T>* temp = listaAdyacencia;
            listaAdyacencia = listaAdyacencia->siguiente;
            delete temp;
        }
    }

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    NodoArista<T>* getListaAdyacencia() const { return listaAdyacencia; }

    void agregarArista(int destino, T peso) {
        Arista<T> nuevaArista(destino, peso);
        NodoArista<T>* nuevoNodo = new NodoArista<T>(nuevaArista);

        if (!listaAdyacencia) {
            listaAdyacencia = nuevoNodo;
        }
        else {
            NodoArista<T>* actual = listaAdyacencia;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
    }

    void mostrarAdyacencias() const {
        cout << "Vertice [" << id << "] " << nombre << ":\n";
        NodoArista<T>* actual = listaAdyacencia;
        if (!actual) {
            cout << "  (Sin conexiones)\n";
            return;
        }
        while (actual) {
            cout << "  ";
            actual->arista.mostrar();
            actual = actual->siguiente;
        }
    }

    // Buscar peso de arista a destino específico
    T buscarPeso(int destinoId) const {
        NodoArista<T>* actual = listaAdyacencia;
        while (actual) {
            if (actual->arista.getDestino() == destinoId) {
                return actual->arista.getPeso();
            }
            actual = actual->siguiente;
        }
        return T(); // Retorna valor por defecto si no encuentra
    }
};

template<typename T>
class NodoVertice {
public:
    Vertice<T>* vertice;
    NodoVertice<T>* siguiente;

    NodoVertice(Vertice<T>* v)
        : vertice(v), siguiente(nullptr) {
    }

    ~NodoVertice() {
        delete vertice;
        siguiente = nullptr;
    }
};

template<typename T>
class Grafo {
private:
    NodoVertice<T>* listaVertices;
    int numeroVertices;
    bool esDirigido;

    // Función auxiliar recursiva para encontrar vértice
    Vertice<T>* buscarVerticeRecursivo(NodoVertice<T>* nodo, int id) const {
        if (!nodo) return nullptr;
        if (nodo->vertice->getId() == id) return nodo->vertice;
        return buscarVerticeRecursivo(nodo->siguiente, id);
    }

    // Función auxiliar recursiva para encontrar vértice por nombre
    Vertice<T>* buscarVerticePorNombreRecursivo(NodoVertice<T>* nodo, const string& nombre) const {
        if (!nodo) return nullptr;
        if (nodo->vertice->getNombre() == nombre) return nodo->vertice;
        return buscarVerticePorNombreRecursivo(nodo->siguiente, nombre);
    }

public:
    Grafo(bool _dirigido = false)
        : listaVertices(nullptr), numeroVertices(0), esDirigido(_dirigido) {
    }

    ~Grafo() {
        while (listaVertices) {
            NodoVertice<T>* temp = listaVertices;
            listaVertices = listaVertices->siguiente;
            delete temp;
        }
    }

    int getNumeroVertices() const { return numeroVertices; }
    bool getEsDirigido() const { return esDirigido; }

    // Agregar vértice al grafo
    void agregarVertice(int id, const string& nombre) {
        // Verificar si ya existe
        if (buscarVertice(id)) {
            cout << "Error: Vertice con ID " << id << " ya existe.\n";
            return;
        }

        Vertice<T>* nuevoVertice = new Vertice<T>(id, nombre);
        NodoVertice<T>* nuevoNodo = new NodoVertice<T>(nuevoVertice);

        if (!listaVertices) {
            listaVertices = nuevoNodo;
        }
        else {
            NodoVertice<T>* actual = listaVertices;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        numeroVertices++;
    }

    // Buscar vértice por ID
    Vertice<T>* buscarVertice(int id) const {
        return buscarVerticeRecursivo(listaVertices, id);
    }

    // Buscar vértice por nombre
    Vertice<T>* buscarVerticePorNombre(const string& nombre) const {
        return buscarVerticePorNombreRecursivo(listaVertices, nombre);
    }

    // Agregar arista entre dos vértices
    void agregarArista(int origen, int destino, T peso) {
        Vertice<T>* vOrigen = buscarVertice(origen);
        Vertice<T>* vDestino = buscarVertice(destino);

        if (!vOrigen || !vDestino) {
            cout << "Error: Vertices no encontrados.\n";
            return;
        }

        vOrigen->agregarArista(destino, peso);

        // Si no es dirigido, agregar arista inversa
        if (!esDirigido) {
            vDestino->agregarArista(origen, peso);
        }
    }

    // Agregar arista por nombres
    void agregarAristaPorNombre(const string& origen, const string& destino, T peso) {
        Vertice<T>* vOrigen = buscarVerticePorNombre(origen);
        Vertice<T>* vDestino = buscarVerticePorNombre(destino);

        if (!vOrigen || !vDestino) {
            cout << "Error: Vertices '" << origen << "' o '" << destino << "' no encontrados.\n";
            return;
        }

        agregarArista(vOrigen->getId(), vDestino->getId(), peso);
    }

    // Mostrar grafo completo
    void mostrarGrafo() const {
        cout << "\n========================================\n";
        cout << "         GRAFO DE RUTAS                 \n";
        cout << "========================================\n";
        cout << "Tipo: " << (esDirigido ? "Dirigido" : "No Dirigido") << "\n";
        cout << "Vertices: " << numeroVertices << "\n";
        cout << "========================================\n\n";

        NodoVertice<T>* actual = listaVertices;
        while (actual) {
            actual->vertice->mostrarAdyacencias();
            cout << "----------------------------------------\n";
            actual = actual->siguiente;
        }
    }

    // Obtener todos los IDs de vértices (útil para Dijkstra)
    vector<int> obtenerTodosLosIds() const {
        vector<int> ids;
        NodoVertice<T>* actual = listaVertices;
        while (actual) {
            ids.push_back(actual->vertice->getId());
            actual = actual->siguiente;
        }
        return ids;
    }

    // Obtener lista de vértices (para iterar)
    NodoVertice<T>* getListaVertices() const {
        return listaVertices;
    }
};


// ============================================================
// ESTRUCTURA PARA RESULTADO DE DIJKSTRA
// ============================================================
template<typename T>
struct ResultadoDijkstra {
    vector<int> camino;
    T distanciaTotal;
    bool exito;

    ResultadoDijkstra() : distanciaTotal(T()), exito(false) {}

    void mostrarCamino(const Grafo<T>& grafo) const {
        if (!exito) {
            cout << "No existe camino disponible.\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "      RUTA OPTIMA ENCONTRADA            \n";
        cout << "========================================\n";
        cout << "Camino: ";

        for (size_t i = 0; i < camino.size(); i++) {
            Vertice<T>* v = grafo.buscarVertice(camino[i]);
            if (v) {
                cout << v->getNombre();
            }
            else {
                cout << "ID:" << camino[i];
            }

            if (i < camino.size() - 1) cout << " -> ";
        }

        cout << "\nDistancia Total: " << distanciaTotal << " km\n";
        cout << "Numero de paradas: " << (camino.size() - 1) << "\n";
        cout << "========================================\n";
    }
};

// ============================================================
// ALGORITMO DE DIJKSTRA - Implementación con recursividad y lambdas
// ============================================================
template<typename T>
class AlgoritmoDijkstra {
private:
    const Grafo<T>& grafo;

    // Lambda para encontrar el nodo no visitado con menor distancia
    function<int(const vector<T>&, const vector<bool>&)> encontrarMinimo =
        [](const vector<T>& distancias, const vector<bool>& visitados) -> int {
        T minDist = (numeric_limits<T>::max)();
        int minIndex = -1;

        for (size_t i = 0; i < distancias.size(); i++) {
            if (!visitados[i] && distancias[i] < minDist) {
                minDist = distancias[i];
                minIndex = i;
            }
        }
        return minIndex;
        };

    // Función recursiva para reconstruir el camino
    void reconstruirCaminoRecursivo(const vector<int>& previo, int actual, vector<int>& camino) const {
        if (previo[actual] != -1) {
            reconstruirCaminoRecursivo(previo, previo[actual], camino);
        }
        camino.push_back(actual);
    }

    // Mapeo de ID a índice en vectores
    map<int, int> idAIndice;
    map<int, int> indiceAId;

    void inicializarMapeos(const vector<int>& ids) {
        for (size_t i = 0; i < ids.size(); i++) {
            idAIndice[ids[i]] = i;
            indiceAId[i] = ids[i];
        }
    }

public:
    AlgoritmoDijkstra(const Grafo<T>& _grafo) : grafo(_grafo) {}

    ResultadoDijkstra<T> ejecutar(int idOrigen, int idDestino) {
        ResultadoDijkstra<T> resultado;

        // Verificar que existen los vértices
        Vertice<T>* vOrigen = grafo.buscarVertice(idOrigen);
        Vertice<T>* vDestino = grafo.buscarVertice(idDestino);

        if (!vOrigen || !vDestino) {
            cout << "Error: Vertices de origen o destino no encontrados.\n";
            return resultado;
        }

        // Obtener todos los IDs y crear mapeos
        vector<int> ids = grafo.obtenerTodosLosIds();
        size_t n = ids.size();
        inicializarMapeos(ids);

        // Verificar que origen y destino están en el grafo
        if (idAIndice.find(idOrigen) == idAIndice.end() ||
            idAIndice.find(idDestino) == idAIndice.end()) {
            return resultado;
        }

        int indiceOrigen = idAIndice[idOrigen];
        int indiceDestino = idAIndice[idDestino];

        // Inicializar estructuras
        vector<T> distancias(n, (numeric_limits<T>::max)());
        vector<bool> visitados(n, false);
        vector<int> previo(n, -1);

        distancias[indiceOrigen] = 0;

        // Algoritmo de Dijkstra
        for (size_t count = 0; count < n - 1; count++) {
            int u = encontrarMinimo(distancias, visitados);

            if (u == -1) break;

            visitados[u] = true;

            // Obtener el vértice correspondiente
            int idActual = indiceAId[u];
            Vertice<T>* vActual = grafo.buscarVertice(idActual);

            if (!vActual) continue;

            // Recorrer adyacentes de forma recursiva
            procesarAdyacentesRecursivo(vActual->getListaAdyacencia(), u, distancias, visitados, previo);
        }

        // Verificar si hay camino al destino
        if (distancias[indiceDestino] == (numeric_limits<T>::max)()) {
            cout << "No existe camino entre origen y destino.\n";
            return resultado;
        }

        // Reconstruir camino
        vector<int> caminoIndices;
        reconstruirCaminoRecursivo(previo, indiceDestino, caminoIndices);

        // Convertir índices a IDs
        for (int idx : caminoIndices) {
            resultado.camino.push_back(indiceAId[idx]);
        }

        resultado.distanciaTotal = distancias[indiceDestino];
        resultado.exito = true;

        return resultado;
    }

    // Función recursiva para procesar adyacentes
    void procesarAdyacentesRecursivo(NodoArista<T>* nodo, int u, vector<T>& distancias,
        vector<bool>& visitados, vector<int>& previo) const {
        if (!nodo) return;

        int idVecino = nodo->arista.getDestino();

        if (idAIndice.find(idVecino) != idAIndice.end()) {
            int v = idAIndice.at(idVecino);
            T peso = nodo->arista.getPeso();

            if (!visitados[v] && distancias[u] != (numeric_limits<T>::max)()) {
                T nuevaDistancia = distancias[u] + peso;
                if (nuevaDistancia < distancias[v]) {
                    distancias[v] = nuevaDistancia;
                    previo[v] = u;
                }
            }
        }

        procesarAdyacentesRecursivo(nodo->siguiente, u, distancias, visitados, previo);
    }

    // Versión con nombres de ciudades
    ResultadoDijkstra<T> ejecutarPorNombre(const string& nombreOrigen, const string& nombreDestino) {
        Vertice<T>* vOrigen = grafo.buscarVerticePorNombre(nombreOrigen);
        Vertice<T>* vDestino = grafo.buscarVerticePorNombre(nombreDestino);

        if (!vOrigen || !vDestino) {
            ResultadoDijkstra<T> resultado;
            cout << "Error: No se encontraron las ciudades especificadas.\n";
            return resultado;
        }

        return ejecutar(vOrigen->getId(), vDestino->getId());
    }
};