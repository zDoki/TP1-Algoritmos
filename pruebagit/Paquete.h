#pragma once

template<typename T>
class Paquete {
public:
	int id;
	int clienteID;  
	string descripcion;
	double peso;

	string sedeOrigen;
	string destino;

	Paquete(string _descripcion = "", double _peso = 0.0,
		string _sedeOrigen = "",
		string _destino = "", int _clienteID = 0) : descripcion(_descripcion), peso(_peso),
		sedeOrigen(_sedeOrigen), destino(_destino), clienteID(_clienteID)
	{
		id = generarIDUnico("paquetes.txt");
	}

	static int generarIDUnico(const string& archivo) {
		int nuevoID;
		bool repetido;

		do {
			
			nuevoID = rand() % 999 + 100;
			repetido = false;

			
			ifstream in(archivo);
			string linea;
			while (getline(in, linea)) {
				if (linea.empty()) continue;

				stringstream ss(linea);
				string campo;
				getline(ss, campo, '|'); 

			
				if (!campo.empty()) {
					try {
						if (stoi(campo) == nuevoID) {
							repetido = true;
							break;
						}
					}
					catch (...) {// Si hay un error 
				
						continue;
					}
				}
			}
			in.close();

		} while (repetido); 

		return nuevoID;
	}

	void mostrarInfoPaquete() const {
		cout << "ID Paquete: " << id << endl;
		cout << "ID Cliente: " << clienteID << endl;
		cout << "Descripcion: " << descripcion << endl;
		cout << "Peso: " << peso << " kg" << endl;
		cout << "Sucursal Origen: " << sedeOrigen << endl;
		cout << "Sucursal Destino: " << destino << endl;
	}

	string toStringFormato() const {
		string resultado = "";
		resultado += "================================\n";
		resultado += "         DATOS DEL PAQUETE      \n";
		resultado += "================================\n";
		resultado += "ID Paquete:         " + to_string(id) + "\n";
		resultado += "ID Cliente:         " + to_string(clienteID) + "\n";
		resultado += "Descripcion:        " + descripcion + "\n";
		resultado += "Peso:               " + to_string(peso) + " kg\n";
		resultado += "Sucursal Origen:    " + sedeOrigen + "\n";
		resultado += "Sucursal Destino:   " + destino + "\n";
		resultado += "================================\n\n";
		return resultado;
	}

	string toStringArchivo() const {
		stringstream ss;
		ss << id << "|" << clienteID << "|" << descripcion << "|"
			<< peso << "|" << sedeOrigen << "|" << destino;
		return ss.str();
	}

	bool leerDesdeArchivo(ifstream& archivo) {
		string linea;
		if (!getline(archivo, linea)) return false;

		if (linea.empty()) return false;

		stringstream ss(linea);
		string campo;

		try {
			getline(ss, campo, '|');
			if (!campo.empty()) id = stoi(campo);

			getline(ss, campo, '|');
			if (!campo.empty()) clienteID = stoi(campo);

			getline(ss, descripcion, '|');

			getline(ss, campo, '|');
			if (!campo.empty()) peso = stod(campo);

			getline(ss, sedeOrigen, '|');
			getline(ss, destino, '|');

			return true;
		}
		catch (...) {
			return false;
		}
	}
};