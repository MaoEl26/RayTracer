#ifndef ___DISCO_H___
#define ___DISCO_H___

#include "input.h"
#include "estructuras.h"

typedef struct
{
	Vector* puntos;
	int cantidadPuntos;
	Vector centro;
	float a;
	float b;
	float c;
	float d;
	float r;
	float rPeq;
}disco;

void* leerDisco();

void normalizarDisco(disco *fig);

Vector calcularNormalDisco(Solido *figSolido, Vector punto, Vector direccion);

float calculoInterseccionDisco(Solido* sol,Rayo rayo);

int puntoEnDisco(Vector rayo, disco fig);

#endif