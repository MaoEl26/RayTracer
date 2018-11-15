#ifndef ___ELIPSE_H___
#define ___ELIPSE_H___

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
	Vector foco1;
	Vector foco2;
	float r;
}elipse;

void* leerElipse();

void normalizarElipse(elipse * fig);

#endif