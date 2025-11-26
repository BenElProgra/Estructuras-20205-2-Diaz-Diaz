
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

#include <stdarg.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

#define LONGITUD 64

void imprimirCadena(void *a);

void liberarCadena(void *a);

char* conversionInPos(char *a);


/*
Para Compilar :
mingw32-make -C src\Estructuras\nodos
mingw32-make -C src\Estructuras\pila
mingw32-make -C src\captura

mingw32-make -C src\practica7
mingw32-make -C src\practica7 rebuild
mingw32-make -C src\practica7 run

*/

int main(void){
	
	char* cadena = NULL;
	char* cadena2 = NULL;

	
	int opcion = 0;
	do{
		printf("\n\n- - Menu InFix - PosFix - -\n");
		printf("[1] Conversion Infix a PosFix\n");
		printf("[2] Salir\n");
		inputEntero("\nSelecciona Opcion : ",&opcion);
		switch(opcion){
			case 1:
				inputCadenaDinamica("\n\nIngresa operacion InFix para ser Convertida a PosFix : ",&cadena,LONGITUD);
				printf("\n Operacion Infix  =  ");
				imprimirCadena(cadena);
				char* cadena2 = conversionInPos(cadena);
				if (cadena != NULL){
					printf("\n Operacion Posfix  =  ");
					imprimirCadena(cadena2);
				}
				else
					printf("\n - - Operacion Invalida - - ");
			break;

			case 2:
				printf("\n - - Saliendo - - \n");
			break;

			default:
				printf("\n - - Dato Invalido - - \n");
			break;
		}
	}while(opcion != 2);
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
				while(comparaPrecedencia(letra,peek(pila)) != 1 && !vacia(pila) && *(char*)peek(pila) != '(')
					sacarPila_a_PostFix(&pila,&con2,posfix);
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
				while(comparaPrecedencia(letra,peek(pila)) != 1 && !vacia(pila) && *(char*)peek(pila) != '(')
					sacarPila_a_PostFix(&pila,&con2,posfix);
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