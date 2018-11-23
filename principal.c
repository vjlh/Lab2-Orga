#include "definiciones.h"
/*
 * En este archivo se encuentran las llamadas a las funciones que hacen la correcta ejecución
   del programa
 * @author: Valentina Ligueño
 * @version: 23/11/2018
 */
int main(int argc, char** argv)
{	
	recibirNombreArchivo();

	leerArchivosYGuardarDatos();

	asignando_jugador();

	desarrolloDeInstrucciones();
	comprobarGanador();

	liberarMemoria();
	printf("\nEl programa ha terminado su ejecucion correctamente, revise sus archivos de salida...\n");
}