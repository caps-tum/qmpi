CC= mpicc
CFLAGS=  -std=c99 
OBJ = qmpi.o
ARFLAGS = rsv
ODIR = .


%.o: %.c
	$(CC) $(CFLAGS) -o $@  -c $^


qmpilib.a: $(OBJ)
	ar $(ARFLAGS) $@ $^
	ar -t $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.a *~ core $(INCDIR)/*~
