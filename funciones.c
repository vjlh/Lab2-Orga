#include "definiciones.h"
char REGISTROS_NOMBRES[9][6] = {"$zero","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$sp"};


void leerArchivosYGuardarDatos()		//Esta funcion se encarga del proceso de lectura y obtencion de los datos del archivo
{										//primero cuenta cuantas lineas tiene el archivo	
	FILE* archivo_instrucciones;		//hecho esto, pasa todas las instrucciones que están en el archivo
	//FILE* archivo_restricciones;		//a un arreglo de estructuras, almacenando el nombre de la instruccion  	
	int aux1, aux2, contador, i, largo, addis,sws;	//y los registros o direcciones de memoria involucrados en ella
	char buffer[100],buffer2[100],*valor1,*valor2, *valor3, *valor4;
										//La función no retorna nada ya que todo lo que va modificando son punteros
	contador = 0;						//A los valores de memoria y variables globales
	archivo_instrucciones = fopen(NOMBRE_ARCHIVO_1,"r"); //Por lo que solo necesita modificar sin retornar

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
	
	aux1 = 0;
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
				strcpy(listaDatos[aux1].funcion,valor1);
				valor2 = strtok(NULL,", ");
				strcpy(listaDatos[aux1].dato1,valor2);
				valor3 = strtok(NULL,", ");
				strcpy(listaDatos[aux1].dato2,valor3);
				valor4 = strtok(NULL," ");
				strcpy(listaDatos[aux1].dato3,valor4);
				addis++;
			}	

			else if ((strcmp(valor1,"lw"))==0 || (strcmp(valor1,"sw"))==0)
			{
				strcpy(listaDatos[aux1].funcion,valor1);
				valor2 = strtok(NULL,", ");
				strcpy(listaDatos[aux1].dato1,valor2);
				valor3 = strtok(NULL," ");
				strcpy(listaDatos[aux1].dato2,valor3);
				sws++;
			}

			else
				strcpy(listaDatos[aux1].funcion,valor1);
			aux1++;	
		}

		fgetc(archivo_instrucciones);
		if (feof(archivo_instrucciones))
			break;	
	}
	fclose(archivo_instrucciones);

	identificandoFormato(addis,sws);
	IF=0;
	ID=0;
	EX=0;
	MEM=0;
	WB=0;

}
void identificandoFormato(int addis,int sws)
{
	if(addis == 3 && sws > 0)
		FORMATO = 1;

	else if(sws == 0)
		FORMATO = 2;

	else
		FORMATO = 3;		
	printf("EL FORMATO ES: %i \n",FORMATO);
}
void asignando_jugador()
{
	strcpy(jugadores[0].nombre,listaDatos[0].dato1);
	jugadores[0].tipo = atoi(listaDatos[0].dato3);
	jugadores[0].aux = 0;
	strcpy(jugadores[1].nombre,listaDatos[1].dato1);
	jugadores[1].tipo = atoi(listaDatos[1].dato3);
	jugadores[1].aux = 0;


	for (int i = 0; i < 2; ++i)
	{
		printf("%s:%d\n",jugadores[i].nombre,jugadores[i].tipo);
	}

}
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
		funcion = listaDatos[aux1].funcion;
		if ((strcmp(funcion,"addi"))==0 || (strcmp(funcion,"subi"))==0)
		{
			dato1 = listaDatos[aux1].dato1;
			dato2 = listaDatos[aux1].dato2;
			dato3 = listaDatos[aux1].dato3;
			num3 = abs(atoi(dato3));
			ID++;	

			if((strcmp(funcion,"addi"))==0)
			{
				int jug1 = contiene(0,num3-1);
				int jug2 = contiene(1,num3-1);
				for (int i = 0; i < 2; ++i)
				{
					if (strcmp(dato1,jugadores[i].nombre)==0 && jug1 == 0 && jug2 == 0)
					{
						jugadores[i].jugadas[jugadores[i].aux] = num3-1;
						jugadores[i].aux = jugadores[i].aux + 1;
					}
				}
				EX++;
				WB++;	

			}
			else if((strcmp(funcion,"subi"))==0)
			{
				for (int i = 0; i < 2; ++i)
				{
					if (strcmp(dato1,jugadores[i].nombre)==0)
					{
						if (contiene(i,num3-1)==1)
							remover_jugada(i,num3-1);
						
					}
				}
				EX++;
				WB++;
			}
					
		}								//Registros despues de pasar por esta funcion, independiente de si haya o no
										//modificado uno de estos	
		else if (strcmp(funcion,"sw")== 0)
		{	
			dato1 = listaDatos[aux1].dato1;
			dato2 = listaDatos[aux1].dato2;
			strcpy(temp,dato2);
			ID++;
			dato2temp = strtok(temp,"(");
			temporal = atoi(dato2temp);
			EX++;

			if(temporal%4 == 0)
			{	
				MEM++;
				for (k = 0; k < 2; ++k)
					if (strcmp(dato1,jugadores[k].nombre)==0)
					{
						jugadores[k].jugadas[jugadores[k].aux] = (temporal/4);
						jugadores[k].aux = jugadores[k].aux +1;
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

	for (int i = 0; i < jugadores[0].aux; ++i)
		TABLERO[jugadores[0].jugadas[i]] = 1;

	for (int i = 0; i < jugadores[1].aux; ++i)
		TABLERO[jugadores[1].jugadas[i]] = 2;	
}
void remover_jugada(int jugador, int jugada)
{
	int aux = 0;

	for (int i = 0; i < jugadores[jugador].aux; ++i)
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
	jugadores[jugador].aux = jugadores[jugador].aux-1;

}

int contiene(int jugador, int jugada)
{
	for (int i = 0; i < jugadores[jugador].aux; ++i)
		if(jugadores[jugador].jugadas[i] == jugada)
			return 1;

	return 0;	
}

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

void escribir_archivo2() 
{
	FILE *salida2;
	salida2 = fopen("salida2.csv","wt");
	fprintf(salida2,"Etapa;Cantidad\nIF;%i\nID;%i\nEX;%i\nMEM;%i\nWB;%i\n",IF,ID,EX,MEM,WB);
	fclose(salida2);
}

void escribir_archivo1(int ganador)
{ 
	FILE *salida1;
	int index;
	salida1 = fopen("salida1.txt","wt");
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
		fprintf(salida1,"\n\nEl ganador es el jugador con el registro %s",jugadores[index].nombre);
	}
	else
		fprintf(salida1,"\n\nNo existe ganador en esta partida");

	fclose(salida1);
}
void recibirNombreArchivo() 
{
	FILE* arch;
	NOMBRE_ARCHIVO_1 = (char*)malloc(sizeof(char)*25);
	printf("Para comenzar primero se necesita el nombre de sus dos archivos de entrada junto a su formato\n");
	printf("Por ejemplo 'entrada1.txt' o prueba1.txt\n\nRecuerde que el primero es el que contiene las instrucciones y el segundo las lineas de control\n");
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
//Función encargada de liberar la memoria que se ocupó durante el procedimiento
void liberarMemoria()
{
	free(listaDatos);
	free(TABLERO);
	free(NOMBRE_ARCHIVO_1);
}