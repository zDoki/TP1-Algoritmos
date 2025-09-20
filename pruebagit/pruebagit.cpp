#include "pch.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
using namespace System;




template<typename T>
class Paquete {
public:
	int id;
	string descripcion;
	double peso;
	string dimensiones;
	string estado; // "registrado", "en_transito", "entregado", "perdido"
	int remitenteId;
	int destinatarioId;
	int sucursalOrigenId;
	int sucursalDestinoId;
	string fechaEnvio;
	string fechaEntregaEstimada;

	Paquete(int _id, string _descripcion, double _peso, string _dimensiones, string _estado, int _remitenteId, int _destinatarioId, int _sucursalOrigenId, int _sucursalDestinoId, string _fechaEnvio, string _fechaEntregaEstimada) :
		id(_id), descripcion(_descripcion), peso(_peso), dimensiones(_dimensiones), estado(_estado), remitenteId(_remitenteId), destinatarioId(_destinatarioId), sucursalOrigenId(_sucursalOrigenId), sucursalDestinoId(_sucursalDestinoId), fechaEnvio(_fechaEnvio), fechaEntregaEstimada(fechaEntregaEstimada) {};

	Paquete() : id(0), peso(0.0), remitenteId(0), destinatarioId(0),
		sucursalOrigenId(0), sucursalDestinoId(0) {}


	void mostrarInfoPaquete() {

		cout << "ID " << id << endl;
		cout << "Descripsion " << descripcion << endl;
		cout << "Peso " << peso << endl;
		cout << "Dimensiones " << dimensiones << endl;
		cout << "Estado " << estado << endl;
		cout << "Remitente ID " << remitenteId << endl;
		cout << "Destinatario ID " << destinatarioId << endl;
		cout << "Sucursal Origen " << sucursalOrigenId << endl;
		cout << "Sucursal Destino " << sucursalDestinoId << endl;
		cout << "Fecha Envio " << fechaEnvio << endl;
		cout << "Fecha estimada de entrega " << fechaEntregaEstimada << endl;


	}

	string toString()const {
		return to_string(id) + "|" + descripcion + "|" + to_string(peso) + "|" +
			dimensiones + "|" + estado + "|" + to_string(remitenteId) + "|" +
			to_string(destinatarioId) + "|" + to_string(sucursalOrigenId) + "|" +
			to_string(sucursalDestinoId) + "|" + fechaEnvio + "|" + fechaEntregaEstimada;
	}

	string toStringFormato() const {
		string resultado = "";
		resultado += "================================\n";
		resultado += "         DATOS DEL PAQUETE      \n";
		resultado += "================================\n";
		resultado += "ID:                 " + to_string(id) + "\n";
		resultado += "Descripcion:        " + descripcion + "\n";
		resultado += "Peso:               " + to_string(peso) + " kg\n";
		resultado += "Dimensiones:        " + dimensiones + "\n";
		resultado += "Estado:             " + estado + "\n";
		resultado += "Remitente ID:       " + to_string(remitenteId) + "\n";
		resultado += "Destinatario ID:    " + to_string(destinatarioId) + "\n";
		resultado += "Sucursal Origen:    " + to_string(sucursalOrigenId) + "\n";
		resultado += "Sucursal Destino:   " + to_string(sucursalDestinoId) + "\n";
		resultado += "Fecha Envio:        " + fechaEnvio + "\n";
		resultado += "Fecha Entrega Est:  " + fechaEntregaEstimada + "\n";
		resultado += "================================\n\n";
		return resultado;
	}


};



template<typename T>
class NodoPila {
public:
	T dato;
	NodoPila<T>* siguiente;

	NodoPila(T _dato,NodoPila<T>* _sig= nullptr) {
		dato = _dato;
		siguiente = _sig;
	};

};

template<typename T>
class PilaPaquete {
public:
	NodoPila<T>* tope;
	int tamanio;

	PilaPaquete():tope(nullptr),tamanio(0) {
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

	void guardarPaqueteEnArchivo(T paquete,const string& nombreArchivo) {
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
		return tope = nullptr;
	}




};






int main()
{

	PilaPaquete<Paquete<int>> pila;
	

	int id;
	string descripcion;
	double peso;
	string dimensiones;
	string estado; // "registrado", "en_transito", "entregado", "perdido"
	int remitenteId;
	int destinatarioId;
	int sucursalOrigenId;
	int sucursalDestinoId;
	string fechaEnvio;
	string fechaEntregaEstimada;
	
	cout << "Ingrese el paquete" << endl;
	cout << "Ingrese el id " << endl;
	cin >> id;
	cin.ignore();
	cout << "Ingrese el descripcion" << endl;
	getline(cin, descripcion);
	cout << "Ingrese el peso" << endl;
	cin >> peso;
	cin.ignore();
	cout << "Ingrese el dimensiones" << endl;
	getline(cin, dimensiones);
	cout << "Ingrese el estado" << endl;
	getline(cin, estado);
	cout << "Ingrese el remitenteId" << endl; 
	cin >> remitenteId;
	cin.ignore();
	cout << "Ingrese el destinatarioId" << endl;
	cin >> destinatarioId;
	cin.ignore();
	cout << "Ingrese el sucursalOrigenId" << endl;
	cin >> sucursalOrigenId;
	cin.ignore();
	cout << "Ingrese el sucursalDestinoId" << endl;
	cin >> sucursalDestinoId;
	cin.ignore();
	cout << "Ingrese el fechaEnvio" << endl;
	getline(cin, fechaEnvio);
	cout << "Ingrese el fechaEntregaEstimada" << endl;
	getline(cin,fechaEntregaEstimada);


	Paquete<int> paquete1(id,descripcion, peso, dimensiones, estado, remitenteId, destinatarioId, sucursalOrigenId, sucursalDestinoId, fechaEnvio, fechaEntregaEstimada);
	pila.push(paquete1);
	pila.guardarPaqueteEnArchivo(paquete1, "paquetes.txt");



    return 0;
}
