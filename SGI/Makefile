.PHONY: all clean

CC=g++
BIN=./bin/
SOURCE=./src/

LIST=$(BIN)SGI
LDLIBS+=-lpthread `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
CFLAGS+=-g -Wall -std=c++11

all: pre-build main-build

clean: 
	rm -f $(LIST)

run: 
	$(LIST)

pre-build: clean

main-build: $(LIST)

$(BIN)%: $(SOURCE)%.cpp
	$(CC) $(SOURCE)* $(CFLAGS) -o $@ $(LDLIBS)