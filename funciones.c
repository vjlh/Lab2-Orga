#include "definiciones.h"
char REGISTROS_NOMBRES[9][6] = {"$zero","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$sp"};
int IF;
int ID;
int EX;
int MEM;
int WB;

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
	REGISTROS_VALOR = (int*)malloc(sizeof(int)*9);

	for (i = 0; i < 9; ++i)
		REGISTROS_VALOR[i] = 0;
	
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

	for (int i = 0; i < 9; ++i)
	{	
		if(strcmp(REGISTROS_NOMBRES[i],listaDatos[0].dato1)==0)
			REGISTROS_VALOR[i] = atoi(listaDatos[0].dato3);
		
		if(strcmp(REGISTROS_NOMBRES[i],listaDatos[1].dato1)==0)
			REGISTROS_VALOR[i] = atoi(listaDatos[1].dato3);
	}
	/*for (int i = 0; i < 9; ++i)
	{
		printf("%s:%d\n",REGISTROS_NOMBRES[i],REGISTROS_VALOR[i]);
	}*/

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
void newDesarrollo()
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
	//esta funcion es la encargada de leer las instrucciones almacenadas por la funcion anterior una a una
	//Haciendo lo que cada instrucción requiere, por ejemplo si es un add, sumará, un sub restará,etc
	
	//Declaracion de variables a utilizar	
	int i, k, aux1, num3, temporal;
	char *funcion, *dato1, *dato2, *dato3, *dato2temp, temp[10];
	//FILE* solucion;
	//solucion = fopen("salida2.csv","wt");
	//fputs("Registro/Instruccion;",solucion);	

	//for (i = 0; i < 31; ++i)
	//	fprintf(solucion,"%s;",REGISTROS_NOMBRES[i]);

	//fputc('\n',solucion);
	
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
		funcion = listaDatos[aux1].funcion;
		if ((strcmp(funcion,"addi"))==0 || (strcmp(funcion,"subi"))==0)
		{
			dato1 = listaDatos[aux1].dato1;
			dato2 = listaDatos[aux1].dato2;
			dato3 = listaDatos[aux1].dato3;
			num3 = abs(atoi(dato3));


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
			}			
		}								//Registros despues de pasar por esta funcion, independiente de si haya o no
										//modificado uno de estos	
		else if (strcmp(funcion,"sw")== 0)
		{	
			dato1 = listaDatos[aux1].dato1;
			dato2 = listaDatos[aux1].dato2;
			strcpy(temp,dato2);

			dato2temp = strtok(temp,"(");
			temporal = atoi(dato2temp);

			if(temporal%4 == 0)
			{	
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
			
		else if (strcmp(funcion,"lw")== 0)
		{	
			dato1 = listaDatos[aux1].dato1;
			dato2 = listaDatos[aux1].dato2;
			strcpy(temp,dato2);

			dato2temp = strtok(temp,"(");
			temporal = atoi(dato2temp);

			if(temporal%4 == 0)
			{	
				for (k = 0; k < 31; ++k)
					if (strcmp(dato1,REGISTROS_NOMBRES[k])==0)
					{	
						REGISTROS_VALOR[k] = TABLERO[(temporal/4)];
						break;
					}
			}
			else if(temporal%4 != 0)
			{
				printf("No se puede ejecutar el programa, ya que LoadWord presenta un error en uno de sus parametros\n");
				exit(0);
			}			

		}
		aux1++;
	}

	for (int i = 0; i < 2; ++i)
	{
		printf("\nLas jugadas del jugador %i son: \n",i);
		for (int j = 0; j < jugadores[i].aux; ++j)
			printf("%i-",jugadores[i].jugadas[j]);

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
	{
		if(jugadores[jugador].jugadas[i] == jugada)
			return 1;
	}
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

	printf("El ganador es el jugador %i\n",ganador);
	for (int i = 0; i < 9; ++i)
	{
		if(i%3 == 0)
			printf("\n");
		printf("|%i|",TABLERO[i]);
	}
	printf("\n");

}

/*
Entra: [3, 5, 7, 1, 2]
jugada = 3
1º ciclo i = 0
	[5,5,7,1,2]
2º ciclo i = 2
	[]	

	
*/
/*void escribir_archivo(FILE *archivo) 
{ //Escribe los valores de los 32 registros cada vez que se le llama, que es cada vez que se ejecuta una instruccion
	int i; //Estos valores van siendo escritos en el archivo de salida 1
	for (i = 0; i < 31; ++i)
		fprintf(archivo,"%d;",REGISTROS_VALOR[i]);
	
	fputc('\n',archivo);
}

void escribir_archivo1()
{ //Busca que funciones si se ejecutaron y las escribe todas en unen el archivo con las lineas de instrucciones
	int i; //que hicieron que el programa se ejecutaron, no aparecen funciones que el programa no recorrió
	char* valor1;//Principalmente por estar en una "etiqueta" a la que nunca se llegaba
	FILE *salida1;
	salida1 = fopen("salida1.txt","wt");

	for (i = 0; i < NINTRUCCIONES; ++i)
	{
		if (listaDatos[i].uso == 1)
		{	
			valor1 = listaDatos[i].funcion;
			if ((strcmp(valor1,"addi"))==0 || (strcmp(valor1,"subi"))==0 || (strcmp(valor1,"add"))==0 
				|| (strcmp(valor1,"sub"))==0 || (strcmp(valor1,"mul"))==0|| (strcmp(valor1,"div"))==0 
				|| (strcmp(valor1,"beq"))==0)
			
				fprintf(salida1,"%s %s %s %s\n",listaDatos[i].funcion,listaDatos[i].dato1,listaDatos[i].dato2,listaDatos[i].dato3);

			else if ((strcmp(valor1,"j"))==0)
				fprintf(salida1,"%s %s\n",listaDatos[i].funcion,listaDatos[i].dato1);
			
			else if ((strcmp(valor1,"lw"))==0 || (strcmp(valor1,"sw"))==0)
				fprintf(salida1,"%s %s %s\n",listaDatos[i].funcion,listaDatos[i].dato1,listaDatos[i].dato2);
			
			else
				fprintf(salida1,"%s\n",listaDatos[i].funcion);
		}
	}
}*/
void recibirNombreArchivo() 
{ //Esta función es la que se encarga de pedirle al usuario el nombre de cada uno de los archivos de entrada
	FILE* arch; //Almacenandolos en NOMBRE_ARCHIVO_1 y NOMBRE_ARCHIVO_2 respectivamente, siendo
	NOMBRE_ARCHIVO_1 = (char*)malloc(sizeof(char)*25);//Estas variables globales definidas en las definiciones
	//NOMBRE_ARCHIVO_2 = (char*)malloc(sizeof(char)*25);
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
	//Los do-while en ambos casos son para verificar que se haya hecho un correcto ingreso de los
	//Nombres de los archivos y si no existe un archivo con el nombre ingresado se pedirá nuevamente
	/*do
	{
		printf("\nIngrese el nombre del segundo archivo solicitado: ");
		scanf("%s",NOMBRE_ARCHIVO_2);
		while(getchar()!='\n');
		arch = fopen(NOMBRE_ARCHIVO_2,"r");
		
		if (arch == NULL) 
			printf("No se encuentra archivo con ese nombre, intente nuevamente\n");
		
	} while (arch == NULL);
	fclose(arch);*/
}
//Función encargada de liberar la memoria que se ocupó durante el procedimiento
void liberarMemoria()
{
	free(listaDatos);
	free(REGISTROS_VALOR);
	free(TABLERO);
	free(NOMBRE_ARCHIVO_1);
	free(NOMBRE_ARCHIVO_2);
}