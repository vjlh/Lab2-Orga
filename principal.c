#include "definiciones.h"

int main(int argc, char** argv)
{	
	recibirNombreArchivo();

	leerArchivosYGuardarDatos();

	asignando_jugador();

	desarrolloDeInstrucciones();
	comprobarGanador();

	//liberarMemoria();
	printf("\nEl programa ha terminado su ejecucion correctamente, revise sus archivos de salida...\n");
}