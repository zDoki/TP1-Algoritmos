#pragma once
#include "Librerias.h"

// ------------------- Función de cálculo de precio -------------------
int calcularPrecio(string depOrigen, string depDestino, int peso) {
    int precioDepartamento = 0, precioPeso = 0;

    // Precio por departamento
    if (depOrigen == "lima" && depDestino == "lima") {
        precioDepartamento = 10;
    }
    else if (depOrigen == "lima" || depDestino == "lima") {
        precioDepartamento = 15;
    }
    else {
        precioDepartamento = 15;
    }

    // Precio por peso
    if (peso >= 1 && peso <= 20) {
        precioPeso = 50;
    }
    else if (peso > 20) {
        precioPeso = 50 + (peso - 20) * 7;
    }

    return precioDepartamento + precioPeso;
}