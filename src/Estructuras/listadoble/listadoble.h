#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include "nododoble.h"
#include "../alumno/alumno.h"
#include "../../captura/captura.h"

#include <stdio.h>
#include <string.h>

//#include "./captura/captura.h"

typedef struct 
{
	NodoD *inicio;
	NodoD *fin;
	int cant;
	int (*comparar)(void *datoA,void *dataB);
	void (*imprimir)(void *datoA);
	void (*liberar)(void *datoA);
}ListaD;

ListaD inicializarListaD(void);

void mostrarListaD(ListaD lista);

void mostrarListaDR(ListaD lista);

void insertarOrdenadoD(ListaD *lista,void* dato);

void* buscarDatoD(ListaD lista,void *dato);

void borrarLista(ListaD *lista);

void crearAlumno(ListaD *lista);

void borrarDatoD(ListaD *lista,void* dato, int(*comparar)(void*,void*));

void reordenarD(ListaD *listaOrigen,int (*comparar)(void*,void*));

void eliminarEnPosicionD(ListaD *lista,int pos);

#endif