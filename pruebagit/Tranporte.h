#pragma once
#include "Librerias.h"
#include "Dijkstra.h"

// ============================================================
// CLASE TRANSPORTE - Sistema de rutas con Dijkstra
// ============================================================
class Transporte {
private:
    Grafo<double>* grafoRutas;

    // Tarifas base por kilómetro
    const double TARIFA_BASE = 0.1;
    const double TARIFA_POR_KG = 0.9;

    // Lambda para calcular precio basado en distancia y peso
    function<double(double, int)> calcularPrecioLambda = [this](double distancia, int peso) -> double {
        double costoDistancia = distancia * TARIFA_BASE;
        double costoPeso = peso * TARIFA_POR_KG;
        return costoDistancia + costoPeso;
        };

    // Función recursiva para calcular descuento por volumen
    double calcularDescuentoRecursivo(int peso, double precioBase) const {
        if (peso <= 20) return precioBase;
        if (peso <= 50) return precioBase * 0.90; // 10% descuento
        if (peso <= 100) return precioBase * 0.85; // 15% descuento
        return calcularDescuentoRecursivo(peso - 100, precioBase * 0.70); // 30% descuento
    }

public:
    Transporte() {
        grafoRutas = new Grafo<double>(false); // Grafo no dirigido
        inicializarRedRutas();
    }

    ~Transporte() {
        delete grafoRutas;
    }

    // Inicializar red de rutas del Perú
    void inicializarRedRutas() {
        // Agregar departamentos principales
        grafoRutas->agregarVertice(0, "Lima");
        grafoRutas->agregarVertice(1, "Arequipa");
        grafoRutas->agregarVertice(2, "Cusco");
        grafoRutas->agregarVertice(3, "Trujillo");
        grafoRutas->agregarVertice(4, "Chiclayo");
        grafoRutas->agregarVertice(5, "Piura");
        grafoRutas->agregarVertice(6, "Ica");
        grafoRutas->agregarVertice(7, "Puno");
        grafoRutas->agregarVertice(8, "Tacna");
        grafoRutas->agregarVertice(9, "Ayacucho");
        grafoRutas->agregarVertice(10, "Huancayo");
        grafoRutas->agregarVertice(11, "Cajamarca");
        grafoRutas->agregarVertice(12, "San Isidro");
        grafoRutas->agregarVertice(13, "Lince");
        grafoRutas->agregarVertice(14, "Brenia");
        grafoRutas->agregarVertice(15, "Surco");

        // Rutas principales (distancias aproximadas en km)
        // Conexiones desde Lima
        grafoRutas->agregarArista(0, 6, 303.0);    // Lima - Ica
        grafoRutas->agregarArista(0, 10, 300.0);   // Lima - Huancayo
        grafoRutas->agregarArista(0, 3, 558.0);    // Lima - Trujillo
        grafoRutas->agregarArista(0, 1, 1009.0);   // Lima - Arequipa

        // Distritos de Lima (distancias cortas)
        grafoRutas->agregarArista(0, 12, 8.0);     // Lima - San Isidro
        grafoRutas->agregarArista(0, 13, 12.0);    // Lima - Lince
        grafoRutas->agregarArista(0, 14, 14.0);    // Lima - Breña
        grafoRutas->agregarArista(0, 15, 18.0);    // Lima - Surco

        // Conexiones entre distritos
        grafoRutas->agregarArista(12, 13, 5.0);    // San Isidro - Lince
        grafoRutas->agregarArista(12, 15, 12.0);   // San Isidro - Surco
        grafoRutas->agregarArista(13, 14, 3.0);    // Lince - Breña

        // Rutas del norte
        grafoRutas->agregarArista(3, 4, 209.0);    // Trujillo - Chiclayo
        grafoRutas->agregarArista(4, 5, 209.0);    // Chiclayo - Piura
        grafoRutas->agregarArista(3, 11, 294.0);   // Trujillo - Cajamarca

        // Rutas del sur
        grafoRutas->agregarArista(6, 1, 702.0);    // Ica - Arequipa
        grafoRutas->agregarArista(1, 2, 488.0);    // Arequipa - Cusco
        grafoRutas->agregarArista(1, 7, 295.0);    // Arequipa - Puno
        grafoRutas->agregarArista(1, 8, 289.0);    // Arequipa - Tacna
        grafoRutas->agregarArista(2, 7, 386.0);    // Cusco - Puno

        // Rutas centrales
        grafoRutas->agregarArista(10, 9, 257.0);   // Huancayo - Ayacucho
        grafoRutas->agregarArista(9, 2, 598.0);    // Ayacucho - Cusco
        grafoRutas->agregarArista(9, 1, 850.0);    // Ayacucho - Arequipa

        cout << "Red de rutas inicializada con " << grafoRutas->getNumeroVertices() << " ubicaciones.\n";
    }

    // Calcular precio de envío usando Dijkstra
    double calcularPrecio(const string& origen, const string& destino, int peso) {
        // Normalizar nombres a minúsculas
        string origenNorm = normalizarNombre(origen);
        string destinoNorm = normalizarNombre(destino);

        // Ejecutar Dijkstra
        AlgoritmoDijkstra<double> dijkstra(*grafoRutas);
        ResultadoDijkstra<double> resultado = dijkstra.ejecutarPorNombre(origenNorm, destinoNorm);

        if (!resultado.exito) {
            cout << "No se encontro ruta entre " << origen << " y " << destino << ".\n";
            cout << "Usando tarifa estimada...\n";
            return 100.0; // Tarifa por defecto
        }

        // Calcular precio basado en distancia y peso
        double precioBase = calcularPrecioLambda(resultado.distanciaTotal, peso);

        // Aplicar descuento por volumen
        double precioFinal = calcularDescuentoRecursivo(peso, precioBase);

        return precioFinal;
    }

    // Sobrecarga con IDs
    double calcularPrecio(int idOrigen, int idDestino, int peso) {
        AlgoritmoDijkstra<double> dijkstra(*grafoRutas);
        ResultadoDijkstra<double> resultado = dijkstra.ejecutar(idOrigen, idDestino);

        if (!resultado.exito) {
            return 100.0;
        }

        double precioBase = calcularPrecioLambda(resultado.distanciaTotal, peso);
        return calcularDescuentoRecursivo(peso, precioBase);
    }

    // Mostrar ruta detallada
    void mostrarRutaDetallada(const string& origen, const string& destino, int peso) {
        string origenNorm = normalizarNombre(origen);
        string destinoNorm = normalizarNombre(destino);

        AlgoritmoDijkstra<double> dijkstra(*grafoRutas);
        ResultadoDijkstra<double> resultado = dijkstra.ejecutarPorNombre(origenNorm, destinoNorm);

        if (!resultado.exito) {
            cout << "No se pudo calcular la ruta.\n";
            return;
        }

        // Mostrar camino
        resultado.mostrarCamino(*grafoRutas);

        // Mostrar detalles de precio
        double precioBase = calcularPrecioLambda(resultado.distanciaTotal, peso);
        double precioFinal = calcularDescuentoRecursivo(peso, precioBase);

        cout << "\n========================================\n";
        cout << "      DETALLES DE COSTO                 \n";
        cout << "========================================\n";
        cout << "Distancia Total: " << fixed << setprecision(2)
            << resultado.distanciaTotal << " km\n";
        cout << "Peso del Paquete: " << peso << " kg\n";
        cout << "----------------------------------------\n";
        cout << "Costo por Distancia: S/ " << (resultado.distanciaTotal * TARIFA_BASE) << "\n";
        cout << "Costo por Peso: S/ " << (peso * TARIFA_POR_KG) << "\n";
        cout << "Subtotal: S/ " << precioBase << "\n";

        if (precioFinal < precioBase) {
            double descuento = ((precioBase - precioFinal) / precioBase) * 100;
            cout << "Descuento por Volumen: " << fixed << setprecision(1)
                << descuento << "%\n";
        }

        cout << "----------------------------------------\n";
        cout << "TOTAL A PAGAR: S/ " << fixed << setprecision(2)
            << precioFinal << "\n";
        cout << "========================================\n";
    }

    // Mostrar red completa de rutas
    void mostrarRedRutas() const {
        grafoRutas->mostrarGrafo();
    }

    // Agregar nueva ruta al sistema
    void agregarRuta(const string& origen, const string& destino, double distancia) {
        string origenNorm = normalizarNombre(origen);
        string destinoNorm = normalizarNombre(destino);

        grafoRutas->agregarAristaPorNombre(origenNorm, destinoNorm, distancia);
        cout << "Ruta agregada: " << origen << " <-> " << destino
            << " (" << distancia << " km)\n";
    }

    // Agregar nueva ubicación
    void agregarUbicacion(int id, const string& nombre) {
        grafoRutas->agregarVertice(id, normalizarNombre(nombre));
        cout << "Ubicacion agregada: " << nombre << " (ID: " << id << ")\n";
    }

    // Obtener el grafo (para consultas externas)
    const Grafo<double>* getGrafoRutas() const {
        return grafoRutas;
    }

private:
    // Normalizar nombres para búsqueda (convertir a minúsculas)
    string normalizarNombre(string nombre) const {
        // Convertir a minúsculas
        transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);

        // Eliminar espacios extras
        nombre.erase(remove_if(nombre.begin(), nombre.end(), ::isspace), nombre.end());

        // Manejar casos especiales
        if (nombre == "sanisidro") return "San Isidro";
        if (nombre == "brenia") return "Brenia";

        // Capitalizar primera letra
        if (!nombre.empty()) {
            nombre[0] = toupper(nombre[0]);
        }

        return nombre;
    }
};

// ============================================================
// FUNCIONES AUXILIARES PARA ANÁLISIS DE RUTAS
// ============================================================

// Calcular todas las rutas posibles (útil para comparación)
template<typename T>
class AnalizadorRutas {
private:
    const Grafo<T>& grafo;

public:
    AnalizadorRutas(const Grafo<T>& g) : grafo(g) {}

    // Encontrar rutas alternativas (implementación futura)
    vector<ResultadoDijkstra<T>> encontrarRutasAlternativas(int origen, int destino, int maxRutas = 3) {
        vector<ResultadoDijkstra<T>> rutas;

        // Por ahora solo retorna la ruta óptima
        AlgoritmoDijkstra<T> dijkstra(grafo);
        ResultadoDijkstra<T> rutaOptima = dijkstra.ejecutar(origen, destino);

        if (rutaOptima.exito) {
            rutas.push_back(rutaOptima);
        }

        return rutas;
    }

    // Calcular estadísticas de la red
    void mostrarEstadisticasRed() const {
        cout << "\n========================================\n";
        cout << "    ESTADISTICAS DE LA RED DE RUTAS     \n";
        cout << "========================================\n";
        cout << "Total de Ubicaciones: " << grafo.getNumeroVertices() << "\n";

        // Contar aristas
        int totalAristas = 0;
        NodoVertice<T>* actual = grafo.getListaVertices();
        while (actual) {
            NodoArista<T>* arista = actual->vertice->getListaAdyacencia();
            while (arista) {
                totalAristas++;
                arista = arista->siguiente;
            }
            actual = actual->siguiente;
        }

        // Si es no dirigido, cada arista se cuenta dos veces
        if (!grafo.getEsDirigido()) {
            totalAristas /= 2;
        }

        cout << "Total de Rutas: " << totalAristas << "\n";
        cout << "Tipo de Red: " << (grafo.getEsDirigido() ? "Dirigida" : "Bidireccional") << "\n";
        cout << "========================================\n";
    }
};