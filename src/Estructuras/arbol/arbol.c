#include "arbol.h"

	void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*))
	{
		/*
		if(comparar(dato,raiz->dato)<=0)
		{
			//IZQUIERDA o DERECHA
			if(raiz->izq)
			{
				if(comparar(dato,raiz->izq->dato) == 0 && !raiz->dch)
					//DERECHA
					raiz->dch = crearNodoA(dato);
				else
					//IZQUIERDA
					insertarArbolOrdenado(raiz->izq,dato,comparar);
			}
			else
				raiz->izq = crearNodoA(dato);
		}
		else
		{
			//DERECHA
			if(raiz->dch)
				insertarArbolOrdenado(raiz->dch,dato,comparar);
			else
				raiz->dch = crearNodoA(dato);
		}
		*/


		if (comparar(dato, raiz->dato) <= 0) {  // va a la izquierda
			if (raiz->izq)
				insertarArbolOrdenado(raiz->izq, dato, comparar);
			else
				raiz->izq = crearNodoA(dato);
		} else {  // va a la derecha
			if (raiz->dch)
				insertarArbolOrdenado(raiz->dch, dato, comparar);
			else
				raiz->dch = crearNodoA(dato);
		}

	}




	void insertarArbol(Arbol *arbol,void *dato)
	{
		if(!arbol->raiz)
			arbol->raiz = crearNodoA(dato);
		else 
			insertarArbolOrdenado(arbol->raiz,dato,arbol->comparar);
		arbol->cantidad++;
	}



void imprimir_arbol(NodoA* nodo, int nivel,void (*imprimir)(void*))
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |		");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |		");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol)
{
	imprimir_arbol(arbol.raiz,0,arbol.imprimir);
}

void preorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(NodoA *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}


void imprimirOrden(Arbol arbol,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			preorden(arbol.raiz,arbol.imprimir);
			break;
		case ORDEN: 
			orden(arbol.raiz,arbol.imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,arbol.imprimir);
			break;
		case POSTORDEN: 
			postorden(arbol.raiz,arbol.imprimir);
			break;
	}
}

void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*))
{
	if(!raiz)
		return;
	eliminar_NodosA(raiz->izq,liberar);
	eliminar_NodosA(raiz->dch,liberar);
	//Liberar
	if(liberar)
		liberar(raiz->dato);
	free(raiz);
		
}

void eliminarArbol(Arbol  *arbol)
{
	eliminar_NodosA( arbol->raiz, arbol->liberar);
	arbol->raiz = NULL;
	arbol->cantidad = 0;
}

Resultado busquedaEnNodos(NodoA *padre,NodoA *raiz,void *dato, int (*comparar)(void*,void*))
{
	Resultado aux;
	if(!raiz)
		return (Resultado){NULL,NULL,NULL,IZQUIERDA};
	if( comparar( raiz->dato,dato) == 0)
		return (Resultado){padre,raiz,raiz->dato,(padre && padre->izq==raiz) ? IZQUIERDA:DERECHA};
	aux = busquedaEnNodos(raiz, raiz->izq, dato,comparar);
	if(!aux.dato)
		aux = busquedaEnNodos(raiz, raiz->dch, dato,comparar);	
	return aux;
}



Resultado buscarEnArbol(Arbol arbol,void *dato)
{
	//Resultado res = {NULL,NULL,NULL,IZQUIERDA};

	Resultado res = busquedaEnNodos(NULL,arbol.raiz,dato,arbol.comparar);
	return res;
}

void eliminarDatoArbol(Arbol *arbol, void *dato)
{
	Resultado res = buscarEnArbol(*arbol,dato);
	if(!res.dato)
		return;
	arbol->cantidad--;
	if(!res.padre)
	{
		//Estoy eliminando la raiz del arbol
		if(!res.eliminar->izq)
			arbol->raiz = res.eliminar->dch;
		else{
			arbol->raiz = res.eliminar->izq;
			NodoA *extD = res.eliminar->izq;
			while(extD->dch!=NULL)
				extD = extD->dch;
			extD->dch = res.eliminar->dch;
		}
	}
	else
	{
		if(!res.eliminar->izq)
		{
			if(res.rama == IZQUIERDA)
				res.padre->izq = res.eliminar->dch;
			else
				res.padre->dch = res.eliminar->dch;
		}				
		else{
			NodoA *extD = res.eliminar->izq;
			while(extD->dch!=NULL)
				extD = extD->dch;
			extD->dch = res.eliminar->dch;
			if(res.rama == IZQUIERDA)
				res.padre->izq = res.eliminar->izq;
			else
				res.padre->dch = res.eliminar->izq;
		}
	}
	arbol->liberar(res.eliminar->dato);
	free(res.eliminar);
}

void calcularAltura(NodoA *raiz,int *altura)
{
	int izquierdo,derecho;
	izquierdo = derecho = *altura;
	if(raiz->izq && izquierdo++ )
		calcularAltura(raiz->izq,&izquierdo);
	if(raiz->dch && derecho++ )
		calcularAltura(raiz->dch,&derecho); 
	*altura = (izquierdo>derecho) ? izquierdo:derecho;
}

int altura(Arbol arbol)
{
	if(!arbol.raiz)
		return 0;
	int altura = 1;
	calcularAltura(arbol.raiz,&altura);
	return altura;
}

void extraccionDatos(NodoA *raiz,void **datos,int *indice)
{
	if(!raiz)
		return;
	extraccionDatos(raiz->izq,datos,indice);
	datos[*indice] = raiz->dato;
	(*indice)++;
	extraccionDatos(raiz->dch,datos,indice);
	
}

void ordenarRaices(void **inicio, void **fin, void **ordenado, int *indice)
{
    if (inicio > fin) return;
    
    int cantidad = (fin - inicio) + 1;
    int mitad = cantidad / 2;
    
    ordenado[*indice] = inicio[mitad];
    (*indice)++;
    
    if (cantidad == 1) return;
    
    // Mitad izquierda
    ordenarRaices(inicio, inicio + mitad - 1, ordenado, indice);
    // Mitad derecha  
    ordenarRaices(inicio + mitad + 1, fin, ordenado, indice);
}

void equilibrar(Arbol *arbol)
{
	void (*liberar)(void*) = arbol->liberar; // GUARDAR FUNCION DE LIBERAR
	//ASIGNAR NULO PARA QUE EN LA ELIMINACION DEL ARBOL
	//NO SE ELIMINEN LOS DATOS
	arbol->liberar = NULL; 
	int indice = 0;
	int cantidad = arbol->cantidad;
	void **datos = calloc(cantidad,sizeof(void*)); //ARREGLO PARA ALMACENAR DATOS
	void **ordenados = calloc(cantidad,sizeof(void*)); //ARREGLO CON LOS DATOS ORDENADOS
	extraccionDatos(arbol->raiz,datos,&indice);	 //PASAR DATOS AL ARREGLO
	eliminarArbol(arbol); //BORRAR ARBOL
	arbol->liberar = liberar; //RESTAURAR FUNCION DE LIBERAR
	indice = 0;
	//ORDENAR LOS DATOS PARA LA RECONSTRUCCION
	//PRIORIZANDO LAS RAICES
	ordenarRaices(datos,datos+(cantidad-1),ordenados,&indice); 
	for( int i=0; i<cantidad ; i++)
		insertarArbol(arbol, ordenados[i]  ); //RECONSTRUIR ARBOL
	free(datos);
	free(ordenados);
}

int comparar_estructura(NodoA* nodoA,NodoA* nodoB, int nivel,int (*comparar)(void*,void*),int comparacion)
{
	//Si en algun punto del proceso, da un valor diferente, retornara 0, y no cumplira la condicion y seguira dando 0 hasta salir de la funcion recursiva.
	if(comparacion == 1){
		//Si son iguales
		//Validar si hay espacio para mover.
		if((nodoA->dch && !nodoB->dch)||(nodoA->izq && !nodoB->izq))
			return 0;

        if(nodoA->dch)
		{
			if(comparar(nodoA->dch->dato,nodoB->dch->dato) == 0)
				comparacion = comparar_estructura(nodoA->dch,nodoB->dch, nivel + 1,comparar,comparacion);
			else
				return 0;
		}
		if(nodoA->izq)
		{
			if(comparar(nodoA->izq->dato,nodoB->izq->dato) == 0)
				comparacion = comparar_estructura(nodoA->izq,nodoB->izq, nivel + 1,comparar,comparacion);
			else
				return 0;
		}
		return 1;
	}
	//Si recorre todo el arbol y todo es igual que el arbol A, en forma de estructura, retorna 1, si en cualquier paso del flujo encuentra discrepancias, retorna 0.
	return 0;
}

int compararArbol(Arbol *arbolA,Arbol *arbolB)
//Retorna 0, si no cumple con datos ni estructura.
//Retorna 1, si cumple con datos pero no estructura.
//Retorna 2, si cumple con datos y estructura.
{
	if(arbolA->cantidad != arbolB->cantidad){
		return 0;
	}
	if(arbolA->cantidad == 0 && arbolA->cantidad ==0){
		//Por si quiebra por seguir.
		return 2;
	}
	int cantidadA = arbolA->cantidad;
	int cantidadB = arbolB->cantidad;

	int *indiceA = calloc(cantidadA,sizeof(int));
	void **datosA = calloc(cantidadA,sizeof(void*));
	extraccionDatos(arbolA->raiz,datosA,indiceA);

	int *indiceB = calloc(cantidadB,sizeof(int));
	void **datosB = calloc(cantidadB,sizeof(void*));
	extraccionDatos(arbolB->raiz,datosB,indiceB);

	for(int i = 0; i<cantidadA; i++){
		if(indiceA[i] != indiceB[i]){
			return 0;
		}
	}
	//Cumple con los datos Falta checar la estructura.
	//Usar la misma estructura que imprimir
	if(comparar_estructura(arbolA->raiz,arbolB->raiz,0,arbolA->comparar,1) == 1)
		return 2;
	else
		return 1;
}
