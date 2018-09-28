CC=mpicc
CFLAGS=-L./src -std=c99 -W -Wall  -Werror
ODIR=./

LIBS= -l:qmpilib.a -ldl 

DEPS =src

_OBJ = main.o  
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -g -o $@  $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
#	(cd $(DEPS) && make clean)
	rm -f ./*.o  

