#pragma once
#include "Librerias.h"
#include "NodoPago.h"


class MetodoPago {
private:
    string tipoPago;
public:
    MetodoPago() : tipoPago("Sin definir") {}

    void PagoYape() {
        tipoPago = "Yape";
    }

    void PagoTarjeta() {
        tipoPago = "Tarjeta";
    }

    void PagoEfectivo() {
        tipoPago = "Efectivo";
    }

    string getTipoPago() const {
        return tipoPago;
    }

    void setTipoPago(const string& tipo) {
        tipoPago = tipo;
    }
};


template <class T>
class Pago {
private:
    T producto;
    int cantidad;
    double precioUnitario;

public:
    MetodoPago metodo;

    Pago(T prod = T(), int cant = 0, double precio = 0.0)
        : producto(prod), cantidad(cant), precioUnitario(precio) {}


    string ajustarTexto(const string& texto, size_t ancho) const {
        if (texto.size() > ancho) {
            // recorta texto
            return texto.substr(0, ancho);
        }
        else
        {
      
            return texto + string(ancho - texto.size(), ' ');
        }
    }

    void imprimirEnBloques(const string& texto, size_t ancho, const string& prefijoPrimera, const string& prefijoResto) const {
        size_t inicio = 0;
        bool primeraLinea = true;

        while (inicio < texto.size()) {
            string bloque = texto.substr(inicio, ancho);
            if (primeraLinea) {
                cout << prefijoPrimera << left << setw(ancho) << bloque << "|\n";
                primeraLinea = false;
            }
            else {
                cout << prefijoResto << left << setw(ancho) << bloque << "|\n";
            }
            inicio += ancho;
        }

        
    }

    //funciones para calcular

    double calcularSubtotal() {
        function<double(double, int)> subtotal = [&](double unit, int n) {
            return n == 0 ? 0.0 : unit + subtotal(unit, n - 1);
            };
        return subtotal(precioUnitario, cantidad);
    }

    double calcularIGV() {
        function<double(double)> igv = [&](double sub) {
            return sub * 0.18;
            };
        return igv(calcularSubtotal());
    }
 
    double calcularTotal() {
        function<double(double, int)> subtotal = [&](double unit, int n) {
            return n == 0 ? 0.0 : unit + subtotal(unit, n - 1);
            };

        function<double(double)> igv = [&](double sub) {
            return sub * 0.18;
            };

        double sub = subtotal(precioUnitario, cantidad);
        return sub + igv(sub);
    }


    string convertirCentena(int num) {
        const string unidades[] = { "", "UNO", "DOS", "TRES", "CUATRO", "CINCO",
                                   "SEIS", "SIETE", "OCHO", "NUEVE",
                                   "DIEZ", "ONCE", "DOCE", "TRECE", "CATORCE", "QUINCE",
                                   "DIECISEIS", "DIECISIETE", "DIECIOCHO", "DIECINUEVE" };
        const string decenas[] = { "", "", "VEINTE", "TREINTA", "CUARENTA", "CINCUENTA",
                                  "SESENTA", "SETENTA", "OCHENTA", "NOVENTA" };
        const string centenas[] = { "", "CIENTO", "DOSCIENTOS", "TRESCIENTOS", "CUATROCIENTOS",
                                   "QUINIENTOS", "SEISCIENTOS", "SETECIENTOS",
                                   "OCHOCIENTOS", "NOVECIENTOS" };

        if (num == 0) { return "CERO"; }
        if (num == 100) { return "CIEN"; }

        string texto = "";

        int c = num / 100;
        int d = (num % 100) / 10;
        int u = num % 10;
        int dosDig = num % 100;

        if (c > 0) {
            texto += centenas[c] + " ";
        }
        if (dosDig < 20) {
            if (dosDig > 0) {
                texto += unidades[dosDig];
            }
        }
        else {
            texto += decenas[d];
            if (u > 0) { texto += " Y " + unidades[u]; }
        }
        return texto;
    }
  
    string numeroATexto(long long num) {
        if (num == 0) return "CERO";

        string texto = "";
        int miles = num / 1000;
        int resto = num % 1000;

        if (miles > 0) {
            if (miles == 1) texto += "MIL ";
            else texto += convertirCentena(miles) + " MIL ";
        }

        if (resto > 0) texto += convertirCentena(resto);

        return texto;
    }
  
    string montoEnTexto() {
        double total = calcularTotal();

        long long parteEntera = static_cast<long long>(total);
        int centimos = static_cast<int>((total - parteEntera) * 100 + 0.5);

        string texto = numeroATexto(parteEntera) + " SOLES";

        if (centimos > 0) {
            ostringstream oss;
            oss << setfill('0') << setw(2) << centimos;
            texto += " CON " + oss.str() + "/100";
        }
        else {
            texto += " CON 00/100";
        }

        return texto;
    }


    T getProducto() const { return producto; }
    int getCantidad() const { return cantidad; }
    double getPrecioUnitario() const { return precioUnitario; }
    double calcularTotal() const { return cantidad * precioUnitario; }

    void setProducto(T prod) { producto = prod; }
    void setCantidad(int cant) { cantidad = cant; }
    void setPrecioUnitario(double precio) { precioUnitario = precio; }

   
    void mostrarPagos() {
        cout << "|-------------------------------------------|\n";
        cout << "| Paquete                      Cant  Importe|\n";
        cout << "| " << setw(25) << left << producto
            << setw(5) << right << cantidad
            << setw(9) << right << fixed << setprecision(2) << precioUnitario << " |\n";
        cout << "|-------------------------------------------|\n";
        cout << "| OP. GRAVADA :                  S/" << setw(7) << right << fixed << setprecision(2) << calcularSubtotal() << "  |\n";
        cout << "| IGV (18%) :                    S/" << setw(7) << right << fixed << setprecision(2) << calcularIGV() << "  |\n";
        cout << "| TOTAL A PAGAR :                S/" << setw(7) << right << fixed << setprecision(2) << calcularTotal() << "  |\n";
        cout << "|-------------------------------------------|\n";
        cout << "| Metodo de Pago: " << ajustarTexto(metodo.getTipoPago(), 26) << "|\n";
        imprimirEnBloques(montoEnTexto(), 37, "| Son: ", "|      ");
        cout << "|                                           |\n";
        cout << "|-------------------------------------------|\n";
    }

    void cargarPagoTexto(const string& pagoStr) {
        istringstream ss(pagoStr);
        string campo, metodoPagoStr;

        if (!getline(ss, campo, '|')) return;
        producto = campo;

        if (!getline(ss, campo, '|')) return;
        cantidad = stoi(campo);

        if (!getline(ss, campo, '|')) return;
        precioUnitario = stod(campo);

        if (!getline(ss, metodoPagoStr, '|')) return;
        metodo.setTipoPago(metodoPagoStr);
    }
};


template <class T>
class GestorPago {
private:
    NodoPago<T>* cabeza;

public:
    GestorPago() : cabeza(nullptr) {}

    void registrarPago(T pago) {
        NodoPago<T>* nuevo = new NodoPago<T>(pago);
        if (!cabeza) {
            cabeza = nuevo;
        }
        else {
            NodoPago<T>* temp = cabeza;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = nuevo;
        }
    }

    void mostrarPagos() const {
        if (!cabeza) {
            cout << "No hay pagos registrados.\n";
            return;
        }
        NodoPago<T>* temp = cabeza;
        int contador = 1;
        cout << "\n===== LISTA DE PAGOS =====\n";
        while (temp) {
            cout << "\n--- Pago #" << contador++ << " ---\n";
            temp->dato.mostrarPagos();
            temp = temp->next;
        }
    }

    ~GestorPago() {
        NodoPago<T>* temp;
        while (cabeza) {
            temp = cabeza;
            cabeza = cabeza->next;
            delete temp;
        }
        cabeza = nullptr;
    }
};