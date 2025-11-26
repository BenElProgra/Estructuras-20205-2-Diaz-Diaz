#ifndef ARBOL_H
#define ARBOL_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>

#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4

#define IZQUIERDA 0
#define DERECHA 1

typedef struct
{
	NodoA *padre;
	NodoA *eliminar;
	void *dato;
	int rama;
}Resultado;

typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
}Arbol;

void eliminarDatoArbol(Arbol *arbol, void *dato);

Resultado buscarEnArbol(Arbol arbol,void *dato);

void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);

void orden(NodoA *raiz,void (*imprimir)(void*));

void imprimirOrden(Arbol arbol,int opcion);
void eliminarArbol(Arbol *arbol);

int altura(Arbol arbol);
void equilibrar(Arbol *arbol);

int compararArbol(Arbol *arbolA,Arbol *arbolB);

#endif