#include "pch.h"
#include "SistemaOlvaCourier.h"

void menuSistema() {
	cout << "===Menu Sistema===" << endl;
	cout << "1. Registrar Paquete" << endl;
	cout << "2. Crear Pago" << endl;
	cout << "3. Mostrar Paquetes y pagos registrados" << endl;
	cout << "4. Consultar Estado" << endl;
	cout << "5. Actualizar Estado" << endl;
	cout << "6. Guardar y cargar pagos" << endl;
	cout << "7. Salir" << endl;
	cout << "Ingrese una opcion: ";
}


int main()
{
	int opcion;
	SistemaPrincipal sistema;
	PilaPaquete<Paquete<int>> pila;

	do
	{
		menuSistema();
		cin >> opcion;
		switch (opcion) {

		case 1: {

			


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
			getline(cin, fechaEntregaEstimada);


			Paquete<int> paquete1(id, descripcion, peso, dimensiones, estado, remitenteId, destinatarioId, sucursalOrigenId, sucursalDestinoId, fechaEnvio, fechaEntregaEstimada);
			pila.push(paquete1);
			pila.guardarPaqueteEnArchivo(paquete1, "paquetes.txt");

			

			break;
		}
		case 2: {
			Pago<string> pago1("Celular",1, 150.5);
			pago1.metodo.PagoEfectivo();
			sistema.registrarPago(pago1);
			break;
		}
		case 3: {

			pila.mostrarPaquetesTxt("paquetes.txt");
			sistema.mostrarPaquetes();
			sistema.mostrarPagos();
			system("pause");
			system("cls");
			break;
		}
		case 4:{
			sistema.estadoPaquete(1);
			system("pause");
			system("cls");
			break;
		}
		case 5: {
			sistema.actualizarEstadoPaquete(1,"Entregado");
			sistema.estadoPaquete(1);
			system("pause");
			system("cls");
			break;
		}
		case 6:
			sistema.guardandoPagos("pagos.dat");
			sistema.cargandoPagos("pagos.dat");
			system("pause");
			system("cls");
			break;
		case 7:
			cout << "Saliendo del programa...." << endl;
			break;
		}
	
	} while (opcion != 7);

	system("pause");
	return 0;
}
