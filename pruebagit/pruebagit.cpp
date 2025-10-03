#include "pch.h"
#include "Pago.h"
#include "Boleta.h"
#include "Cliente.h"
#include "Tranporte.h"


// funciones adicionales para el sistema
bool funcionSalida(const string& e, string& v) {
    cout << e;
    v.clear();

    char digit;
    while (true) {
        digit = getch();

        if (digit == 27) { // ESC
            cout << "\nOperacion cancelada. Volviendo al menu principal...\n";
            system("pause");
            return false;      // Usuario cancelo accion
        }
        else if (digit == '\r') {  // Enter
            cout << endl;
            break;
        }
        else if (digit == '\b') {  // Barra Espacio
            if (!v.empty()) {
                v.pop_back();
                cout << "\b \b";
            }
        }
        else {                 // Otro caracter 
            v.push_back(digit);
            cout << digit;
        }
    }

    return true;
}

void pruebaBoleta() {
    GestorPago<Pago<string>> gestorPagos;
    string archivoBoletas = "boleta.txt";

    srand((unsigned)time(0));

    // Crear pago de prueba
    Pago<string> pago1("celular", 2, 150.0);
    pago1.metodo.PagoYape();
    gestorPagos.registrarPago(pago1);

    // Crear boleta y guardarla
    string numBol = "B" + to_string(rand() % 10) + "OVS-" + to_string(rand() % 1000);
    Boleta<string> boleta1(numBol, pago1);
    boleta1.guardarArchivoTexto(archivoBoletas);

    // Cargar la última boleta guardada en archivo en una nueva instancia
    Boleta<string> boletaCargada;
    boletaCargada.cargarArchivoTexto(archivoBoletas);

    // Mostrar boleta cargada
    boletaCargada.mostrarBoleta();

    system("pause");
}

// almacenamiento de Menus del sistema
void menuInicio() {
    cout << "===============================" << endl;
    cout << "      BIENVENIDO A OLVA        " << endl;
    cout << "===============================" << endl;
    cout << "1. Ingrese con su cuenta" << endl;
    cout << "2. Crear una cuenta" << endl;
    cout << "Precione ESC para salir" << endl;
    cout << "Seleccione una opcion" << endl;
}
void menuCliente() {
    system("cls");
    cout << "========================================\n";
    cout << "           MENU CLIENTE                \n";
    cout << "========================================\n";
    cout << " [1] Registrar productos\n";
    cout << " [2] Ver mis envios\n";
    cout << " [3] Cotizador\n";
    cout << " [4] Realizar pagos\n";
    cout << " [5] Ver seguimiento de envio\n";
    cout << " [6] Salir\n";
    cout << "----------------------------------------\n";
    cout << " Presione ESC para salir al menu previo\n";
    cout << "----------------------------------------\n";
    cout << "Seleccione una opcion: ";
}
void menuAdmin() {
    cout << "========================================" << endl;
    cout << "           MENU ADMIN                " << endl;
    cout << "========================================" << endl;
    cout << " [1] Actualizar estado de envio" << endl;
    cout << " [2] Ver todos los envios" << endl;
    cout << " [3] Ver todos los clientes" << endl;
    cout << " [4] Ver Pagos realizados" << endl;
    cout << " [5] Ver Boletas emitidas" << endl;
    cout << " [6] Salir" << endl;
    cout << "----------------------------------------\n";
    cout << " Presione ESC para salir al menu previo\n";
    cout << "----------------------------------------\n";
    cout << "Seleccione una opcion: ";
}

// total de sistemas integrados para que corra olva courier
void sistemaCotizador() {

    string continuar = "s";
    while (continuar == "s") {

        cout << "\n--- COTIZADOR ---\n";
        string depOrigen, provOrigen, disOrigen;
        string depDestino, provDestino, disDestino;
        string lugarRecibe, tipoEnvio;
        int peso;

        cout << "Donde te encuentras?\n";
        cout << "Departamento: "; cin >> depOrigen;
        cout << "Provincia: "; cin >> provOrigen;
        cout << "Distrito: "; cin >> disOrigen;

        cout << "\nA dónde lo llevamos?\n";
        cout << "Departamento: "; cin >> depDestino;
        cout << "Provincia: "; cin >> provDestino;
        cout << "Distrito: "; cin >> disDestino;

        cout << "\nDonde lo recibes? (tienda/domicilio): ";
        cin >> lugarRecibe;

        cout << "\nQue quieres enviar? (sobres/paquetes): ";
        cin >> tipoEnvio;
        cout << "Cuanto pesa? (kg): ";
        cin >> peso;

        int precioEstimado = calcularPrecio(depOrigen, depDestino, peso);

        cout << "\nPrecio estimado: " << precioEstimado << " soles\n";

        cout << "\nDesea generar otra cotizacion? (s/n): ";
        cin >> continuar;

        if (continuar == "n") {
            string confirmar;
            cout << "Deseas confirmar la cotizacion? (s/n): ";
            cin >> confirmar;
            if (confirmar == "si") {
                cout << "Total a pagar: " << precioEstimado << " soles\n";
            }
        }
    }
}
void sistemaInicioSesion() {
    GestoCliente<Cliente> listaClientes;
    string n, a, d, p, c, pass;
    listaClientes.cargarClientes("clientes.dat");

    char tecla;
    bool salir = false;

    // --------------------- Menu Principal ---------------------
    while (!salir) {
        system("cls");
        menuInicio();

        tecla = getch();

        switch (tecla) {
            // ------------------- Opción 1: Ingreso Cliente -------------------
        case '1': {
            system("cls");
            cout << "\n--- INGRESO CLIENTE ---\n";
            cout << "(Presione ESC en cualquier momento para cancelar)\n\n";


            // Cancelar el ingreso presionando ESC
            if (!funcionSalida("Correo: ", c)) { break; }
            if (!funcionSalida("Contrasenia: ", pass)) { break; }

            if (listaClientes.ingresoCuenta(c, pass)) {
                cout << "Ingreso exitoso\n";

int main()
{
	int opcion;
	SistemaPrincipal sistema;

                    switch (tecla) {

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

            cout << "Registro exitoso\n";
            system("pause");
            break;
        }
                // ------------------- SALIR DEL PROGRAMA -------------------
        case 27:
            cout << "Saliendo del sistem..." << endl;
            salir = true;
            break;
        default:
            cout << "Opciones no validadas. Intente de nuevo" << endl;
            system("pause");
            break;
        }
    }
}

int main() {
    sistemaInicioSesion();
    //pruebaBoleta();

    return 0;
}