#pragma once
template<typename T>
class NodoPila {
public:
	T dato;
	NodoPila<T>* siguiente;

	NodoPila(T _dato, NodoPila<T>* _sig = nullptr) {
		dato = _dato;
		siguiente = _sig;
	};

};