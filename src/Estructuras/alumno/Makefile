cflags = -Wall -Werror -pedantic -std=c99 -O2 -c
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libAlumno.a

build :
	gcc $(cflags) $(source) 
	ar rcs $(output) $(source_o) 
	@echo "Compilo Exitosamente!!!"
