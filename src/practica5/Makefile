cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
includes = -I ../src/captura -I ../src/Estructuras/cola
libs = ../../lib -lCaptura -lCola
source = $(wildcard *.c) 
output = ../../bin/practica5

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
	
rebuild:
	make -C ../captura
	make -c ../Estructuras/nodos
	make -c ../Estructuras/cola
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"