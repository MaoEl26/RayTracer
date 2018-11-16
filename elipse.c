#include "elipse.h"

void* leerElipse(){

	elipse * fig;
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
	fig->foco1 = setVector(x,y,z);

	readFloat();
	x = getFloat(0);
	y = getFloat(1);
	z = getFloat(2);
	fig->foco2 = setVector(x,y,z);

	readFloat();
	fig->r = getFloat(0);

	normalizarElipse(fig);

	return fig;
}

void normalizarElipse(elipse * fig){
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