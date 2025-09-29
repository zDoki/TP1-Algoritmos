#pragma once

template<typename T>
class Paquete {
public:
	int id;
	string descripcion;
	double peso;
	string dimensiones;
	string estado; // "registrado", "en_transito", "entregado", "perdido"
	int remitenteId;
	int destinatarioId;
	int sucursalOrigenId;
	int sucursalDestinoId;
	string fechaEnvio;
	string fechaEntregaEstimada;

	Paquete(int _id, string _descripcion, double _peso, string _dimensiones, string _estado, int _remitenteId, int _destinatarioId, int _sucursalOrigenId, int _sucursalDestinoId, string _fechaEnvio, string _fechaEntregaEstimada) :
		id(_id), descripcion(_descripcion), peso(_peso), dimensiones(_dimensiones), estado(_estado), remitenteId(_remitenteId), destinatarioId(_destinatarioId), sucursalOrigenId(_sucursalOrigenId), sucursalDestinoId(_sucursalDestinoId), fechaEnvio(_fechaEnvio), fechaEntregaEstimada(fechaEntregaEstimada) {};

	Paquete() : id(0), peso(0.0), remitenteId(0), destinatarioId(0),
		sucursalOrigenId(0), sucursalDestinoId(0) {}


	void mostrarInfoPaquete() {

		cout << "ID " << id << endl;
		cout << "Descripsion " << descripcion << endl;
		cout << "Peso " << peso << endl;
		cout << "Dimensiones " << dimensiones << endl;
		cout << "Estado " << estado << endl;
		cout << "Remitente ID " << remitenteId << endl;
		cout << "Destinatario ID " << destinatarioId << endl;
		cout << "Sucursal Origen " << sucursalOrigenId << endl;
		cout << "Sucursal Destino " << sucursalDestinoId << endl;
		cout << "Fecha Envio " << fechaEnvio << endl;
		cout << "Fecha estimada de entrega " << fechaEntregaEstimada << endl;


	}

	string toString()const {
		return to_string(id) + "|" + descripcion + "|" + to_string(peso) + "|" +
			dimensiones + "|" + estado + "|" + to_string(remitenteId) + "|" +
			to_string(destinatarioId) + "|" + to_string(sucursalOrigenId) + "|" +
			to_string(sucursalDestinoId) + "|" + fechaEnvio + "|" + fechaEntregaEstimada;
	}

	string toStringFormato() const {
		string resultado = "";
		resultado += "================================\n";
		resultado += "         DATOS DEL PAQUETE      \n";
		resultado += "================================\n";
		resultado += "ID:                 " + to_string(id) + "\n";
		resultado += "Descripcion:        " + descripcion + "\n";
		resultado += "Peso:               " + to_string(peso) + " kg\n";
		resultado += "Dimensiones:        " + dimensiones + "\n";
		resultado += "Estado:             " + estado + "\n";
		resultado += "Remitente ID:       " + to_string(remitenteId) + "\n";
		resultado += "Destinatario ID:    " + to_string(destinatarioId) + "\n";
		resultado += "Sucursal Origen:    " + to_string(sucursalOrigenId) + "\n";
		resultado += "Sucursal Destino:   " + to_string(sucursalDestinoId) + "\n";
		resultado += "Fecha Envio:        " + fechaEnvio + "\n";
		resultado += "Fecha Entrega Est:  " + fechaEntregaEstimada + "\n";
		resultado += "================================\n\n";
		return resultado;
	}


};