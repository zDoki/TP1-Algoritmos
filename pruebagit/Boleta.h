#pragma once
#include "Pago.h"

template <class T>
class Boleta {
private:
	string numeroBoleta;
	string fechaEmision;
	Pago<T> pagoAsociado;
public:

	string ajustarTexto(const string& texto, size_t ancho) const {
		if (texto.size() > ancho) {
			return texto.substr(0, ancho); // recortar texto
		}
		else
		{
			return texto + string(ancho - texto.size(), ' '); // rellena con espacios
		}
	}

	Boleta(string num = "", const Pago<T>& pago = Pago<T>())
		: numeroBoleta(num), pagoAsociado(pago)
	{
		// para saber fecha
		fechaEmision = obtenerFechaHoraActual();
	}

	static string obtenerFechaHoraActual() {
		time_t horaActual = time(0);
		tm* tiempo = localtime(&horaActual);
		char buffer[20];
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", tiempo);
		return string(buffer);
	}

	void guardarArchivoTexto(const string& archivo) {
		ofstream out(archivo, ios::app);
		if (!out) {
			cout << "No se pudo abrir el archivo para guardar boleta.\n";
			return;
		}

		
		ostringstream pagoStr;
		pagoStr << pagoAsociado.getProducto() << "|"
			<< pagoAsociado.getCantidad() << "|"
			<< fixed << setprecision(2) << pagoAsociado.getPrecioUnitario() << "|"
			<< pagoAsociado.metodo.getTipoPago();

		out << numeroBoleta << "|" << fechaEmision << "|" << pagoStr.str() << "\n";
		out.close();
	}

	void cargarArchivoTexto(const string& archivo) {
		ifstream in(archivo);
		if (!in) {
			cout << "No se pudo abrir el archivo: " << archivo << "\n";
			return;
		}

		string linea, ultima;
		while (getline(in, linea)) {
			if (!linea.empty()) ultima = linea;
		}
		in.close();

		if (ultima.empty()) {
			cout << "El archivo de boletas est� vac�o.\n";
			return;
		}

		// numeroBoleta | fechaEmision | pagoStr
		istringstream ss(ultima);
		string pagoStr;
		if (!getline(ss, numeroBoleta, '|') ||
			!getline(ss, fechaEmision, '|') ||
			!getline(ss, pagoStr)) {
			cout << "Formato de boleta inv�lido en el archivo.\n";
			return;
		}

		
		pagoAsociado.cargarPagoTexto(pagoStr);
	}

	
	void mostrarBoleta() {
		cout << "|-------------------------------------------|\n";
		cout << "|                                           |\n";
		cout << "|===========================================|\n";
		cout << "|               BOLETA DE PAGO              |\n";
		cout << "|===========================================|\n";
		cout << "|              OLVA COURIER SAC             |\n";
		cout << "|-------------------------------------------|\n";
		cout << "| NUMERO OPERACION: " << ajustarTexto(numeroBoleta, 24) << "|\n";
		cout << "| FECHA Y HORA: " << ajustarTexto(fechaEmision, 28) << "|\n";
		pagoAsociado.mostrarPagos();
		cout << "|        GRACIAS POR SU PREFERENCIA         |\n";
		cout << "|===========================================|\n";
		cout << "|                                           |\n";
		cout << "|-------------------------------------------|\n";
	}


};