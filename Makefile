CC= mpicc
CFLAGS=  -std=c99 -g
OBJ = qmpi.o
ARFLAGS = rsv
ODIR = .


%.o: %.c
	$(CC) $(CFLAGS) -o $@  -c $^


libqmpi.a: $(OBJ)
	ar $(ARFLAGS) $@ $^
	ar -t $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.a *~ core $(INCDIR)/*~
	rm -rf *.dSYM/ main