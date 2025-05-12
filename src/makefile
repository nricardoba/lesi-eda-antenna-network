OBJ = func.o extra.o menus.o nefasto.o termio.o
HEADER = includes.h dados.h func.h menus.h extra.h nefasto.h termio.h

all: run

%.o: %.c $(HEADER)
	gcc -c $< -o $@

prog: main.c $(OBJ)
	gcc main.c $(OBJ) -o prog

run: prog
	./prog

clean:
	rm prog *.o
