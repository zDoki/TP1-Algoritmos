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

	do
	{
		menuSistema();
		cin >> opcion;
		switch (opcion) {

		case 1: {
			Paquete<double> paquete1(1, "Celular", 10.25, "15x15x6 cm",
				"registrado",101, 102, 1, 2, "01-10-2025", "05-10-2025");
			sistema.registrarPaquete(paquete1);
			break;
		}
		case 2: {
			Pago<string> pago1("Celular",1, 150.5);
			pago1.metodo.PagoEfectivo();
			sistema.registrarPago(pago1);
			break;
		}
		case 3: {
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
