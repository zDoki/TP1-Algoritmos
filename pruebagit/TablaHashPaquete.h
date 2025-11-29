#pragma once
#include "Paquete.h"
#include "Librerias.h"

using namespace std;

template<typename T>
class TablaHashPaquete {
private:
    static const int TAM = 19; // buckets
    vector<vector<Paquete<T>>> tabla; // (colisiones)

    // Función hash: usa el ID del paquete
    int hashID(int id) const {
        return id % TAM;
    }

public:
    
    TablaHashPaquete() {
        tabla.resize(TAM);
    }
    ~TablaHashPaquete() {}

    // Insertar un paquete en la tabla hash
    void insertarPaquete(const Paquete<T>& p) {
        int pos = hashID(p.id);
        tabla[pos].push_back(p);
        cout << "Paquete insertado en bucket " << pos << " (ID: " << p.id << ")" << endl;
    }

    // Buscar paquete por su ID
    Paquete<T>* buscarPorID(int id) {
        int pos = hashID(id);
        for (auto& p : tabla[pos]) {
            if (p.id == id)
                return &p;
        }
        return nullptr;
    }

    // Buscar todos los paquetes de un cliente
    vector<Paquete<T>*> buscarPorClienteID(int clienteID) {
        vector<Paquete<T>*> encontrados;
        for (int i = 0; i < TAM; i++) {
            for (auto& p : tabla[i]) {
                if (p.clienteID == clienteID)
                    encontrados.push_back(&p);
            }
        }
        return encontrados;
    }

    // Eliminar paquete por ID
    bool eliminarPaquete(int id) {
        int pos = hashID(id);
        for (auto it = tabla[pos].begin(); it != tabla[pos].end(); ++it) {
            if (it->id == id) {
                tabla[pos].erase(it);
                cout << "Paquete eliminado del bucket " << pos << endl;
                return true;
            }
        }
        cout << "Paquete no encontrado.\n";
        return false;
    }

    // Mostrar todos los buckets y paquetes
    void mostrarTabla() {
        cout << "\n========== TABLA HASH DE PAQUETES ==========\n";
        for (int i = 0; i < TAM; ++i) {
            cout << "Bucket " << i << ": ";
            if (tabla[i].empty()) {
                cout << "(vacío)";
            }
            else {
                for (auto& p : tabla[i]) {
                    cout << " -> [ID " << p.id << " | Cliente " << p.clienteID << "]";
                }
            }
            cout << endl;
        }
        cout << "===========================================\n";
    }
};
