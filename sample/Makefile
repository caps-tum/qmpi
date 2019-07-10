CC=mpicc
CFLAGS=-L../ -std=c99 -W -Wall  -Werror
ODIR=./

LIBS= -lqmpi -ldl 

DEPS =libqmpi

_OBJ = main.o  
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	cd .. && make 
	$(CC) -g -o $@  $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f ./*.o  
	rm -rf *.dSYM/ main

