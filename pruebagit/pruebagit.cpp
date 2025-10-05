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

    Paquete<string> nuevoPaquete(descripcion, peso, sedeOrigen, destino);
    pilaPaquetes.push(nuevoPaquete);
    pilaPaquetes.guardarPaqueteEnArchivo(nuevoPaquete, "paquetes.txt");

    cout << "\n========================================\n";
    cout << "  PAQUETE REGISTRADO EXITOSAMENTE!\n";
    cout << "  ID del Paquete: " << nuevoPaquete.id << "\n";
    cout << "========================================\n";
    system("pause");
}

void verMisPaquetes() {
    system("cls");
    cout << "========================================\n";
    cout << "         MIS PAQUETES                   \n";
    cout << "========================================\n";

    if (pilaPaquetes.estaVacia()) {
        cout << "\nNo tiene paquetes registrados.\n";
    }
    else {
        pilaPaquetes.mostrarTodos();
    }

    cout << "\n========================================\n";
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

    // Generar boleta
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

    // Leer paquetes desde el archivo
    ifstream archivo("paquetes.txt");
    if (!archivo.is_open()) {
        cout << "\nError: No se pudo abrir el archivo paquetes.txt\n";
        cout << "Verifique que el archivo existe.\n";
        system("pause");
        return;
    }

    vector<Paquete<string>> paquetes;
    string linea;

    // Leer todas las líneas del archivo
    while (getline(archivo, linea)) {
        // Buscar líneas que contienen ID (formato: "ID:                 569")
        if (linea.find("ID:") != string::npos) {
            Paquete<string> paq;

            // Extraer ID
            size_t posID = linea.find("ID:") + 20;
            string idStr = linea.substr(posID);
            idStr.erase(0, idStr.find_first_not_of(" \t"));
            idStr.erase(idStr.find_last_not_of(" \t\n\r") + 1);

            try {
                paq.id = stoi(idStr);
            }
            catch (...) {
                continue; // Si falla, ignorar este paquete
            }

            // Leer descripción
            if (getline(archivo, linea) && linea.find("Descripcion:") != string::npos) {
                size_t pos = linea.find("Descripcion:") + 20;
                paq.descripcion = linea.substr(pos);
                paq.descripcion.erase(0, paq.descripcion.find_first_not_of(" \t"));
                paq.descripcion.erase(paq.descripcion.find_last_not_of(" \t\n\r") + 1);
            }

            // Leer peso
            if (getline(archivo, linea) && linea.find("Peso:") != string::npos) {
                size_t pos = linea.find("Peso:") + 20;
                string pesoStr = linea.substr(pos);
                pesoStr = pesoStr.substr(0, pesoStr.find(" kg"));
                pesoStr.erase(0, pesoStr.find_first_not_of(" \t"));

                try {
                    paq.peso = stod(pesoStr);
                }
                catch (...) {
                    paq.peso = 0.0;
                }
            }

            // Leer sede origen
            if (getline(archivo, linea) && linea.find("Sucursal Origen:") != string::npos) {
                size_t pos = linea.find("Sucursal Origen:") + 20;
                paq.sedeOrigen = linea.substr(pos);
                paq.sedeOrigen.erase(0, paq.sedeOrigen.find_first_not_of(" \t"));
                paq.sedeOrigen.erase(paq.sedeOrigen.find_last_not_of(" \t\n\r") + 1);
            }

            // Leer sede destino
            if (getline(archivo, linea) && linea.find("Sucursal Destino:") != string::npos) {
                size_t pos = linea.find("Sucursal Destino:") + 20;
                paq.destino = linea.substr(pos);
                paq.destino.erase(0, paq.destino.find_first_not_of(" \t"));
                paq.destino.erase(paq.destino.find_last_not_of(" \t\n\r") + 1);
            }

            // Agregar paquete al vector si tiene datos válidos
            if (paq.id > 0 && paq.peso > 0) {
                paquetes.push_back(paq);
            }
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

    // Mostrar paquetes ordenados
    cout << "========================================\n";
    cout << "   PAQUETES ORDENADOS POR PESO         \n";
    cout << "   (Menor a Mayor)                     \n";
    cout << "========================================\n\n";

    for (size_t i = 0; i < paquetes.size(); i++) {
        cout << "Posicion #" << (i + 1) << "\n";
        cout << "  ID:          " << paquetes[i].id << "\n";
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

    // Leer paquetes desde el archivo
    ifstream archivo("paquetes.txt");
    if (!archivo.is_open()) {
        cout << "\nError: No se pudo abrir el archivo paquetes.txt\n";
        cout << "Verifique que el archivo existe.\n";
        system("pause");
        return;
    }

    vector<Paquete<string>> paquetes;
    string linea;

    // Leer todas las líneas del archivo
    while (getline(archivo, linea)) {
        // Buscar líneas que contienen ID
        if (linea.find("ID:") != string::npos) {
            Paquete<string> paq;

            // Extraer ID
            size_t posID = linea.find("ID:") + 20;
            string idStr = linea.substr(posID);
            idStr.erase(0, idStr.find_first_not_of(" \t"));
            idStr.erase(idStr.find_last_not_of(" \t\n\r") + 1);

            try {
                paq.id = stoi(idStr);
            }
            catch (...) {
                continue;
            }

            // Leer descripción
            if (getline(archivo, linea) && linea.find("Descripcion:") != string::npos) {
                size_t pos = linea.find("Descripcion:") + 20;
                paq.descripcion = linea.substr(pos);
                paq.descripcion.erase(0, paq.descripcion.find_first_not_of(" \t"));
                paq.descripcion.erase(paq.descripcion.find_last_not_of(" \t\n\r") + 1);
            }

            // Leer peso
            if (getline(archivo, linea) && linea.find("Peso:") != string::npos) {
                size_t pos = linea.find("Peso:") + 20;
                string pesoStr = linea.substr(pos);
                pesoStr = pesoStr.substr(0, pesoStr.find(" kg"));
                pesoStr.erase(0, pesoStr.find_first_not_of(" \t"));

                try {
                    paq.peso = stod(pesoStr);
                }
                catch (...) {
                    paq.peso = 0.0;
                }
            }

            // Leer sede origen
            if (getline(archivo, linea) && linea.find("Sucursal Origen:") != string::npos) {
                size_t pos = linea.find("Sucursal Origen:") + 20;
                paq.sedeOrigen = linea.substr(pos);
                paq.sedeOrigen.erase(0, paq.sedeOrigen.find_first_not_of(" \t"));
                paq.sedeOrigen.erase(paq.sedeOrigen.find_last_not_of(" \t\n\r") + 1);
            }

            // Leer sede destino
            if (getline(archivo, linea) && linea.find("Sucursal Destino:") != string::npos) {
                size_t pos = linea.find("Sucursal Destino:") + 20;
                paq.destino = linea.substr(pos);
                paq.destino.erase(0, paq.destino.find_first_not_of(" \t"));
                paq.destino.erase(paq.destino.find_last_not_of(" \t\n\r") + 1);
            }

            // Agregar paquete al vector si tiene datos válidos
            if (paq.id > 0) {
                paquetes.push_back(paq);
            }
        }
    }
    archivo.close();

    if (paquetes.empty()) {
        cout << "\nNo se encontraron paquetes en el archivo.\n";
        system("pause");
        return;
    }

    // Mostrar todos los paquetes
    cout << "========================================\n";
    cout << "      LISTADO COMPLETO DE PAQUETES     \n";
    cout << "========================================\n\n";

    for (size_t i = 0; i < paquetes.size(); i++) {
        cout << "Paquete #" << (i + 1) << "\n";
        cout << "----------------------------------------\n";
        cout << "  ID:          " << paquetes[i].id << "\n";
        cout << "  Descripcion: " << paquetes[i].descripcion << "\n";
        cout << "  Peso:        " << fixed << setprecision(2) << paquetes[i].peso << " kg\n";
        cout << "  Origen:      " << paquetes[i].sedeOrigen << "\n";
        cout << "  Destino:     " << paquetes[i].destino << "\n";
        cout << "========================================\n\n";
    }

    cout << "Total de paquetes registrados: " << paquetes.size() << "\n";
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

// ==================== SISTEMAS DE LOGIN ====================

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

                bool salirUsuario = false;
                while (!salirUsuario) {
                    menuUsuario(nombreCompleto);
                    char opcionUsuario = _getch();

                    switch (opcionUsuario) {
                    case '1':
                        agregarPaquete(clienteActual->getID());
                        break;
                    case '2':
                        verMisPaquetes();
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
        case '2': { // Registrarse
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

    // Credenciales de administrador
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

// ==================== MAIN ====================

int main() {
    srand(time(0));

    // Cargar datos existentes
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