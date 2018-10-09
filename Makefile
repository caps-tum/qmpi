CC=mpicc
CFLAGS=-L./libqmpi -std=c99 -W -Wall  -Werror
ODIR=./

LIBS= -lqmpi -ldl 

DEPS =libqmpi

_OBJ = main.o  
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	cd libqmpi && make 
	$(CC) -g -o $@  $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	(cd libqmpi && make clean)
	rm -f ./*.o  
	rm -rf *.dSYM/ main

