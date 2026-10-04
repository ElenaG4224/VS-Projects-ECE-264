CC = gcc

# compiles to debug
CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -pedantic

# compiles to release
OFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic

test: 
	$(CC) $(CFLAGS) *.c *.h -o hw12

testE: hw12
	./hw12 ./examples/empty.b ./inverted/invertedE.b
	./hw12 ./inverted/invertedE.b ./doubinv/doubinvE.b

test0: hw12
	./hw12 ./examples/tree0.b ./inverted/inverted0.b
	./hw12 ./inverted/inverted0.b ./doubinv/doubinv0.b

test1: hw12
	./hw12 ./examples/tree1.b ./inverted/inverted1.b
	./hw12 ./inverted/inverted1.b ./doubinv/doubinv1.b

test2: hw12
	./hw12 ./examples/tree2.b ./inverted/inverted2.b
	./hw12 ./inverted/inverted2.b ./doubinv/doubinv2.b

test3: hw12
	./hw12 ./examples/tree3.b ./inverted/inverted3.b
	./hw12 ./inverted/inverted3.b ./doubinv/doubinv3.b

testall: teste test0 test1 test2 test3


hw12: 
	$(CC) $(OFLAGS) *.c *.h -o hw12

clean:
	rm -f vgcore.* *.o hw12 *.disc *.txt *.b
