CC=clang
CXX=clang++

CXXFLAGS=-std=c++14
LDFLAGS=-L.. -lcsalt -lgsl

all: tests
	./tests

tests: tests.cpp ../libcsalt.a
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)
