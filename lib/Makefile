CC= mpicc
CFLAGS= -g -std=c99 -fPIC -rdynamic -shared 

%.so: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f ./*.o ./*.so *~ core $(INCDIR)/*~   
