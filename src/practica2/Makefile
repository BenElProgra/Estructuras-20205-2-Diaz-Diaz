cflags = -Wall -Werror -pedantic -std=c99 -O2
includes = -I ../src/captura -I ../src/Estructuras/listadoble -I ../src/Estructuras/alumno
libs = ../../lib -lCaptura -lListaDoble -lAlumno
source = $(wildcard *.c) 
output = ../../bin/practica2

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
