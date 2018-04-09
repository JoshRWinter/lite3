CPP := gcc
REMOVE := rm -rf
TESTDB := testdb

CPPFLAGS := -g -std=c++14
LFLAGS := -lsqlite3

all:
	$(REMOVE) $(TESTDB)
	g++ -o main.test $(CPPFLAGS) main.cpp lite3.cpp $(LFLAGS)
	./main.test
