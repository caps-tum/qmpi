CC= mpicc
CFLAGS= -I../../ -std=c99 -fPIC -rdynamic -shared 
LIBS = -lqmpi -L../../ -ldl
OBJ = very_simple_tool
ODIR = ./


./very_simple_tool.so: ./very_simple_tool.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ ../../qmpi.c 
#	cd ./mpiP_refactored && make clean && make shared && cd ..

clean:
	rm -f $(ODIR)/*.so  
#	cd mpiP_refactored && make clean && cd ..
