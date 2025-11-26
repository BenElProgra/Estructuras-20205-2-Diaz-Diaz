#include "alumno.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void imprimirAlumno(void *a)
{
	Alumno *aa;
	aa = a;
	printf("%d - %s - %d - %.2f ",aa->matricula,aa->nombre,aa->semestres,aa->promedio);
	
}

int compararAlumnosMatricula(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	if ( aa->matricula > ab->matricula)
		return 1;
	if ( aa->matricula < ab->matricula)
		return -1;
	return 0;
}

int compararAlumnosNombre(void *a,void *b)
{
	Alumno *aa,*ab;  
	aa = a;
	ab = b;
	return strcmp( aa->nombre,ab->nombre);
}

int compararAlumnosSemestre(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	if ( aa->semestres > ab->semestres)
		return 1;
	if ( aa->semestres < ab->semestres)
		return -1;
	return 0;
}

int compararAlumnosPromedio(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	if ( aa->promedio > ab->promedio)
		return 1;
	if ( aa->promedio < ab->promedio)
		return -1;
	return 0;
}	

int compararEnteros(void *a, void *b)
{
	int *ea,*eb;
	ea = a;
	eb = b;
	if( *ea < *eb )
		return -1;
	else if ( *ea > *eb)
		return 1;
	else
		return 0;	
}