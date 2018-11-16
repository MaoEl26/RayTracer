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
}poligono;

void* leerPoligono();

float puntoEnPlano(Solido * sol, Rayo rayo);

int testFigura(poligono fig, int flag,Vector p);

int puntoEnFigura(Vector ojo, Vector p, poligono fig);

void normalizarPoly(poligono * poly);

Vector calcularNormalPoligono(Solido *figSolido, Vector punto);

int puntoEnSegmento(Vector p,Rayo segmento);

#endif