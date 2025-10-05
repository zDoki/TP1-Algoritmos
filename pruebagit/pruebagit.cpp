#include "pch.h"
#include "Pago.h"
#include "Boleta.h"
#include "Cliente.h"
#include "Tranporte.h"
#include "PilaPaquete.h"
#include "Paquete.h"
#include "ColaPago.h"

// Variables globales del sistema
PilaPaquete<Paquete<string>> pilaPaquetes;
GestoCliente<Cliente> listaClientes;
ColaPago<Pago<string>> colaPagos;

// Función auxiliar para cancelar operaciones con ESC
bool funcionSalida(const string& mensaje, string& entrada) {
    cout << mensaje;
    entrada.clear();
    char digit;

    while (true) {
        digit = _getch();
        if (digit == 27) { // ESC
            cout << "\nOperacion cancelada. Volviendo al menu...\n";
            system("pause");
            return false;
        }
        else if (digit == '\r') { // Enter
            cout << endl;
            break;
        }
        else if (digit == '\b') { // Backspace
            if (!entrada.empty()) {
                entrada.pop_back();
                cout << "\b \b";
            }
        }
        else {
            entrada.push_back(digit);
            cout << digit;
        }
    }
    return true;
}

// ==================== MENÚS ====================

void menuPrincipal() {
    system("cls");
    cout << "========================================\n";
    cout << "      SISTEMA OLVA COURIER              \n";
    cout << "========================================\n";
    cout << " [1] Ingresar como Usuario\n";
    cout << " [2] Ingresar como Administrador\n";
    cout << " [3] Salir\n";
    cout << "========================================\n";
    cout << " Presione ESC para salir\n";
    cout << "----------------------------------------\n";
    cout << "Seleccione una opcion: ";
}

void menuLoginUsuario() {
    system("cls");
    cout << "========================================\n";
    cout << "         LOGIN DE USUARIO               \n";
    cout << "========================================\n";
    cout << " [1] Iniciar Sesion\n";
    cout << " [2] Registrarse\n";
    cout << " [3] Volver al Menu Principal\n";
    cout << "========================================\n";
    cout << " Presione ESC para volver\n";
    cout << "----------------------------------------\n";
    cout << "Seleccione una opcion: ";
}

void menuUsuario(const string& nombreUsuario) {
    system("cls");
    cout << "========================================\n";
    cout << "         MENU USUARIO                   \n";
    cout << "  Bienvenido: " << nombreUsuario << "\n";
    cout << "========================================\n";
    cout << " [1] Agregar Paquete\n";
    cout << " [2] Ver mis Paquetes\n";
    cout << " [3] Realizar Pago\n";
    cout << " [4] Cerrar Sesion\n";
    cout << "========================================\n";
    cout << " Presione ESC para cerrar sesion\n";
    cout << "----------------------------------------\n";
    cout << "Seleccione una opcion: ";
}

void menuAdministrador() {
    system("cls");
    cout << "========================================\n";
    cout << "       MENU ADMINISTRADOR               \n";
    cout << "========================================\n";
    cout << " [1] Ordenar Paquetes por Peso\n";
    cout << " [2] Mostrar Todos los Paquetes\n";
    cout << " [3] Calcular Costo de Envio\n";
    cout << " [4] Ver Todos los Clientes\n";
    cout << " [5] Ver Cola de Pagos\n";
    cout << " [6] Volver al Menu Principal\n";
    cout << "========================================\n";
    cout << " Presione ESC para volver\n";
    cout << "----------------------------------------\n";
    cout << "Seleccione una opcion: ";
}

// ==================== FUNCIONES DE USUARIO ====================

void agregarPaquete(int clienteID) {
    system("cls");
    cout << "========================================\n";
    cout << "       AGREGAR NUEVO PAQUETE            \n";
    cout << "========================================\n";
    cout << "(Presione ESC para cancelar)\n\n";

    string descripcion, sedeOrigen, destino, pesoStr;
    double peso = 0.0;

    if (!funcionSalida("Descripcion del paquete: ", descripcion)) return;
    if (!funcionSalida("Peso (kg): ", pesoStr)) return;

    try {
        peso = stod(pesoStr);
        if (peso <= 0) {
            cout << "El peso debe ser mayor a 0\n";
            system("pause");
            return;
        }
    }
    catch (...) {
        cout << "Peso invalido\n";
        system("pause");
        return;
    }

    if (!funcionSalida("Sede de Origen: ", sedeOrigen)) return;
    if (!funcionSalida("Sede de Destino: ", destino)) return;

    // MODIFICADO: Pasar el clienteID al crear el paquete
    Paquete<string> nuevoPaquete(descripcion, peso, sedeOrigen, destino, clienteID);
    pilaPaquetes.push(nuevoPaquete);
    pilaPaquetes.guardarPaqueteEnArchivo(nuevoPaquete, "paquetes.txt");

    cout << "\n========================================\n";
    cout << "  PAQUETE REGISTRADO EXITOSAMENTE!\n";
    cout << "  ID del Paquete: " << nuevoPaquete.id << "\n";
    cout << "  ID del Cliente: " << nuevoPaquete.clienteID << "\n";
    cout << "========================================\n";
    system("pause");
}

void verMisPaquetes(int clienteID) {
    system("cls");

    // Usar el método que lee desde archivo y filtra por cliente
    pilaPaquetes.mostrarPaquetesDeCliente("paquetes.txt", clienteID);

    system("pause");
}

void realizarPago() {
    system("cls");
    cout << "========================================\n";
    cout << "         REALIZAR PAGO                  \n";
    cout << "========================================\n";
    cout << "(Presione ESC para cancelar)\n\n";

    string producto, cantidadStr, precioStr, metodoPago;
    int cantidad;
    double precioUnitario;

    if (!funcionSalida("Producto/Servicio: ", producto)) return;
    if (!funcionSalida("Cantidad: ", cantidadStr)) return;

    try {
        cantidad = stoi(cantidadStr);
        if (cantidad <= 0) {
            cout << "La cantidad debe ser mayor a 0\n";
            system("pause");
            return;
        }
    }
    catch (...) {
        cout << "Cantidad invalida\n";
        system("pause");
        return;
    }

    if (!funcionSalida("Precio Unitario: ", precioStr)) return;

    try {
        precioUnitario = stod(precioStr);
        if (precioUnitario <= 0) {
            cout << "El precio debe ser mayor a 0\n";
            system("pause");
            return;
        }
    }
    catch (...) {
        cout << "Precio invalido\n";
        system("pause");
        return;
    }

    cout << "\nMetodos de Pago Disponibles:\n";
    cout << "1. Yape\n";
    cout << "2. Tarjeta\n";
    cout << "3. Efectivo\n";
    cout << "Seleccione metodo (1-3): ";

    char opcionPago = _getch();
    cout << opcionPago << endl;

    Pago<string> nuevoPago(producto, cantidad, precioUnitario);

    switch (opcionPago) {
    case '1':
        nuevoPago.metodo.PagoYape();
        break;
    case '2':
        nuevoPago.metodo.PagoTarjeta();
        break;
    case '3':
        nuevoPago.metodo.PagoEfectivo();
        break;
    default:
        cout << "Opcion invalida. Pago cancelado.\n";
        system("pause");
        return;
    }

    colaPagos.encolar(nuevoPago);

  
    string numBoleta = "B" + to_string(rand() % 10) + "OVS-" + to_string(rand() % 1000);
    Boleta<string> boleta(numBoleta, nuevoPago);
    boleta.guardarArchivoTexto("boleta.txt");

    cout << "\n========================================\n";
    cout << "       PAGO PROCESADO EXITOSAMENTE      \n";
    cout << "========================================\n";
    boleta.mostrarBoleta();
    system("pause");
}

// ==================== FUNCIONES DE ADMINISTRADOR ====================

void ordenarPaquetesPorPeso() {
    system("cls");
    cout << "========================================\n";
    cout << "    ORDENAR PAQUETES POR PESO (BURBUJA) \n";
    cout << "========================================\n";
    cout << "Leyendo paquetes desde paquetes.txt...\n\n";

    ifstream archivo("paquetes.txt");
    if (!archivo.is_open()) {
        cout << "\nError: No se pudo abrir el archivo paquetes.txt\n";
        cout << "Verifique que el archivo existe.\n";
        system("pause");
        return;
    }

    vector<Paquete<string>> paquetes;
    string linea;

  
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campo;
        Paquete<string> paq;

        try {
            getline(ss, campo, '|');
            paq.id = stoi(campo);

            getline(ss, campo, '|');
            paq.clienteID = stoi(campo);

            getline(ss, paq.descripcion, '|');

            getline(ss, campo, '|');
            paq.peso = stod(campo);

            getline(ss, paq.sedeOrigen, '|');
            getline(ss, paq.destino, '|');

            if (paq.id > 0 && paq.peso > 0) {
                paquetes.push_back(paq);
            }
        }
        catch (...) {
            continue;
        }
    }
    archivo.close();

    if (paquetes.empty()) {
        cout << "\nNo se encontraron paquetes validos en el archivo.\n";
        system("pause");
        return;
    }

    cout << "Se cargaron " << paquetes.size() << " paquetes del archivo.\n";
    cout << "Aplicando ordenamiento burbuja...\n\n";

    // Ordenamiento Burbuja por peso
    int n = paquetes.size();
    bool intercambio;
    int comparaciones = 0;
    int intercambios = 0;

    for (int i = 0; i < n - 1; i++) {
        intercambio = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparaciones++;
            if (paquetes[j].peso > paquetes[j + 1].peso) {
                swap(paquetes[j], paquetes[j + 1]);
                intercambio = true;
                intercambios++;
            }
        }
        if (!intercambio) break;
    }

    cout << "========================================\n";
    cout << "   PAQUETES ORDENADOS POR PESO         \n";
    cout << "   (Menor a Mayor)                     \n";
    cout << "========================================\n\n";

    for (size_t i = 0; i < paquetes.size(); i++) {
        cout << "Posicion #" << (i + 1) << "\n";
        cout << "  ID Paquete:  " << paquetes[i].id << "\n";
        cout << "  ID Cliente:  " << paquetes[i].clienteID << "\n";
        cout << "  Descripcion: " << paquetes[i].descripcion << "\n";
        cout << "  Peso:        " << fixed << setprecision(2) << paquetes[i].peso << " kg\n";
        cout << "  Ruta:        " << paquetes[i].sedeOrigen << " -> " << paquetes[i].destino << "\n";
        cout << "----------------------------------------\n";
    }

    cout << "\n========================================\n";
    cout << "ESTADISTICAS DEL ORDENAMIENTO:\n";
    cout << "  Total de paquetes: " << n << "\n";
    cout << "  Comparaciones:     " << comparaciones << "\n";
    cout << "  Intercambios:      " << intercambios << "\n";
    cout << "========================================\n";
    system("pause");
}

void mostrarTodosPaquetes() {
    system("cls");
    cout << "========================================\n";
    cout << "       TODOS LOS PAQUETES               \n";
    cout << "========================================\n";
    cout << "Leyendo paquetes desde paquetes.txt...\n\n";

    ifstream archivo("paquetes.txt");
    if (!archivo.is_open()) {
        cout << "\nError: No se pudo abrir el archivo paquetes.txt\n";
        system("pause");
        return;
    }

    cout << "========================================\n";
    cout << "      LISTADO COMPLETO DE PAQUETES     \n";
    cout << "========================================\n\n";

    string linea;
    bool hayPaquetes = false;
    int contador = 1;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campo;
        int idPaquete, idCliente;
        string desc, origen, destino;
        double peso;

        try {
            getline(ss, campo, '|');
            idPaquete = stoi(campo);

            getline(ss, campo, '|');
            idCliente = stoi(campo);

            getline(ss, desc, '|');

            getline(ss, campo, '|');
            peso = stod(campo);

            getline(ss, origen, '|');
            getline(ss, destino, '|');

            cout << "Paquete #" << contador++ << "\n";
            cout << "----------------------------------------\n";
            cout << "  ID Paquete:  " << idPaquete << "\n";
            cout << "  ID Cliente:  " << idCliente << "\n";
            cout << "  Descripcion: " << desc << "\n";
            cout << "  Peso:        " << fixed << setprecision(2) << peso << " kg\n";
            cout << "  Origen:      " << origen << "\n";
            cout << "  Destino:     " << destino << "\n";
            cout << "========================================\n\n";
            hayPaquetes = true;
        }
        catch (...) {
            continue;
        }
    }

    archivo.close();

    if (!hayPaquetes) {
        cout << "\nNo se encontraron paquetes en el archivo.\n";
    }
    else {
        cout << "Total de paquetes: " << (contador - 1) << "\n";
    }

    cout << "========================================\n";
    system("pause");
}

void calcularCostoEnvio() {
    system("cls");
    cout << "========================================\n";
    cout << "       CALCULAR COSTO DE ENVIO          \n";
    cout << "========================================\n";
    cout << "(Presione ESC para cancelar)\n\n";

    string depOrigen, depDestino, pesoStr;
    int peso;

    if (!funcionSalida("Departamento de Origen: ", depOrigen)) return;
    if (!funcionSalida("Departamento de Destino: ", depDestino)) return;
    if (!funcionSalida("Peso del paquete (kg): ", pesoStr)) return;

    try {
        peso = stoi(pesoStr);
        if (peso <= 0) {
            cout << "El peso debe ser mayor a 0\n";
            system("pause");
            return;
        }
    }
    catch (...) {
        cout << "Peso invalido\n";
        system("pause");
        return;
    }

    int costo = calcularPrecio(depOrigen, depDestino, peso);

    cout << "\n========================================\n";
    cout << "       DETALLES DEL CALCULO             \n";
    cout << "========================================\n";
    cout << " Origen:      " << depOrigen << "\n";
    cout << " Destino:     " << depDestino << "\n";
    cout << " Peso:        " << peso << " kg\n";
    cout << "----------------------------------------\n";
    cout << " COSTO TOTAL: S/ " << costo << ".00\n";
    cout << "========================================\n";
    system("pause");
}

void verTodosClientes() {
    system("cls");
    cout << "========================================\n";
    cout << "       LISTA DE CLIENTES                \n";
    cout << "========================================\n";

    listaClientes.mostrar();

    cout << "\n========================================\n";
    system("pause");
}

void verColaPagos() {
    system("cls");
    cout << "========================================\n";
    cout << "       COLA DE PAGOS PENDIENTES         \n";
    cout << "========================================\n";

    colaPagos.mostrarCola();

    cout << "\n========================================\n";
    system("pause");
}



void sistemaUsuario() {
    char tecla;
    bool salir = false;

    while (!salir) {
        menuLoginUsuario();
        tecla = _getch();

        switch (tecla) {
        case '1': { // Iniciar Sesión
            system("cls");
            cout << "\n--- INICIAR SESION ---\n";
            cout << "(Presione ESC para cancelar)\n\n";

            string correo, pass;
            if (!funcionSalida("Correo: ", correo)) break;
            if (!funcionSalida("Contrasena: ", pass)) break;

            if (listaClientes.ingresoCuenta(correo, pass)) {
                Cliente* clienteActual = listaClientes.buscarPorCorreo(correo);
                string nombreCompleto = correo;
                int clienteID = clienteActual->getID(); // OBTENER EL ID

                bool salirUsuario = false;
                while (!salirUsuario) {
                    menuUsuario(nombreCompleto);
                    char opcionUsuario = _getch();

                    switch (opcionUsuario) {
                    case '1':
                        agregarPaquete(clienteID); // PASAR EL ID
                        break;
                    case '2':
                        verMisPaquetes(clienteID); // PASAR EL ID
                        break;
                    case '3':
                        realizarPago();
                        break;
                    case '4':
                    case 27:
                        cout << "\nCerrando sesion...\n";
                        salirUsuario = true;
                        break;
                    default:
                        cout << "\nOpcion no valida\n";
                        system("pause");
                        break;
                    }
                }
            }
            else {
                cout << "\nCorreo o contrasena incorrectos.\n";
                system("pause");
            }
            break;
        }
        case '2': {
            system("cls");
            cout << "\n--- REGISTRO DE USUARIO ---\n";
            cout << "(Presione ESC para cancelar)\n\n";

            string n, a, d, p, c, pass;

            if (!funcionSalida("Nombres: ", n)) break;
            if (!funcionSalida("Apellidos: ", a)) break;
            if (!funcionSalida("DNI: ", d)) break;
            if (!funcionSalida("Pais: ", p)) break;
            if (!funcionSalida("Correo: ", c)) break;
            if (!funcionSalida("Contrasena: ", pass)) break;

            int nuevoID = Cliente::generarIDUnico("clientes.txt");
            Cliente nuevo(nuevoID, n, a, d, p, c, pass);
            listaClientes.insertar(nuevo);
            listaClientes.guardarClientes("clientes.txt");

            cout << "\n========================================\n";
            cout << "  REGISTRO EXITOSO!\n";
            cout << "  Su ID de cliente es: " << nuevoID << "\n";
            cout << "========================================\n";
            system("pause");
            break;
        }
        case '3':
        case 27:
            salir = true;
            break;
        default:
            cout << "\nOpcion no valida\n";
            system("pause");
            break;
        }
    }
}

void sistemaAdministrador() {
    system("cls");
    cout << "\n--- ACCESO ADMINISTRADOR ---\n";
    string usuario, contrasena;

    if (!funcionSalida("Usuario: ", usuario)) return;
    if (!funcionSalida("Contrasena: ", contrasena)) return;

    // log in administrador
    if (usuario != "admin" || contrasena != "admin123") {
        cout << "\nCredenciales incorrectas.\n";
        system("pause");
        return;
    }

    bool salir = false;
    while (!salir) {
        menuAdministrador();
        char tecla = _getch();

        switch (tecla) {
        case '1':
            ordenarPaquetesPorPeso();
            break;
        case '2':
            mostrarTodosPaquetes();
            break;
        case '3':
            calcularCostoEnvio();
            break;
        case '4':
            verTodosClientes();
            break;
        case '5':
            verColaPagos();
            break;
        case '6':
        case 27:
            salir = true;
            break;
        default:
            cout << "\nOpcion no valida\n";
            system("pause");
            break;
        }
    }
}



int main() {
    srand(time(0));

   
    listaClientes.cargarClientes("clientes.txt");
    pilaPaquetes.cargarDesdeArchivo("paquetes.txt");

    bool salir = false;
    while (!salir) {
        menuPrincipal();
        char tecla = _getch();

        switch (tecla) {
        case '1':
            sistemaUsuario();
            break;
        case '2':
            sistemaAdministrador();
            break;
        case '3':
        case 27:
            cout << "\n\nGracias por usar Olva Courier. Hasta pronto!\n";
            salir = true;
            break;
        default:
            cout << "\nOpcion no valida\n";
            system("pause");
            break;
        }
    }

    return 0;
}