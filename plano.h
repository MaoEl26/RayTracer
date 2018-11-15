#ifndef ___PLANO_H___
#define ___PLANO_H___

#include "input.h"
#include "estructuras.h"

typedef struct
{
	Vector* puntos;
	int cantidadPuntos;
	float a;
	float b;
	float c;
	float d;
}plano;

void* leerPlano();

void normalizarPlano(plano * fig);

#endif