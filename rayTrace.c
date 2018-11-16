/* Tarea Programada #3
 * Autor: Mauricio Castillo Vega
 * Autor: Ricardo Sanchez Alpizar
 * Curso: Computer Graphics 2-2018
 * Profesor: Dr. Francisco Torres
 */

#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "rayTrace.h"
#include "estructuras.h" 
#include "estructuras.c"
#include "poligono.h"
#include "disco.h"

unsigned int ancho;
unsigned int alto;
int muestras;
unsigned int numeroCuerpos;
unsigned int epsilon = 0.000001;

//Variables globales y de funcionamiento
float pixeles[5008*5000*3];

cuerpo* objetos;
int totalEsferas;
Vector luces[1000];

Vector e;
float d = 10;

Vector w;
Vector u;
Vector v;

float facAtenuacion;

float izq = -8.064, der = 8.064;
float abajo = -4.536, arriba = 4.536;

float luz;
int numeroLuces;
float intensidadAmbiente;

Color colorFondo;

bool llaveAntiAlias, llaveRefleccion;
bool llaveTransparencia, llaveProfundidad;

FILE *file; 

// Inicio de las funciones de trabajo
int escribirArchivo() {

    FILE *fp = fopen("out.tga", "w");
    if (fp == NULL) return 0;

    // The image header
    char header[18] = {0}; // char = byte
    header[2] = 2; // truecolor
    header[12] = ancho & 0xFF;
    header[13] = (ancho >> 8) & 0xFF;
    header[14] = alto & 0xFF;
    header[15] = (alto >> 8) & 0xFF;
    header[16] = 24; // bits per pixel

    fwrite((const char *) &header, 1, sizeof(header), fp);
    int ipos;
    for (int y = 0; y < alto; y++)
        for (int x = 0; x < ancho; x++) {
            ipos = (3*y*ancho) +(x*3); //
            
            fputc((int) (pixeles[ipos+2] * 255), fp);
            fputc((int) (pixeles[ipos+1] * 255), fp);
            fputc((int) (pixeles[ipos+0] * 255), fp);
        }

    // The file footer
    static const char footer[26] =
            "\0\0\0\0" 
            "\0\0\0\0" 
            "TRUEVISION-XFILE" 
            ".";
    fwrite((const char *) &footer, 1, sizeof(footer), fp);

    fclose(fp);
    return 1;
}

void inicioVectores() {
    getFile(file);
    readInt();
    ancho = getInt(0);
    alto = getInt(1);
    readInt();
    muestras = getInt(0);
    llaveAntiAlias = (bool)getInt(1);
    llaveRefleccion = (bool)getInt(2);
    llaveTransparencia = (bool)getInt(3);
    llaveProfundidad = (bool)getInt(4);
    readInt();
    numeroCuerpos = getInt(0);

    readFloat();
    facAtenuacion = getFloat(0);
    readFloat();
    luz = getFloat(0);
    readInt();
    numeroLuces = getInt(0);
    readFloat();
    intensidadAmbiente = getFloat(0);
    
    int r,g,b;
    float x,y,z;
    readInt();
    r = getInt(0);
    g = getInt(1);
    b = getInt(2);
    
    colorFondo = setColor(r, g, b);
    readFloat();
    x = getFloat(0);
    y = getFloat(1);
    z = getFloat(2);
    e = setVector(x, y, z);

    readFloat();
    x = getFloat(0);
    y = getFloat(1);
    z = getFloat(2);

    Vector vecSuperior = setVector(x, y, z);

    readFloat();
    x = getFloat(0);
    y = getFloat(1);
    z = getFloat(2);

    Vector vistaDireccion = setVector(x, y, z);

    w = escalaVector(vistaDireccion,-1/magnitud(vistaDireccion));
    Vector vecPCruz = pCruz(vecSuperior, w);
    u = escalaVector(vecPCruz,1/magnitud(vecPCruz));
    v = pCruz(w, u);
    for (int i = 0; i < numeroLuces; ++i)
    {
    	readFloat();
    	x = getFloat(0);
    	y = getFloat(1);
    	z = getFloat(2);
        luces[i] = setVector(x,y,z);
        luces[i] = escalaVector(luces[i],1/magnitud(luces[i]));
    }

    objetos = (cuerpo*)malloc((numeroCuerpos)* sizeof(cuerpo));

    for (int i = 0; i < numeroCuerpos; ++i)
	{
		objetos[i].id = i;
		objetos[i].ri = 0;
		objetos[i].refleccion = 1;
        objetos[i].obj = readSolid();
        if (objetos[i].obj->tipo == 0)
        {
            objetos[i].interseccion = calculoInterseccion;
            objetos[i].normal = normalEsfera;
        }
        if (objetos[i].obj->tipo == 3){
            objetos[i].interseccion = puntoEnPlano;
            objetos[i].normal = calcularNormalPoligono;
        }
        if (objetos[i].obj->tipo == 4){
            objetos[i].interseccion = calculoInterseccionDisco;
            objetos[i].normal = calcularNormalDisco;
        }
        if (objetos[i].obj->tipo == 5){
            objetos[i].interseccion = calculoInterseccionElipse;
            objetos[i].normal = calcularNormalElipse;
        }
    } 
}

bool sombra(Rayo rayo){
    for (int i = 0; i < numeroCuerpos; i++)
    {
        if (objetos[i].interseccion(objetos[i].obj, rayo)>0)
        {
            return true;
        }
    }
    return false;
}

float choqueEscena(Rayo rayo, Choque* choque){

    float valor = 0;
    float valorFinal = 9999999;
    float resultado = -1;

    for(int i=0; i<numeroCuerpos; i++){
        //calculoInterseccion(rayo,objetos[i].obj)
        valor = objetos[i].interseccion(objetos[i].obj, rayo);
        //printf("%d",valor);
        if (valor > 0 && valor < valorFinal){
            //printf("%f",valor);
            resultado = valor;
            choque->objeto = &objetos[i]; 
        }
    }
    choque->t = resultado;
}

Rayo analisisRayoVision(float i, float j, Vector origen){
    Rayo rayo;

    float us = izq + (der-izq) * (i+0.5) / ancho;
    float vs = abajo + (arriba-abajo) * (j+0.5) / alto;

    rayo.origen = origen;
    rayo.direccion = restaVector(sumaVector(escalaVector(u,us),escalaVector(v,vs)), rayo.origen);
    rayo.direccion = escalaVector(rayo.direccion,1/magnitud(rayo.direccion));

    return rayo;
}

Color blur(Vector vector,Color color, int numluces){
    float valor = pPunto(vector,luces[numluces]);
    float max = (valor > 0) ? valor : 0;
    float escala = luz * max;

    return aumentoColor(color,escala);
}

Color ambiente(Color color){
    return aumentoColor(color,intensidadAmbiente);
}

Color choqueRayo(Rayo rayo, int valor){
    Choque choque;
    Solido figSolido;
    choqueEscena(rayo,&choque);

    if(choque.t > epsilon){
        //figSolido = *(Solido*)(choque.objeto->obj);
        choque.p = sumaVector(rayo.origen, escalaVector(rayo.direccion,choque.t-0.01));
        choque.n = choque.objeto->normal(choque.objeto->obj, choque.p, rayo.direccion);

        //choque.n = escalaVector(restaVector(choque.p, figSphere.c),-1/figSphere.r);
        //choque.n = escalaVector(choque.n,1/magnitud(choque.n));
        return shade(choque, rayo, valor);
    }
    return colorFondo;
}

Color colorEspecular(Rayo rayo, Vector vectorIn, int numLuz){
    Color color = setColor(250,250,250);
    unsigned int potencia = 40;

    Vector vectorVista = escalaVector(rayo.direccion,1/magnitud(rayo.direccion));
    Vector vector = sumaVector(vectorVista,luces[numLuz]);
    vector = escalaVector(vector,1/magnitud(vector));

    float ppVectores = pPunto(vectorIn,vector);
    float max = (ppVectores > 0)? ppVectores : 0;

    max = pow(max,potencia);

    float escala = max * luz;

    return aumentoColor(color,escala);
}

Rayo calculoSombra(Vector vector, Vector iluminacion){
    Rayo sombra;
    sombra.origen = vector;
    sombra.direccion = escalaVector(iluminacion,-1);
    return sombra;
}

Vector refleccion(Vector direccion, Vector normal){
    Vector vector = escalaVector(direccion,1/magnitud(direccion));
    return restaVector(vector,escalaVector(normal,2*pPunto(vector,normal)));
}

bool refraccion(Vector vectorInA, Vector vectorInB, float valor, Vector *temp){

    Vector temp1 = escalaVector(restaVector(vectorInA, escalaVector(vectorInB, pPunto(vectorInA, vectorInB))),1/valor);
    float raiz = 1 - (1 - pow(pPunto(vectorInA, vectorInB), 2.0)) / pow(valor, 2.0);
    
    if (raiz < 0) {
        return false;
    }
	
    Vector temp2 = escalaVector(vectorInB,sqrt(raiz));
    *temp = restaVector(temp1, temp2);
    *temp = escalaVector(*temp,1/magnitud(*temp));
	
    return true;
}

Color atenuacion(float factor, Color color) {
    Color salida;
    salida.r = color.r * factor;
    salida.g = color.g * factor;
    salida.b = color.b * factor;
    return salida;
}

Color shade(Choque choque, Rayo rayo, int valor){
    Color color = setColor(0,0,0);
    Solido figSolid;
    cuerpo* figBody;

    figBody = (cuerpo*)choque.objeto;
    figSolid = (*(Solido*) figBody->obj);

    color = ambiente(figSolid.color);

    for (int i = 0; i < numeroLuces; i++){
        Rayo rayoSombra = calculoSombra(choque.p,luces[i]);

        if (!sombra(rayoSombra)) {
            //color = atenuacion(facAtenuacion,color);
            color = sumaColor(color, blur(choque.n, figSolid.color, i));
            color = sumaColor(color, colorEspecular(rayo, choque.n, i));
        }
    }

    if (llaveRefleccion && figBody->refleccion && valor > 0) {
        Rayo rayoRefleccion;
        rayoRefleccion.origen = choque.p;
        rayoRefleccion.direccion = refleccion(rayo.direccion, choque.n);
        color = sumaColor(color, aumentoColor(choqueRayo(rayoRefleccion, valor-1), 0.25));
    }

    if (llaveTransparencia && figBody->ri != 1 && valor > 0) {
        Vector vectorR = refleccion(rayo.direccion, choque.n);
        float kr, kg, kb;
        Rayo rayo1, rayo2;
        Vector temp;
        float valTemp;

        if (pPunto(rayo.direccion, choque.n) < 0) {
            refraccion(rayo.direccion, choque.n, figBody->ri, &temp);
            valTemp = pPunto(escalaVector(rayo.direccion,-1), choque.n);
        } else {
            if (refraccion(rayo.direccion, escalaVector(choque.n,-1), 1/ figBody->ri, &temp)) {
                valTemp = pPunto(temp, choque.n);
            } else {
                rayo1.origen= choque.p;
                rayo1.direccion = vectorR;
                return sumaColor(color, choqueRayo(rayo1, valor-1));
            }
        }

        float r0 = pow(figBody->ri-1, 2.0) / pow(figBody->ri+1, 2.0);
        float r1 = r0 + (1-r0) * pow(1-valTemp, 5.0);

        rayo1.origen = choque.p;
        rayo1.direccion = vectorR;

        rayo2.origen = choque.p;
        rayo2.direccion = temp;

        return sumaColor(color,sumaColor(aumentoColor(choqueRayo(rayo1, valor-1), r1), 
            aumentoColor(choqueRayo(rayo2, valor-1), (1-r1))));
    }
    return color;
}

Color AntiAlias(int antiX, int antiY){
    //float muestras = 6;
    Color color = setColor(0,0,0);
    float x,y;
    float r;

    for(int i=0;i<muestras;i++){
        for(int j=0;j<muestras;j++){
			r = (rand()%100)/100.0f;
			
			x = (float)antiX + ((float)i+r)/muestras;
			y = (float)antiY + ((float)j+r)/muestras;
			
			Vector ojo = e;
			
			if(llaveProfundidad){
				ojo.y += ((float)j+r)/muestras;
				ojo.z += ((float)i+r)/muestras;
			}
			
			Rayo rayoVision = analisisRayoVision(x,y,ojo);
			color = sumaColor(color,choqueRayo(rayoVision,3));
        }
    }

    return aumentoColor(color,1/pow(muestras,2.0));
}

void display(){

    srand(time(NULL));

    Solido figSolid;
    disco figSphere;
    cuerpo* figBody;
    
    for (int i = 0; i < 0; ++i)
    {
        figBody = (cuerpo*)objetos[i].obj;
        figSolid = (*(Solido*) figBody);
        figSphere = (*(disco*) figSolid.figura);
        printf("%d\n", i);
        printf("puntos: %d\n", figSphere.cantidadPuntos);
        printf("Radio: %f\n",figSphere.r);
        printf("Radio pequeño: %f\n",figSphere.rPeq);
        printf("r: %f\n", figSolid.color.r);
        printf("g: %f\n", figSolid.color.g);
        printf("b: %f\n", figSolid.color.b);
        printf("c: %f\n", figSphere.c);
        printf("a: %f\n", figSphere.a);
        printf("b: %f\n", figSphere.b);
        printf("d: %f\n", figSphere.d);
    }

    //free(figSphere);
    //free(figSolid);
    //free(cuerpo);

    for (int i=0; i<ancho-1; i++) {
        for (int j=0; j<alto-1; j++) {
            
            Color color;

            if (llaveAntiAlias || llaveProfundidad) {
                color = AntiAlias(i,j);
            } else {
                color = choqueRayo(analisisRayoVision(i,j,e), 5);
            }

            int ipos = 3*(j*ancho+i);
            setColorPixel(color, &pixeles[ipos]);
        }
    }
    printf("fin Ray-Tracer\n");
    escribirArchivo();
    printf("Fin creacioArchivo\n");
}

int main(int argc, char** argv){
    
    char* ruta;
    if (argc != 2){
        printf("Los argumentos son insuficientes o tiene argumentos de más\n");
        exit(1);
    }
    if(argc == 2){
        ruta = argv[1];
        file = fopen(ruta,"r");
        if(file == NULL){
            printf("fallo\n");
            exit(0);
        }
    }
    inicioVectores();
    display();
    return 0;
}
