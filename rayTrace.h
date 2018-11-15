#ifndef ___RAYTRACE_H___
#define ___RAYTRACE_H___

#include <GL/glut.h>

#include <math.h>
#include <time.h>
#include "input.h"
#include "Esfera.h"
#include "estructuras.h"

//Funciones para el uso de las estructuras

void setColorPixel(Color pixel, Color* pixeles){
	pixeles->r = pixel.r/255;
	if(pixeles->r > 1) {
		pixeles->r = 1.0;
	}
	pixeles->g = pixel.g/255;
	if(pixeles->g > 1) {
		pixeles->g = 1.0;
	}
	pixeles->b = pixel.b/255;
	if(pixeles->b > 1) {
		pixeles->b = 1.0;
	}

	
}

Color shade(Choque choque,Rayo rayo, int valor);

#endif
