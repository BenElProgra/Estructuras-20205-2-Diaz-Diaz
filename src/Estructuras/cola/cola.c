#include "cola.h"
#include <stdio.h>


Cola inicializarCola(void)
{
	return (Cola) {NULL,NULL,-1,0,NULL,NULL};
}

int llenaC(Cola cola)
{
	return cola.cantidad == cola.capacidad;
}

int vaciaC(Cola cola)
{	
	return cola.cantidad == 0 && cola.inicio == NULL && cola.fin == NULL;
}

//Push

//En inicio se tiene los datos insertados, mientras que fin contiene el primer dato instertado, [1] [2] [3], si fueron puesto en orden, 1 esta en inicio y 3 estaria en final. (Inicio , primero en ser atendido, Final, final de la cola)
void enqueue(Cola *cola,void *dato)
{	
	if(llenaC(*cola)){
		printf("\n Overflow");
	}
	else
	{
		Nodo *nuevo = crearNodo(dato);
		if(vaciaC(*cola)){
			//Es el primero y ultimo porque es el unico
			cola->fin = nuevo;
			cola->inicio = nuevo;
		}
		else{
			//No es el unico.
			cola->fin->sig = nuevo;
			cola->fin = nuevo;
		}
		cola->cantidad++;
	
	}
	return;
}

void* peekC(Cola cola)
{	
	if(vaciaC(cola))
		return NULL;
	return cola.inicio->dato;
}

//Pop
void* dequeue(Cola *cola)
{	
	if(vaciaC(*cola)){
		printf("\n UnderFlow");
		return NULL;
	}
	else
	{
		Nodo *aux = cola->inicio;		
		void *dato = aux->dato;
		//LIBERAR EL NODO
		cola->inicio = aux->sig;
		//Si era el unico
		if(cola->inicio == NULL)
			cola->fin = NULL;
		free(aux);
		cola->cantidad--;
		return dato;
	}
	return NULL;
}





void queue_nodo(Cola *cola,Nodo *nuevo)
{	
	if(llenaC(*cola)){
		return;
	}
	else
	{
		if(vaciaC(*cola)){
			//Es el primero y ultimo porque es el unico
			cola->fin = nuevo;
			cola->inicio = nuevo;
		}
		else{
			//No es el unico.
			cola->fin->sig = nuevo;
			cola->fin = nuevo;
		}
		cola->cantidad++;
	}
	return;
}

Nodo* dequeue_nodo(Cola *cola)
{
	if(vaciaC(*cola))
		return NULL;
	else
	{
		Nodo *aux = cola->inicio;
		cola->inicio = aux->sig;
		
		if(cola->inicio == NULL)
			cola->fin = NULL;
		aux->sig = NULL;
		cola->cantidad--;
		return aux;
	}
}


void eliminarCola(Cola *cola)
{
	void *dato;
	while(!vaciaC(*cola))
	{
		dato = dequeue(cola);
		if( cola->liberar )
			cola->liberar(dato);
	}
}


void* buscarC(Cola cola,void *dato,int (*comparar)(void*,void*))
{
	void *encontrado = NULL;
	for(int i = 0; i < cola.cantidad; i++){
		if( comparar(dato,peekC(cola)) == 0)
		{
			encontrado = peekC(cola);
		}
		queue_nodo(&cola,dequeue_nodo(&cola));
	}
	return encontrado;
}

void imprimirCola(Cola cola)
{
	Cola aux = (Cola){NULL,NULL,cola.capacidad,0,NULL};
	Nodo *nodo;
	printf("\n\nCola [%d]: ",cola.cantidad);
	
	while( !vaciaC(cola) )
	{
		nodo = dequeue_nodo(&cola);
		cola.imprimir(nodo->dato);
		printf(" -> ");
		queue_nodo(&aux,nodo);
	}
	while( !vaciaC(aux) )
		queue_nodo(&cola,dequeue_nodo(&aux));
}
