#ifndef ___ESFERA_H___
#define ___ESFERA_H___

#include "input.h"
#include "estructuras.h"

//extern struct Vector;
//extern struct Color;

typedef struct
{
	float r;
	Vector c;
}Esfera;

void* leerEsfera(void);

float calculoInterseccion(Solido *figSolido, Rayo rayo);

Vector normalEsfera(Solido *figSolido, Vector punto);

#endif