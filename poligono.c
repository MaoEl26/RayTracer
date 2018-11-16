#include "poligono.h"
#include "estructuras.h"

void* leerPoligono(){

	poligono * fig;
	fig = (poligono*)malloc(sizeof(poligono));
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

	normalizarPoly(fig);

	return fig;
}

void normalizarPoly(poligono * fig){
	Vector centro,izq,der;
	Vector vectA,vectB;
	Vector pcruz;
	float d, norma;

	centro = fig->puntos[0];
	izq = fig->puntos[1];
	der = fig->puntos[2];

	vectA = restaVector(centro,izq);
	vectB = restaVector(centro,der);
	pcruz = pCruz(vectA,vectB);

	norma = magnitud(pcruz);

	d = -pPunto(pcruz, centro)/norma;

	pcruz = escalaVector(pcruz,1/norma);

	fig->a = pcruz.x;
	fig->b = pcruz.y;
	fig->c = pcruz.z;
	fig->d = d;
}

int testFigura(poligono fig, int flag,Vector p){
    int cantidadParedes=0;
    int i,j;

    if(flag == 1){
        int puntosPoligono = fig.cantidadPuntos;

        for (i = 0, j = puntosPoligono-1; i < puntosPoligono; j = i++)
        {
            float polyYI, polyYJ, polyXI, polyXJ;
            polyYI = fig.puntos[i].z;
            polyYJ = fig.puntos[j].z;
            polyXI = fig.puntos[i].y;
            polyXJ = fig.puntos[j].y;

            if (((polyYI > p.y) != (polyYJ > p.y)) &&
                (p.x < (polyXJ-polyXI) * (p.y-polyYI) /
                       (polyYJ-polyYI) + polyXI))
            {
                cantidadParedes++;
            }
        }
        return cantidadParedes%2;
    }
    if(flag == 2){
        int puntosPoligono = fig.cantidadPuntos;

        for (i = 0, j = puntosPoligono-1; i < puntosPoligono; j = i++)
        {
            float polyYI, polyYJ, polyXI, polyXJ;
            polyYI = fig.puntos[i].z;
            polyYJ = fig.puntos[j].z;
            polyXI = fig.puntos[i].x;
            polyXJ = fig.puntos[j].x;

            if (((polyYI > p.y) != (polyYJ > p.y)) &&
                (p.x < (polyXJ-polyXI) * (p.y-polyYI) /
                       (polyYJ-polyYI) + polyXI))
            {
                cantidadParedes++;
            }
        }
        return cantidadParedes%2;
    }
    if(flag == 3){
        int puntosPoligono = fig.cantidadPuntos;
        for (i = 0, j = puntosPoligono-1; i < puntosPoligono; j = i++)
        {
            float polyYI, polyYJ, polyXI, polyXJ;
            polyYI = fig.puntos[i].y;
            polyYJ = fig.puntos[j].y;
            polyXI = fig.puntos[i].x;
            polyXJ = fig.puntos[j].x;

            if (p.x < (polyXJ - polyXI) * (p.y - polyYI) /
                      (polyYJ - polyYI) + polyXI) {
                if ((polyYI > p.y) != (polyYJ > p.y)) {
                    cantidadParedes++;
                }
            }
        }
        return cantidadParedes%2;
    }
}

float puntoEnPlano(Solido * sol, Rayo rayo) {
	poligono fig;
	float a, b, c, d, denom;
	float t;

    fig = *((poligono*)(sol->figura));
	a = fig.a;
	b = fig.b;
	c = fig.c;
	d = fig.d;

    denom = (a*rayo.direccion.x+b*rayo.direccion.y+c*rayo.direccion.z);

	if (denom > EPSILON || denom < EPSILON)
	{
		if (puntoEnFigura(rayo.origen, rayo.direccion, fig) == 1)
		{
		    printf("punto en figura");
			t = (-(a*rayo.origen.x + b*rayo.origen.y + c*rayo.origen.z)+d)/denom;
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

int puntoEnFigura(Vector ojo, Vector p, poligono fig){
    float temp;
    float a,b,c,d;

    float t;
	int flag = 0;

	temp=0;
	a = fig.a;
	b = fig.b;
	c = fig.c;
	d = fig.d;

	if(abs(a) >= temp){
		temp = abs(a);
		flag = 1;
	}
	if(abs(b) >= temp){
		temp = abs(b);
		flag = 2;
	}
	if(abs(c) >= temp) {
        temp = abs(c);
        flag = 3;
    }

	double denominador = (a*p.x+b*p.y+c*p.z);

	if(denominador>EPSILON || denominador<EPSILON)
	{
		t = (-(a*ojo.x+b*ojo.y+c*ojo.z)+d)/denominador;
		printf("T: %lf \n", t);
		Vector punto;
		punto.x = ojo.x + t * p.x;
		punto.y = ojo.y + t * p.y;
		punto.z = ojo.z + t * p.z;
		if(testFigura(fig,flag,punto)==1){
			return 1;
		}
	}
	return 0;
}

Vector calcularNormalPoligono(Solido *figSolido, Vector punto, Vector direccion)
{
	Vector normal;
	poligono fig;
	fig = *((poligono*)(figSolido->figura));
	normal.x = fig.a;
	normal.y = fig.b;
	normal.z = fig.c;

    if (pPunto(direccion, normal) < 0){
        normal = escalaVector(normal, -1);
    }

	return normal;
}
