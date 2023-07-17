CC=g++
CFLAGS= -march=native 
LIB= -O3 -lgmp 
SOURCES= Montgomery.cpp
all: 
	$(CC) -o test $(SOURCES) $(LIB) $(CFLAGS) 
clean: 
	rm *.o 