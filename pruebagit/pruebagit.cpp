#include "pch.h"
#include "Pago.h"
#include "Boleta.h"
#include "Cliente.h"
#include "Tranporte.h"
#include "PilaPaquete.h"
#include "Paquete.h"


// funciones adicionales para el sistema
bool funcionSalida(const string& mensaje, string& entrada) {
    cout << mensaje;
    entrada.clear();

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
        else if (digit == '\b') {  // Retroceso (Backspace)
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b";
            }
        }
        else {                 // Otro caracter 
            entrada.push_back(digit);
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
    cout << "[1] Ingrese con su cuenta" << endl;
    cout << "[2] Crear una cuenta" << endl;
	cout << "[3] Cotizador" << endl;
    cout << "Precione ESC para salir" << endl;
    cout << "Seleccione una opcion" << endl;
}
void menuCliente() {
    system("cls");
    cout << "========================================\n";
    cout << "           MENU CLIENTE                \n";
    cout << "========================================\n";
    cout << " [1] Registrar paquetes\n";
    cout << " [2] Mostrar mis paquetes\n";
    cout << " [3] Realizar pagos\n";
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
        
        if (!funcionSalida("Departamento: ", depOrigen)) { break; }
        if (!funcionSalida("Provincia: ", provOrigen)) { break; }
        if (!funcionSalida("Distrito: ", disOrigen)) { break; }

        cout << "\nA donde lo llevamos?\n";

        if (!funcionSalida("Departamento: ", depDestino)) { break; }
        if (!funcionSalida("Provincia: ", provDestino)) { break; }
        if (!funcionSalida("Distrito: ", disDestino)) { break; }

        if (!funcionSalida("\nDonde lo recibes? (sede/domicilio): ", lugarRecibe)) { break; }

        if (!funcionSalida("Que quieres enviar? (sobres/paquetes): ", tipoEnvio)) { break; }
        
        cout << "Cuanto pesa? (kg): ";
        cin >> peso;

        int precioEstimado = calcularPrecio(depOrigen, depDestino, peso);

        cout << "\nPrecio estimado: " << precioEstimado << " soles\n";

        cout << "\nDesea generar otra cotizacion? (s/n): ";
        cin >> continuar;

        if (continuar == "n") {
            cout << "Total a pagar: " << precioEstimado << " soles\n";
        }
    }
}
void sistemaRegistroPaquetes() {
    PilaPaquete<Paquete<string>> pilaPaquetes;
    GestoCliente<Cliente> listaClientes;

    string descripcion, sedeOrigen, destino, input;
    double peso = 0.0;
    int remitenteId = 0, destinatarioId = 0;
    char tecla;

    bool salir = false;
    while (!salir) {
        system("cls");
        cout << "========================================\n";
        cout << "       REGISTRO DE PAQUETES            \n";
        cout << "========================================\n";
        cout << "(Presione ESC en cualquier momento para cancelar)\n\n";
        // Cancelar el ingreso presionando ESC

        if (!funcionSalida("Descripcion: ", descripcion)) { break; }

        if (!funcionSalida("Peso (kg): ", input)) { break; }
		peso = abs(peso); // Asegurar que el peso sea positivo
        peso = stod(input);

        if (!funcionSalida("Sede Origen: ", sedeOrigen)) { break; }

        if (!funcionSalida("Destino: ", destino)) { break; }
        
        if (!funcionSalida("ID Destinatario: ", input)) { break; }
		destinatarioId = stoi(input);
       
		Cliente* destinatario = listaClientes.buscarPorID(destinatarioId);

        if (destinatario == nullptr) {
			cout << "\nEl destinatario no se encontro, debe estar registrado" << endl;
            system("pause");
            continue;
        }

        if (!funcionSalida("ID Remitente: ", input)) { break; }
		remitenteId = stoi(input);

        if (remitenteId == destinatarioId) {
            cout << "\nEl ID del remitente no se ha encontrado." << endl;
            system("pause");
            continue;
        }

        Paquete<string> nuevoPaquete(descripcion, peso, remitenteId,
            destinatarioId, sedeOrigen, destino);

        pilaPaquetes.push(nuevoPaquete);
        pilaPaquetes.guardarPaqueteEnArchivo(nuevoPaquete, "paquetes.txt");
        cout << "\nPaquete registrado exitosamente!\n";

        cout << "\nDesea registrar otro paquete? (s/n): ";
        tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            salir = true;
            cout << "Saliendo del registro de paquetes..." << endl;
        }
	}
}
void sistemaMostarPaquetes() {

    system("pause");
}
void sistemaPagos() {
    system("pause");

}

void sistemaInicioSesion() {
    GestoCliente<Cliente> listaClientes;
    string n, a, d, p, c, pass;
    listaClientes.cargarClientes("clientes.txt");

    char tecla;
    bool salir = false;

    // --------------------- Menu Principal ---------------------
    while (!salir) {
        system("cls");
        menuInicio();

        tecla = getch();

        switch (tecla) {
            // ------------------- Opcion 1: Ingreso Cliente -------------------
        case '1': {
            system("cls");
            cout << "\n--- INGRESO CLIENTE ---\n";
            cout << "(Presione ESC en cualquier momento para cancelar)\n\n";

            // Cancelar el ingreso presionando ESC
            if (!funcionSalida("Correo: ", c)) { break; }
            if (!funcionSalida("Contrasenia: ", pass)) { break; }

            if (listaClientes.ingresoCuenta(c, pass)) {
                cout << "Ingreso exitoso\n";

                char teclaUser;

                bool salirUser = false;
                while (!salirUser) {
					
                    system("cls");
                    menuCliente();

                    teclaUser = getch();

                    switch (teclaUser) {

                        // ------------------- Opcion 1: Registrar productos -------------------
                    case '1': {
                        sistemaRegistroPaquetes();
                        system("pause");
                        break;
                    }
                        // ------------------- Opcion 2: Mostrar mis paquetes ----------------
                    case '2': {
                        sistemaMostarPaquetes();
						break;
                    }
                        // ------------------- Opcion 3: Realizar pagos ----------------
                    case '3': {

                        system("pause");
                        break;
                    }
                    case 27:
                        cout << "Volviendo al menu principal..." << endl;
                        salirUser = true;
                        break;
                    default:
                        cout << "Opcione no validada. Intente de nuevo" << endl;
                        system("pause");
                        break;
                    }
                }
            }
            else
            {
                cout << "Correo o contrasenia incorrectos. Vuelva a intentar\n";
            }

            system("pause");
            break;
        }
            // ------------------- Opcion 2: Registro Cliente -------------------
        case '2': {

            cout << "\n--- REGISTRO DE CLIENTE ---\n";

            // Cancelar el ingreso presionando ESC
            if (!funcionSalida("Nombres: ", n)) { break; }
            if (!funcionSalida("Apellido: ", a)) { break; }
            if (!funcionSalida("DNI: ", d)) { break; }
            if (!funcionSalida("Pais: ", p)) { break; }
            if (!funcionSalida("Correo: ", c)) { break; }
            if (!funcionSalida("Contrasenia: ", pass)) { break; }

			int nuevoID = Cliente::generarIDUnico("clientes.txt");

            Cliente nuevo(nuevoID,n, a, d, p, c, pass);
            listaClientes.insertar(nuevo);
            listaClientes.guardarClientes("clientes.txt");

            cout << "Registro exitoso " << endl;
            cout << "Su ID unico es : " << nuevoID << endl;
            system("pause");
            break;
        }
			// -------------------- Opcion 3: Cotizador --------------------
        case '3': {
            sistemaCotizador();
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
	srand(time(0));
    
    sistemaInicioSesion();
    //pruebaBoleta();
    //sistemaPagos();

    return 0;
}