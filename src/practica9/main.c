#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../captura/captura.h"
#include "../Estructuras/heap/heap.h"

#define LONGITUD 64

typedef struct
{
	char nombre[50];
	int cantidad;
}Archivo;

void desplegarArbolyArreglo(Heap *heap);

void cambiarPrioridad(Heap *heap);
void imprimirPaginas(void *a);

void imprimirArchivo(void *a);

int compararArchivo(void*a,void*b);

Archivo* crearArchivo(char* nombre,int* cantidad);

void vaciarHeap(Heap *heap);

/*
Para Compilar :
mingw32-make -C src\Estructuras\nodos
mingw32-make -C src\Estructuras\pila
mingw32-make -C src\Estructuras\heap
mingw32-make -C src\captura

mingw32-make -C src\practica9
mingw32-make -C src\practica9 rebuild
mingw32-make -C src\practica9 run

*/

int main(void){
	
	Heap heap = inicializarHeap( &imprimirArchivo,&compararArchivo);
	heap.arbol.imprimir = &imprimirPaginas;
	char* cadena = NULL;
	int cantidad = 0;

	int opcion = 0;
	do{
		//Mostrar el Heap de los Primeros 5 Archivos, de no existir no imprimir nada.
		printf("\n\n\n\n\n- - Heap Primeros 5 Archivos - -\n");
		imprimirHeap_5(heap);
		
		printf("\n\n     - - Menu Heap - -\n");
		if(heap.tipo==MIN)
			printf("[0] Cambiar Prioridad (Act. MIN)\n");
		else
			printf("[0] Cambiar Prioridad (Act. MAX)\n");
		printf("[1] Mostrar Cola de Impresion\n");
		printf("[2] Agregar Archivo\n");
		printf("[3] Procesa / Imprime Archivo\n");
		printf("[4] Eliminar Archivo\n");
		printf("[5] Eliminar todos los Archivos\n");
		printf("[6] Salir\n");
		inputEntero("\nSelecciona Opcion : ",&opcion);
		switch(opcion){
			case 0:
				//Mostrado de Estad antes de Operacion
				desplegarArbolyArreglo(&heap);

				cambiarPrioridad(&heap);
				printf("\n- - Prioridad Invertida - -");
				heapify(&heap);

				//Mostrado de Estad despues de Operacion
				desplegarArbolyArreglo(&heap);
			break;

			case 1:
				printf("\n- - Archivos Cola de Impresion - -\n");
				desplegarArbolyArreglo(&heap);
			break;

			case 2:
				inputCadenaDinamica("\nIngresa el Nombre del Archivo : ",&cadena,LONGITUD);
				inputEntero("\nIngresa Numero de Paginas del Archivo : ",&cantidad);
				
				//Mostrado de Estad antes de Operacion
				desplegarArbolyArreglo(&heap);

				insertarHeap(&heap,crearArchivo(cadena,&cantidad));
				printf("\n - -Archivo Creado Exitosamente- - \n");
				heapify(&heap);

				//Mostrado de Estad despues de Operacion
				desplegarArbolyArreglo(&heap);

			break;

			case 3:
				//Mostrado de Estad antes de Operacion
				desplegarArbolyArreglo(&heap);

				if(heap.cantidad)
				{
					printf("\n\n_ - _ Procesamiento de Archivo _ - _\n    Archivo = ");
					imprimirArchivo(quitarHeap(&heap));
				}
				else
					printf(" - Lista Vacia - ");

				//Mostrado de Estad despues de Operacion
				desplegarArbolyArreglo(&heap);

			break;

			case 4:
				if(!heap.cantidad){
					printf(" - Lista Vacia - ");
					break;
				}
				int seleccion = -1;
				printf("_-_ Seleccion Archivo a Eliminar _-_\n");
				//Muestra la Lista de Archivos, indicando el indice en el Arreglo
				imprimirHeapIndice(heap);

				inputEntero("\n_-_ Selecciona el Indice a Eliminar _-_",&seleccion);
				if(seleccion >= 0 && seleccion <=((heap.cantidad)-1))
				{
					//Mostrado de Estad antes de Operacion
					desplegarArbolyArreglo(&heap);

					eliminarPosicionHeap(&heap,seleccion);

					//Mostrado de Estad despues de Operacion
					desplegarArbolyArreglo(&heap);
				}
				else
				printf("-_- Dato Invalido -_-");
				
			break;

			case 5:
				//Mostrado de Estad antes de Operacion
				desplegarArbolyArreglo(&heap);

				printf("\n -- Vaciado de Lista --");
				vaciarHeap(&heap);

				//Mostrado de Estad despues de Operacion
				desplegarArbolyArreglo(&heap);
			break;

			case 6:
				printf("\n - - Saliendo - - \n");
			break;

			default:
				printf("\n - - Dato Invalido - - \n");
			break;
		}
	}while(opcion != 6);
	//free(&heap);
	free(cadena);
}


void desplegarArbolyArreglo(Heap *heap)
{
	if(!heap->cantidad)
		return;
	printf("\n -_- Estado De Heap Arbol -_-\n");
	imprimirArbol(heap->arbol);	
	printf("\n -_- Estado De Heap Arreglo -_-\n");
	imprimirHeap(*heap);	
}

void cambiarPrioridad(Heap *heap)
{
	heap->tipo = (heap->tipo == MIN) ? MAX:MIN;
	heapify(heap);
}

void imprimirArchivo(void *a)
{
	Archivo *archivo =a;
	printf("[ %s - %d ]",archivo->nombre,archivo->cantidad);
}

void imprimirPaginas(void *a)
{
	Archivo *archivo =a;
	printf("%d",archivo->cantidad);
}


int compararArchivo(void*a,void*b)
{
	//DeCastear de Void* a tipo Archivo

	Archivo *archivo_a = a,*archivo_b=b;
	if(archivo_a->cantidad==archivo_b->cantidad)return 0;
	else if(archivo_a->cantidad<archivo_b->cantidad)return -1;
	else return 1;
}

Archivo* crearArchivo(char* nombre,int* cantidad)
{
	Archivo *nuevo = calloc(1,sizeof(Archivo));
	strcpy(nuevo->nombre,nombre);
	nuevo->cantidad = *cantidad;
	return nuevo;
}

void vaciarHeap(Heap *heap)
{
	while(heap->cantidad){
		void* a = quitarHeap(heap);
		Archivo *archivo_a = a;
		printf("%d - ", archivo_a->cantidad);
	}
}