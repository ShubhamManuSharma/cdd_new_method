CC=gcc
TARGET=app
CFLAGS=-I.
LDFLAGS=-lpthread
DEPS = header.h declaration.h
OBJ = main.o init.o mainMenu.o operation.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

app: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o ${TARGET}
