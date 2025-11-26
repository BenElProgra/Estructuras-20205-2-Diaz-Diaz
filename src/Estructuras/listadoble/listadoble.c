#include "listadoble.h"

#define LONGITUD 64

//#include "../captura/captura.h"

//Arreglar cuando sea ultimo en insertar, tipo ariel 99,
//Arreglar cuando arreglar alrevez, el primero no sale, osea ariel, INSERTAR AL FINAL ESTA MAL.s

//Actualizar para qeu incluya el puntero a detras
void insertarOrdenadoD(ListaD *lista,void* dato)
{
	NodoD *nuevo = crearNodoD(dato);
	NodoD *actual,*anterior=NULL;
	
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if( lista->comparar(dato,actual->dato) == -1)
		//if( dato < actual->dato) //CONDICION DE PARO: AQUI VOY A INSERTAR
		{
			if(anterior!=NULL)
			{
				//INSERTO EN MEDIO
				nuevo->sig = actual;
				anterior->sig = nuevo;
				nuevo->ant = anterior;
				actual->ant = nuevo;
			}
			else
			{
				//INSERTAR EN EL INICIO
				nuevo->sig = actual;
				nuevo->ant = NULL;
				actual->ant = nuevo;
				lista->inicio = nuevo;
			}
			lista->cant++;
			return;
		}
		anterior = actual;
	}		
	if(lista->inicio == NULL) //LISTA VACIA : INSERTAR UNICO DATO
	{	
		lista->inicio = nuevo;
		lista->fin = nuevo;
		nuevo->ant = NULL;
		nuevo->sig = NULL;
	}	
	else if ( anterior !=NULL) // RECORRI TODA LA LISTA: INSERTAR AL FINAL
	{
		anterior->sig = nuevo;
		nuevo->ant = anterior;
		lista->fin = nuevo;
		nuevo->sig = NULL;
	}
	lista->cant++;	
}

void* buscarDatoD(ListaD lista,void *dato)
{
	NodoD *actual = NULL;
	//NodoD *anterior=NULL;
	for( actual = lista.inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if( lista.comparar(dato,actual->dato) == 0)
		{
			return actual->dato;
		}
		//anterior = actual;
	}	
	return NULL;
	
}

ListaD inicializarListaD(void)
{
	return (ListaD) {NULL,NULL,0,NULL,NULL,NULL};
}

void mostrarListaD(ListaD lista)
{
	NodoD *p;	
	printf("\n Lista[%d]: ",lista.cant);
	for( p = lista.inicio ;  p!=NULL ; p = p->sig  )
	{
		printf("\n ");
		lista.imprimir(p->dato);
		printf("->");
	}
	printf("NULL\n");
}

void mostrarListaDR(ListaD lista)
{
	NodoD *p;	
	printf("\n Lista[%d]: ",lista.cant);
	for( p = lista.fin ;  p!=NULL ; p = p->ant  )
	{
		printf("\n ");
		lista.imprimir(p->dato);
		printf("->");
	}
	printf("NULL\n");
}

void borrarLista(ListaD *lista)
{
	NodoD *actual,*anterior = NULL;
	for( actual = lista->inicio ; actual!=NULL ;  )
	{
		anterior = actual;
		actual = actual->sig;
		//free(anterior->dato);
		free(anterior);		
	}
	lista->inicio = NULL;
	lista->cant = 0;		
}

void crearAlumno(ListaD *lista)
{
	int mat;
	char name[64];
	int sem;
	float prom;

	/*

	int LONGITUD = 64;

	inputEntero("Ingrese su Matricula : ", &mat);

	Alumno buscar2;
	buscar2.matricula = mat;
	if (buscarDatoD(*lista,&buscar2) != NULL)
	{
		printf("Matricula ya ingresada...");
		return;
	}

	inputCadena("Ingresa el Nombre : ",&name,LONGITUD);

	inputEntero("Ingrese el Semestre : ",&sem);

	inputFloat("Ingrese el Promedio : ",&prom);
	
	*/

	

	printf("\nIngrese su Matricula : ");
	scanf("%d", &mat);
	lista->comparar = &compararAlumnosMatricula;
	Alumno buscar2;
	buscar2.matricula = mat;
	if (buscarDatoD(*lista,&buscar2) != NULL)
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

	

	//Alumno *a;
	Alumno *nuevo = malloc(sizeof(Alumno));

	nuevo->matricula = mat;
	strcpy(nuevo->nombre, name);
	nuevo->semestres = sem;
	nuevo->promedio = prom;
	
	//a = nuevo;
	
	insertarOrdenadoD(lista,nuevo);
	
	printf("\nAlumno creado Exitosamente = %d - %s - %d - %.2f \n",nuevo->matricula,nuevo->nombre,nuevo->semestres,nuevo->promedio);	
}

//Como que se quiebra cuando encuentra al usuario a eliminar.
//Actualizar para qeu incluya el puntero a detras
void borrarDatoD(ListaD *lista,void* dato, int(*comparar)(void*,void*))
{
	NodoD *actual,*anterior = NULL;
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if(comparar(dato,actual->dato) == 0)
		{
			//printf("Alumno Detectado");
			if(anterior!=NULL)
			{
				//printf("Puerta Entrada");
				//Validar si es el ultimo en la lista
				if(actual->sig == NULL)
				{
					//printf("Ultimo");
					anterior->sig = NULL;
					lista->fin = anterior;
				}
				//Esta en medio, por ende no se modifica el fin.
				else
				{
					//printf("Medio");
					NodoD *siguente = actual->sig;
					anterior->sig = actual->sig;
					siguente->ant = anterior;
				}
			}
			//Si es el primero
			else
			{
				//Si es el unico en la lista
				if (lista->cant == 1)
				{
					//printf("Unico");
					//Error principal, actual siguente es null, cuando lo intenta crear se pudre. 
					lista->fin = NULL;
					lista->inicio = NULL;
				}
				else
				{
					//printf("Principio");
					lista->inicio = actual->sig;
					NodoD *siguente = actual->sig;
					siguente->ant = NULL;
				}
			}
			//free(actual->dato);
			free(actual);
			lista->cant--;
			//printf("Alumno Borrado");
			break;			
		}		
		anterior = actual;
		//printf("Alumno No Borrado");
	}	
}

//No optimizado, creo
void reordenarD(ListaD *listaOrigen, int (*comparar)(void*,void*))
{
	ListaD aux = (ListaD) {NULL, NULL , 0 ,comparar, NULL, NULL};

	aux.comparar = comparar;
	aux.imprimir = listaOrigen->imprimir;
	NodoD *actual = NULL;
	for(actual = listaOrigen->inicio ; actual!=NULL;)
	{
		insertarOrdenadoD(&aux,actual->dato);
		actual = actual->sig;
		eliminarEnPosicionD(listaOrigen,0);
	}
	*listaOrigen = aux;
}

void eliminarEnPosicionD(ListaD *lista,int pos)
{		
	//VALIDAR
	if( pos==0 ||(pos > 0  && pos < lista->cant ))
	{			
		NodoD *anterior ,*actual;
		anterior = NULL;
		actual = lista->inicio;
		for (int i=0; i<lista->cant  ; i++)
		{
			if( i==pos)
			{
				//Primero en la Lista
				if(anterior == NULL)
				{
					if(lista->cant == 1)
					{
						lista->fin = NULL;
						lista->inicio = NULL;
					}
					else
					{
						lista->inicio = actual->sig;
						NodoD *siguente = actual->sig;
						siguente->ant = NULL;
					}
				}
				//No primero en la lista
				else
				{
					NodoD *siguente = actual->sig;
					//Validar si es el ultimo en la lista
					if(siguente->sig == NULL)
					{
						anterior->sig = NULL;
						lista->fin = anterior;
					}
					//Esta en medio, por ende no se modifica el fin.
					else
					{
						anterior->sig = siguente;
						siguente->ant = anterior;
					}
				}
				free(actual);
				lista->cant--;
				break;
			}
			anterior = actual;
			actual = actual->sig;
		}			
	}	
}