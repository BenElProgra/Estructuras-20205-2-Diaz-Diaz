#include <stdio.h>
#include <stdlib.h>

//Vertical
#define REN 27
//Horizontal
#define COL 26

#define ARRIBA 1
#define ABAJO 2
#define DERECHA 4
#define IZQUIERDA 8

#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

/*
Para Compilar :
mingw32-make -C src\Estructuras\pila
mingw32-make -C src\Estructuras\nodos
mingw32-make -C src\captura
mingw32-make -C src\practica4
bin\practica4
*/


//El plan de Funcionamiento es el Siguente:
//Se empieza en el laberinto en coordenada A, y es un bucle while la coordenada actual sea diferente a B,
//Todas las coordenadas que recorre se guardaran en una pila
//En cada iteracion checa cuantas alternativas tenga, dentro de la verificacion de la alternativa validara el simbolo de la coordenada, 
//si todas las alternativas de todas direcciones tienen migajas 'o', hara pop a esa pila, regresando hasta que haya una interseccion que no tenga migaja, y de ser el caso, regresar hasta el inicio.
//Cuando regresa de un camino sin salida, pone un 'o' en el laberinto

typedef struct
{
    int x,y;
}Coordenada;

Coordenada* crearCoordenada(int x,int y);

void imprimirLab(unsigned char **lab);

void imprimirCoordenada(void* dato);

int compararCoordenada(void *a,void *b);

unsigned char ** crear_laberinto(void);

Pila solucion(unsigned char **lab);

void imprimirPosibles(unsigned char caminos);

unsigned char alternativas(unsigned char **lab,Coordenada *coordenada);

void liberarCoordenada(void* dato);

void liberarLaberinto(unsigned char **lab);


int main(void)
{   
    unsigned char **lab; 
    lab = crear_laberinto();
    
    imprimirLab(lab);

    Pila resultado = inicializarPila();
    resultado = solucion(lab);

    resultado.imprimir = &imprimirCoordenada;
    resultado.liberar = &liberarCoordenada;
    imprimirPila(resultado);
    eliminarPila(&resultado);

    imprimirLab(lab);

    liberarLaberinto(lab);

    printf("\n\n");
    return 0;
}


unsigned char ** crear_laberinto(void)
{
    int i,j;
    char *tmp = 
    
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x*************Bx\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";


 /*

"xxxxxxxxxxxxxxxxxxxxxxxxxx\
x*x*****x****************x\
xAxxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**xBx\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x**************x\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

*/

    unsigned char **lab;
    lab = (unsigned char**) malloc(sizeof(unsigned char *)*REN);
    
    for(i=0;i<REN;i++)
    {
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char)*COL);
    }
    
    for(i=0;i<REN;i++)
    {
        for(j=0;j<COL;j++)
        {
            lab[i][j] = tmp[(i*COL)+j];
            if(lab[i][j] == 'B' || lab[i][j] == 'A')
                printf("\nCaracter : [%d][%d]",i,j);
        }   
    }
    return lab;
}

void imprimirLab(unsigned char **lab)
{
    printf("\n");
	int i,j;
	for(i=0;i<REN;i++)
    {
        printf("\n");
        for(j=0;j<COL;j++)
        {
            if(lab[i][j]=='*')
                printf("   ");
			else 
                printf(" %c ",lab[i][j]);
        }   
    }
}

Pila solucion(unsigned char **lab){
    Pila respuesta = inicializarPila();
    //Coordinada Meta de Laberinto, nose si en verdad se ocupa o se puede checar si el caracter del laberinto es 'B'
    lab[25][24] = '*';
    Coordenada *aux = crearCoordenada(9,1);
    lab[9][1] = 'B';
    //Coordenada *aux = crearCoordenada(16,24);

    //Coordenada mas reciente de la pila, para sacar alternativas
    Coordenada *cima;

    unsigned char posibles;

    //Inicio de Laberinto
    push(&respuesta, crearCoordenada(1,1));
    //push(&respuesta, crearCoordenada(2,1));
    
    while(!compararCoordenada(peek(respuesta),aux))
    {
        cima = peek(respuesta);
        posibles = alternativas(lab,cima);
        //imprimirPosibles(posibles);

        //Prioridad de Alternativas
        if(posibles&ARRIBA){
            push(&respuesta,crearCoordenada((cima->x)-1,(cima->y))); 
            //Para que no convierta 'B' en '.' 
            if (lab[cima->x-1][cima->y] != 'A' && lab[cima->x-1][cima->y] != 'B')
                lab[cima->x-1][cima->y] = '.';
        }  
        else if(posibles&ABAJO){
            push(&respuesta,crearCoordenada((cima->x)+1,(cima->y))); 
            if (lab[cima->x+1][cima->y] != 'A' && lab[cima->x+1][cima->y] != 'B')
                lab[cima->x+1][cima->y] = '.';
        }
        else if(posibles&IZQUIERDA){
            push(&respuesta,crearCoordenada((cima->x),(cima->y)-1));
            if (lab[cima->x][cima->y-1] != 'A' && lab[cima->x][cima->y-1] != 'B')
                lab[cima->x][cima->y-1] = '.';
        }        
        else if(posibles&DERECHA){
            push(&respuesta,crearCoordenada((cima->x),(cima->y)+1)); 
            if (lab[cima->x][cima->y+1] != 'A' && lab[cima->x][cima->y+1] != 'B')
                lab[cima->x][cima->y+1] = '.';
        }

 
        
        //Si no cumple ninguno significa que esta en un fin, debe hacer pop pero antes convertir esa coordenada a 'o', significando un camino cerrado
        else{
            //printf("Camino sin Salida!");
            pop(&respuesta);
            lab[cima->x][cima->y] = 'o';
        }
    }
    //printf("Llego!!!");
    free(aux);

    return respuesta;
}


Coordenada* crearCoordenada(int x,int y)
{
    Coordenada *nueva = malloc(sizeof(Coordenada));
    nueva->x = x;
    nueva->y = y;
    return nueva;
}

void imprimirCoordenada(void* dato)
{
    Coordenada *a = dato;
    printf(" [%-2d, %-2d]",a->x,a->y);
}

void liberarCoordenada(void* dato)
{
    Coordenada *a = dato;
    free(a);
}

void liberarLaberinto(unsigned char **lab){    
    for(int i=0;i<REN;i++)
    {
        free(lab[i]);
    }
    free(lab);
}

int compararCoordenada(void *a,void *b)
{
	Coordenada *aa=a,*bb=b;
	if(aa->x==bb->x && aa->y==bb->y)
		return 1;
	return 0;
}

unsigned char alternativas(unsigned char **lab,Coordenada *coordenada)
{		
	unsigned char caracter;
	unsigned char banderas;
	banderas = 0;	
	//EVALUAR ALTERNATIVA Y REGISTRAR POSIBILIDAD DE MOVIMIENTO
	//EN UN REGISTRO DE BITS/BANDERAS	
	caracter = lab[coordenada->x-1][coordenada->y];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= ARRIBA;
	
	caracter = lab[coordenada->x+1][coordenada->y];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= ABAJO;
	
	caracter = lab[coordenada->x][coordenada->y+1];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= DERECHA;
	
	caracter = lab[coordenada->x][coordenada->y-1];
	if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
		banderas |= IZQUIERDA;
	return banderas;	
}


void imprimirPosibles(unsigned char caminos)
{
    printf("\n");
    if(caminos&ARRIBA)
        printf("\n Arriba");
    if(caminos&ABAJO)
        printf("\n Abajo");
    if(caminos&IZQUIERDA)
        printf("\n Izquierda");
    if(caminos&DERECHA)
        printf("\n Derecha");
    printf("\n");
}


