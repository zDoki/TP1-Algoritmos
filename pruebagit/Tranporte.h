#pragma once
#include "Librerias.h"
#include "Dijkstra.h"

class Transporte {
private:
    Grafo<double>* grafoRutas;

    // Calcula precio base según distancia
    double calcularPrecioPorDistancia(double distancia) const {
        if (distancia <= 50) return 25.0;
        else if (distancia <= 150) return 45.0;
        else if (distancia <= 300) return 75.0;
        else if (distancia <= 500) return 120.0;
        else return 180.0;
    }

    // Calcula recargo según peso del paquete
    double calcularRecargoPorPeso(int peso) const {
        if (peso <= 5) return 0.0;
        else if (peso <= 10) return 10.0;
        else if (peso <= 20) return 25.0;
        else if (peso <= 30) return 45.0;
        else return 70.0;
    }

public:
    Transporte() {
        grafoRutas = new Grafo<double>();
        inicializarRutas();
    }

    ~Transporte() {
        delete grafoRutas;
    }

  


    // Inicializa la red de rutas del Perú
    void inicializarRutas() {
        grafoRutas->agregarNodo(0, "Lima");
        grafoRutas->agregarNodo(1, "Arequipa");
        grafoRutas->agregarNodo(2, "Cusco");
        grafoRutas->agregarNodo(3, "Trujillo");
        grafoRutas->agregarNodo(4, "Chiclayo");
        grafoRutas->agregarNodo(5, "Piura");
        grafoRutas->agregarNodo(6, "Iquitos");
        grafoRutas->agregarNodo(7, "Pucallpa");
        grafoRutas->agregarNodo(8, "Ayacucho");
        grafoRutas->agregarNodo(9, "Huancayo");
        grafoRutas->agregarNodo(10, "Puno");
        grafoRutas->agregarNodo(11, "Ica");
        grafoRutas->agregarNodo(12, "Cajamarca");
        grafoRutas->agregarNodo(13, "Tacna");
        grafoRutas->agregarNodo(14, "Puerto Maldonado");
        grafoRutas->agregarNodo(15, "Huaraz");
        

        // Conexiones bidireccionales con distancias en km
        grafoRutas->agregarAristaBidireccional(0, 1, 1010.0);  // Lima - Arequipa
        grafoRutas->agregarAristaBidireccional(0, 2, 1100.0);  // Lima - Cusco
        grafoRutas->agregarAristaBidireccional(0, 3, 560.0);   // Lima - Trujillo
        grafoRutas->agregarAristaBidireccional(0, 9, 305.0);   // Lima - Huancayo
        grafoRutas->agregarAristaBidireccional(0, 7, 810.0);   // Lima - Pucallpa

        grafoRutas->agregarAristaBidireccional(3, 4, 210.0);   // Trujillo - Chiclayo
        grafoRutas->agregarAristaBidireccional(3, 12, 294.00); // Trujillo - Cajamarca

        grafoRutas->agregarAristaBidireccional(1, 2, 620.0);   // Arequipa - Cusco
        grafoRutas->agregarAristaBidireccional(4, 5, 210.0);   // Chiclayo - Piura
        grafoRutas->agregarAristaBidireccional(7, 6, 535.0);   // Pucallpa - Iquitos

        grafoRutas->agregarAristaBidireccional(8, 9, 255.0);   // Ayacucho - Huancayo
        grafoRutas->agregarAristaBidireccional(8, 2, 580.0);   // Ayacucho - Cusco

        grafoRutas->agregarAristaBidireccional(1, 13, 370.0);   // Arequipa - Tacna
        grafoRutas->agregarAristaBidireccional(1, 10, 340.0);   // Arequipa - Puno

        grafoRutas->agregarAristaBidireccional(2, 10, 389.0);   // Cusco - Puno
        grafoRutas->agregarAristaBidireccional(2, 14, 465.0);   // Cusco - Puerto Maldonado
        grafoRutas->agregarAristaBidireccional(10, 13, 440.0);  // Puno - Tacna

        grafoRutas->agregarAristaBidireccional(0, 11, 303.0);   // Lima - Ica
        grafoRutas->agregarAristaBidireccional(11, 1, 710.0);   // Ica - Arequipa
        grafoRutas->agregarAristaBidireccional(11, 8, 480.0);   // Ica - Ayacucho

        grafoRutas->agregarAristaBidireccional(0, 15, 420.0);   // Lima - Huaraz
        grafoRutas->agregarAristaBidireccional(15, 9, 390.0);   // Huaraz - Huancayo

        grafoRutas->agregarAristaBidireccional(5, 12, 395.0);   // Piura - Cajamarca

        grafoRutas->agregarAristaBidireccional(9, 7, 450.0);   // Huancayo - Pucallpa
        grafoRutas->agregarAristaBidireccional(12, 6, 950.0);  // Cajamarca - Iquitos 
    }

    // Calcula el precio total del envío
    double calcularPrecio(const string& origen, const string& destino, int peso) const {
        AlgoritmoDijkstra<double> dijkstra(*grafoRutas);
        ResultadoDijkstra<double> resultado = dijkstra.ejecutarPorNombre(origen, destino);

        if (!resultado.exito) {
            cout << "No existe ruta entre " << origen << " y " << destino << "\n";
            return 0.0;
        }

        double precioBase = calcularPrecioPorDistancia(resultado.distanciaTotal);
        double recargo = calcularRecargoPorPeso(peso);

        return precioBase + recargo;
    }

    // Muestra información detallada de la ruta
    void mostrarRutaDetallada(const string& origen, const string& destino, int peso) const {
        AlgoritmoDijkstra<double> dijkstra(*grafoRutas);

        int idOrigen = -1, idDestino = -1;
        NodoGrafo<double>* actual = grafoRutas->obtenerNodos();
        while (actual) {
            if (actual->nombre == origen) idOrigen = actual->id;
            if (actual->nombre == destino) idDestino = actual->id;
            actual = actual->siguiente;
        }

        if (idOrigen == -1 || idDestino == -1) {
            cout << "Error: Ubicacion no encontrada\n";
            return;
        }

        ResultadoDijkstra<double> resultado = dijkstra.ejecutar(idOrigen);

        if (resultado.distancias[idDestino] >= 999999) {
            cout << "No existe ruta disponible\n";
            return;
        }

        // Reconstruir ruta
        const int MAX_RUTA = 50;
        int ruta[MAX_RUTA];
        int longitudRuta = 0;
        dijkstra.reconstruirRuta(idDestino, resultado, ruta, longitudRuta);

        cout << "\n========================================\n";
        cout << "       INFORMACION DE RUTA              \n";
        cout << "========================================\n";
        cout << "Origen:          " << origen << "\n";
        cout << "Destino:         " << destino << "\n";
        cout << "Distancia total: " << fixed << setprecision(2)
            << resultado.distancias[idDestino] << " km\n";

        cout << "\nRuta optima:\n";
        for (int i = 0; i < longitudRuta; i++) {
            cout << "  " << grafoRutas->obtenerNombrePorId(ruta[i]);
            if (i < longitudRuta - 1) {
                cout << " -> ";
            }
        }
        cout << "\n";

        double precioBase = calcularPrecioPorDistancia(resultado.distancias[idDestino]);
        double recargo = calcularRecargoPorPeso(peso);
        double precioTotal = precioBase + recargo;

        cout << "\n--- CALCULO DE PRECIO ---\n";
        cout << "Precio base:     S/ " << fixed << setprecision(2) << precioBase << "\n";
        cout << "Recargo por peso: S/ " << recargo << "\n";
        cout << "TOTAL:           S/ " << precioTotal << "\n";
        cout << "========================================\n";
    }

    void mostrarRedRutas() const {
        grafoRutas->mostrarGrafo();
    }

    void agregarRuta(const string& origen, const string& destino, double distancia) {
        grafoRutas->agregarAristaBidireccionalPorNombre(origen, destino, distancia);
        cout << "Ruta agregada exitosamente\n";
    }

    void agregarUbicacion(int id, const string& nombre) {
        grafoRutas->agregarNodo(id, nombre);
        cout << "Ubicacion agregada exitosamente\n";
    }

    Grafo<double>* getGrafoRutas() const {
        return grafoRutas;
    }
};