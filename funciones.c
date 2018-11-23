#include "definiciones.h"
/*
 * En este archivo se encuentran todas las funciones que se utilizan para el correcto funcionamiento
   del programa
 * @author: Valentina Ligueño
 * @version: 23/11/2018
 */


/*
 * Esta función se encarga de recibir el nombre del archivo de entrada, asegurandose de que
   se entregue un archivo existente.
 * @return No retorna nada, ya que el nombre del archivo queda guardado en una variable global
 */
void recibirNombreArchivo() 
{
	FILE* arch;
	NOMBRE_ARCHIVO_1 = (char*)malloc(sizeof(char)*25);
	printf("Para comenzar primero se necesita el nombre de su archivo de entrada junto a su formato\n");
	printf("Por ejemplo 'entrada.txt' o prueba.txt\n");
	do
	{
		printf("\nIngrese el nombre del primer archivo solicitado: ");
		scanf("%s",NOMBRE_ARCHIVO_1);
		while(getchar()!='\n');
		arch = fopen(NOMBRE_ARCHIVO_1,"r");
		
		if (arch == NULL) 
			printf("No se encuentra archivo con ese nombre, intente nuevamente\n");
		
	} while (arch == NULL);
	fclose(arch);
}

/*
 * Esta funcion se encarga del proceso de lectura y obtencion de los datos del archivo 
 * @return No retorna nada porque los datos se almacenan en una estructura declarada de manera
 	global
 */
void leerArchivosYGuardarDatos()		
{											
	FILE* archivo_instrucciones;	 	
	int linea, aux2, contador, i, largo, addis, sws;
	char buffer[100],buffer2[100],*valor1,*valor2, *valor3, *valor4;
									
	archivo_instrucciones = fopen(NOMBRE_ARCHIVO_1,"r");
	contador = 0;
	while (!feof(archivo_instrucciones))
	{
		memset(buffer,0, 100);
		aux2 = 1;
		fscanf(archivo_instrucciones, "%119[^\n]", buffer);

		for (i = 0; i < strlen(buffer); ++i)
			if (buffer[i] == ' ')
				aux2++;

		if (buffer[0] != '\0' && aux2 != strlen(buffer) && buffer[0] != '#')
			contador++;

		fgetc(archivo_instrucciones);
	}
	fclose(archivo_instrucciones);

	NINTRUCCIONES = contador;
	listaDatos = (Datos*)malloc(sizeof(Datos)*NINTRUCCIONES);
	
	archivo_instrucciones = fopen(NOMBRE_ARCHIVO_1,"r");
	
	linea = 0;
	addis = 0;
	sws = 0;

	while (!feof(archivo_instrucciones))
	{
		memset(buffer,0, 100);
		memset(buffer2,0, 100);
		aux2 = 1;
		fscanf(archivo_instrucciones," %119[^\n]",buffer);
		largo = strlen(buffer);

		for (i = 0; i < largo; ++i)
			if (buffer[i] == ' ')
				aux2++;

		if (buffer[0] != '\0' && aux2 != largo && buffer[0] != '\n'&& buffer[0] != '#')
		{	
			for (i = 0; i < largo; ++i)
				if (buffer[i] != ' ')
					break;

			strncpy(buffer2,buffer+i,largo-i);
			
			if (aux2==1)
				valor1 = strtok(buffer2,":");

			else
				valor1 = strtok(buffer2," ");

			if ((strcmp(valor1,"addi"))==0 || (strcmp(valor1,"subi"))==0)
			{
				strcpy(listaDatos[linea].funcion,valor1);
				valor2 = strtok(NULL,", ");
				strcpy(listaDatos[linea].dato1,valor2);
				valor3 = strtok(NULL,", ");
				strcpy(listaDatos[linea].dato2,valor3);
				valor4 = strtok(NULL," ");
				strcpy(listaDatos[linea].dato3,valor4);
				addis++;
			}	

			else if ((strcmp(valor1,"sw"))==0)
			{
				strcpy(listaDatos[linea].funcion,valor1);
				valor2 = strtok(NULL,", ");
				strcpy(listaDatos[linea].dato1,valor2);
				valor3 = strtok(NULL," ");
				strcpy(listaDatos[linea].dato2,valor3);
				sws++;
			}
			linea++;	
		}

		fgetc(archivo_instrucciones);
		if (feof(archivo_instrucciones))
			break;	
	}
	fclose(archivo_instrucciones);
	identificandoFormato(addis,sws);

}
/*
 * Esta funcion se encarga del proceso de identificar si se recibió el formato 1 2 o 3 de archivo 
 * @return No retorna nada porque el número de formato se almacena en una variable global
 */
void identificandoFormato(int addis,int sws)
{
	if(addis == 3 && sws > 0)
		FORMATO = 1;

	else if(sws == 0)
		FORMATO = 2;

	else
		FORMATO = 3;		
}
/*
 * Se hace el camino de datos para las dos primeras instrucciones, para asignar al registro
   su valor correspondiente 
 * @return No retorna nada porque la estructura jugadores está declarada de manera global para
 		   poder acceder a ella desde cualquier función.
 */
void asignando_jugador()
{
	strcpy(jugadores[0].registro,listaDatos[0].dato1);
	jugadores[0].tipo = atoi(listaDatos[0].dato3);
	jugadores[0].numJugadas = 0;
	strcpy(jugadores[1].registro,listaDatos[1].dato1);
	jugadores[1].tipo = atoi(listaDatos[1].dato3);
	jugadores[1].numJugadas = 0;
	IF=2;
	ID=2;
	EX=2;
	MEM=0;
	WB=2;
}

/*
 * Se hace el desarrollo para el resto de las instrucciones, es decir para las jugadas, se pasan
   todas estas por el camino de datos y se almacenan las jugadas en un arreglo de la estructura
   jugadores, al final de la función estos arreglos contienen como quedaron las jugadas despues
   de ser leídas todas las lineas de instrucción y dichas jugadas son traspasadas al tablero
 * @return No retorna nada porque tanto la estructura jugadores como el tablero están 
 		   declarados de manera global para poder acceder a ellos desde cualquier función.
*/
void desarrolloDeInstrucciones()
{
	int i, k, aux1, num3, temporal;
	char *funcion, *dato1, *dato2, *dato3, *dato2temp, temp[10];

	if((FORMATO == 1 || FORMATO == 3) && strcmp(listaDatos[2].dato1,"$sp")==0)
	{
		dato3 = listaDatos[2].dato3;
		num3 = abs(atoi(dato3));

		if(num3 == 36)
		{
			TABLERO = (int*)malloc(sizeof(int)*9);
			for (i = 0; i < 9; ++i)
				TABLERO[i] = 0;
			aux1 = 3;
			IF++;
			ID++;
			EX++;
			WB++;
		}
		else
		{
			printf("Error de formato, intente con un archivo valido\n");
			exit(1);
		}
	}

	else
	{
		TABLERO = (int*)malloc(sizeof(int)*9);
			for (i = 0; i < 9; ++i)
				TABLERO[i] = 0;
		aux1 = 2;
	}
	

	while (aux1<NINTRUCCIONES) //Con este while se irá recorriendo la estructura, donde aux irá desde ¡
	{						   //Hasta el numero total de instrucciones que fue contado al comienzo de esta función
		IF++;
		ID++;	
		dato1 = listaDatos[aux1].dato1;
		dato2 = listaDatos[aux1].dato2;
		dato3 = listaDatos[aux1].dato3;
		
		funcion = listaDatos[aux1].funcion;
		if ((strcmp(funcion,"addi"))==0 || (strcmp(funcion,"subi"))==0)
		{
			num3 = abs(atoi(dato3));
			EX++;
			if((strcmp(funcion,"addi"))==0)
			{
				int jug1 = contiene(0,num3-1);
				int jug2 = contiene(1,num3-1);

				for (int i = 0; i < 2; ++i)
					if (strcmp(dato1,jugadores[i].registro)==0 && jug1 == 0 && jug2 == 0)
					{
						jugadores[i].jugadas[jugadores[i].numJugadas] = num3-1;
						jugadores[i].numJugadas = jugadores[i].numJugadas + 1;
						WB++;	
					}	
			}
			else if((strcmp(funcion,"subi"))==0)
				for (int i = 0; i < 2; ++i)
					if (strcmp(dato1,jugadores[i].registro)==0)
						if (contiene(i,num3-1)==1)
						{
							remover_jugada(i,num3-1);
							WB++;
						}
		}								//Registros despues de pasar por esta funcion, independiente de si haya o no
										//modificado uno de estos	
		else if (strcmp(funcion,"sw")== 0)
		{	
			strcpy(temp,dato2);
			dato2temp = strtok(temp,"(");
			temporal = atoi(dato2temp);
			EX++;

			if(temporal%4 == 0)
			{	
				for (k = 0; k < 2; ++k)
					if (strcmp(dato1,jugadores[k].registro)==0)
					{
						MEM++;
						jugadores[k].jugadas[jugadores[k].numJugadas] = (temporal/4);
						jugadores[k].numJugadas = jugadores[k].numJugadas +1;
					}	
			}		
			else if(temporal%4 != 0)
			{
				printf("No se puede ejecutar el programa, ya que StoreWord presenta un error en uno de sus parametros\n");
				exit(0);
			}		
		}		
		aux1++;
	}

	for (int i = 0; i < jugadores[0].numJugadas; ++i)
		TABLERO[jugadores[0].jugadas[i]] = 1;

	for (int i = 0; i < jugadores[1].numJugadas; ++i)
		TABLERO[jugadores[1].jugadas[i]] = 2;	
}

/*
 * Esta función se encarga de remover la jugada del arreglo de jugadas de un jugador
   cuando se lee la instrucción subi
   @param jugador: entero que puede ser 1 o 2 según el jugador que sea que quiera eliminar la jugada
   @param jugada: entero que representa la posición en el tablero de la jugada a eliminar
 * @return No retorna nada porque la estructura jugadores está declarada de manera global para
 		   poder acceder a ella desde cualquier función.
 */
void remover_jugada(int jugador, int jugada)
{
	int aux = 0;

	for (int i = 0; i < jugadores[jugador].numJugadas; ++i)
	{
		if(jugadores[jugador].jugadas[i] == jugada)
		{
			jugadores[jugador].jugadas[aux] = jugadores[jugador].jugadas[i+1];
			i++;
		}
		else
			jugadores[jugador].jugadas[aux] = jugadores[jugador].jugadas[i];
		aux++;
	}
	jugadores[jugador].numJugadas = jugadores[jugador].numJugadas-1;

}

/*
 * Esta función se encarga de verificar si una jugada está asociada o no a un jugador determinado
   existe para cuando aparece la instrucción subi y debe verificarse que el jugador que realizó
   la jugada es el que quiere borrarla
   @param jugador: entero que puede ser 1 o 2 según el jugador al que se le busque la jugada
   @param jugada: entero que representa la posición en el tablero de la jugada a buscar
 * @return Retorna un entero, 1 si la jugada está y 0 si no está
 */
int contiene(int jugador, int jugada)
{
	for (int i = 0; i < jugadores[jugador].numJugadas; ++i)
		if(jugadores[jugador].jugadas[i] == jugada)
			return 1;

	return 0;	
}

/*
 * Esta función se encarga de verificar si en el tablero existe o no una jugada ganadora, solo
   es invocada cuando al tablero ya se le hizo el traspaso de todas las jugadas
 * @return No retorna nada, pero una vez que descubre quien es el ganador si es que lo hay
 		   llama a las funciones encargadas de crear los archivos de salida 
 */
void comprobarGanador()
{
	int ganador = 0;
	bool l1 = (TABLERO[0] == TABLERO[1] && TABLERO[1] == TABLERO[2]);
	bool l2 = (TABLERO[3] == TABLERO[4] && TABLERO[4] == TABLERO[5]);
	bool l3 = (TABLERO[6] == TABLERO[7] && TABLERO[7] == TABLERO[8]);

	bool c1 = (TABLERO[0] == TABLERO[3] && TABLERO[3] == TABLERO[6]);
	bool c2 = (TABLERO[1] == TABLERO[4] && TABLERO[4] == TABLERO[7]);
	bool c3 = (TABLERO[2] == TABLERO[5] && TABLERO[5] == TABLERO[8]);

	bool d1 = (TABLERO[0] == TABLERO[4] && TABLERO[4] == TABLERO[8]);
	bool d2 = (TABLERO[2] == TABLERO[4] && TABLERO[4] == TABLERO[6]);

	if(l1)
		ganador = TABLERO[0];

	else if(l2)
		ganador = TABLERO[3];

	else if(l3)
		ganador = TABLERO[6];

	else if(c1)	
		ganador = TABLERO[0];

	else if(c2)
		ganador = TABLERO[1];

	else if(c3)	
		ganador = TABLERO[2];

	else if(d1)	
		ganador = TABLERO[0];

	else if(d2)	
		ganador = TABLERO[2];

	escribir_archivo1(ganador); 
	escribir_archivo2(); 
}

/*
 * Esta función se encarga de crear el primer archivo de salida, por lo tanto toma los valores
   existentes en el tablero (que en un principio tiene 1 y 2 en las jugadas ya que ese es el 
   valor que se le asocia a cada registro) y se transforman a X u O para el tablero que se le
   muestra al usuario, si hay un campo sin jugada se deja con un espacio, además se encarga de
   escribir al ganador de la partida y también si no existe ganador lo indica
 * @param ganador: entero que puede ser 0, 1 o 2, el cero indica que no existe ganador y el 1 y 2
 	indica si gano el jugador 1 o 2 respectivamente
 * @return No retorna nada, ya que el contenido es escrito en el archivo 
 */
void escribir_archivo1(int ganador)
{ 
	FILE *salida1;
	int index; 
	char* nombreArchivo = recibirNombreArchivoSalida(1,".txt");
	salida1 = fopen(nombreArchivo,"wt");
	for (int i = 0; i < 9; ++i)
	{
		if (i%3 == 0 && i>0)
			fprintf(salida1,"\n");
		if (TABLERO[i] == 1)
			fprintf(salida1,"|X|");
		else if (TABLERO[i] == 2)
			fprintf(salida1,"|O|");
		else if (TABLERO[i] == 0)
			fprintf(salida1,"| |");
	}
	if (ganador != 0)
	{
		if (jugadores[0].tipo == ganador)
			index = 0;
		else
			index = 1;
		fprintf(salida1,"\n\nEl ganador es el jugador con el registro %s",jugadores[index].registro);
	}
	else
		fprintf(salida1,"\n\nNo existe ganador en esta partida");

	fclose(salida1);
}

/*
 * Esta función se encarga de crear el segundo archivo de salida, por lo tanto toma los valores
   de IF, ID, EX, MEM Y WB y los escribe en un archivo de texto en formato Excel.
 * @return No retorna nada, ya que el contenido es escrito en el archivo 
 */
void escribir_archivo2() 
{
	FILE *salida2;
	char* nombreArchivo = recibirNombreArchivoSalida(2,".csv");
	salida2 = fopen(nombreArchivo,"wt");
	fprintf(salida2,"Etapa;Cantidad\nIF;%i\nID;%i\nEX;%i\nMEM;%i\nWB;%i\n",IF,ID,EX,MEM,WB);
	fclose(salida2);
}

/*
 * Esta función se encarga de recibir el nombre de los archivos de salida, es invocada por cada
   función encargada de la escritura de los datos.
   @param i: entero que indica para cual archivo de salida corresponde el nombre si el 1 o el 2
   @param formato: string que le asigna la extensión al nombre de archivo indicado por el usuario
   	pudiendo este ser .txt o .csv
 * @return Retorna el nombre del archivo junto con su extensión.
 */
char* recibirNombreArchivoSalida(int i, char* formato) 
{
	char* fileOut;
	bool validar;
	fileOut = (char*)malloc(sizeof(char)*30);

	printf("\nPara guardar los resultados se necesita el nombre de su archivo de salida número %i, este será guardado por defecto en %s\n",i,formato);
	do
	{
		validar = false;
		printf("\nIngrese el nombre para el archivo: ");
		scanf("%s",fileOut);	
		for (int i = 0; i < strlen(fileOut); ++i)
		{
			if (fileOut[i] == '\\' || fileOut[i] == '/' || fileOut[i] == ':' || fileOut[i] == '*' || fileOut[i] == '?' || fileOut[i] == '<' || fileOut[i] == '>' || fileOut[i] == '|')
				validar = true;
		}

		if (!validar) 
			validar = false;

		else
			printf("\nEl nombre escogido no debe poseer ninguno de los siguientes carácteres: \\/ : * ? < > | intente nuevamente\n");

		
	} while (validar);
	while(getchar()!='\n');
	strcat(fileOut,formato);

	return fileOut;

}

/*
 * Esta función se encarga de liberar todos los arreglos o variables globales que reservaron 
   memoria dinamicamente de la memoria, es decir los que no son estáticos.
 * @return No retorna nada, ya que solo libera memoria
 */
void liberarMemoria()
{
	free(listaDatos);
	free(TABLERO);
	free(NOMBRE_ARCHIVO_1);
}