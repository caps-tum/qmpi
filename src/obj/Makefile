CC= mpicc
CFLAGS=  -g -std=c99 #-W -Wall -Werror
OBJ = qmpi.o #cast.o 
ARFLAGS = rsv
#DEPS = vector
ODIR = .


%.o: %.c
#	(cd $(DEPS) && make)
	$(CC) $(CFLAGS) -o $@  -c $^


qmpilib.a: $(OBJ)
	ar $(ARFLAGS) $@ $^
	ar -t $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.a *~ core $(INCDIR)/*~
#	(cd $(DEPS) && make clean)
