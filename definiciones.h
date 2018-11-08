#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct Datos
{
	char funcion[10];
	char dato1[10];
	char dato2[10];
	char dato3[10];
	char estado;
};

struct Jugadores
{
	char nombre[10];
	int tipo;
	int jugadas[5];
};

typedef struct Datos Datos;
typedef struct Jugadores Jugadores;

Datos *listaDatos;
Jugadores jugadores[2];

int NINTRUCCIONES;
int *REGISTROS_VALOR;
int *ARREGLO_SP;
int JUGADAS[15];
int FORMATO;
char TABLERO[9];
char *NOMBRE_ARCHIVO_1;
char *NOMBRE_ARCHIVO_2;

void escribir_archivo(FILE *archivo);
void leerArchivosYGuardarDatos();
void newDesarrollo();
void desarrolloDeInstrucciones();
void escribir_archivo1();
void recibirNombreArchivo();
void liberarMemoria();
void identificandoFormato(int,int);
