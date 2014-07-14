CXX=g++
CPPFLAGS=-I/usr/local/include -Isrc
CXXFLAGS=-Wall -pedantic -Wextra -std=c++11 -g3 `sdl-config --cflags` `pkg-config --cflags --libs SDL_image``pkg-config --cflags --libs SDL_mixer`
BIN=prpa
SRC=src/main.cc src/node.cc src/random_suite.cc src/update.cc
OBJ=$(SRC:.cc=.o)
LOGIN=morle_g
TARPREFIX=--prefix=$(LOGIN)-$(BIN)/
TARBALL=$(LOGIN)-$(BIN).tar.bz2

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

check:

leak: $(BIN)
	valgrind --leak-check=full --show-reachable=yes ./$(BIN) $(CHKIN)

clean:
	rm -f $(BIN) $(OBJ) $(BIN).core src/*.orig

export: clean
	git archive HEAD $(TARPREFIX) | bzip2 > $(TARBALL)

.PHONY: clean check doc
