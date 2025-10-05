#pragma once

template<typename T>
class Paquete {
public:
	int id;
	string descripcion;
	double peso;
	
	string sedeOrigen;
	string destino;

	Paquete(string _descripcion = "", double _peso = 0.0,
		  string _sedeOrigen = "",
		string _destino = "") : descripcion(_descripcion), peso(_peso),
		sedeOrigen(_sedeOrigen), destino(_destino)
	{
		id = generarIDUnico("paquetes.txt");
	}

	static int generarIDUnico(const string& archivo) {
		int nuevoID;
		bool repetido;

		do {
			// Genera ID en el rango [100, 999]
			nuevoID = rand() % 999 + 100;
			repetido = false;

			// Verificar si el ID ya existe en el archivo
			ifstream in(archivo);
			string linea;
			while (getline(in, linea)) {
				if (linea.empty()) continue;

				stringstream ss(linea);
				string campo;
				getline(ss, campo, '|'); // Leer el primer campo (ID)

				// Validar que el campo no esté vacío antes de convertir
				if (!campo.empty()) {
					try {
						if (stoi(campo) == nuevoID) {
							repetido = true;
							break;
						}
					}
					catch (...) {
						// Ignorar líneas con formato inválido
						continue;
					}
				}
			}
			in.close();

		} while (repetido); // Repetir hasta encontrar uno que no exista

		return nuevoID;
	}

	void mostrarInfoPaquete() const {

		cout << "ID " << id << endl;
		cout << "Descripcion " << descripcion << endl;
		cout << "Peso " << peso << endl;
		cout << "Sucursal Origen " << sedeOrigen << endl;
		cout << "Sucursal Destino " << destino << endl;

	}



	string toStringFormato() const {
		string resultado = "";
		resultado += "================================\n";
		resultado += "         DATOS DEL PAQUETE      \n";
		resultado += "================================\n";
		resultado += "ID:                 " + to_string(id) + "\n";
		resultado += "Descripcion:        " + descripcion + "\n";
		resultado += "Peso:               " + to_string(peso) + " kg\n";
		resultado += "Sucursal Origen:    " + sedeOrigen + "\n";
		resultado += "Sucursal Destino:   " + destino + "\n";

		resultado += "================================\n\n";
		return resultado;
	}

	bool leerDesdeArchivo(ifstream& archivo) {
		string linea;
		if (!getline(archivo, linea)) return false;

		if (linea.empty()) return false;

		// Separar por '|'
		stringstream ss(linea);
		string campo;

		try {
			getline(ss, campo, '|');
			if (!campo.empty()) id = stoi(campo);

			getline(ss, descripcion, '|');

			getline(ss, campo, '|');
			if (!campo.empty()) peso = stod(campo);

			
			getline(ss, sedeOrigen, '|');  // CORREGIDO: Ya no usa stoi
			getline(ss, destino, '|');      // CORREGIDO: Ya no usa stoi

			return true;
		}
		catch (...) {
			return false;
		}
	}


};