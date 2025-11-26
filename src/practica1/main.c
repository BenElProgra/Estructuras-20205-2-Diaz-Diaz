//INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.h"
//Funcion Main

typedef struct 
{
    unsigned int matricula;
    char nombre[64];
    int semestres;
    float promedio;
} Alumno;

// Prototipos de Funciones

void* crearEntero(int dato); //No utilizado

int compararEnteros(void *a, void *b);  //No utilizado

void imprimirEntero(void *a); //No utilizado

void* crearFlotante(float dato); //No utilizado

int compararFlotante(void *a, void *b); //No utilizado

void imprimirFlotante(void *a); //No utilizado

void crearAlumno(Lista*);

int compararAlumnosNombre(void *a,void *b);

int compararAlumnosMatricula(void *a,void *b);

int compararAlumnosSemestre(void *a,void *b);

int compararAlumnosPromedio(void *a,void *b);

void imprimirAlumno(void *a);

void menuReordenar(Lista *lista);

void menuBuscar(Lista *lista);

int main(void)
{
	Lista lista;
	lista.inicio = NULL;
	lista.cant = 0;
	lista.imprimir = &imprimirAlumno;
	lista.comparar = &compararEnteros;

	int opcion = 0;
	
	do {
		printf("\n\nMenu Alumnos:\n[1] Registrar Alumno\n[2] Desplegar Alumnos\n[3] Reordenar\n[4] Buscar Alumno\n[5] Borrar Alumno\n[6] Finalizar Progrma\n\nIngresa Opcion : ");
		scanf("%d",&opcion);
		switch (opcion)
		{
			case 1:
				crearAlumno(&lista);
			break;
		
			case 2:
				//En caso de estar vacio solo -> NULL
				mostrarLista(lista);
			break;
		
			case 3:
				if (lista.cant == 0)
					printf("\n\nLista Vacia\n");
				else
					menuReordenar(&lista);
			break;
		
			case 4:
				if (lista.cant == 0)
					printf("\n\nLista Vacia\n");
				else
					menuBuscar(&lista);
			break;
		
			case 5:
				if (lista.cant == 0)
					printf("Lista Vacia\n");
				else
				{
					Alumno mat;
					printf("Ingresa la Matricula del Alumno a Eliminar = ");
					scanf("%d",&mat.matricula);
					borrarDato(&lista,&mat,&compararAlumnosMatricula);
				}
			break;
		
			case 6:
				printf("Saliendo");
			break;

			default:
				printf("Dato Invalido");
			break;	
		}	
	} while(opcion != 6);
	
	return 0;
}



void* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEnteros(void *a, void *b)
{
	int *ea,*eb;
	ea = a;
	eb = b;
	if( *ea < *eb )
		return -1;
	else if ( *ea > *eb)
		return 1;
	else
		return 0;	
}

void imprimirEntero(void *a)
{
	int *ea;
	ea = a;
	printf("%d",*ea);
}

void* crearFlotante(float dato)
{
	float *nuevo = malloc(sizeof(float));
	*nuevo = dato;
	return nuevo;
}



int compararFlotante(void *a, void *b)
{
	float *ea,*eb;
	ea = a;
	eb = b;
	if( *ea < *eb )
		return -1;
	else if ( *ea > *eb)
		return 1;
	else
		return 0;	
}


void imprimirFlotante(void *a)
{
	float *ea;
	ea = a;
	printf("%.2f",*ea);
}

void crearAlumno(Lista *lista)
{
	int mat;
	char name[64];
	int sem;
	float prom;


	printf("\nIngrese su Matricula : ");
	scanf("%d", &mat);
	lista->comparar = &compararAlumnosMatricula;
	Alumno buscar2;
	buscar2.matricula = mat;
	if (buscarDato(*lista,&buscar2) != NULL)
	{
		printf("Matricula ya ingresada...");
		return;
	}

	getchar();
	printf("Ingrese el Nombre : ");
	fgets(name, 64, stdin);
	name[strcspn(name, "\n")] = '\0';
	printf("Ingrese el Semestre : ");
	scanf("%d", &sem);
	printf("Ingrese el Promedio : ");
	scanf("%f", &prom);
	
	Alumno *a;
	Alumno *nuevo = malloc(sizeof(Alumno));

	nuevo->matricula = mat;
	strcpy(nuevo->nombre, name);
	nuevo->semestres = sem;
	nuevo->promedio = prom;
	
	a = nuevo;

	printf("\nAlumno creado Exitosamente = %d - %s - %d - %.2f \n",nuevo->matricula,nuevo->nombre,nuevo->semestres,nuevo->promedio);

	
	insertarOrdenado(lista,nuevo);
}



int compararAlumnosMatricula(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	if ( aa->matricula > ab->matricula)
		return 1;
	if ( aa->matricula < ab->matricula)
		return -1;
	return 0;
}

int compararAlumnosNombre(void *a,void *b)
{
	Alumno *aa,*ab;  
	aa = a;
	ab = b;
	return strcmp( aa->nombre,ab->nombre);
}

int compararAlumnosSemestre(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	if ( aa->semestres > ab->semestres)
		return 1;
	if ( aa->semestres < ab->semestres)
		return -1;
	return 0;
}

int compararAlumnosPromedio(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	if ( aa->promedio > ab->promedio)
		return 1;
	if ( aa->promedio < ab->promedio)
		return -1;
	return 0;
}


void imprimirAlumno(void *a)
{
	Alumno *aa;
	aa = a;
	printf("%d - %s - %d - %.2f ",aa->matricula,aa->nombre,aa->semestres,aa->promedio);
	
}

void menuBuscar(Lista *lista)
{
	int opcion2 = 0;
	do
	{
		printf("\n\nQue Dato Quieres Buscar:\n[1] Matricula\n[2] Nombre\n[3] Semestres\n[4] Promedio\n[5] Salir\nIngresa Opcion = ");
		scanf("%d",&opcion2);
		//Se utiliza una variable alumno temporal que funciona para la funcion "buscarDato", despues de cada iteracion se borra con free y se crea otro.
		Alumno *buscar = malloc(sizeof(Alumno));
		switch(opcion2)
		{
			case 1:
				//Se cambia el puntero a funcion dependiendo del dato a buscar
				lista->comparar = &compararAlumnosMatricula;
				int matBus;
				printf("\nIngresa la Matricula del Alumno = ");
				scanf("%d",&matBus);
				//Se ingresa el dato 
				buscar->matricula = matBus;
				//En caso de no encontrar el dato en la lista
				if (buscarDato(*lista,buscar) == NULL)
					printf("\nMatricula Inexistente\n");
				else
				{
					Alumno *res = buscarDato(*lista,buscar);
					printf("\nAlumno encontrado = ");
					imprimirAlumno(res);
				}
				break;
	
			case 2:
				lista->comparar = &compararAlumnosNombre;
				char nameBus[64];
				printf("\nIngresa el Nombre del Alumno = ");
								
				while (getchar() != '\n');
				fgets(nameBus, 64, stdin);
				nameBus[strcspn(nameBus, "\n")] = '\0';
				strcpy(buscar->nombre, nameBus);

				if (buscarDato(*lista,buscar) == NULL)
					printf("\nNombre Inexistente\n");
				else
				{
					Alumno *res = buscarDato(*lista,buscar);
					printf("\nAlumno encontrado = ");
					imprimirAlumno(res);
				}
				break;
				
			case 3:
				int semBus;
				lista->comparar = &compararAlumnosSemestre;
				printf("\nIngresa el Semestre del Alumno = ");
				scanf("%d",&semBus);
				buscar->semestres = semBus;
				if (buscarDato(*lista,buscar) == NULL)
					printf("\nSemestre Inexistente\n");
				else
				{
					Alumno *res = buscarDato(*lista,buscar);
					printf("\nAlumno encontrado = ");
					imprimirAlumno(res);
				}
				break;
				
			case 4:
				float promBus;
				lista->comparar = &compararAlumnosPromedio;
				printf("\nIngresa el Promedio del Alumno = ");
				scanf("%f",&promBus);
				buscar->promedio = promBus;
				if (buscarDato(*lista,buscar) == NULL)
					printf("\nPromedio Inexistente\n");
				else
				{
					Alumno *res = buscarDato(*lista,buscar);
					printf("\nAlumno encontrado = ");
					imprimirAlumno(res);
				}
				break;

			case 5:
				break;

			default:
				printf("Dato Invalido");
				break;
		}
		free(buscar);
		lista->comparar = &compararEnteros;
	} while(opcion2 < 1 && opcion2 > 5);	
}



void menuReordenar(Lista *lista)
{
	int opcion3 = 0;
	do
	{
		printf("\n\nComo quiere que la lista este ordenada?\n[1] Matricula\n[2] Nombre\n[3] Semestre\n[4] Promedio\n[5] Salir\n\nIngresa Opcion : ");
		scanf("%d",&opcion3);
		switch(opcion3)
		{
			case 1:
				reordenar(lista,&compararAlumnosMatricula);
				mostrarLista(*lista);
			break;

			case 2:
				reordenar(lista,&compararAlumnosNombre);
				mostrarLista(*lista);
			break;

			case 3:
				reordenar(lista,&compararAlumnosSemestre);
				mostrarLista(*lista);
			break;

			case 4:
				reordenar(lista,&compararAlumnosPromedio);
				mostrarLista(*lista);
			break;

			case 5:
				printf("\n\nSaliendo\n");
			break;

			default:
				printf("\n\nDato Invalido\n");
			break;
		}
	}
	while(opcion3 != 5);
}