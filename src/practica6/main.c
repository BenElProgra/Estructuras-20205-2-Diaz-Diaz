
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/arbol/arbol.h"

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);

//void myprintf(char *formato,...);

/*
Para Compilar :
mingw32-make -C src\Estructuras\arbol
mingw32-make -C src\Estructuras\nodos
mingw32-make -C src\captura
mingw32-make -C src\practica6
mingw32-make -C src\practica6 rebuild
mingw32-make -C src\practica6 run

*/

int main(void)
{
	Arbol arbolA;
	arbolA.raiz = NULL;
	arbolA.cantidad = 0;
	arbolA.imprimir = &imprimirEntero;
	arbolA.comparar = &compararEntero;
	arbolA.liberar = &free;

	Arbol arbolB;
	arbolB.raiz = NULL;
	arbolB.cantidad = 0;
	arbolB.imprimir = &imprimirEntero;
	arbolB.comparar = &compararEntero;
	arbolB.liberar = &free;

	int opcion;	
	int insertar;
	Resultado val;
	do
	{
		opcion = 0;
		//DESPLEGAR LAS CAJAS
		printf("\n\n- - - Menu Arboles - - -");
		printf("\n [1] Insertar en Arbol A");
		printf("\n [2] Insertar en Arbol B");
		printf("\n [3] Comparar Arboles");
		printf("\n [4] Eliminar dato en Arbol A");
		printf("\n [5] Eliminar dato en Arbol B");
		printf("\n [6] Profundidades");
		printf("\n [7] Equilibrar arboles");
		printf("\n [8] Mostrar Arboles");
		printf("\n [9] Terminar Programa");
		inputEntero("\n\n Selecciona opcion: ",&opcion);
		switch(opcion)
		{
			case 1:
				inputEntero("\nIngresa entero a insertar en arbol A: ",&insertar);
				insertarArbol(&arbolA, crearEntero(insertar));

			break;
			
			case 2:
				inputEntero("\nIngresa entero a insertar en arbol B: ",&insertar);
				insertarArbol(&arbolB, crearEntero(insertar));
			break;

			case 3:
				if(compararArbol(&arbolA,&arbolB) == 0){
					printf("\n- - Datos Diferentes - -");
					printf("\n- - Diferente Estructura - -");
				}
				else if(compararArbol(&arbolA,&arbolB) == 1){
					printf("\n- - Datos Iguales - -");
					printf("\n- - Diferente Estructura - -");
				}

				else if(compararArbol(&arbolA,&arbolB) == 2){
					printf("\n- - Datos Iguales - -");
					printf("\n- - Misma Estructura - -");
				}
				else 
				printf("WTF");
			break;

			case 4:
				inputEntero("\nIngresa entero a eliminar en arbol A: ",&insertar);
				val = buscarEnArbol(arbolA,&insertar);
				if(!val.dato)
					printf("\n- - Dato Inexistente en Arbol - -\n");
				else 
				{
					eliminarDatoArbol(&arbolA,&insertar);
					printf("\n- - Dato Eliminado de Arbol Exitosamente- -\n");
				}
			break;

			case 5:
				inputEntero("\nIngresa entero a eliminar en arbol B: ",&insertar);
				val = buscarEnArbol(arbolB,&insertar);
				if(!val.dato)
					printf("\n- - Dato Inexistente en Arbol - -\n");
				else 
				{
					eliminarDatoArbol(&arbolB,&insertar);
					printf("\n- - Dato Eliminado de Arbol Exitosamente- -\n");
				}
			break;

			case 6:
				printf("\n- - Profundidad de Arbol A = = %d - -\n\n- - Profundidad de Arbol B = = %d - -\n\n",altura(arbolA),altura(arbolB));
			break;

			case 7:
				if(arbolA.cantidad != 0)
					equilibrar(&arbolA);
				else
					printf("\n- -Arbol A vacio - -");
				if(arbolB.cantidad != 0)
					equilibrar(&arbolB);
				else
					printf("\n- -Arbol B vacio - -");
			break;

			case 8:
				printf("\n\n - - - Arbol A - - - \n\n");
				imprimirArbol(arbolA);
				printf("\n\n - - - Arbol B - - - \n\n");
				imprimirArbol(arbolB);
			break;

			case 9:
				printf("\n [Saliendo]");
			break;

			default:
				printf("\n [Default]");
			break;	
		}	
	}while(opcion!=9);

	eliminarArbol(&arbolA);
	eliminarArbol(&arbolB);
	return 0;
}


int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a,void*b)
{
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}

/*
void myprintf(char *formato,...)
{
	va_list args;
    va_start(args, strlen(formato));
	while(*formato!='\0')
	{
		switch(*formato)
		{
			case 'd':
				printf("%d",(int)va_arg(args, int));
				break;
			case 'c':
				printf("%c",(char)va_arg(args, char));				
				break;
		}
		formato++;
	}
	va_end(args);
}
*/