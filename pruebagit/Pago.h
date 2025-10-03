#pragma once
#include "Librerias.h"
#include "NodoPago.h"

class metodoPago {
public:
	string tipoPago;

	metodoPago(string tipo = "")
		: tipoPago(tipo) {
	}

	void PagoYape() { tipoPago = "Yape"; }
	void PagoPlin() { tipoPago = "Plin"; }
	void PagoTarjeta() { tipoPago = "Tarjeta"; }
	void PagoEfectivo() { tipoPago = "Efectivo"; }

	string getTipoPago() const { return tipoPago; }

	// Guardar archivo en texto
	void guardarMetodoPago(ofstream& out) const {
		out << tipoPago;
	}

	// Abrir archivo en texto
	void cargarMetodoPago(const string& tipo) {
		tipoPago = tipo;
	}
};

template <class T>
class Pago {
private:
	string producto;
	int cantidad;
	double precioUnitario;
public:
	metodoPago metodo;

	string ajustarTexto(const string& texto, size_t ancho) const {
		if (texto.size() > ancho) {
			// recorta texto
			return texto.substr(0, ancho);
		}
		else
		{
			// rellena con espacios
			return texto + string(ancho - texto.size(), ' ');
		}
	}

	Pago(string produc = "", int cant = 0, double precioU = 0.0)
		: producto(produc), cantidad(cant), precioUnitario(precioU) {
	}

	// caluclar subtotal recursivo
	double calcularSubtotal() {
		function<double(double, int)> subtotal = [&](double unit, int n) {
			return n == 0 ? 0.0 : unit + subtotal(unit, n - 1);
			};
		return subtotal(precioUnitario, cantidad);
	}

	// calcular IGV recursivo
	double calcularIGV() {
		function<double(double)> igv = [&](double sub) {
			return sub * 0.18;
			};
		return igv(calcularSubtotal());
	}

	// calcular total recursivo (igv + subtotal)
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

	// Convierte un número entero (1..999) a texto en español
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
	// Convierte montos hasta 999999 en letras
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
	// Muestra el monto total en texto (SOLES Y CENTIMOS)
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

	// metodos getters y setters
	string getProducto() const { return producto; }
	int getCantidad() const { return cantidad; }
	double getPrecioUnitario() const { return precioUnitario; }

	void setProducto(const string& p) { producto = p; }
	void setCantidad(int c) { cantidad = c; }
	void setPrecioUnitario(double pu) { precioUnitario = pu; }

	// ver datos del pago
	void mostrarPagos() {
		cout << "|-------------------------------------------|\n";
		cout << "| Paquete                      Cant  Importe|\n";
		cout << "| " << setw(26) << left << producto
			<< setw(5) << right << cantidad
			<< setw(10) << right << fixed << setprecision(2) << precioUnitario << " |\n";
		cout << "|-------------------------------------------|\n";
		cout << "| OP. GRAVADA :                  S/" << setw(7) << right << fixed << setprecision(2) << calcularSubtotal() << "  |\n";
		cout << "| IGV (18%) :                    S/" << setw(7) << right << fixed << setprecision(2) << calcularIGV() << "  |\n";
		cout << "| TOTAL A PAGAR :                S/" << setw(7) << right << fixed << setprecision(2) << calcularTotal() << "  |\n";
		cout << "|-------------------------------------------|\n";
		cout << "| Metodo de Pago: " << ajustarTexto(metodo.getTipoPago(), 26) << "|\n";
		cout << "| Son: " << ajustarTexto(montoEnTexto(), 37) << "|\n";
		cout << "|                                           |\n";
		cout << "|-------------------------------------------|\n";
	}

	// guardo de los pago en archivo de texto
	void guardarPagoTexto(ofstream& out) const {
		out << producto << "|" << cantidad << "|"
			<< fixed << setprecision(2) << precioUnitario << "|";
		metodo.guardarMetodoPago(out);
		out << "\n";
	}

	// cargo los pagos desde el archivo de texto
	void cargarPagoTexto(const string& linea) {
		stringstream ss(linea);
		string cant, precio, tipo;

		getline(ss, producto, '|');
		getline(ss, cant, '|');
		getline(ss, precio, '|');
		getline(ss, tipo, '|');

		cantidad = stoi(cant);
		precioUnitario = stod(precio);
		metodo.cargarMetodoPago(tipo);
	}
};


template <class T>
class GestorPago {
private:
	NodoPago<T>* cabeza;
public:

	GestorPago() : cabeza(nullptr) {}

	~GestorPago() {
		NodoPago<T>* temp;
		while (cabeza) {
			temp = cabeza;
			cabeza = cabeza->next;
			delete temp;
		}
		cabeza = nullptr;
	}

	void registrarPago(T pago) {
		NodoPago<T>* nuevoNodo = new NodoPago<T>(pago);
		if (!cabeza) {
			cabeza = nuevoNodo;
		}
		else {
			NodoPago<T>* temp = cabeza;
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = nuevoNodo;
		}
	}

	bool eliminarPago(const string& nombreProducto) {
		if (!cabeza) return false;

		if (cabeza->dato.getProducto() == nombreProducto) {
			NodoPago<T>* temp = cabeza;
			cabeza = cabeza->next;
			delete temp;
			return true;
		}

		NodoPago<T>* actual = cabeza;
		while (actual->next && actual->next->dato.getProducto() != nombreProducto) {
			actual = actual->next;
		}

		if (actual->next) {
			NodoPago<T>* temp = actual->next;
			actual->next = actual->next->next;
			delete temp;
			return true;
		}
		return false;
	}

	void mostrarPagos() {
		NodoPago<T>* temp = cabeza;
		while (temp) {
			temp->dato.mostrarPagos();
			temp = temp->next;
		}
	}

	void guardarPagosTexto(const string& nombreArchivo) {
		ofstream out(nombreArchivo);
		if (!out) {
			cout << "No se pudo abrir el archivo.\n";
			return;
		}
		NodoPago<T>* temp = cabeza;
		while (temp) {
			temp->dato.guardarPagoTexto(out);
			temp = temp->next;
		}
		out.close();
	}

	void cargarPagosTexto(const string& nombreArchivo) {
		ifstream in(nombreArchivo);
		if (!in) {
			cout << "No se pudo abrir el archivo.\n";
			return;
		}
		string linea;
		while (getline(in, linea)) {
			if (linea.empty()) continue;
			T pago;
			pago.cargarPagoTexto(linea);
			registrarPago(pago);
		}
		in.close();
	}
};

