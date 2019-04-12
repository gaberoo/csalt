CC=clang
CXX=clang++

CFLAGS=-Wall -O3
CXXFLAGS=$(CFLAGS) -std=c++14
LDFLAGS=-lgsl

C_SRC = $(wildcard *.c)
C_OBJ = $(C_SRC:%.c=%.o)

all: libcsalt.a

clean:
	@rm -rf *.o
	@rm -f libcsalt.a

libcsalt.a: $(C_OBJ)
	ar rcs libcsalt.a $^

.c.o: $<
	$(CC) $(CFLAGS) -c $<

.cpp.o: $<
	$(CXX) $(CXXFLAGS) -c $<


