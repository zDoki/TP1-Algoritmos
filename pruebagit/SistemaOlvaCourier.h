#pragma once
#include "Librerias.h"
#include "Paquete.h"
#include "Pago.h"
#include "Boleta.h"

class SistemaPrincipal
{
private:
	vector<Paquete<double>> listaPaquete;
	GestorPago<Pago<string>> gestionarPagos;
	Boleta<GestorPago<string>> gestionBoleta;

public:

	SistemaPrincipal() {}


	// administrar paquetes
	void registrarPaquete(const Paquete<double>& paquete) {
		listaPaquete.push_back(paquete);
		cout << "Paquete registrado exitosamente." << endl;
	}

	void mostrarPaquetes() {
		if (listaPaquete.empty()) {
			cout << "No hay paquetes registrados." << endl;
			return;
		}
		for (const auto& paquete : listaPaquete) {
			paquete.toStringFormato();
			cout << "-----------------------------" << endl;
		}
	}

	void estadoPaquete(int _id) {
		for (const auto& paquete : listaPaquete) {
			if (paquete.id == _id) {
				cout << "Estado del paquete ID " << _id << ": " << paquete.estado << endl;
				return;
			}
		}
		cout << "No se encontró un paquete con ID " << _id << "." << endl;
	}

	bool actualizarEstadoPaquete(int _id, const string& nuevoEstado) {
		for (auto& paquete : listaPaquete) {
			if (paquete.id == _id) {
				paquete.estado = nuevoEstado;
				cout << "Estado Actualizado a '" << nuevoEstado 
					<< "' para paquete ID." << _id << endl;
				return true;
			}
		}
		cout << "No se encontró un paquete con ID " << _id << "." << endl;
		return false;
	}

	// administrar pagos

	void registrarPago(const Pago<string>& pago) {
		gestionarPagos.registrarPago(pago);
		cout << "Pago registrado exitosamente." << endl;
	}

	void mostrarPagos() {
		gestionarPagos.mostrarPagos();
	}

	void mostrarBoletas() {
		gestionBoleta.mostrarBoleta();
	}

	// guardado en archivos
	void guardandoPagos(const string& archivo) {
		gestionarPagos.guardarPagosBinario(archivo);
		cout << "Los pagos se guardaron en " << archivo << endl;
	}

	void cargandoPagos(const string& archivo) {
		gestionarPagos.cargarPagosBinario(archivo);
		cout << "Los pagos se cargaron de " << archivo << endl;
	}

};

