CC=mpicc
CFLAGS=-L./obj -g -std=c99 -W -Wall  -Werror


ODIR=obj
LDIR =../lib

LIBS= -l:qmpilib.a -ldl 

DEPS = obj

_OBJ = main.o  
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c
	(cd $(DEPS) && make) 
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -g -o $@  $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	(cd $(DEPS) && make clean)
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

