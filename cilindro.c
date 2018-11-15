#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cilindro.h"

void* leerCilindro()
{	
	Vector vec;
	float r,g,b;
	cilindro* c;
	//double getDouble(10);
	c = malloc(sizeof(cilindro));
	readFloat();
	r = getFloat(0);
	g = getFloat(1);
	b = getFloat(2);
	c->inicio = setVector(r,g,b);
	readFloat();
	r = getFloat(0);
	g = getFloat(1);
	b = getFloat(2);
	c->fin = setVector(r,g,b);
	readFloat();
	c->rad = getFloat(0);

	readFloat();
	r = getFloat(4);
	g = getFloat(5);
	b = getFloat(6);

	c->color =setColor(r,g,b);
	
	return c;
}



