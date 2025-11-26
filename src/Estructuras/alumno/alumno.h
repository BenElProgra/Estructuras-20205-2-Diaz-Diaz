#ifndef ALUMNO_H
#define ALUMNO_H

#include <stdlib.h>

#include "../listadoble/listadoble.h"
#include "../listadoble/nododoble.h"


typedef struct 
{
    unsigned int matricula;
    char nombre[64];
    int semestres;
    float promedio;
} Alumno;

void imprimirAlumno(void *a);

int compararAlumnosMatricula(void *a,void *b);

int compararAlumnosNombre(void *a,void *b);

int compararAlumnosSemestre(void *a,void *b);

int compararAlumnosPromedio(void *a,void *b);

int compararEnteros(void *a, void *b);

#endif