//INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

/*
Para Compilar :
mingw32-make -C src\Estructuras\pila
mingw32-make -C src\Estructuras\nodos
mingw32-make -C src\captura
mingw32-make -C src\practica3
bin\practica3
*/

#define LONGITUD 64

void imprimirCadena(void *a);

void liberarCadena(void *a);

bool validacionPalindromo(void*a);

bool validacionParentesis(void *a);

//FUNCION MAIN




//Primera parte, tener dos pilas, una con el arreglo nrormal y otro con arreglo invertido, luego se hacen pops y valida que los nodos sacados tengan en mismo caracter.
/*
char *p1,*p2
p1 = pop(&pila1);
p2 = pop(&pila2);
if (*p1==*p2)
*/

//Segunda parte, llaves que abren hace push, llaves que cierran hacen pop y analizas, cuando hay llave que cierra y haces pop comparas que sean complementarios (),[],{}, en caso de que no lo sea {],(} cancelas el proceso y cierras ya que no es valido, si terminas la cadena y sobra llaves en la pila significa que no es valido tampoco (al finalizar la cadena la pila no esta vacia), o cuando hay underflow (pop cuando pila esta vacio (   ][)]  ).

/*
switch(*apertura)
	case '{';
		cierre == '}'
*/

int main(void)
{
	// {INICIO NULO, SIN LIMITE, CANTIDAD 0, COMO IMPRIMIR, COMO LIBERAR}
	//Pila pila = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	//Pila pilaC = {NULL,-1,0,&imprimirCadena,NULL};

	char *p = NULL;
	int opcion = 0;
	do{
		inputEntero("\n\n- - - - Menu - - -\n[1] Palindromo\n[2] Verificacion de Parentesis\n[3] Salir\n\nOpcion : ",&opcion);
		switch(opcion){
			case 1:
				inputCadenaDinamica("Ingresa la cadena : ",&p,LONGITUD);
				printf("\n\nLa cadena '");
				imprimirCadena(p);
				if (validacionPalindromo(p))
					printf("' es Palindomo.");
				else
					printf("' no es Palindomo.");
				break;

			case 2:
				inputCadenaDinamica("Ingresa la cadena : ",&p,LONGITUD);
				printf("\n\nLa cadena '");
				imprimirCadena(p);
				if (validacionParentesis(p))
					printf("' es Valida.");
				else
					printf("' no es Invalida.");
				break;
				break;

			case 3:
				printf("\n\nSaliendo ... ");
				break;

			default:
				printf("\n\nDato Invalido\n\n");
				break;
		}
	}while(opcion!=3);
	return 0;
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

bool validacionPalindromo(void *a)
{
	char *aa = a;
	Pila pila1 = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	Pila pila2 = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	int con = 0;
	//Insertar caracters a las dos pilas, una normal y otra inversa sin incluir espacios
	while(aa[con] != '\0')
	{
		if (aa[con] != ' ')
		{
			if(aa[con] >= 'A' && aa[con] <= 'Z' )
				aa[con] += 32;
			char *letra = malloc(2);
			letra[0] = aa[con];
			letra[1] = '\0';
			push(&pila1, cadenaDinamica(letra));
			liberarCadena(letra);
		}
		con++;
	}
	while(con != 0)
	{
		con--;
		if(aa[con] != ' ')
		{
			char *letra = malloc(2);
			letra[0] = aa[con];
			letra[1] = '\0';
			push(&pila2, cadenaDinamica(letra));
			liberarCadena(letra);
		}
	}
	//imprimirPila(pila1);
	//imprimirPila(pila2);

	while (!vacia(pila1))
	{
		char* dato1 = pop(&pila1);
		char* dato2 = pop(&pila2);

		if(*dato1 != *dato2)
		{
			free(dato1);
			free(dato2);
			eliminarPila(&pila1);
			eliminarPila(&pila2);
			return false;
		}
		else
		{
			free(dato1);
			free(dato2);
		}
	}
	eliminarPila(&pila1);
	eliminarPila(&pila2);
	return true;
}

bool validacionParentesis(void *a)
{
	char *aa = a;
	Pila pila1 = {NULL,-1,0,&imprimirCadena,&liberarCadena};
	int cant = 0;
	while (aa[cant] != '\0')
	{
		if(aa[cant] == '[' || aa[cant] == '{' || aa[cant] == '(')
		{
		char *letra = malloc(2);
		letra[0] = aa[cant];
		letra[1] = '\0';
		push(&pila1,cadenaDinamica(letra));
		liberarCadena(letra);
		}
		else if(aa[cant] == ']' || aa[cant] == '}' || aa[cant] == ')')
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

					case '[':
						if (aa[cant] != ']')
						{
							eliminarPila(&pila1);
							free(dato);
							return false;
						}
					break;

					case '{':
						if (aa[cant] != '}')
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