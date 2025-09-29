#include "pch.h"
#include"Librerias.h"
#include"NodoPila.h"
#include"Paquete.h"
#include"PilaPaquete.h"



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

	pila.mostrarPaquetesTxt("paquetes.txt");
	
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
