#pragma once
#include "Librerias.h"
#include "Paquete.h"
#include "GestorCliente.h"
#include "GestorPago.h"
#include "Boleta.h"
#include "PilaPaquete.h"
#include "NodoPila.h"
#include "ColaPago.h"
#include "Tranporte.h"
#include "HashTablePaquete.h"
#include "Dijkstra.h"
#include "ArbolPaquete.h"

class SistemaOlvaCourier {
private:

    PilaPaquete<Paquete<string>> pilaPaquetes;
    GestoCliente<Cliente> listaClientes;
    ColaPago<Pago<string>> colaPagos;
    Transporte sistemaTransporte;
    HashTablePaquete<string> hashPaquetes;
    ArbolPaquete<string> arbolPaquetes;



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
            else if (digit == '\b') { // espacio
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



    void mostrarLogoOLVA() {
        cout << "#####################   ##########             ############          #############   ###############################\n";
        cout << "#####################   ##########             ############          #############   ###############################\n";
        cout << "#####################   ##########             ############          #############   ###############################\n";
        cout << "#####################   ##########             ############          #############   ###########           #########\n";
        cout << "######        #######   ##########             ############          #############   ###########           #########\n";
        cout << "######        #######   ##########             ############          #############   ###########           #########\n";
        cout << "######        #######   ##########             ############          #############   ###########           #########\n";
        cout << "######        #######   ##########             ############          #############   ###########           #########\n";
        cout << "######        #######   ##########             ############          #############   ###########           #########\n";
        cout << "######        #######   ##########             ############          #############   ###########           #########\n";
        cout << "######        #######   ##########             ############          #############   ###########           #########\n";
        cout << "######        #######   ##########             ############          #############   ###############################\n";
        cout << "######        #######   ##########             ############          ############    ###############################\n";
        cout << "######        #######   ##########             ############         ############     ###########           #########\n";
        cout << "######        #######   ##########             ############        ############      ###########           #########\n";
        cout << "######        #######   ##########             ############       ############       ###########           #########\n";
        cout << "######        #######   ##########             ############      ###########         ###########           #########\n";
        cout << "######        #######   ##########             ############     ###########          ###########           #########\n";
        cout << "#####################   ####################   ############    ###########           ###########           #########\n";
        cout << "#####################   ####################   ############   ###########            ###########           #########\n";
        cout << "#####################   ####################   ############ ############             ###########           #########\n";
        cout << "#####################   ####################   ########################              ###########           #########\n";
    }

    void menuPrincipal() {
        system("cls");
        mostrarLogoOLVA();
        cout << "\n";
        cout << "=====================================================================================================\n";
        cout << "                                    SISTEMA OLVA COURIER                                             \n";
        cout << "=====================================================================================================\n";
        cout << " [1] Ingresar como Usuario\n";
        cout << " [2] Ingresar como Administrador\n";
        cout << " [3] Salir\n";
        cout << "=====================================================================================================\n";
        cout << " Presione ESC para salir\n";
        cout << "-----------------------------------------------------------------------------------------------------\n";
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
        cout << " [3] Calcular costo de Envio\n";
        cout << " [4] Realizar Pago\n";
        cout << " [5] Cerrar Sesion\n";
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
        cout << " [3] Calcular costo de Envio\n";
        cout << " [4] Ver Todos los Clientes\n";
        cout << " [5] Ver Cola de Pagos\n";
        cout << " [6] Procesar Siguiente Pago\n";
        cout << " [7] Buscar Paquete por ID (Hash)\n";
        cout << " [8] Ver Estadisticas Hash Table\n";
        cout << " [9] Buscar por Rango de Peso\n";
        cout << " [10] Ver Red de Rutas\n";
        cout << " [11] Agregar Nueva Ruta\n";
        cout << " [12] Agregar Nueva Ubicacion\n";
        cout << " [13] Analizar Eficiencia de Rutas\n";
        cout << " [14] Comparar Rutas Alternativas\n";
        cout << "========================================\n";
        cout << " Presione ESC para volver\n";
        cout << "----------------------------------------\n";
        cout << "Seleccione una opcion: ";
    }


    void agregarPaqueteConAnalisis(int clienteID) {
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

       
        cout << "\n--- ANALISIS DE RUTA ---\n";

        sistemaTransporte.mostrarRutaDetallada(sedeOrigen, destino, (int)peso);

        cout << "\n¿Desea confirmar el registro del paquete? (S/N): ";
        char confirmar = _getch();
        cout << confirmar << "\n";

        if (confirmar != 'S' && confirmar != 's') {
            cout << "Registro cancelado.\n";
            system("pause");
            return;
        }

        Paquete<string> nuevoPaquete(descripcion, peso, sedeOrigen, destino, clienteID);

       
        pilaPaquetes.push(nuevoPaquete);
        hashPaquetes.insertar(nuevoPaquete);
        arbolPaquetes.insertar(nuevoPaquete);
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
        pilaPaquetes.mostrarPaquetesDeCliente("paquetes.txt", clienteID);
        system("pause");
    }

    void realizarPago() {
        system("cls");
        cout << "========================================\n";
        cout << "         REALIZAR PAGO DE ENVIO         \n";
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

        cout << "\nCalculando ruta optima...\n";
        sistemaTransporte.mostrarRutaDetallada(depOrigen, depDestino, peso);

     
        double precioTotal = sistemaTransporte.calcularPrecio(depOrigen, depDestino, peso);

        cout << "\nMetodos de Pago Disponibles:\n";
        cout << "1. Yape\n";
        cout << "2. Tarjeta\n";
        cout << "3. Efectivo\n";
        cout << "4. Cancelar\n";
        cout << "Seleccione metodo (1-4): ";

        char opcionPago = _getch();
        cout << opcionPago << endl;

        if (opcionPago == '4' || opcionPago == 27) {
            cout << "Pago cancelado.\n";
            system("pause");
            return;
        }

        string descripcionServicio = "Envio " + depOrigen + " -> " + depDestino + " (" + to_string(peso) + " kg)";
        Pago<string> nuevoPago(descripcionServicio, 1, (int)precioTotal);

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

        ofstream archivoPagos("pagos_pendientes.txt", ios::app);
        if (archivoPagos.is_open()) {
            archivoPagos << nuevoPago.getProducto() << "|"
                << nuevoPago.getCantidad() << "|"
                << fixed << setprecision(2) << nuevoPago.getPrecioUnitario() << "|"
                << nuevoPago.metodo.getTipoPago() << "\n";
            archivoPagos.close();
        }

        string numBoleta = "B" + to_string(rand() % 10) + "OVS-" + to_string(rand() % 1000);
        Boleta<string> boleta(numBoleta, nuevoPago);
        boleta.guardarArchivoTexto("boleta.txt");

        cout << "\n========================================\n";
        cout << "       PAGO PROCESADO EXITOSAMENTE      \n";
        cout << "========================================\n";
        boleta.mostrarBoleta();

        cout << "\nEl pago ha sido agregado a la cola de pagos pendientes.\n";
        cout << "Pagos en cola: " << colaPagos.contarElementos() << "\n";
        system("pause");
    }

    void ordenarPaquetesPorPeso() {
        system("cls");
        cout << "========================================\n";
        cout << "    ORDENAR PAQUETES POR PESO (BST)    \n";
        cout << "========================================\n";
        cout << "Leyendo paquetes desde paquetes.txt...\n\n";

        ArbolPaquete<string> arbolPaquetes;

        ifstream archivo("paquetes.txt");
        if (!archivo.is_open()) {
            cout << "\nError: No se pudo abrir el archivo paquetes.txt\n";
            system("pause");
            return;
        }

        string linea;
        int cargados = 0;
        int errores = 0;

        arbolPaquetes.cargarDesdeArchivo("paquetes.txt");

        arbolPaquetes.mostrarEnOrdenConEstadisticas();

        arbolPaquetes.mostrarEnOrden();

        system("pause");
    }



    void mostrarTodosPaquetes() {
        system("cls");
        cout << "========================================\n";
        cout << "       TODOS LOS PAQUETES               \n";
        cout << "========================================\n";

        ifstream archivo("paquetes.txt");
        if (!archivo.is_open()) {
            cout << "\nError: No se pudo abrir el archivo paquetes.txt\n";
            system("pause");
            return;
        }

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

        Grafo<double>* grafo = sistemaTransporte.getGrafoRutas();
        vector<string> ciudadesDisponibles = grafo->obtenerTodosLosNombres();

        cout << "Ciudades disponibles:\n";
        if (ciudadesDisponibles.empty()) {
            cout << "  (No hay ciudades cargadas en el sistema).\n\n";
        }
        else {
            for (size_t i = 0; i < ciudadesDisponibles.size(); i++) {
                cout << "  " << i + 1 << ". " << ciudadesDisponibles[i] << "\n";
            }
        }
        cout << "----------------------------------------\n\n";

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

        sistemaTransporte.mostrarRutaDetallada(depOrigen, depDestino, peso);

        system("pause");
    }

    void verRedRutas() {
        system("cls");
        cout << "========================================\n";
        cout << "       RED DE RUTAS DISPONIBLES         \n";
        cout << "========================================\n";
        sistemaTransporte.mostrarRedRutas();
        cout << "\n========================================\n";
        system("pause");
    }

    void agregarNuevaRuta() {
        system("cls");
        cout << "========================================\n";
        cout << "       AGREGAR NUEVA RUTA               \n";
        cout << "========================================\n";
        cout << "(Presione ESC para cancelar)\n\n";

        string origen, destino, distanciaStr;

        if (!funcionSalida("Ciudad de Origen: ", origen)) return;
        if (!funcionSalida("Ciudad de Destino: ", destino)) return;
        if (!funcionSalida("Distancia (km): ", distanciaStr)) return;

        try {
            double distancia = stod(distanciaStr);
            if (distancia <= 0) {
                cout << "La distancia debe ser mayor a 0\n";
                system("pause");
                return;
            }

            sistemaTransporte.agregarRuta(origen, destino, distancia);

            cout << "\n========================================\n";
            cout << "       RUTA AGREGADA EXITOSAMENTE      \n";
            cout << "========================================\n";
            cout << "Origen: " << origen << "\n";
            cout << "Destino: " << destino << "\n";
            cout << "Distancia: " << distancia << " km\n";
            cout << "========================================\n";
        }
        catch (...) {
            cout << "Error: Distancia invalida\n";
        }

        system("pause");
    }

    void agregarNuevaUbicacion() {
        system("cls");
        cout << "========================================\n";
        cout << "     AGREGAR NUEVA UBICACION            \n";
        cout << "========================================\n";
        cout << "(Presione ESC para cancelar)\n\n";

        string idStr, nombre;

        if (!funcionSalida("ID de la ubicacion: ", idStr)) return;
        if (!funcionSalida("Nombre de la ubicacion: ", nombre)) return;

        try {
            int id = stoi(idStr);

            sistemaTransporte.agregarUbicacion(id, nombre);

            cout << "\n========================================\n";
            cout << "    UBICACION AGREGADA EXITOSAMENTE    \n";
            cout << "========================================\n";
            cout << "ID: " << id << "\n";
            cout << "Nombre: " << nombre << "\n";
            cout << "========================================\n";
            cout << "\nAhora puede agregar rutas desde/hacia esta ubicacion.\n";
        }
        catch (...) {
            cout << "Error: ID invalido\n";
        }

        system("pause");
    }

    void analizarEficienciaRutas() {
        system("cls");
        cout << "========================================\n";
        cout << "     ANALISIS DE EFICIENCIA DE RUTAS    \n";
        cout << "========================================\n\n";

        struct RutaComun {
            string origen;
            string destino;
            int peso;
        };

        vector<RutaComun> rutasComunes = {
            {"Lima", "Arequipa", 20},
            {"Lima", "Cusco", 25},
            {"Lima", "Trujillo", 15},
            {"Arequipa", "Cusco", 30},
            {"Puno", "Lima", 36},
            {"Lima", "Cangallo", 40},
            {"Cusco", "Ica", 28},
        };

        cout << "Analizando rutas mas comunes...\n\n";
        cout << left << setw(15) << "Origen"
            << setw(15) << "Destino"
            << setw(12) << "Peso(kg)"
            << setw(15) << "Distancia"
            << setw(15) << "Precio" << "\n";
        cout << string(72, '-') << "\n";

        for (const auto& ruta : rutasComunes) {
           
            Dijkstra<double> dijkstra(*sistemaTransporte.getGrafoRutas());
            ResultadoDijkstra<double> resultado =
                dijkstra.ejecutarPorNombre(ruta.origen, ruta.destino);

            if (resultado.exito) {
                double precio = sistemaTransporte.calcularPrecio(
                    ruta.origen, ruta.destino, ruta.peso);

                cout << left << setw(15) << ruta.origen
                    << setw(15) << ruta.destino
                    << setw(12) << ruta.peso
                    << setw(15) << (to_string((int)resultado.distanciaTotal) + " km")
                    << "S/ " << fixed << setprecision(2) << precio << "\n";
            }
        }

        cout << "\n========================================\n";

        AnalizadorRutas<double> analizador(*sistemaTransporte.getGrafoRutas());
        analizador.mostrarEstadisticasRed();

        system("pause");
    }

    void compararRutasAlternativas() {
        system("cls");
        cout << "========================================\n";
        cout << "     COMPARAR RUTAS ALTERNATIVAS        \n";
        cout << "========================================\n";
        cout << "(Presione ESC para cancelar)\n\n";

        string origen, destino, pesoStr;
        int peso;

        if (!funcionSalida("Ciudad de Origen: ", origen)) return;
        if (!funcionSalida("Ciudad de Destino: ", destino)) return;
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

        cout << "\n--- RUTA OPTIMA (Dijkstra) ---\n";
        sistemaTransporte.mostrarRutaDetallada(origen, destino, peso);

        cout << "\n¿Desea ver estadisticas de la red? (S/N): ";
        char opcion = _getch();
        cout << opcion << "\n\n";

        if (opcion == 'S' || opcion == 's') {
            AnalizadorRutas<double> analizador(*sistemaTransporte.getGrafoRutas());
            analizador.mostrarEstadisticasRed();
        }

        system("pause");
    }


    void verTodosClientes() {
        system("cls");
        cout << "========================================\n";
        cout << "       LISTA DE CLIENTES                \n";
        cout << "========================================\n\n";

        listaClientes.mostrar();

        cout << "\n========================================\n";
        system("pause");
    }

    void verColaPagos() {
        system("cls");
        colaPagos.mostrarCola();
        cout << "\nPagos totales en cola: " << colaPagos.contarElementos() << "\n";
        system("pause");
    }

    void procesarSiguientePago() {
        system("cls");
        cout << "========================================\n";
        cout << "      PROCESAR SIGUIENTE PAGO           \n";
        cout << "========================================\n\n";

        if (colaPagos.estaVacia()) {
            cout << "No hay pagos pendientes para procesar.\n";
            system("pause");
            return;
        }

        cout << "Procesando el siguiente pago de la cola...\n\n";

        bool procesado = colaPagos.desencolar();

        if (procesado) {
            cout << "========================================\n";
            cout << "  PAGO PROCESADO EXITOSAMENTE          \n";
            cout << "========================================\n";
            cout << "El pago ha sido retirado de la cola.\n";
            cout << "Pagos restantes en cola: " << colaPagos.contarElementos() << "\n";

            ofstream temp("pagos_temp.txt");
            ifstream original("pagos_pendientes.txt");

            if (original.is_open() && temp.is_open()) {
                string linea;
                bool primera = true;
                while (getline(original, linea)) {
                    if (primera) {
                        primera = false;
                        continue;
                    }
                    temp << linea << "\n";
                }
                original.close();
                temp.close();

                remove("pagos_pendientes.txt");
                rename("pagos_temp.txt", "pagos_pendientes.txt");
            }
        }
        else {
            cout << "Error al procesar el pago.\n";
        }

        system("pause");
    }



    void sistemaUsuario() {
        bool salir = false;

        while (!salir) {
            menuLoginUsuario();

            string opcionPrincipalStr;
            int opcionPrincipal = -1;

            if (!funcionSalida("", opcionPrincipalStr)) {
                opcionPrincipal = 3; 
            }
            else {
                try {
                    if (!opcionPrincipalStr.empty()) {
                        opcionPrincipal = stoi(opcionPrincipalStr);
                    }
                }
                catch (...) {
                    opcionPrincipal = -1;
                }
            }

            switch (opcionPrincipal) {
            case 1: {
                system("cls");
                cout << "\n--- INICIAR SESION ---\n";
                cout << "(Presione ESC para cancelar)\n\n";

                string correo, pass;
                if (!funcionSalida("Correo: ", correo)) break;
                if (!funcionSalida("Contrasena: ", pass)) break;

                if (listaClientes.ingresoCuenta(correo, pass)) {
                    Cliente* clienteActual = listaClientes.buscarPorCorreo(correo);
                    string nombreCompleto = correo;
                    int clienteID = clienteActual->getID();

                    bool salirUsuario = false;
                    while (!salirUsuario) {
                        menuUsuario(nombreCompleto);

                        string opcionUsuarioStr;
                        int opcionUsuario = -1;

                        if (!funcionSalida("", opcionUsuarioStr)) {
                            opcionUsuario = 5; // ESC
                        }
                        else {
                            try {
                                if (!opcionUsuarioStr.empty()) {
                                    opcionUsuario = stoi(opcionUsuarioStr);
                                }
                            }
                            catch (...) {
                                opcionUsuario = -1;
                            }
                        }

                        switch (opcionUsuario) {
                        case 1:
                            agregarPaqueteConAnalisis(clienteID);
                            break;
                        case 2:
                            verMisPaquetes(clienteID);
                            break;
                        case 3:
                            calcularCostoEnvio();
                            break;
                        case 4:
                            realizarPago();
                            break;
                        case 5:
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
            case 2: {
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
            case 3:
                salir = true;
                break;
            default:
                cout << "\nOpcion no valida\n";
                system("pause");
                break;
            }
        }
    }

    void buscarPaquetePorID() {
        system("cls");
        cout << "========================================\n";
        cout << "     BUSCAR PAQUETE POR ID (HASH)      \n";
        cout << "========================================\n";

        string idStr;
        if (!funcionSalida("Ingrese ID del paquete: ", idStr)) return;

        try {
            int id = stoi(idStr);
            Paquete<string>* paquete = hashPaquetes.buscar(id);

            if (paquete) {
                cout << "\n¡PAQUETE ENCONTRADO!\n";
                cout << "========================================\n";
                paquete->mostrarInfoPaquete();
                cout << "========================================\n";
            }
            else {
                cout << "\nPaquete no encontrado con ID: " << id << "\n";
            }
        }
        catch (...) {
            cout << "ID invalido\n";
        }

        system("pause");
    }

    void verEstadisticasHash() {
        system("cls");
        hashPaquetes.mostrarEstadisticas();
        system("pause");
    }

    void buscarPorRangoPeso() {
        system("cls");
        string pesoMinStr, pesoMaxStr;

        if (!funcionSalida("Peso minimo (kg): ", pesoMinStr)) return;
        if (!funcionSalida("Peso maximo (kg): ", pesoMaxStr)) return;

        try {
            double pesoMin = stod(pesoMinStr);
            double pesoMax = stod(pesoMaxStr);
            hashPaquetes.buscarPorRangoPeso(pesoMin, pesoMax);
        }
        catch (...) {
            cout << "Valores invalidos\n";
        }

        system("pause");
    }


    void sistemaAdministrador() {
        bool salir = false;
        while (!salir) {
            menuAdministrador();

            string opcionStr;
            int opcion = -1;

           
            if (!funcionSalida("", opcionStr)) {
                salir = true; 
                continue;
            }

         
            try {
                if (!opcionStr.empty()) {
                    opcion = stoi(opcionStr);
                }
            }
            catch (...) {
                opcion = -1;
            }

            switch (opcion) {
            case 1:
                ordenarPaquetesPorPeso();
                break;
            case 2:
                mostrarTodosPaquetes();
                break;
            case 3:
                calcularCostoEnvio();
                break;
            case 4:
                verTodosClientes();
                break;
            case 5:
                verColaPagos();
                break;
            case 6:
                procesarSiguientePago();
                break;
            case 7:
                buscarPaquetePorID();
                break;
            case 8:
                verEstadisticasHash();
                break;
            case 9:
                buscarPorRangoPeso();
                break;
            case 10:
                verRedRutas();
                break;
            case 11:
                agregarNuevaRuta();
                break;
            case 12:
                agregarNuevaUbicacion();
                break;
            case 13:
                analizarEficienciaRutas();
                break;
            case 14:
                compararRutasAlternativas();
                break;
            case 27:  
                salir = true;
                break;
            default:
                cout << "\nOpcion no valida. Por favor, ingrese un numero de opcion valido.\n";
                system("pause");
                break;
            }
        }
    }


public:

    SistemaOlvaCourier() {
        srand((unsigned int)time(0));
    }



    void inicializar() {
        cout << "Cargando datos del sistema...\n";
        listaClientes.cargarClientes("clientes.txt");
        pilaPaquetes.cargarDesdeArchivo("paquetes.txt");
        colaPagos.cargarColaPagos("pagos_pendientes.txt");
        hashPaquetes.cargarDesdeArchivo("paquetes.txt");
        arbolPaquetes.cargarDesdeArchivo("paquetes.txt");

        cout << "Datos cargados exitosamente.\n\n";
        Sleep(1000);
    }

    void ejecutar() {
        bool salir = false;
        while (!salir) {
            menuPrincipal();

           
            string opcionStr;
            int opcion = -1;

            if (!funcionSalida("", opcionStr)) {
                opcion = 3; // ESC  salir 
            }
            else {
               
                try {
                    if (!opcionStr.empty()) {
                        opcion = stoi(opcionStr);
                    }
                }
                catch (...) {
                    opcion = -1; 
                }
            }
          

            switch (opcion) {
            case 1:
                sistemaUsuario();
                break;
            case 2:
                sistemaAdministrador();
                break;
            case 3:
                cout << "\n\nGracias por usar Olva Courier. Hasta pronto!\n";
                salir = true;
                break;
            default:
                cout << "\nOpcion no valida\n";
                system("pause");
                break;
            }
        }
    }
};