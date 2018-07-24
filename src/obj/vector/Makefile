CC= mpicc
CFLAGS=-g -std=c99 -Wall  -Werror
RM= rm -rf

vector.o: vector.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	$(RM) *.o $(OUT)
