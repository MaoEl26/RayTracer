#include "estructuras.h"
#include "Esfera.c"
#include "Esfera.h"
#include "cilindro.c"
#include "cilindro.h"
#include "disco.h"
#include "disco.c"
#include "elipse.h"
#include "elipse.c"
#include "poligono.h"
#include "poligono.c"
#include "plano.h"
#include "plano.c"

char* ID[] = {"ESFERA","CILINDRO","PLANO","POLIGONO","DISCO","ELIPSE"};

void* (*READ[])(void) = {leerEsfera,leerCilindro,leerPlano,leerPoligono,leerDisco,leerElipse};

void* readSolid()
{
	char str[100];
	int i;
	Solido* s;

	FILE *file = retFile();
	fgets(str, 100, file);

	s = (Solido*)malloc(sizeof(Solido));
	char chars[100];
	memmove(&str[strlen(str)-1],&str[strlen(str)],strlen(str)-1);
	
	for(i=0;i<sizeof(ID)/sizeof(char*);++i){
		if(strcmp(str,ID[i]) == 0)
		{	
			float r,g,b;
			s->tipo = i;
			s->figura = READ[i]();
			readFloat();
			r = getFloat(0);
			g = getFloat(1);
			b = getFloat(2);
			printf("asq %f\n",getFloat(0));
			s->color.r = r;
			s->color.g = g;
			s->color.b = b;
			return s;
		}
	}
	return NULL;
}
