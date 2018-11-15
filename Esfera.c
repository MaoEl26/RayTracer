#include "Esfera.h"
//#include "estructuras.h"

void* leerEsfera(void){
	Esfera *esfera;

	esfera = (Esfera*)malloc(sizeof(Esfera));
	
    float r,g,b;
	
	readFloat();
	esfera->r = getFloat(0);
	
	esfera->c.x = getFloat(1);
	esfera->c.y = getFloat(2);
	esfera->c.z = getFloat(3);
	

	return esfera;
}

float calculoInterseccion (Solido *figSolido, Rayo rayo) {
	Esfera figSphere;
	figSphere = *((Esfera*)(figSolido->figura));
	
	Vector restaVec = restaVector(rayo.origen, figSphere.c);
	float multiVector = pPunto(rayo.direccion,rayo.direccion);
	float discriminante = pPunto(rayo.direccion, restaVec);
	discriminante *= discriminante;
	discriminante -= (multiVector*(pPunto(restaVec,restaVec)-pow(figSphere.r,2.0)));
	
	if(discriminante >=0){
		Vector escala = escalaVector(rayo.direccion,-1);
		float t = pPunto(escala,restaVec);
		float t1 = (t + sqrt(discriminante))/multiVector;
		float t2 = (t - sqrt(discriminante))/multiVector; /*multiVector*/
				
		if (t1 > 0 && t2 > 0) {
			if(t1 < t2){
				return t1;
			} else{
				return t2;
			}
		} else if(t1 > 0) {
			return t1;
		} else if(t2 > 0) {
			return t2;
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

Vector normalEsfera(Solido *figSolido, Vector punto){
	Vector n;
	Esfera figSphere;

	figSphere = *((Esfera*)(figSolido->figura));
	n = escalaVector(restaVector(punto, figSphere.c),-1/figSphere.r);
	n = escalaVector(n,1/magnitud(n));

	return n;
}
