#pragma once
#include "Librerias.h"

class Transporte
{
public:

    int calcularPrecio(string depOrigen, string depDestino, int peso) {
        int precioDepartamento = 0, precioPeso = 0;

        // Precio por departamento
        if (depOrigen == "lima" && depDestino == "lima") {
            precioDepartamento = 8;
        }
        else if (depOrigen == "lima" && depDestino == "lince") {
            precioDepartamento = 12;
        }
        else if (depOrigen == "lima" && depDestino == "brenia") {
            precioDepartamento = 14;
        }
        else if (depOrigen == "lima" && depDestino == "surco") {
            precioDepartamento = 18;
        }
        else if (depOrigen == "lima" && depDestino == "sanisidro") {
            precioDepartamento = 10;
        }
        else {
            precioDepartamento = 25;
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


};