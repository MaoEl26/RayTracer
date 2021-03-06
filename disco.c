#include "disco.h"
#include "estructuras.h"

void* leerDisco(){
	disco * fig;
	fig = (disco*)malloc(sizeof(disco));
	float x,y,z;
	int cant;
	readInt();
	cant = getInt(0);
	fig->cantidadPuntos = cant;
	fig->puntos = (Vector*)malloc(cant*sizeof(Vector));
	for (int i = 0; i < cant; ++i)
	{
		readFloat();
		x = getFloat(0);
		y = getFloat(1);
		z = getFloat(2);
		fig->puntos[i] = setVector(x,y,z);
	}
	readFloat();
    x = getFloat(0);
    y = getFloat(1);
    z = getFloat(2);
	fig->centro = setVector(x,y,z);
	readFloat();
	fig->r = getFloat(0);
	fig->rPeq = getFloat(1);

	normalizarDisco(fig);

	return fig;
}

void normalizarDisco(disco * fig){
	Vector centro,izq,der;
	Vector vectA,vectB;
	Vector pcruz;
	float d;

	centro = fig->puntos[0];
	izq = fig->puntos[1];
	der = fig->puntos[2];

	vectA = restaVector(centro,izq);
	vectB = restaVector(centro,der);
	pcruz = pCruz(vectA,vectB);

	d = pPunto(escalaVector(pcruz,-1/magnitud(pcruz)),escalaVector(centro,-1/magnitud(pcruz)));

	pcruz = escalaVector(pcruz,1/magnitud(pcruz));

	fig->a = pcruz.x;
	fig->b = pcruz.y;
	fig->c = pcruz.z;
	fig->d = d;
}

Vector calcularNormalDisco(Solido *figSolido, Vector punto, Vector direccion){
	Vector normal;
	disco fig;
	fig = *((disco*)(figSolido->figura));
	normal.x = fig.a;
	normal.y = fig.b;
	normal.z = fig.c;

	if (pPunto(direccion, normal) < 0){
		normal = escalaVector(normal, -1);
	}

	return normal;
}

float calculoInterseccionDisco(Solido* sol,Rayo rayo){
	disco fig;
	fig = *((disco*)(sol->figura));

	float a, b, c, d, denom;
	float t;

	a = fig.a;
	b = fig.b;
	c = fig.c;
	d = fig.d;

    denom = (a*rayo.direccion.x+b*rayo.direccion.y+c*rayo.direccion.z);

	if (denom > EPSILON||denom<EPSILON)
	{
		t = (-(a*rayo.origen.x + b*rayo.origen.y + c*rayo.origen.z)+d)/denom;
		Vector vectorI = sumaVector(rayo.origen, escalaVector(rayo.direccion,t-0.01));

		if (puntoEnDisco(vectorI, fig) == 1)
		{
		}
		else
		{
			t = -1;
		}
	}
	else
	{
		t = -1;
	}
	return t;
}

int puntoEnDisco(Vector rayo, disco fig){
	float valor;;
	int ret = 0;

	valor = distanciaEucladiana(rayo,fig.centro);

	if(valor<=fig.r){
		ret = 1;
	}

	if ((fig.rPeq > 0) && (ret == 1)) {
		if (valor >= fig.rPeq) {
			ret = 1;
		} else {
			ret = 0;
		}
	}
	return ret;
}