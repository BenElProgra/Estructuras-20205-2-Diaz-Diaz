#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <math.h>

#include <stdbool.h>

#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"
#include "../Estructuras/cola/cola.h"
#include "../Estructuras/arbol/arbol.h"
#include "../Estructuras/nodos/nodoarbol.h"


#define LONGITUD 64

typedef struct
{
	char caracter;
	float valor;
}Dato;

Dato* crearDato(char caracter,float valor);
void imprimirDato(void *dato);

Cola* expresionACola(char *expresion);
Cola* expresionAColaEvaluado(char *expresion);

void expresionAArbol(Cola *cola,Arbol *arbol);

void imprimirCaracter(void *a);
void imprimirFlotante(void *a);

void imprimirCadena(void *a);
void liberarCadena(void *a);
char* conversionInPos(char *a);

float evaluacionArbol(NodoA *nodo);

void flip(NodoA *nodo);

/*
Para Compilar :
mingw32-make -C src\Estructuras\nodos
mingw32-make -C src\Estructuras\pila
mingw32-make -C src\captura

mingw32-make -C src\practica8
mingw32-make -C src\practica8 rebuild
mingw32-make -C src\practica8 run

*/

int main(void){
	
	char* cadena = NULL;
	char* cadena2 = NULL;

	Arbol expresion;
	expresion.raiz = NULL;
	expresion.cantidad = 0;
	expresion.imprimir = &imprimirCaracter;
	expresion.liberar = &free;

	
	int opcion = 0;
	do{
		printf("\n\n- - Menu InFix - PosFix - -\n");
		printf("[1] Conversion Infix a PosFix\n");
		printf("[2] Imprimir Arbol de Expresion\n");
		printf("[3] Evaluar Expresion\n");
		printf("[4] Salir\n");
		inputEntero("\nSelecciona Opcion : ",&opcion);
		switch(opcion){
			case 1:
				inputCadenaDinamica("\n\nIngresa operacion InFix para ser Convertida a PosFix : ",&cadena,LONGITUD);
				printf("\n Operacion Infix  =  ");
				imprimirCadena(cadena);
				cadena2 = conversionInPos(cadena);
				if (cadena != NULL){
					printf("\n Operacion Posfix  =  ");
					imprimirCadena(cadena2);

					//Cadena2 es la operacion en formato postfix
					Cola *colaExpresion = expresionACola(cadena2);
					expresionAArbol(colaExpresion,&expresion);
				}
				else
					printf("\n - - Operacion Invalida - - ");
			break;

			case 2:
				if(expresion.raiz != NULL){
					printf(" - - Arbol de Expresion - - \n\n");
					//expresion.imprimir = &imprimirCaracter;
					expresion.imprimir = &imprimirDato;
					//expresion.imprimir = &imprimirFlotante;
					imprimirArbol(expresion);
				}
				else{
					printf("No hay expresion capturada");
				}
			break;

			case 3:
				if(cadena2 != NULL){
					Cola *colaExpresion = expresionAColaEvaluado(cadena2);
					expresionAArbol(colaExpresion,&expresion);
					float resultado = evaluacionArbol(expresion.raiz);

					printf("\n\nEl Resultado de la Operacion es: %.2f\n\n",resultado);

				}
				else{
					printf("\n\n - - Expresion PostFix sin Declarar - - \n\n");
				}
			break;

			case 4:
				printf("\n - - Saliendo - - \n");
			break;

			case 5:
				imprimirOrden(expresion,ORDEN);
				printf("\n");
				flip(expresion.raiz);
				imprimirOrden(expresion,ORDEN);

			break;

			default:
				printf("\n - - Dato Invalido - - \n");
			break;
		}
	}while(opcion != 4);
	eliminarArbol(&expresion);
	free(cadena);
	free(cadena2);
}

int calculaPrecedencia(char c)
{
	switch(c)
	{
		case '+':
			return 1;
		case '-':
			return 1;

		case '*':
			return 2;
		case '/':
			return 2;

		case '^':
			return 3;
	}
	return 0;
}

int comparaPrecedencia(void *a,void *b)
{
	char *aa = a , *bb = b;
	if( calculaPrecedencia(*aa)>calculaPrecedencia(*bb))
		return 1;
	else if ( calculaPrecedencia(*aa)<calculaPrecedencia(*bb))
		return -1;
	else return 0;
}

bool validacionParentesis(void *a)
{
	char *aa = a;
	Pila pila1 = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	int cant = 0;
	while (aa[cant] != '\0')
	{
		if(aa[cant] == '(')
		{
		char *letra = malloc(2);
		letra[0] = aa[cant];
		letra[1] = '\0';
		push(&pila1,cadenaDinamica(letra));
		liberarCadena(letra);
		}
		else if(aa[cant] == ')')
		{
			if(vacia(pila1))
			{
				eliminarPila(&pila1);
				return false;
			}
			else
			{
				char *dato = pop(&pila1);
				switch(*dato){
					case '(':
						if (aa[cant] != ')')
						{
							eliminarPila(&pila1);
							free(dato);
							return false;
						}	
					break;
				}
				free(dato);
			}
		}
		cant++;
	}
	if(vacia(pila1))
	{
		eliminarPila(&pila1);
		return true;
	}
	else
	{
		eliminarPila(&pila1);
		return false;
	}
}

int contarParentesis(void *a)
{
	char *aa = a;
	int cant = 0;
	int total = 0;
	while (aa[cant] != '\0')
	{
		if(aa[cant] == '(' || aa[cant] == ')')
			total++;
		cant++;
	}
	return total;
}

void imprimirCadena(void *a)
{
	char *aa = a;
	printf("%s",aa);	
}

void liberarCadena(void *a)
{
	char *aa = a;
	free(aa);
}

//Costaron un trabajito pero para modular la practica y no estar tan grande.
void sacarPila_a_PostFix(Pila *pila,int *con2,char *posfix)
{
	char* dato = pop(pila);
	posfix[(*con2)] = dato[0];
	free(dato);
	(*con2)++;
}

void insertarPila(Pila *pila,char caracter)
{
	char *letra = malloc(2);
	letra[0] = caracter;
	letra[1] = '\0';
	push(pila,cadenaDinamica(letra));
	liberarCadena(letra);
}


char* conversionInPos(char *a)
{
	if(!validacionParentesis(a))
		return NULL;

	int longitud_Expresion = strlen(a)+1;
	int cantidad_Parentesis = contarParentesis(a);

	int longitudFinal = longitud_Expresion - cantidad_Parentesis;

	char *posfix = calloc(longitudFinal,sizeof(char));

	//Nota:
	//Simbolos : ^,( ,) ,* ,/ ,+ ,-.

	Pila pila = {NULL,-1,0,NULL,&liberarCadena};
	int con = 0;
	int con2 = 0;

	while (a[con] != '\0')
	{
		if(a[con] == '(')
		{
			insertarPila(&pila,a[con]);
		}
		else if(a[con] == ')')
		{
			//Cilclo de poner en la cadena 2 todos los operadores hasta que llegue a '(', o en el peor caso la pila se acaba y de ese ser el caso es una operacion incorrecta y retorna falso o algo.
			while(*(char*)peek(pila) != '(' && !vacia(pila))
				sacarPila_a_PostFix(&pila,&con2,posfix);
			if(*(char*)peek(pila) == '(')
				pop(&pila);
		}
		else if(a[con] == '^')
		{
			//Si esta vacio insertar inmediatamente
			if(vacia(pila) || *(char*)peek(pila) == '(')
				insertarPila(&pila,a[con]);	
			else
			{
				char *letra = malloc(2);
				letra[0] = '^';
				letra[1] = '\0';
				//Validar La Jerarquia, si hay de jerarquia mayor o igual se saca de la pila y se pone en la cadena 2, puede ser mas de una vez por lo que debe ser while.
				
				while(!vacia(pila)){
					if(comparaPrecedencia(letra,peek(pila)) != 1 && *(char*)peek(pila) != '(')
						sacarPila_a_PostFix(&pila,&con2,posfix);
					else
						break;
				}

				letra[0] = a[con];
				letra[1] = '\0';
				push(&pila,cadenaDinamica(letra));
				liberarCadena(letra);
			}
		}
		else if(a[con] == '*' || a[con] == '/'){
			if(vacia(pila) || *(char*)peek(pila) == '(')
				insertarPila(&pila,a[con]);
			else
			{
				char *letra = malloc(2);
				letra[0] = '*';
				letra[1] = '\0';
				//Validar La Jerarquia, si hay de jerarquia mayor o igual se saca de la pila y se pone en la cadena 2, puede ser mas de una vez por lo que debe ser while.
			
				while(!vacia(pila)){
					if(comparaPrecedencia(letra,peek(pila)) != 1 && *(char*)peek(pila) != '(')
						sacarPila_a_PostFix(&pila,&con2,posfix);
					else
						break;
				}
				
				letra[0] = a[con];
				letra[1] = '\0';
				push(&pila,cadenaDinamica(letra));
				liberarCadena(letra);
			}
		}
		else if(a[con] == '+' || a[con] == '-'){
				//Validar La Jerarquia, si hay de jerarquia mayor o igual se saca de la pila y se pone en la cadena 2, puede ser mas de una vez por lo que debe ser while.
				//En este caso se deberia quitar todos los operandos hasta que la pila sea vacia o llegue a un '('
			if(vacia(pila) || *(char*)peek(pila) == '(')
				insertarPila(&pila,a[con]);
			else
			{
				//Validar La Jerarquia, si hay de jerarquia mayor o igual se saca de la pila y se pone en la cadena 2, puede ser mas de una vez por lo que debe ser while.
				while(!vacia(pila) && *(char*)peek(pila) != '(')
					sacarPila_a_PostFix(&pila,&con2,posfix);
				//Ya que puso en la cadena todos los otros simbolos, pone en la pila la '+' o '-'
				insertarPila(&pila,a[con]);
			}
		}
		else{
		//Es Operando
			posfix[con2] = a[con];
			con2++;
		}
		con++;
	}
	//Recorrio toda la cadena

	while(!vacia(pila))
		sacarPila_a_PostFix(&pila,&con2,posfix);
	eliminarPila(&pila);
	posfix[con2] = '\0';
	return posfix;
}



//Practica 8.
Dato* crearDato(char caracter,float valor)
{
	Dato *nuevo = calloc(1,sizeof(Dato));
	nuevo->caracter = caracter;
	nuevo->valor = valor;
	return nuevo;
}

int compararCaracteres(void *param_a,void *param_b)
{	
	char *datoa  = param_a;
	NodoA *nodob = param_b;
	Dato *datob  = nodob->dato;
	if( *datoa == datob->caracter)
		return 0;
	return 1;
}


Cola* expresionACola(char *expresion)
{
	Cola *cola = calloc(1,sizeof(Cola));
	*cola = inicializarCola();
	cola->imprimir = &imprimirDato;
	int i;
	for( i = 0; expresion[i]!='\0' ; i++)
	{
		//Cuando un caracter de la expresion ya fue previamente encontrada en la cola, ponia el dato
		NodoA *nodo = buscarC(*cola,&expresion[i],&compararCaracteres);
		Dato* dato;
		if(nodo)
			dato = nodo->dato;
		else 
			dato = crearDato(expresion[i],0);
		NodoA *nodoa = crearNodoA(dato);
		enqueue(cola,nodoa);
	}
	return cola;
}

void expresionAArbol(Cola *cola,Arbol *arbol){
	//printf("Puerta 1");
	//Pila donde se ingresaran los nodos de la expresion ya guardados en la cola
	Pila pila = {NULL,-1,0,NULL,&liberarCadena};

	while(!vaciaC(*cola)){
		//Hace peek a cola, retorna un void*, que es casteado a NodoA, posteriormente se intenta accede a dato que es void*, despues es caseado a un tipo estructura Dato, y finalmente puede acceder al caracter para comparar.
		if(((Dato*)((NodoA*)peekC(*cola))->dato)->caracter != '+' && ((Dato*)((NodoA*)peekC(*cola))->dato)->caracter != '-' && ((Dato*)((NodoA*)peekC(*cola))->dato)->caracter != '*' && ((Dato*)((NodoA*)peekC(*cola))->dato)->caracter != '/' && ((Dato*)((NodoA*)peekC(*cola))->dato)->caracter != '^')
		{
			//Poner en la pila el dequeue (Es Letra)
			push(&pila,dequeue(cola));
		}
		else
		{
			//Hacer dos dequeue para poner el primero en la derecha 
			NodoA *nodo = dequeue(cola);
			nodo->dch = pop(&pila);
			nodo->izq = pop(&pila);
			push(&pila,nodo);
		}
	}
	//En teoria al final solo deberia quedar la rama del arbol en la pila
	arbol->raiz = pop(&pila);
	//printf("Puerta 2");
}

void imprimirDato(void *dato)
{
	Dato *info = dato;
	printf(" %c = %f",info->caracter,info->valor);
}

void imprimirCaracter(void *a)
{
	char *aa=a;
	printf("%c",*aa);
}

void imprimirFlotante(void *a)
{
	float *aa=a;
	printf("%.2f",*aa);
}

Cola* expresionAColaEvaluado(char *expresion)
{
	Cola *cola = calloc(1,sizeof(Cola));
	*cola = inicializarCola();
	cola->imprimir = &imprimirDato;
	float valor;

	for(int i = 0; expresion[i] != '\0';i++){
		Dato *dato = NULL;
		if(expresion[i] != '+' && expresion[i] != '-' && expresion[i] != '*' && expresion[i] != '/' && expresion[i] != '^'){
			//Validar que el caracter no haya sido previamente ingresado.
			int validacion = 0;
			for(int j =0; j<i ; j++){
				//Mismo Caracter
				if(expresion[i] == expresion[j])
				{
					//printf("\nEncontrado previamente\n");
					validacion = 1;
					break;
				}
			}
			if(validacion == 0){
				//Si validacion es 1 es porque no se encontro el mismo caracter previamente, por ende se le pide.
				printf("\n - - Ingresa el Valor correspondiente al caracter %c   =   ",expresion[i]);
				inputFloat("",&valor);
				dato = crearDato(expresion[i],valor);
			}
			else{
				//En teoria como si existe nunca devolvera null.
				NodoA *nodo = buscarC(*cola,&expresion[i],&compararCaracteres);
				dato = nodo->dato;
			}
		}
		else{
			//Crear el nodo tipo dato
			valor = 0;
			dato = crearDato(expresion[i],valor);
			//printf("Caracter Detectado");
		}
		NodoA *nodoa = crearNodoA(dato);
		enqueue(cola,nodoa);
	}
	//printf("\n\nPuerta X\n\n");
	return cola;
}

float evaluacionArbol(NodoA *nodo){
	//Funcion recursiva que navegue hasta abajo y en forma PostOrden haga las operaciones de 
	//abajo a arriba, guardando el valor de la operacion en el nodo padre.
	if(!nodo)
		return 0;
	float valor = 0;

	float dato_izq = evaluacionArbol(nodo->izq);
	float dato_der = evaluacionArbol(nodo->dch);

	switch(((Dato*)nodo->dato)->caracter){
		case '+':
			valor = dato_izq + dato_der;
			return valor;
		break;

		case '-':
			valor = dato_izq - dato_der;
			return valor;	
		break;
		
		case '*':
			valor = dato_izq * dato_der;
			return valor;
		break;
		
		case '/':
			valor = dato_izq / dato_der;
			return valor;
		break;

		case '^':
			valor = pow(dato_izq , dato_der);
			return valor;
		break;
	}

	return ((Dato*)((NodoA*)nodo)->dato)->valor;
}

void flip(NodoA *nodo){

	if(nodo!= NULL){
		flip(nodo->izq);
		flip(nodo->dch);
		NodoA *tmp = nodo->izq;
		nodo->izq = nodo->dch;
		nodo->dch = tmp;
	}
	return;
	/*
	if(!nodo)
		return;
	flip(nodo->izq);
	flip(nodo->dch);
	NodoA *tmp = nodo->izq;
	nodo->izq = nodo->dch;
	nodo->dch = tmp;
	*/
}