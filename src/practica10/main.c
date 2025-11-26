#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/hash/hashtable.h"
#include "../Estructuras/arbol/arbol.h"


#include "Libro.h"

/*
Para Compilar :
mingw32-make -C src\Estructuras\nodos
mingw32-make -C src\Estructuras\pila
mingw32-make -C src\Estructuras\heap
mingw32-make -C src\captura

mingw32-make -C src\practica10
mingw32-make -C src\practica10 rebuild
mingw32-make -C src\practica10 run

*/

char minuscula(char caracter);
int compararCadenasIC(char *cadA,char *cadB);

int compararISBN(void* datoA,void *datoB);
int compararTitulo(void* datoA,void *datoB);
int compararTitulo_I(void* datoA,void *datoB);
int compararTituloL(void* datoA,void *datoB);
int compararAutor(void* datoA,void *datoB);
int compararAutor_I(void* datoA,void *datoB);
int compararAutorL(void* datoA,void *datoB);
int compararFecha(void* datoA,void *datoB);
int compararFechaL(void* datoA,void *datoB);

void imprimirISBN(void* datoA);
void imprimirTitulo(void* datoA);
void imprimirAutor(void* datoA);
void imprimirFecha(void* datoA);

int foldingISBN(void* dato);
int foldingTitulo(void* dato);
int foldingTitulo_I(void* dato);
int foldingAutor(void* dato);
int foldingAutor_I(void* dato);
int foldingFecha(void* dato);

int foldingChar_I(void* dato);
int foldingChar(void* dato);
int foldingInt(void* dato);

void agregacion_Libros(Libro *libros,int cant_libros,HashTable *hashtable_ISBN,HashTable *hashtable_Titulo,HashTable *hashtable_Titulo_I,HashTable *hashtable_Autor,HashTable *hashtable_Autor_I,HashTable *hashtable_Fecha);
void vaciarHashes(HashTable *hashtable_ISBN,HashTable *hashtable_Titulo,HashTable *hashtable_Titulo_I,HashTable *hashtable_Autor,HashTable *hashtable_Autor_I,HashTable *hashtable_Fecha);

void cola_A_Arbol(Cola *cola,Arbol *arbol);
void liberarArbol(void *a);

float calcularRangoHash(HashTable *hashTable);

int main(void)
{
	int tam_Hashes = 100;
	char* cadena = NULL;
	
	Arbol expresion;
	expresion.raiz = NULL;
	expresion.cantidad = 0;
	expresion.liberar = &liberarArbol;

	Cola cola;
	
	//Declaracion de Todas los HashMap
	HashTable hashtable_ISBN = inicializarHashTable(tam_Hashes,&imprimirLibro,&compararISBN);
	hashtable_ISBN.folding = &foldingISBN;

	HashTable hashtable_Titulo = inicializarHashTable(tam_Hashes,&imprimirLibro,&compararTitulo);
	hashtable_Titulo.folding = &foldingTitulo;
	
	HashTable hashtable_Titulo_I = inicializarHashTable(tam_Hashes,&imprimirLibro,&compararTitulo_I);
	hashtable_Titulo_I.folding = &foldingTitulo_I;

	HashTable hashtable_Autor = inicializarHashTable(tam_Hashes,&imprimirLibro,&compararAutor);
	hashtable_Autor.folding = &foldingAutor;
	
	HashTable hashtable_Autor_I = inicializarHashTable(tam_Hashes,&imprimirLibro,&compararAutor_I);
	hashtable_Autor_I.folding = &foldingAutor_I;

	HashTable hashtable_Fecha = inicializarHashTable(tam_Hashes,&imprimirLibro,&compararFecha);
	hashtable_Fecha.folding = &foldingFecha;

	//VARIABLE PARA MANEJAR INDICES

	//PUNTERO QUE ALMACENA LA REFERENCIA DEL INICIO DE LOS DATOS
 	int cant_libros = CANT_LIBROS;
	
	Libro *libros_static = obtener_libros();
	Libro *libros = malloc(cant_libros * sizeof(Libro));

	for(int i = 0; i < cant_libros ; i++)
		libros[i] = libros_static[i];

	agregacion_Libros(libros,cant_libros,&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);

	//Menu Principal
	int opcion = 0;
	do{
		printf("\n[ - - - Menu Principal - - - ]\n");
		printf("[1] Busqueda\n");
		printf("[2] Eliminar Libro\n");
		printf("[3] Agregar Libro\n");
		printf("[4] Mostrar Libros\n");
		printf("[5] Salir\n");
		inputEntero("\nSelecciona Opcion : ",&opcion);
		switch(opcion){

			case 1:
			{
				int opcion2 = 0;
				do{
					printf("\n\n\n[ - - - Menu Busqueda - - - ]\n");
					printf("[1] ISBN\n");
					printf("[2] Titulo\n");
					printf("[3] Titulo - Rango\n");
					printf("[4] Autor\n");
					printf("[5] Autor - Rango\n");
					printf("[6] Fecha\n");
					printf("[7] Fecha - Rango\n");
					printf("[8] Salir\n");
					inputEntero("\nSelecciona Opcion : ",&opcion2);
					switch(opcion2){
						case 1:
							if (!inputCadenaDinamica("\nIngresa el ISBN del Libro a Buscar : ", &cadena, MAX_ISBN)) {
								printf("Error leyendo ISBN\n");
								break;
							}
							remover_salto(cadena);

							hashtable_ISBN.folding = &foldingChar;
							cola = buscarClave(&hashtable_ISBN,cadena);
							hashtable_ISBN.folding = &foldingISBN;

							if(!vaciaC(cola)){
								
								expresion.imprimir = &imprimirLibro;
								expresion.comparar = &compararISBN;
								cola_A_Arbol(&cola,&expresion);
								equilibrar(&expresion);

								printf("\n\n - Informacion - \n");
								
								//imprimirArbol(expresion);
								imprimirOrden(expresion,ORDEN);
							}
							else{
								printf("\nNingun Libro Encontrado\n");
							}
						break;

						case 2:
							if (!inputCadenaDinamica("\nIngresa el Titulo del Libro a Buscar : ", &cadena, MAX_TITULO)) {
								printf("Error leyendo Titulo\n");
								break;
							}
							remover_salto(cadena);

							hashtable_Titulo.folding = &foldingChar;
							cola = buscarClave(&hashtable_Titulo,cadena);
							hashtable_Titulo.folding = &foldingTitulo;

							if(!vaciaC(cola)){
								
								expresion.imprimir = &imprimirLibro;
								expresion.comparar = &compararTituloL;
								cola_A_Arbol(&cola,&expresion);
								equilibrar(&expresion);

								printf("\n\n - Informacion - \n");
								
								//imprimirArbol(expresion);
								imprimirOrden(expresion,ORDEN);
							}
							else{
								printf("\nNingun Libro Encontrado\n");
							}
						break;

						case 3:
						{
							char* inferior = NULL;
							char* superior = NULL;
							//Pedir Limite Inferior y Superior
							if (!inputCadenaDinamica("\nIngresa la Inicial Titulo del Libro a Buscar (Limite Inferior): ", &inferior, 5)) {
								printf("Error leyendo Caracter\n");
								break;
							}
							if (!inputCadenaDinamica("\nIngresa la Inicial Titulo del Libro a Buscar (Limite Superior): ", &superior, 5)) {
								printf("Error leyendo Caracter\n");
								break;
							}

							hashtable_Titulo_I.folding = &foldingChar_I;
							cola = buscarClave_Rango(&hashtable_Titulo_I,inferior,superior);
							hashtable_Titulo_I.folding = &foldingTitulo_I;

							if(!vaciaC(cola)){
								
								expresion.imprimir = &imprimirLibro;
								expresion.comparar = &compararTituloL;
								cola_A_Arbol(&cola,&expresion);
								equilibrar(&expresion);

								printf("\n\n - Informacion - \n");
								
								//imprimirArbol(expresion);
								imprimirOrden(expresion,ORDEN);
							}
							else{
								printf("\nNingun Libro Encontrado\n");
							}
						}
						break;

						case 4:
							if (!inputCadenaDinamica("\nIngresa el Autor del Libro a Buscar : ", &cadena, MAX_AUTOR)) {
								printf("Error leyendo Autor\n");
								break;
							}
							remover_salto(cadena);
							hashtable_Autor.folding = &foldingChar;
							cola = buscarClave(&hashtable_Autor,cadena);
							hashtable_Autor.folding = &foldingAutor;
							if(!vaciaC(cola)){
								
								expresion.imprimir = &imprimirLibro;
								expresion.comparar = &compararAutorL;
								cola_A_Arbol(&cola,&expresion);
								equilibrar(&expresion);

								printf("\n\n - Informacion - \n");
								
								//imprimirArbol(expresion);
								imprimirOrden(expresion,ORDEN);
							}
							else{
								printf("\nNingun Libro Encontrado\n");
							}
						break;

						case 5:
						{
							char* inferior = NULL;
							char* superior = NULL;
							//Pedir Limite Inferior y Superior
							if (!inputCadenaDinamica("\nIngresa la Inicial Autor del Libro a Buscar (Limite Inferior): ", &inferior, 5)) {
								printf("Error leyendo Caracter\n");
								break;
							}
							if (!inputCadenaDinamica("\nIngresa la Inicial Autor del Libro a Buscar (Limite Superior): ", &superior, 5)) {
								printf("Error leyendo Caracter\n");
								break;
							}

							hashtable_Autor_I.folding = &foldingChar_I;
							cola = buscarClave_Rango(&hashtable_Autor_I,inferior,superior);
							hashtable_Autor_I.folding = &foldingAutor_I;

							if(!vaciaC(cola)){
								
								expresion.imprimir = &imprimirLibro;
								expresion.comparar = &compararAutorL;
								cola_A_Arbol(&cola,&expresion);
								equilibrar(&expresion);

								printf("\n\n - Informacion - \n");
								
								//imprimirArbol(expresion);
								imprimirOrden(expresion,ORDEN);
							}
							else{
								printf("\nNingun Libro Encontrado\n");
							}
						}
						break;

						case 6:
						{
							int fecha = 0;
							if (!inputEntero("\nIngresa la Fecha del Libro a Buscar : ",&fecha)){
								printf("Error leyendo Fecha\n");
								break;
							}
							printf("%d",fecha);
							hashtable_Fecha.folding = &foldingInt;
							cola = buscarClave(&hashtable_Fecha,&fecha);
							hashtable_Fecha.folding = &foldingFecha;
							if(!vaciaC(cola)){
								
								expresion.imprimir = &imprimirLibro;
								expresion.comparar = &compararFechaL;
								cola_A_Arbol(&cola,&expresion);
								equilibrar(&expresion);

								printf("\n\n - Informacion - \n");
								
								//imprimirArbol(expresion);
								imprimirOrden(expresion,ORDEN);
							}
							else{
								printf("\nNingun Libro Encontrado\n");
							}
						}
						break;

						case 7:
						{
							int inferior = 0;
							int superior = 0;
							//Pedir Limite Inferior y Superior
							if (!inputEntero("\nIngresa la Fecha del Libro a Buscar (Limite Inferior): ",&inferior)){
								printf("Error leyendo Fecha\n");
								break;
							}
							if (!inputEntero("\nIngresa la Fecha del Libro a Buscar (Limite Superior): ",&superior)){
								printf("Error leyendo Fecha\n");
								break;
							}

							hashtable_Fecha.folding = &foldingInt;
							cola = buscarClave_Rango(&hashtable_Fecha,&inferior,&superior);
							hashtable_Fecha.folding = &foldingFecha;

							
							if(!vaciaC(cola)){
								
								expresion.imprimir = &imprimirLibro;
								expresion.comparar = &compararFechaL;
								cola_A_Arbol(&cola,&expresion);
								equilibrar(&expresion);

								printf("\n\n - Informacion - \n");
								
								//imprimirArbol(expresion);
								imprimirOrden(expresion,ORDEN);
							}
							
							else{
								printf("\nNingun Libro Encontrado\n");
							}
						}
						break;

						case 8:
							printf("\n - - Saliendo - - \n");
						break;

						default:
							printf("\n - - Dato Invalido - - \n");
						break;
					}
				}while(opcion2 != 8);
			}
			break;

			case 2:
			{
				if (!inputCadenaDinamica("\nIngresa el ISBN del Libro a Eliminar : ", &cadena, MAX_ISBN)) {
					printf("Error leyendo ISBN\n");
					break;
				}
				remover_salto(cadena);

				//Eliminar del arreglo de libros el libro indicado, decrementando cant_libros
				int validar = 0;
				for(int i = 0 ; i < cant_libros ; i++){
					
					if (strcmp(libros[i].isbn,cadena) == 0){
						printf("Libro Encontrado: %s \n",libros[i].titulo);
						libros[i] = libros[cant_libros-1];
						cant_libros--;
						validar = 1;
						break;
					}
				}
				if(validar == 1){

					//Elimina todos los datos de los hashes
					vaciarHashes(&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);
					//Los vuelve a insertar pero sin el libro eliminado.
					agregacion_Libros(libros,cant_libros,&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);
							
					//Validar El Rango de Cantidades, si es menor al 30 o mayor al 60 se modifica adecuadamente.
					//Con uno se calculan todos
					float porcentaje = calcularRangoHash(&hashtable_ISBN);
					porcentaje = porcentaje*100;
					printf("%%%.2f",porcentaje);

					if(porcentaje < 30){
						//Restarle 10 al Tamano
						hashtable_ISBN.tam -= 10;
						hashtable_Titulo.tam -= 10;
						hashtable_Titulo_I.tam -= 10;
						hashtable_Autor.tam -= 10;
						hashtable_Autor_I.tam -= 10;
						hashtable_Fecha.tam -= 10;
						printf("\n - Remapeado - \n");

						vaciarHashes(&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);
						agregacion_Libros(libros,cant_libros,&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);

						float porcentaje = calcularRangoHash(&hashtable_ISBN);
						porcentaje = porcentaje*100;
						printf("-Nuevo Porcentaje = %%%.2f",porcentaje);
					}
					printf("\n\nLibro Eliminado y Hashes Actualizados\n\n");
				}
				else
					printf("\n\nLibro no Encontrado\n\n");

				free(cadena);
				cadena = NULL;
			}
			break;

			case 3:
			{
				char *isbn = NULL;
				char *titulo = NULL;
				char *autor = NULL;
				int fecha;
				//Pide al Usuario todos los Datos
				if (!inputCadenaDinamica("\nIngresa el ISBN del Libro a Crear : ", &isbn, MAX_ISBN)) {
					printf("Error leyendo ISBN\n");
					break;
				}
				remover_salto(isbn);

				if (!inputCadenaDinamica("\nIngresa el Titulo del Libro a Crear : ", &titulo, MAX_TITULO)) {
					printf("Error leyendo Titulo\n");
					break;
				}
				remover_salto(titulo);

				if (!inputCadenaDinamica("\nIngresa el Autor del Libro a Crear : ", &autor, MAX_AUTOR)) {
					printf("Error leyendo Autor\n");
					break;
				}
				remover_salto(autor);

				if (!inputEntero("\nIngresa la Fecha del Libro a Crear : ",&fecha)){
					printf("Error leyendo Fecha\n");
					break;
				}

				//Validacion de que el ISBN no se repita.
				int validar = 0;
				for(int i = 0 ; i < cant_libros ; i++){
					
					if (strcmp(libros[i].isbn,isbn) == 0){
						validar = 1;
						break;
					}
				}
				if (validar == 1){
					printf("\n\nISBN Repetida - - - Regresando al Menu.\n");
					break;
				}
				else
				{
					//Crea el Libro y lo Agrega
					Libro *nuevo_libros = realloc(libros, (cant_libros + 1) * sizeof(Libro));
					if (nuevo_libros == NULL) {
						printf("Error al reasignar memoria\n");
						break;
					}
					libros = nuevo_libros;

					strcpy(libros[cant_libros].isbn,isbn);
					strcpy(libros[cant_libros].titulo,titulo);
					strcpy(libros[cant_libros].autor,autor);
					libros[cant_libros].fecha = fecha;
					libros[cant_libros].disponible = 1;

					cant_libros++;

					vaciarHashes(&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);
					agregacion_Libros(libros,cant_libros,&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);

					float porcentaje = calcularRangoHash(&hashtable_ISBN);
					porcentaje = porcentaje*100;
					printf("%%%.2f",porcentaje);

					if(porcentaje > 60){
						//Sumarle 10 al Tamano
						hashtable_ISBN.tam += 10;
						hashtable_Titulo.tam += 10;
						hashtable_Titulo_I.tam += 10;
						hashtable_Autor.tam += 10;
						hashtable_Autor_I.tam += 10;
						hashtable_Fecha.tam += 10;
						printf("\n - Remapeado - \n");

						vaciarHashes(&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);
						agregacion_Libros(libros,cant_libros,&hashtable_ISBN,&hashtable_Titulo,&hashtable_Titulo_I,&hashtable_Autor,&hashtable_Autor_I,&hashtable_Fecha);

						float porcentaje = calcularRangoHash(&hashtable_ISBN);
						porcentaje = porcentaje*100;
						printf("-Nuevo Porcentaje = %%%.2f",porcentaje);
					}

				}

			}
			break;

			case 4:
				printf("- - - - - - Libros - - - - - \n\n");
				for(int i = 0 ; i<cant_libros;i++){
					imprimirLibro(&libros[i]);
					printf("\n");
				}
			break;			
			
			case 5:
				printf("\n - - Saliendo - - \n");
			break;

			default:
				printf("\n - - Dato Invalido - - \n");
			break;
		}
	}while(opcion != 5);
	
    printf("\n\n FIN DE PROGRAMA \n");
    return 0;
}

//Recibe un caracter y lo convierte de mayuscula a minuscula
char minuscula(char caracter)
{
	if( caracter>='A' && caracter<='Z')
		return caracter+32;
	return caracter;
}

//Funcion Utilizado en la Comparacion
int compararCadenasIC(char *cadA,char *cadB)
{
	int i;
	char a,b;	
	for( i = 0; cadA[i]!='\0' && cadB[i]!='\0';i++)
	{
		a = minuscula(cadA[i]);
		b = minuscula(cadB[i]);
		if( a == b)
			continue;
		else if(a > b)
			return 1;
		else if(a < b)
		return -1;
	}
	return 0;
}

//Funcion utilizada por la clase Hash para Comparacion entre Datos
int compararISBN(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	char *b=datoB;
	return compararCadenasIC(a->isbn,b);
}

int compararTitulo(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	char *b=datoB;
	return compararCadenasIC(a->titulo,b);
}

int compararTitulo_I(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	char *cadA=a->titulo;
	char b=*((char*)datoB);
	if(minuscula(cadA[0])==minuscula(b))
		return 0;
	else if(minuscula(cadA[0]) < minuscula(b))
		return -1;
	return 1;
}

int compararTituloL(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	Libro *b=datoB;
	return compararCadenasIC(a->titulo,b->titulo);
}

int compararAutor(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	char *b=datoB;
	return compararCadenasIC(a->autor,b);
}

int compararAutor_I(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	char *cadA=a->autor;
	char b=*((char*)datoB);
	if(minuscula(cadA[0])==minuscula(b))
		return 0;
	else if(minuscula(cadA[0]) < minuscula(b))
		return -1;
	return 1;
}

int compararAutorL(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	Libro *b=datoB;
	return compararCadenasIC(a->autor,b->autor);
}

int compararFecha(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	int bb=*((int*)datoB);
	int aa = a->fecha;

	if(aa == bb)
		return 0;
	else if(aa < bb)
		return -1;
	return 1;
}

int compararFechaL(void* datoA,void *datoB)
{	
	Libro *a=datoA;
	Libro *b=datoB;
	int aa = a->fecha;
	int bb = b->fecha;

	if(aa == bb)
		return 0;
	else if(aa < bb)
		return -1;
	return 1;
}

//Funcion utilizada por la clase Hash para Imprimir Datos
void imprimirISBN(void* datoA)
{
	Libro *a =datoA;
	printf("%s",a->isbn);
}

void imprimirTitulo(void* datoA)
{
	Libro *a =datoA;
	printf("%s",a->titulo);
}

void imprimirAutor(void* datoA)
{
	Libro *a =datoA;
	printf("%s",a->autor);
}

void imprimirFecha(void* datoA)
{
	Libro *a =datoA;
	printf("%d",a->fecha);
}

//Funcion para que sea el apuntador a la funcion, se hara uno por cada dato pero a excepcion de la fecha, sera el mismo proceso.
//Algo simple, recorre 
int foldingISBN(void* dato)
{
	Libro *a =dato;
	char *cadena = a->isbn;
	int clave = 0;
	int n = 1;
	
	for(int i = 0; cadena[i]!='\0' ; i++)
	{
		clave+= minuscula(cadena[i]) * n;
		n++;
	}
	return clave;
}

int foldingTitulo(void* dato)
{
	Libro *a =dato;
	char *cadena = a->titulo;
	int clave = 0;
	int n = 1;
	
	for(int i = 0; cadena[i]!='\0' ; i++)
	{
		clave+= minuscula(cadena[i]) * n;
		n++;
	}
	return clave;
}

int foldingTitulo_I(void* dato)
{
	Libro *a =dato;
	char *cadena = a->titulo;

	return minuscula(cadena[0]);
}

int foldingAutor(void* dato)
{
	Libro *a =dato;
	char *cadena = a->autor;
	int clave = 0;
	int n = 1;
	
	for(int i = 0; cadena[i]!='\0' ; i++)
	{
		clave+= minuscula(cadena[i]) * n;
		n++;
	}
	return clave;
}

int foldingAutor_I(void* dato)
{	
	Libro *a =dato;
	char *cadena = a->autor;

	return minuscula(cadena[0]);
}

int foldingFecha(void* dato)
{
	Libro *a = dato;
	return a->fecha;
}

int foldingChar(void* dato)
{
	char *cadena = dato;
	int clave = 0;
	int n = 1;
	
	for(int i = 0; cadena[i]!='\0' ; i++)
	{
		clave+= minuscula(cadena[i]) * n;
		n++;
	}
	return clave;
}

int foldingChar_I(void* dato)
{
	char *cadena = dato;
	return minuscula(cadena[0]);
}

int foldingInt(void* dato)
{
	return (*(int*)dato);
}

void agregacion_Libros(Libro *libros,int cant_libros,HashTable *hashtable_ISBN,HashTable *hashtable_Titulo,HashTable *hashtable_Titulo_I,HashTable *hashtable_Autor,HashTable *hashtable_Autor_I,HashTable *hashtable_Fecha)
{
	int validaciones = 0;

    for(int i = 0 ; i < cant_libros ; i++)
    {
        //printf("\n ");
        //imprimirLibro(&libros[i]);

		//Agregacion a Tablas
		//TABLA ISBN
		validaciones += insertarClave(hashtable_ISBN, &libros[i]);
		//TABLA Titulo
		validaciones += insertarClave(hashtable_Titulo, &libros[i]);
		//TABLA Inicial Titulo
		validaciones += insertarClave(hashtable_Titulo_I, &libros[i]);
		//TABLA Autor		
		validaciones += insertarClave(hashtable_Autor, &libros[i]);
		//TABLA Inicial Autor
		validaciones += insertarClave(hashtable_Autor_I, &libros[i]);
		//TABLA Fecha
		validaciones += insertarClave(hashtable_Fecha, &libros[i]);
    }
	//printf("\n\n Numero de Validaciones = %d\n\n",validaciones);
}

void vaciarHashes(HashTable *hashtable_ISBN,HashTable *hashtable_Titulo,HashTable *hashtable_Titulo_I,HashTable *hashtable_Autor,HashTable *hashtable_Autor_I,HashTable *hashtable_Fecha){
	vaciarHash(hashtable_ISBN);
	vaciarHash(hashtable_Titulo);
	vaciarHash(hashtable_Titulo_I);
	vaciarHash(hashtable_Autor);
	vaciarHash(hashtable_Autor_I);
	vaciarHash(hashtable_Fecha);
}

void cola_A_Arbol(Cola *cola,Arbol *arbol)
{
	arbol->raiz = NULL;
	arbol->cantidad = 0;
	while(!vaciaC(*cola)){
		insertarArbol(arbol,dequeue(cola));
	}
}

void liberarArbol(void *a)
{
	Arbol *aa = a;
	free(aa);
}

float calcularRangoHash(HashTable *hashTable){
	float tam = hashTable->tam;
	float cant = hashTable->cant;
	return (cant/tam);
}