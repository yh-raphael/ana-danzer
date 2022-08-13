.PHONY: all clean
.DEFAULT_GOAL := all

LIBS=-lrt -lm -lstdc++fs -lssl -lcrypto
INCLUDES=-./include
CFLAGS=-std=c++17 -O3 -g

output = ana-danzer

all: main

main: analyze.cpp
	g++ $(CFLAGS) -o ana-danzer analyze.cpp $(LIBS)

clean:
	rm $(output)
