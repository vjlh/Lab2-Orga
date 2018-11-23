#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

/*
 * En este archivo se encuentran las cabeceras de las funciones, las estructuras utilizadas
   y la declaración de las variables globales que se usan durante el programa
 * @author: Valentina Ligueño
 * @version: 23/11/2018
 */

struct Datos
{
	char funcion[10];
	char dato1[10];
	char dato2[10];
	char dato3[10];
};

struct Jugadores
{
	char registro[5];
	int tipo;
	int jugadas[6];
	int numJugadas;
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

void recibirNombreArchivo();
void leerArchivosYGuardarDatos();
void identificandoFormato(int,int);
void asignando_jugador();
void desarrolloDeInstrucciones();
void remover_jugada(int , int );
int contiene(int , int );
void comprobarGanador();
void escribir_archivo1(int);
void escribir_archivo2();
char* recibirNombreArchivoSalida(int,char*);
void liberarMemoria();

