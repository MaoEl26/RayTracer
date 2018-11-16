#ifndef ___ESTRUCTURAS_H___
#define ___ESTRUCTURAS_H___

#define EPSILON 0.000005

//#include "Esfera.h"
#include <math.h>
#include <stdlib.h>

void* readSolid();

typedef struct
{
	float r;
	float g;
	float b;
}Color;

typedef struct
{
    float x;
    float y;
    float z;
}Vector;

typedef struct
{
	int tipo;
	void* figura;
	float m;
	Vector v;
	Color color;
}Solido;

typedef struct
{
	Vector direccion;
	Vector origen;
}Rayo;

typedef float (*Op1)(Solido *i, Rayo rayo);
typedef Vector (*Op2)(Solido *i, Vector punto, Vector direccion);

typedef struct
{
	Solido* obj;
	Op1 interseccion;
	Op2 normal;
	int id;
	float ri;
	int refleccion;
}cuerpo;

typedef struct
{
	cuerpo* objeto;
	Vector n;
	Vector p;
	float t;
}Choque;

Color setColor(float r,float g, float b){
	Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	return color;
}

Vector setVector(float x,float y, float z){
	Vector vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

Color sumaColor(Color color1, Color color2){
	return (setColor(color1.r+color2.r,color1.g+color2.g,color1.b+color2.b));
}

Color aumentoColor(Color color, float aumento){
	return (setColor(color.r * aumento,color.g * aumento,color.b * aumento));
}

float magnitud(Vector vector){
    return sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
}

float distanciaEucladiana(Vector vec1,Vector vec2){
    return sqrt(pow((vec2.x-vec1.x),2)+pow((vec2.y-vec1.y),2)+pow((vec2.z-vec1.z),2));
}

float pPunto(Vector vector1, Vector vector2){
	return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

Vector pCruz(Vector vector1,Vector vector2){
	return setVector(vector1.y*vector2.z - vector1.z*vector2.y, vector1.z*vector2.x
	 - vector1.x*vector2.z, vector1.x*vector2.y - vector1.y*vector2.x);
}

Vector escalaVector(Vector vector, float escala){
	return setVector(vector.x * escala, vector.y * escala, vector.z * escala);
}

Vector sumaVector(Vector vector1, Vector vector2){
	return setVector(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector restaVector(Vector vector1, Vector vector2){
	return sumaVector(vector1,escalaVector(vector2,-1));
}

float potenciaCuadrada(float valor){
    return (valor*valor);
}


#endif
