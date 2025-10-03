#pragma once

template<typename T>
class Paquete {
public:
	int id;
	string descripcion;
	double peso;
	int remitenteId;
	int destinatarioId;
	string sedeOrigen;
	string destino;

	Paquete(string _descripcion = "", double _peso = 0.0,
		int _remitenteId = 0, int _destinatarioId = 0, string _sedeOrigen = "",
		string _destino = "") :	descripcion(_descripcion), peso(_peso),
		remitenteId(_remitenteId), destinatarioId(_destinatarioId),
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
				if (stoi(campo) == nuevoID) {
					repetido = true;
					break;
				}
			}
			in.close();

		} while (repetido); // Repetir hasta encontrar uno que no exista

		return nuevoID;
	}

	void mostrarInfoPaquete() const {

		cout << "ID " << id << endl;
		cout << "Descripsion " << descripcion << endl;
		cout << "Peso " << peso << endl;
		cout << "Remitente ID " << remitenteId << endl;
		cout << "Destinatario ID " << destinatarioId << endl;
		cout << "Sucursal Origen " << sedeOrigen << endl;
		cout << "Sucursal Destino " << destino << endl;

	}

	string toString()const {
		return to_string(id) + "|" + descripcion + "|" + to_string(peso) + "|" +
			to_string(remitenteId) + "|" +
			to_string(destinatarioId) + "|" + to_string(sedeOrigen) + "|" +
			to_string(destino);
	}

	string toStringFormato() const {
		string resultado = "";
		resultado += "================================\n";
		resultado += "         DATOS DEL PAQUETE      \n";
		resultado += "================================\n";
		resultado += "ID:                 " + to_string(id) + "\n";
		resultado += "Descripcion:        " + descripcion + "\n";
		resultado += "Peso:               " + to_string(peso) + " kg\n";
		resultado += "Remitente ID:       " + to_string(remitenteId) + "\n";
		resultado += "Destinatario ID:    " + to_string(destinatarioId) + "\n";
		resultado += "Sucursal Origen:    " + sedeOrigen + "\n";
		resultado += "Sucursal Destino:   " + destino + "\n";

		resultado += "================================\n\n";
		return resultado;
	}

	bool leerDesdeArchivo(ifstream& archivo) {
		string linea;
		if (!getline(archivo, linea)) return false; //

		if (linea.empty()) return false;

		// Separar por '|'
		stringstream ss(linea);
		string campo;

		getline(ss, campo, '|'); id = stoi(campo);
		getline(ss, descripcion, '|');
		getline(ss, campo, '|'); peso = stod(campo);
		getline(ss, campo, '|'); remitenteId = stoi(campo);
		getline(ss, campo, '|'); destinatarioId = stoi(campo);
		getline(ss, campo, '|'); sedeOrigen = stoi(campo);
		getline(ss, campo, '|'); destino = stoi(campo);

		return true;
	}


};