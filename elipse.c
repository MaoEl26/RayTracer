#include "elipse.h"

void* leerElipse(){
	elipse * fig;
    fig = (elipse*)malloc(sizeof(elipse));
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

Vector calcularNormalElipse(Solido *figSolido, Vector punto, Vector direccion){
    Vector normal;
    elipse fig;
    fig = *((elipse*)(figSolido->figura));

    normal.x = fig.a;
    normal.y = fig.b;
    normal.z = fig.c;

    printf("%lf nd\n", pPunto(normal, direccion));

    if (pPunto(direccion, normal) < 0){
        normal = escalaVector(normal, -1);
    }

    return normal;
}

float calculoInterseccionElipse(Solido* sol,Rayo rayo){
    elipse fig;
    fig = *((elipse*)(sol->figura));

    float a, b, c, d, denom;
    float t; //*interseccion;

    a = fig.a;
    b = fig.b;
    c = fig.c;
    d = fig.d;

    denom = (a*rayo.direccion.x+b*rayo.direccion.y+c*rayo.direccion.z);

    if (denom > EPSILON||denom<EPSILON)
    {
        t = (-(a*rayo.origen.x + b*rayo.origen.y + c*rayo.origen.z)+d)/denom;
        Vector vectorI = sumaVector(rayo.origen, escalaVector(rayo.direccion,t-0.01));

        if (puntoEnElipse(vectorI, fig) == 1)
        {
            printf("punto en elipse\n");
            //printf("%f",t);
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

int puntoEnElipse(Vector rayo, elipse fig){
    //Vector centro;
    float valor1;
    float valor2;
    //centro = fig.puntos[0];
    int ret = 0;

    valor1 = distanciaEucladiana(rayo,fig.foco1);
    valor2 = distanciaEucladiana(rayo,fig.foco2);
    //printf("Valor %f\n",valor);

    if(valor1+valor2<=fig.r) {
        ret = 1;
        printf("entro");
    }

    return ret;
}