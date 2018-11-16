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
	Vector foco1;
	Vector foco2;
	float r;
}elipse;

void* leerElipse();

void normalizarElipse(elipse * fig);

Vector calcularNormalElipse(Solido *figSolido, Vector punto, Vector direccion);

float calculoInterseccionElipse(Solido* sol,Rayo rayo);

int puntoEnElipse(Vector rayo, elipse fig);

#endif