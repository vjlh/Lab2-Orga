#include "definiciones.h"

int main(int argc, char** argv)
{	
	recibirNombreArchivo();

	leerArchivosYGuardarDatos();

	newDesarrollo();

	desarrolloDeInstrucciones();

	for (int i = 0; i < 9; ++i)
	{
		if(i%3 == 0)
			printf("\n");
		if (ARREGLO_SP[i] == 1)
			printf("|X|");
		else if (ARREGLO_SP[i] == 2)
			printf("|O|");
			
	}
			printf("\n\n");

	//escribir_archivo1();
	//liberarMemoria();
	//printf("\nEl programa ha terminado su ejecucion correctamente, revise sus archivos de salida...\n");
}