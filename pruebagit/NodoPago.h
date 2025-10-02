#pragma once
#include "Librerias.h"

template<typename T>
class NodoPago {
public:
	T dato;
	NodoPago<T>* next;
	NodoPago(T v) : dato(v), next(nullptr) {}
	~NodoPago() { next = nullptr; }
};