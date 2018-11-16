#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cilindro.h"
#include "estructuras.h"

void* leerCilindro()
{
	Vector vec;
	float r,g,b;
	cilindro* c;
	//double getDouble(10);
	c = (cilindro*)malloc(sizeof(cilindro));
	readFloat();
	r = getFloat(0);
	g = getFloat(1);
	b = getFloat(2);
	c->centro = setVector(r,g,b);
	readFloat();
	r = getFloat(0);
	g = getFloat(1);
	b = getFloat(2);
	c->eje = setVector(r,g,b);
	readFloat();
	c->rad = getFloat(0);
	c->d1 = getFloat(1);
	c->d2 = getFloat(2);
	readFloat();
	return c;
}

float calculoInterseccionCilindro(Solido * sol,Rayo rayo){
	float a,b,c;
	float t,discriminante;
	float t1,t2;
	cilindro cyl;
	cyl = *((cilindro*)(sol->figura));

	Vector aux, Vectori;
	aux = restaVector(rayo.origen,cyl.centro);

	a = potenciaCuadrada(rayo.direccion.x) + potenciaCuadrada(rayo.direccion.y) + potenciaCuadrada(rayo.direccion.z)-
			potenciaCuadrada(pPunto(rayo.direccion,cyl.eje));

	b = 2.0*(pPunto(rayo.direccion,aux)-pPunto(rayo.direccion,cyl.eje)*pPunto(aux,cyl.eje));

	c = pPunto(aux,aux)-potenciaCuadrada(pPunto(aux,cyl.eje))- potenciaCuadrada(cyl.rad);

	discriminante = (b*b-4*a*c);

	if(discriminante < EPSILON){
		return -1;
	}else{
		discriminante = sqrt(discriminante);
		t1 = (-1 * b + discriminante)/2;
		t2 = (-1 * b - discriminante)/2;

		if(t2 < t1) {
			float auxVal = t1;
			t1 = t2;
			t2 = auxVal;
		}

		Vectori.x = rayo.origen.x + t1*rayo.direccion.x;
		Vectori.y = rayo.origen.y + t1*rayo.direccion.y;
		Vectori.z = rayo.origen.z + t1*rayo.direccion.z;

		Vector limite;

		limite.x = Vectori.x - cyl.centro.x;
		limite.y = Vectori.y - cyl.centro.y;
		limite.z = Vectori.z - cyl.centro.z;

		sol->v = Vectori;

		double d = pPunto(limite,cyl.eje);

		double valor = d/magnitud(cyl.eje);

		if( (valor >= cyl.d1) && (valor <= cyl.d2)){
            t = t1;
			sol->m = valor;
		}else{
			Vectori.x = rayo.origen.x + t2*rayo.direccion.x;
			Vectori.y = rayo.origen.y + t2*rayo.direccion.y;
			Vectori.z = rayo.origen.z + t2*rayo.direccion.z;
			sol->v = Vectori;

			limite.x = Vectori.x - cyl.centro.x;
			limite.y = Vectori.y - cyl.centro.y;
			limite.z = Vectori.z - cyl.centro.z;

			d = pPunto(limite,cyl.eje);
			valor = d/magnitud(cyl.eje);

			if( (valor >= cyl.d1) && (valor <= cyl.d2)){
				t = t1;
				sol->m = valor;
			}else {
				t = -1;
			}
		}
	}
	return t;
}

Vector calculoNormalCilindro(Solido *sol, Vector punto, Vector direccion){
	Vector normal;

	cilindro cyl;
	cyl = *((cilindro*)(sol->figura));

	normal.x = sol->v.x-cyl.centro.x-cyl.eje.x*sol->m;
	normal.x = sol->v.y-cyl.centro.y-cyl.eje.y*sol->m;
	normal.x = sol->v.z-cyl.centro.z-cyl.eje.z*sol->m;

	return normal;
}
