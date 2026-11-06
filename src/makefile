OBJ = func.o extra.o menus.o adverse_effects.o termio.o antenna.o traversals.o
HEADER = includes.h data.h func.h menus.h extra.h adverse_effects.h termio.h antenna.h traversals.h

all: run

%.o: %.c $(HEADER)
	gcc -c $< -o $@

prog: main.c $(OBJ)
	gcc main.c $(OBJ) -o prog

run: prog
	./prog

clean:
	rm prog *.o *.bin
