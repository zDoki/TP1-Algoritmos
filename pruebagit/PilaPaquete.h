#pragma once
#include"NodoPila.h"

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

	void guardarPaqueteEnArchivo(T paquete, const string& nombreArchivo) {
		ofstream archivo(nombreArchivo, ios::app);
		if (archivo.is_open()) {

			archivo.seekp(0, ios::end);
			if (archivo.tellp() == 0) {
				archivo << "========================================\n";
				archivo << "      REGISTRO DE PAQUETES             \n";
				archivo << "========================================\n\n";
			}

			archivo << paquete.toStringFormato();
			archivo.close();
			cout << "Paquete guardado exitosamente en " << nombreArchivo << endl;
		}
		else {
			cout << "Error No se pudo abrir el archivo" << endl;
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

	int getTamaino()const {
		return tamanio;
	}

	bool estaVacia()const {
		return tope == nullptr;
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

