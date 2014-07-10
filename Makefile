CXX?=g++
CPPFLAGS=-I/usr/local/include -Isrc
CXXFLAGS=-Werror -Wall -pedantic -Wextra -std=c++11 -O3
BIN=prpa
SRC=
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
	rm -f $(BIN) $(OBJ) $(BIN).core

export: clean
	git archive HEAD $(TARPREFIX) | bzip2 > $(TARBALL)

.PHONY: clean check doc
