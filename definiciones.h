#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

struct Datos
{
	char funcion[10];
	char dato1[10];
	char dato2[10];
	char dato3[10];
};

struct Jugadores
{
	char nombre[5];
	int tipo;
	int jugadas[5];
	int aux;
};

typedef struct Datos Datos;
typedef struct Jugadores Jugadores;

Datos *listaDatos;
Jugadores jugadores[2];

int NINTRUCCIONES;
int *TABLERO;
int FORMATO;
char *NOMBRE_ARCHIVO_1;
int IF;
int ID;
int EX;
int MEM;
int WB;

void escribir_archivo1(int);
void escribir_archivo2();
void leerArchivosYGuardarDatos();
void asignando_jugador();
void desarrolloDeInstrucciones();
void recibirNombreArchivo();
void liberarMemoria();
void identificandoFormato(int,int);
void remover_jugada(int , int );
int contiene(int , int );
void comprobarGanador();
