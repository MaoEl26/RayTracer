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
	int tipo;
	void* figura;
	Color color;
}Solido;

typedef struct
{
	float x;
	float y;
	float z;
}Vector;

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

float productoTriple(Vector u, Vector v, Vector w)
{
	float ret;

	ret = u.x*v.y*w.z
		  -u.x*v.z*w.y
		  -u.y*v.x*w.z
		  +u.y*v.z*w.x
		  +u.z*v.x*w.y
		  -u.z*v.y*w.x;

	return ret;
}

int coplanar(Vector a, Vector b, Vector c, Vector d)
	{
		Vector u,v,w;

		u = restaVector(b,a);
		v = restaVector(c,a);
		w = restaVector(d,a);

		return (abs(productoTriple(u,v,w)) < EPSILON);
	}

float randomVal(){
	float val;
	val = (rand()%32768)-16384;
	val = val/32768.0;
	return val;
}

Rayo vectorARayo(Vector a, Vector b){
	Rayo s;
	s.origen = a;
	s.direccion = b;
	return s;
}

Vector rayoAVector(Rayo s)
{
	Vector v;
	v.x = s.direccion.x - s.origen.x;
	v.y = s.direccion.y - s.origen.y;
	v.z = s.direccion.z - s.origen.z;

	return v;
}

Vector aleatorio(Vector vector){
	Vector random;
	float valor;
	random = setVector(randomVal(),randomVal(),randomVal());

	random = pCruz(vector,random);

	valor = magnitud(random);

	if(valor<EPSILON){
	    printf("in");
		return aleatorio(vector);
	}else{
		return escalaVector(random,1/valor);
	}
}

float potenciaCuadrada(float valor){
    return (valor*valor);
}

int interseccionSegmento(Rayo s, Rayo r){
	Vector u,v,w;

	if(!coplanar(s.origen,s.direccion,r.origen,r.direccion)) return 0;

	u = restaVector(s.direccion,s.origen);
	v = restaVector(r.origen,s.origen);
	w = restaVector(r.direccion,s.origen);

	v = pCruz(u,v);
	w = pCruz(u,w);

	if(pPunto(v,w) > EPSILON) return 0;

	u = restaVector(r.direccion,r.origen);
	v = restaVector(s.origen,r.origen);
	w = restaVector(s.direccion,r.origen);

	v = pCruz(u,v);
	w = pCruz(u,w);

	if(pPunto(v,w) > EPSILON) return 0;

	return 1;
}

#endif
