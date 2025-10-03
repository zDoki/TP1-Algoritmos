#pragma once
#include "Librerias.h"
#include "Paquete.h"
#include "Pago.h"
#include "Boleta.h"
#include"PilaPaquete.h"
#include"NodoPila.h"
#include"Paquete.h"


class SistemaPrincipal
{
private:
	vector<Paquete<double>> listaPaquete;
	GestorPago<Pago<string>> gestionarPagos;
	Boleta<GestorPago<string>> gestionBoleta;

public:

};

