#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/cola/cola.h"

#define NUMERO_CAJAS 5
#define HABILITADA 1
#define DESHABILITADA 0
#define MIN_ARTICULOS 1
#define MAX_ARTICULOS 50

#define MAX_CLIENTES 20


/*
Para Compilar :
mingw32-make -C src\Estructuras\arbol
mingw32-make -C src\Estructuras\nodos
mingw32-make -C src\captura
mingw32-make -C src\practica5
bin\practica5
*/


typedef struct
{
	Cola cola;
	int estado;
}Caja;

void imprimirEntero(void *a);
void liberarEntero(void *a);

int* generar_articulos(void);

int main(void)
{
	
	Caja cajas[NUMERO_CAJAS];
	//Inicializacion de Cajas previo a todos los calculos
	for(int i = 0; i<NUMERO_CAJAS;i++){
		Cola c = (Cola) {NULL,NULL,MAX_CLIENTES,0,&imprimirEntero,&liberarEntero};
		cajas[i].cola = c;
		//Se inicializan de Una
		cajas[i].estado = HABILITADA;
	}
	
	int opcion;	
	do
	{
		printf("\n- - - - Cajas - - - -");
		for(int i = 0; i<NUMERO_CAJAS;i++){
			imprimirCola(cajas[i].cola);
		}
		
		
		
		opcion = 0;
		//DESPLEGAR LAS CAJAS
		printf("\n\n [1] Generar Cliente");
		printf("\n [2] Escanear Articulos");
		printf("\n [3] Habilitar Caja");
		printf("\n [4] DesHabilitar Caja");
		printf("\n [5] Terminar Programa");
		inputEntero("\n\n Selecciona opcion: ",&opcion);
		switch(opcion)
		{
			case 1:
			//Genera Los Clientes
			for(int i = 0; i<NUMERO_CAJAS ; i++)
			{
				if(cajas[i].estado && !llenaC(cajas[i].cola)){
					enqueue( &cajas[i].cola , generar_articulos());
				}
			}
			break;
			
			case 2:
			for(int i = 0; i<NUMERO_CAJAS ; i++)
			{
				if(!vaciaC(cajas[i].cola)){
					int* x = peekC(cajas[i].cola);
					if (*x == 1)
					{
						dequeue(&(cajas[i].cola));
						//Lo hace cero y elimina directamente.
					}
					else
					{
						(*x)--;
					}					
				}
			}
			break;
			
			case 3:
			{
				int opcion_habilitar = 0;
				printf("- - - - Cajas - - - -\n");
				for(int i = 0; i<NUMERO_CAJAS; i++){
					if (cajas[i].estado == HABILITADA)
						printf("[%d] Estado : Habilitada\n",(i+1));
					else if (cajas[i].estado == DESHABILITADA)
						printf("[%d] Estado : DesHabilitada\n",(i+1));
					else
						printf("ERROR\n");
				}
				inputEntero("\n Selecciona Caja a Habilitar: ",&opcion_habilitar);
				if (opcion_habilitar >= 1 && opcion_habilitar <= 5){
					cajas[opcion_habilitar - 1].estado = HABILITADA;
				}
				else{
					printf("\n\nError\n\n");
				}	
			break;
			}
			
			case 4:
			{
				int opcion_deshabilitar = 0;
				printf("\n- - - - Cajas - - - -\n");
				for(int i = 0; i<NUMERO_CAJAS; i++){
					if (cajas[i].estado == HABILITADA)
						printf("[%d] Estado : Habilitada\n",(i+1));
					else if (cajas[i].estado == DESHABILITADA)
						printf("[%d] Estado : DesHabilitada\n",(i+1));
					else
						printf("ERROR\n");
				}
				inputEntero("\n Selecciona Caja a DesHabilitar: ",&opcion_deshabilitar);
				if (opcion_deshabilitar >= 1 && opcion_deshabilitar <= 5){
					cajas[opcion_deshabilitar - 1].estado = DESHABILITADA;
				}
				else{
					printf("\n\nError\n\n");
				}	
			break;
			}

			case 5:
			break;

			default:
			printf("\n [Default]");
			break;	
		}	
	}while(opcion!=5);
	
	for(int i = 0; i<NUMERO_CAJAS;i++){
		eliminarCola(&cajas[i].cola);
	}

	printf("\n\n Fin de Programa");
	return 0;
}


int *generar_articulos(void)
{		
	int *articulos = malloc(sizeof(int));
	*articulos = rand() % (MAX_ARTICULOS - MIN_ARTICULOS + 1) + MIN_ARTICULOS;
	return articulos;
}

void imprimirEntero(void *a)
{
	int *aa = a;
	printf("%d",*aa);
	
}

void liberarEntero(void *a)
{
	int *aa = a;
	free(aa);
}