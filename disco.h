#ifndef ___DISCO_H___
#define ___DISCO_H___

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
	Color color; 
	float r;
	float rPeq;
}disco;

void* leerDisco();

void normalizarDisco(disco *fig);

#endif