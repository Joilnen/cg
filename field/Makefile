CC=c++
SRC=main.c
OBJ=main.o 
LIBS=-lGL -lGLU -lglut -lm

.c.o:
	c++ -g  -c $(SRC) $(LIBS)

all:$(OBJ)
	c++ -o field $(OBJ) $(LIBS)
clean:
	rm -rf *.o imgui/*.o > /dev/null
