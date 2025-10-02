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
			return texto.substr(0, ancho); // recorta texto
		}
		else
		{
			return texto + string(ancho - texto.size(), ' '); // rellena con espacios
		}
	}

	Boleta(string num = "", const Pago<T>& pago = Pago<T>())
		: numeroBoleta(num), pagoAsociado(pago)
	{
		// Obtener la fecha actual
		fechaEmision = obtenerFechaHoraActual();
	}

	static string obtenerFechaHoraActual() {
		time_t horaActual = time(0);
		tm* tiempo = localtime(&horaActual);
		char buffer[20];
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", tiempo);
		return string(buffer);
	}

	void guardarArchivoBinario(const string& archivo) {
		ofstream out(archivo, ios::binary | ios::app);
		if (!out) {
			cout << "El archivo no se pudo guardar.\n";
			return;
		}
		size_t len;

		// Guardar numero de boleta
		len = numeroBoleta.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(numeroBoleta.c_str(), len);

		// Guardar fecha de emision
		len = fechaEmision.size();
		out.write(reinterpret_cast<const char*>(&len), sizeof(len));
		out.write(fechaEmision.c_str(), len);

		// Guardar datos del pago asociado
		pagoAsociado.guardarPago(out);

		out.close();
	}

	void cargarArchivoBinario(const string& archivo) {
		ifstream in(archivo, ios::binary);
		if (!in) {
			cout << "El archivo no se pudo abrir.\n";
			return;
		}

		size_t len;
		string buffer;

		// Cargar numero de boleta
		in.read(reinterpret_cast<char*>(&len), sizeof(len));
		buffer.resize(len);
		in.read(&buffer[0], len);
		numeroBoleta = buffer;

		// Cargar fecha de emision
		in.read(reinterpret_cast<char*>(&len), sizeof(len));
		buffer.resize(len);
		in.read(&buffer[0], len);
		fechaEmision = buffer;

		// Cargar datos del pago asociado
		pagoAsociado.cargarPago(in);

		in.close();
	}

	// Mostrar detalle de la boleta
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