#ifndef ___CILINDRO_H___
#define ___CILINDRO_H___

#include "input.h"
#include "estructuras.h"

typedef struct
{
	Vector centro,eje;
	float rad,d1,d2;
}cilindro;

void* leerCilindro();

float puntoEnPlano(Solido * sol, Rayo rayo);

float calculoInterseccionCilindro(Solido * sol,Rayo rayo);

Vector calculoNormalCilindro(Solido *figSolido, Vector punto, Vector direccion);

#endif