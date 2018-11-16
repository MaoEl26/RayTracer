#ifndef ___CILINDRO_H___
#define ___CILINDRO_H___

#include "input.h"
#include "estructuras.h"

typedef struct
{
	Vector inicio,fin;
	float rad;
	Color color;
}cilindro;

void* leerCilindro();

float puntoEnPlano(Solido * sol, Rayo rayo);

//int testFigura(poligono fig, int flag,Vector p);

//float puntoEnFigura(Vector ojo, Vector p, poligono fig);

#endif