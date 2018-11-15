#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

FILE *file;
int resultado[10];
double resultadoFloat[10];

void getFile(FILE *inFile){
    file = inFile;
}

FILE* retFile(){
	return file;
}

void readInt(){
    int x = 0;
    char * token;
    char caracter[100];
    

    if((fgets(caracter, 100, file))!= EOF){
    	token = strtok(caracter," ");
	while( token != NULL ) {
	  resultado[x] = atoi(token);
	  x++;
	  token = strtok(NULL, " ");
	}
    }
}

void readFloat(){
    int x = 0;
    char * token;
    char * token2;
    char caracter[100];
    

    if((fgets(caracter, 100, file))!= EOF){
        token = strtok(caracter, " ");
	    while( token != NULL ) {;
	      resultadoFloat[x] = strtof(token, &token2);
	      x++;
	      token = strtok(NULL, " ");
	    }
    } 
}

int getInt(int x){
    return resultado[x];
}

float getFloat(int x){
    return resultadoFloat[x];
}

