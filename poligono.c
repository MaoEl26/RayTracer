#include "poligono.h"

void* leerPoligono(){

	poligono * fig;
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
	fig->color = setColor(x,y,z);

	normalizarPoly(fig);

	return fig;
}

void normalizarPoly(poligono * fig){
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

float puntoEnPlano(Solido * sol, Vector ojo, Vector p){

	poligono fig;
	fig = *((poligono*)(sol->figura));

	float a, b, c, d, denom;
	float t, *interseccion;
	
	a = fig.a;
	b = fig.b;
	c = fig.c;
	d = fig.d;
	
	//printf("%f\n", figuras[idFigura].values[0]);
	//printf("%f\n", figuras[idFigura].values[1]);
	//printf("%f\n", figuras[idFigura].values[2]);
	//printf("%f\n", figuras[idFigura].values[3]);

	denom = (a*p.x+b*p.y+c*p.z);
	
	if (denom > EPSILON||denom<EPSILON)
	{

		if (puntoEnFigura(ojo, p, fig) == 1)
		{
			t = -(a*ojo.x + b*ojo.y + c*ojo.z + d)/denom;
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
	//interseccion = &t;
	
	return t; 
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
		//if (cantidadParedes%2==0) prueba++;;
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
		//if (cantidadParedes%2==0) prueba++;;
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
			
			if (((polyYI > p.y) != (polyYJ > p.y)) &&
			     (p.x < (polyXJ-polyXI) * (p.y-polyYI) /
			     (polyYJ-polyYI) + polyXI))
			{
				cantidadParedes++;
			}
		}
		//if (cantidadParedes%2==0) prueba++;;
		return cantidadParedes%2;
	}
}

float puntoEnFigura(Vector ojo, Vector p, poligono fig){
	float temp;
	float a,b,c,d;

	double t;
	int flag = 0;

	temp=0;

	a = abs(fig.a);
	b = abs(fig.b);
	c = abs(fig.c);
	d = abs(fig.d);

	if(a >= temp){
		temp = a;
	}
	if(b >= temp){
		temp = b;
	}
	if(c >= temp){
		temp = c;
	}
	
	if(a == temp){
		flag = 1;
	}
	else if(b == temp){
		flag = 2;
	}
	else if(c == temp){
		flag = 3;
	}
	
	double denominador = (a*p.x+b*p.y+c*p.z);
	if(denominador>EPSILON)
	{	

		t = -((a*ojo.x+b*ojo.y+c*ojo.z+d)/denominador);
		Vector punto;
		punto.x = ojo.x + t * p.x;
		punto.y = ojo.y + t * p.y;
		punto.z = ojo.z + t * p.z;
		/*printf("%f denominador\n", denominador);
		printf("%f t\n", t);
		printf("%d\n", flag);*/
		if(testFigura(fig,flag,punto)==1){
			return 1;
		}
	}
	return 0;
}