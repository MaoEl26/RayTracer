OBJECTS=rayTrace.o
OUTPUT=rayTrace

CFLAGS=-I/usr/local/Mesa-3.4/include
LDLIBS=-lX11 -lglut -lGLU -lGL -lm -lXext -lXmu
LDFLAGS=-L/usr/local/Mesa-3.4/lib -L/usr/X11R6/lib

$(OUTPUT): input.o rayTrace.o
	gcc -g input.o rayTrace.o -o $(OUTPUT) $(LDLIBS) $(CFLAGS) $(LDFLAGS)

input.o: input.h

rayTrace.o:Esfera.h estructuras.h rayTrace.h

clean:
	rm -f *.o
	rm -f raytrace
