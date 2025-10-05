#pragma once
#include "NodoPila.h"

template<typename T>
class PilaPaquete {
public:
	NodoPila<T>* tope;
	int tamanio;

	PilaPaquete() :tope(nullptr), tamanio(0) {
	}

	~PilaPaquete() {
		while (tope)
		{
			NodoPila<T>* temp = tope;
			tope = tope->siguiente;
			delete temp;
		}
	}

	void push(T valor) {
		NodoPila<T>* nuevo = new NodoPila<T>(valor);
		nuevo->siguiente = tope;
		tope = nuevo;
		tamanio++;
		cout << "Paquete agregado a la pila" << endl;
	}

	T pop() {
		if (!tope)
		{
			cout << "Pila vacia " << endl;
			return T();
		}
		T data = tope->dato;
		NodoPila<T>* temp = tope;
		tope = tope->siguiente;
		delete temp;
		tamanio--;
		return data;
	}

	// MODIFICADO: Guardar con formato separado por |
	void guardarPaqueteEnArchivo(T paquete, const string& nombreArchivo) {
		ofstream archivo(nombreArchivo, ios::app);
		if (archivo.is_open()) {
			archivo << paquete.toStringArchivo() << "\n";
			archivo.close();
			cout << "Paquete guardado exitosamente en " << nombreArchivo << endl;
		}
		else {
			cout << "Error: No se pudo abrir el archivo" << endl;
		}
	}

	void mostrarTodos() {
		if (!tope)
		{
			cout << "Pila vacia" << endl;
			return;
		}
		NodoPila<T>* actual = tope;
		cout << "===Paquetes en la pila===" << endl;
		while (actual)
		{
			actual->dato.mostrarInfoPaquete();
			cout << "-----------------------------" << endl;
			actual = actual->siguiente;
		}
	}

	// NUEVO: Mostrar solo paquetes de un cliente específico
	void mostrarPorCliente(int clienteID) {
		if (!tope) {
			cout << "No hay paquetes registrados." << endl;
			return;
		}

		NodoPila<T>* actual = tope;
		bool encontrado = false;
		int contador = 1;

		cout << "\n========================================\n";
		cout << "     MIS PAQUETES REGISTRADOS          \n";
		cout << "========================================\n\n";

		while (actual) {
			if (actual->dato.clienteID == clienteID) {
				cout << "--- Paquete #" << contador++ << " ---\n";
				actual->dato.mostrarInfoPaquete();
				cout << "----------------------------------------\n";
				encontrado = true;
			}
			actual = actual->siguiente;
		}

		if (!encontrado) {
			cout << "No tiene paquetes registrados.\n";
		}
	}

	int getTamaino() const {
		return tamanio;
	}

	bool estaVacia() const {
		return tope == nullptr;
	}

	// NUEVO: Leer paquetes de un cliente desde archivo
	void mostrarPaquetesDeCliente(const string& nombreArchivo, int clienteID) {
		ifstream archivo(nombreArchivo);

		if (!archivo.is_open()) {
			cout << "\nNo hay paquetes registrados en el sistema." << endl;
			return;
		}

		cout << "\n========================================\n";
		cout << "     MIS PAQUETES REGISTRADOS          \n";
		cout << "========================================\n\n";

		string linea;
		bool encontrado = false;
		int contador = 1;

		while (getline(archivo, linea)) {
			if (linea.empty()) continue;

			stringstream ss(linea);
			string campo;
			int idPaquete, idCliente;

			try {
				// Leer ID del paquete
				getline(ss, campo, '|');
				idPaquete = stoi(campo);

				// Leer ID del cliente
				getline(ss, campo, '|');
				idCliente = stoi(campo);

				// Si el paquete pertenece al cliente actual
				if (idCliente == clienteID) {
					encontrado = true;

					string desc, origen, destino;
					double peso;

					getline(ss, desc, '|');
					getline(ss, campo, '|');
					peso = stod(campo);
					getline(ss, origen, '|');
					getline(ss, destino, '|');

					cout << "--- Paquete #" << contador++ << " ---\n";
					cout << "ID Paquete:      " << idPaquete << "\n";
					cout << "Descripcion:     " << desc << "\n";
					cout << "Peso:            " << fixed << setprecision(2) << peso << " kg\n";
					cout << "Origen:          " << origen << "\n";
					cout << "Destino:         " << destino << "\n";
					cout << "----------------------------------------\n";
				}
			}
			catch (...) {
				continue;
			}
		}

		if (!encontrado) {
			cout << "No tiene paquetes registrados.\n";
		}

		archivo.close();
		cout << "\n========================================\n";
	}

	void mostrarPaquetesTxt(const string& nombreArchivo) {
		ifstream archivo(nombreArchivo);

		if (!archivo.is_open()) {
			cout << "\nError: No se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
			cout << "Es posible que no existan paquetes guardados aún." << endl;
			return;
		}

		cout << "\n========== PAQUETES GUARDADOS EN ARCHIVO ==========" << endl;

		string linea;
		bool hayContenido = false;

		while (getline(archivo, linea)) {
			cout << linea << endl;
			hayContenido = true;
		}

		if (!hayContenido) {
			cout << "El archivo está vacío. No hay paquetes guardados." << endl;
		}

		archivo.close();
		cout << "\n===============================================" << endl;
	}

	void cargarDesdeArchivo(const string& nombreArchivo) {
		ifstream archivo(nombreArchivo);
		if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo '" << nombreArchivo << "'\n";
			return;
		}

		while (!archivo.eof()) {
			T paquete;
			if (paquete.leerDesdeArchivo(archivo)) {
				push(paquete);
			}
		}

		archivo.close();
		cout << "Paquetes cargados desde " << nombreArchivo << endl;
	}
};