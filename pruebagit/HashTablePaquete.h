#pragma once
#pragma once
#include "Librerias.h"
#include "Paquete.h"

// Nodo para manejar colisiones mediante encadenamiento
template<typename T>
class NodoHash {
public:
    int clave;
    Paquete<T> paquete;
    NodoHash<T>* siguiente;

    NodoHash(int k, const Paquete<T>& p)
        : clave(k), paquete(p), siguiente(nullptr) {}
};

template<typename T>
class HashTablePaquete {
private:
    static const int TAMANO_TABLA = 100; // Tamaño de la tabla hash
    NodoHash<T>* tabla[TAMANO_TABLA];
    int numElementos;

    // Función hash: usa módulo para calcular el índice
    int funcionHash(int clave) const {
        return clave % TAMANO_TABLA;
    }

public:
    HashTablePaquete() : numElementos(0) {
        
        for (int i = 0; i < TAMANO_TABLA; i++) {
            tabla[i] = nullptr;
        }
    }

    ~HashTablePaquete() {
        limpiar();
    }

  
    bool insertar(const Paquete<T>& paquete) {
        int clave = paquete.id;
        int indice = funcionHash(clave);

   
        NodoHash<T>* actual = tabla[indice];
        while (actual) {
            if (actual->clave == clave) {
                cout << "Error: El paquete con ID " << clave << " ya existe.\n";
                return false;
            }
            actual = actual->siguiente;
        }

        // Insertar al inicio de la lista enlazada (manejo de colisiones)
        NodoHash<T>* nuevoNodo = new NodoHash<T>(clave, paquete);
        nuevoNodo->siguiente = tabla[indice];
        tabla[indice] = nuevoNodo;
        numElementos++;

        return true;
    }

    // Buscar un paquete por su ID
    Paquete<T>* buscar(int idPaquete) {
        int indice = funcionHash(idPaquete);
        NodoHash<T>* actual = tabla[indice];

        while (actual) {
            if (actual->clave == idPaquete) {
                return &(actual->paquete);
            }
            actual = actual->siguiente;
        }

        return nullptr; // No encontrado
    }

    bool eliminar(int idPaquete) {
        int indice = funcionHash(idPaquete);
        NodoHash<T>* actual = tabla[indice];
        NodoHash<T>* anterior = nullptr;

        while (actual) {
            if (actual->clave == idPaquete) {
                if (anterior) {
                    anterior->siguiente = actual->siguiente;
                }
                else {
                    tabla[indice] = actual->siguiente;
                }
                delete actual;
                numElementos--;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }

        return false; 
    }

    void mostrarTodos() const {
        if (numElementos == 0) {
            cout << "\nNo hay paquetes en la tabla hash.\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "   PAQUETES EN HASH TABLE              \n";
        cout << "========================================\n\n";

        int contador = 0;
        for (int i = 0; i < TAMANO_TABLA; i++) {
            NodoHash<T>* actual = tabla[i];
            while (actual) {
                cout << "--- Paquete #" << (++contador) << " ---\n";
                actual->paquete.mostrarInfoPaquete();
                cout << "  [Hash Index: " << i << "]\n";
                cout << "----------------------------------------\n";
                actual = actual->siguiente;
            }
        }

        cout << "\nTotal de paquetes: " << numElementos << "\n";
        cout << "========================================\n";
    }


    void mostrarPorCliente(int clienteID) const {
        if (numElementos == 0) {
            cout << "\nNo hay paquetes registrados.\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "     PAQUETES DEL CLIENTE #" << clienteID << "        \n";
        cout << "========================================\n\n";

        bool encontrado = false;
        int contador = 0;

        for (int i = 0; i < TAMANO_TABLA; i++) {
            NodoHash<T>* actual = tabla[i];
            while (actual) {
                if (actual->paquete.clienteID == clienteID) {
                    cout << "--- Paquete #" << (++contador) << " ---\n";
                    actual->paquete.mostrarInfoPaquete();
                    cout << "----------------------------------------\n";
                    encontrado = true;
                }
                actual = actual->siguiente;
            }
        }

        if (!encontrado) {
            cout << "No se encontraron paquetes para este cliente.\n";
        }

        cout << "========================================\n";
    }

    void cargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
            return;
        }

        int cargados = 0;
        string linea;

        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            stringstream ss(linea);
            string campo;
            Paquete<T> paquete;

            try {
                getline(ss, campo, '|');
                if (!campo.empty()) paquete.id = stoi(campo);

                getline(ss, campo, '|');
                if (!campo.empty()) paquete.clienteID = stoi(campo);

                getline(ss, paquete.descripcion, '|');

                getline(ss, campo, '|');
                if (!campo.empty()) paquete.peso = stod(campo);

                getline(ss, paquete.sedeOrigen, '|');
                getline(ss, paquete.destino, '|');

                if (insertar(paquete)) {
                    cargados++;
                }
            }
            catch (...) {
                continue;
            }
        }

        archivo.close();
        cout << "Se cargaron " << cargados << " paquetes en la Hash Table.\n";
    }

  
    void guardarEnArchivo(const string& nombreArchivo) const {
        ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "Error al abrir archivo para guardar.\n";
            return;
        }

        int guardados = 0;
        for (int i = 0; i < TAMANO_TABLA; i++) {
            NodoHash<T>* actual = tabla[i];
            while (actual) {
                archivo << actual->paquete.toStringArchivo() << "\n";
                guardados++;
                actual = actual->siguiente;
            }
        }

        archivo.close();
        cout << "Se guardaron " << guardados << " paquetes en " << nombreArchivo << "\n";
    }

    void mostrarEstadisticas() const {
        cout << "\n========================================\n";
        cout << "   ESTADISTICAS DE HASH TABLE          \n";
        cout << "========================================\n";
        cout << "  Tamaño de tabla:    " << TAMANO_TABLA << "\n";
        cout << "  Elementos totales:  " << numElementos << "\n";
        cout << "  Factor de carga:    " << fixed << setprecision(2)
            << (float)numElementos / TAMANO_TABLA << "\n";

       
        int bucketsUsados = 0;
        int maxColisiones = 0;
        int bucketConMasColisiones = -1;

        for (int i = 0; i < TAMANO_TABLA; i++) {
            if (tabla[i] != nullptr) {
                bucketsUsados++;
                int colisiones = 0;
                NodoHash<T>* actual = tabla[i];
                while (actual) {
                    colisiones++;
                    actual = actual->siguiente;
                }
                if (colisiones > maxColisiones) {
                    maxColisiones = colisiones;
                    bucketConMasColisiones = i;
                }
            }
        }

        cout << "  Espacios usados:     " << bucketsUsados << "\n";
        cout << "  Espacios vacíos:     " << (TAMANO_TABLA - bucketsUsados) << "\n";
        cout << "  Máx. colisiones:    " << maxColisiones
            << " (Espacio #" << bucketConMasColisiones << ")\n";
        cout << "========================================\n";
    }

   
    void buscarPorRangoPeso(double pesoMin, double pesoMax) const {
        cout << "\n========================================\n";
        cout << "  BUSQUEDA POR RANGO DE PESO           \n";
        cout << "  Rango: " << pesoMin << " - " << pesoMax << " kg\n";
        cout << "========================================\n\n";

        bool encontrado = false;
        int contador = 0;

        for (int i = 0; i < TAMANO_TABLA; i++) {
            NodoHash<T>* actual = tabla[i];
            while (actual) {
                if (actual->paquete.peso >= pesoMin &&
                    actual->paquete.peso <= pesoMax) {
                    cout << "--- Paquete #" << (++contador) << " ---\n";
                    actual->paquete.mostrarInfoPaquete();
                    cout << "----------------------------------------\n";
                    encontrado = true;
                }
                actual = actual->siguiente;
            }
        }

        if (!encontrado) {
            cout << "No se encontraron paquetes en ese rango de peso.\n";
        }

        cout << "========================================\n";
    }

    
    void limpiar() {
        for (int i = 0; i < TAMANO_TABLA; i++) {
            NodoHash<T>* actual = tabla[i];
            while (actual) {
                NodoHash<T>* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
            tabla[i] = nullptr;
        }
        numElementos = 0;
    }

  
    int size() const {
        return numElementos;
    }

 
    bool estaVacia() const {
        return numElementos == 0;
    }
};