#include <stdio.h>

#include "../Estructuras/listadoble/listadoble.h"
#include "../Estructuras/listadoble/nododoble.h"
#include "../Estructuras/alumno/alumno.h"
#include "../captura/captura.h"

#define LONGITUD 64

/*
Para Compilar :
mingw32-make -C src\Estructuras\listadoble
mingw32-make -C src\Estructuras\alumno
mingw32-make -C src\captura
mingw32-make -C src\practica2
bin\practica2
*/

void menuBuscar(ListaD *lista);

void menuReordenar(ListaD *lista);

int main(void)
{
	ListaD lista;
	lista = inicializarListaD();

	lista.imprimir = &imprimirAlumno;
	lista.comparar = &compararAlumnosMatricula;

	//char cadena[LONGITUD];
	//inputCadena("\n Captura nombre: ",cadena,LONGITUD);

	int opcion;
	
	do {
	
		inputEntero("\n\nMenu Alumnos:\n[1] Registrar Alumno\n[2] Desplegar Alumnos\n[3] Reordenar\n[4] Buscar Alumno\n[5] Borrar Alumno\n[6] Finalizar Progrma\n\nIngresa Opcion : ",&opcion);
		switch (opcion)
		{
			case 1:
				crearAlumno(&lista);
			break;
		
			case 2:
				//En caso de estar vacio solo -> NULL
			{
				int orden;
				inputEntero("\n De que manera quieres imprimirlo:\n[1] Normal\n[2] Alrevez\n\nIngresa Opcion : ",&orden);
				if (orden == 1)
					mostrarListaD(lista);
				
				else if (orden == 2)
					mostrarListaDR(lista);
				else
					printf("\n\nError\n\n");			
			break;
			}
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
					int elim;
					inputEntero("Ingresa la Matricula del Alumno a Eliminar = ",&elim);
					mat.matricula =  elim;
					borrarDatoD(&lista,&mat,&compararAlumnosMatricula);
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

void menuBuscar(ListaD *lista)
{
	int opcion2;
	do
	{
		inputEntero("\n\nQue Dato Quieres Buscar:\n[1] Matricula\n[2] Nombre\n[3] Semestres\n[4] Promedio\n[5] Salir\nIngresa Opcion = ",&opcion2);

		//Se utiliza una variable alumno temporal que funciona para la funcion "buscarDato", despues de cada iteracion se borra con free y se crea otro.
		Alumno *buscar = malloc(sizeof(Alumno));
		switch(opcion2)
		{
			case 1:
				//Se cambia el puntero a funcion dependiendo del dato a buscar
				lista->comparar = &compararAlumnosMatricula;
				int matBus;
				inputEntero("\nIngresa la Matricula del Alumno = ",&matBus);

				//Se ingresa el dato 
				buscar->matricula = matBus;
				//En caso de no encontrar el dato en la lista
				if (buscarDatoD(*lista,buscar) == NULL)
					printf("\nMatricula Inexistente\n");
				else
				{
					Alumno *res = buscarDatoD(*lista,buscar);
					printf("\nAlumno encontrado = ");
					imprimirAlumno(res);
				}
				break;
	
			case 2:
				lista->comparar = &compararAlumnosNombre;
				char nameBus[LONGITUD];

				inputCadena("\nIngresa el Nombre del Alumno = ",nameBus,LONGITUD);				
				strcpy(buscar->nombre, nameBus);

				if (buscarDatoD(*lista,buscar) == NULL)
					printf("\nNombre Inexistente\n");
				else
				{
					Alumno *res = buscarDatoD(*lista,buscar);
					printf("\nAlumno encontrado = ");
					imprimirAlumno(res);
				}
				break;
				
			case 3:
				lista->comparar = &compararAlumnosSemestre;
				int semBus;

				inputEntero("\nIngresa la Matricula del Alumno = ",&semBus);
				buscar->semestres = semBus;

				if (buscarDatoD(*lista,buscar) == NULL)
					printf("\nSemestre Inexistente\n");
				else
				{
					Alumno *res = buscarDatoD(*lista,buscar);
					printf("\nAlumno encontrado = ");
					imprimirAlumno(res);
				}
				break;
				
			case 4:
				lista->comparar = &compararAlumnosPromedio;
				float promBus;

				inputFloat("\nIngresa la Matricula del Alumno = ",&promBus);
				buscar->promedio = promBus;

				if (buscarDatoD(*lista,buscar) == NULL)
					printf("\nPromedio Inexistente\n");
				else
				{
					Alumno *res = buscarDatoD(*lista,buscar);
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
		lista->comparar = &compararAlumnosMatricula;
	} while(opcion2 < 1 && opcion2 > 5);	
}



void menuReordenar(ListaD *lista)
{
	int opcion3;
	do
	{
		inputEntero("\n\nComo quiere que la lista este ordenada?\n[1] Matricula\n[2] Nombre\n[3] Semestre\n[4] Promedio\n[5] Salir\n\nIngresa Opcion : ",&opcion3);

		switch(opcion3)
		{
			case 1:
				reordenarD(lista,&compararAlumnosMatricula);
				mostrarListaD(*lista);
			break;

			case 2:
				reordenarD(lista,&compararAlumnosNombre);
				mostrarListaD(*lista);
			break;

			case 3:
				reordenarD(lista,&compararAlumnosSemestre);
				mostrarListaD(*lista);
			break;

			case 4:
				reordenarD(lista,&compararAlumnosPromedio);
				mostrarListaD(*lista);
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