#ifndef ___POLIGONO_H___
#define ___POLIGONO_H___

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
}poligono;

void* leerPoligono();

float puntoEnPlano(Solido * sol, Vector ojo, Vector p);

int testFigura(poligono fig, int flag,Vector p);

float puntoEnFigura(Vector ojo, Vector p, poligono fig);

void normalizarPoly(poligono * poly);

#endif