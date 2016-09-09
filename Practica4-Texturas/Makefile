# fichero Makefile
#
# nombre del fichero ejecutable
#
INC = ./include
SRC = ./src
OBJ = ./obj

TARGETS= practica4

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -v -g -DXWINDOWS -DSHM -I/usr/include -I. -I$(INC)
CXXFLAGS=  -v -g -DXWINDOWS -DSHM -I/usr/include -I$(INC)

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#
$(TARGETS) : $(OBJ)/practica4.o
	$(CC) -o $@ $(CXXFLAGS) practica4.o $(LDFLAGS)

$(OBJ)/practica4.o : $(SRC)/practica3.cc $(INC)/*
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(SRC)/practica3.cc -o $(OBJ)/practica4.o
#
#
clean:
	rm -f $(OBJ)/*.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *

