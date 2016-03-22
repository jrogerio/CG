.PHONY: all clean

CC=gcc
BIN=./bin/
SOURCE=./src/

LIST=$(BIN)SGI
LDLIBS+=`pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
CFLAGS+=-Wall -rdynamic -lstdc++ -std=c++11 -lm

all: pre-build main-build

clean: 
	rm -f $(LIST)

run: 
	$(LIST)

pre-build: clean

main-build: $(LIST)

$(BIN)%: $(SOURCE)%.cpp
	$(CC) -o vpl_wexecution $(SOURCE)* $(LDLIBS) $(CFLAGS)