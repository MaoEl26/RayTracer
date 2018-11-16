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

	d = -pPunto(pcruz,centro);

	pcruz = escalaVector(pcruz,1/magnitud(pcruz));

	fig->a = pcruz.x;
	fig->b = pcruz.y;
	fig->c = pcruz.z;
	fig->d = d;
}

float puntoEnPlano(Solido * sol, Rayo rayo){

	poligono fig;
	fig = *((poligono*)(sol->figura));

	float a, b, c, d, denom;
	float t; //*interseccion;
	
	a = fig.a;
	b = fig.b;
	c = fig.c;
	d = fig.d;

	denom = (a*rayo.direccion.x+b*rayo.direccion.y+c*rayo.direccion.z);
	
	if (denom > EPSILON||denom<EPSILON)
	{

		if (puntoEnFigura(rayo.origen, rayo.direccion, fig) == 1)
		{
		    printf("punto en figura");
			t = (-(a*rayo.origen.x + b*rayo.origen.y + c*rayo.origen.z) + d)/denom;
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
				
		/*for (i = 0, j = puntosPoligono-1; i < puntosPoligono; j = i++)
		{
			float polyYI, polyYJ, polyXI, polyXJ;
			polyYI = fig.puntos[i].y;
			polyYJ = fig.puntos[j].y;
			polyXI = fig.puntos[i].x;
			polyXJ = fig.puntos[j].x;
            //printf("polyYI %f, polyYJ %f, polyXI %f polyXJ %f \n",polyYI,polyYJ,polyXI,polyXJ);
            //printf("p.x %f, p.y %f\n",p.x,p.y);
            if (p.x < (polyXJ - polyXI) * (p.y - polyYI) /
                      (polyYJ - polyYI) + polyXI) {
                if ((polyYI > p.y) != (polyYJ > p.y)) {
                    cantidadParedes++;
                    //printf("in");
                }
            }
		}*/


		for(i=0; i < puntosPoligono;i++){
		    j = (i+1)%(puntosPoligono);

		    if((fig.puntos[i].y-p.y>0 && fig.puntos[j].y-p.y<0)||
                    (fig.puntos[i].y-p.y<0 && fig.puntos[j].y-p.y>0)){
                printf("in");
		        if(fig.puntos[i].x-p.x>0 && fig.puntos[j].x-p.x>0){
		            cantidadParedes++;
		        }
		        else if(fig.puntos[i].x-p.x>0 && fig.puntos[j].x-p.x>0){
		            if((fig.puntos[i].x-p.x)-(fig.puntos[i].y-p.y)*
                                             ((fig.puntos[j].x-p.x)-(fig.puntos[i].x-p.x))/
                                                     ((fig.puntos[j].y-p.y)-(fig.puntos[i].y-p.y))){
		                cantidadParedes++;
		            }
		        }
		    }
		}
		if(cantidadParedes>0) {
            printf("paredes %d\n", cantidadParedes);
        }
		//if (cantidadParedes%2==0) prueba++;;
		return cantidadParedes%2;
	}
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
	if(abs(c) >= temp){
		temp = abs(c);
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
		printf("%f denominador\n", denominador);
		printf("%f t\n", t);
		if(testFigura(fig,flag,punto)==1){
			return 1;
		}
	}
	return 0;

    /*if(!coplanar(fig.puntos[0],fig.puntos[1],fig.puntos[2],p)){
        printf("aqui?");
        return 0;
    }

    for (int i = 0; i < fig.cantidadPuntos; ++i) {
        if(puntoEnSegmento(p,vectorARayo(fig.puntos[i],fig.puntos[i-1])))
			return 1;
    }
	if(puntoEnSegmento(p,vectorARayo(fig.puntos[0],fig.puntos[fig.cantidadPuntos-1]))){
		return 1;
    }

	Vector o;
	Rayo rayo;
	nuevorayo:
	o = aleatorio(setVector(fig.a,fig.b,fig.c));
	rayo = vectorARayo(p,sumaVector(p,o));

	int c =0;

	for (int i = 0; i < fig.cantidadPuntos; ++i) {
		if(puntoEnSegmento(fig.puntos[i],rayo))
			goto nuevorayo;
	}

	for (int i = 1; i < fig.cantidadPuntos; ++i) {
		if(interseccionSegmento(rayo,vectorARayo(fig.puntos[i],fig.puntos[i-1]))){
			c =!c;
		}
	}
	if (interseccionSegmento(rayo,vectorARayo(fig.puntos[0],fig.puntos[fig.cantidadPuntos-1]))){
		c=!c;
	}
	printf("c: %d",c);
	return c;*/
}

Vector calcularNormalPoligono(Solido *figSolido, Vector punto)
{
	Vector normal;
	poligono fig;
	fig = *((poligono*)(figSolido->figura));
	normal.x = fig.a;
	normal.y = fig.b;
	normal.z = fig.c;

	return normal;
}

int puntoEnSegmento(Vector p,Rayo segmento){
	if (pPunto(pCruz(rayoAVector(segmento),restaVector(segmento.origen,p)),
			  pCruz(rayoAVector(segmento),restaVector(segmento.origen,p)))>EPSILON)
		return 0;

	if((p.x - segmento.origen.x) * (p.x - segmento.direccion.x) > 0) return 0;
	if((p.y - segmento.origen.y) * (p.y - segmento.direccion.y) > 0) return 0;
	if((p.z - segmento.origen.z) * (p.z - segmento.direccion.z) > 0) return 0;

	return 1;
}