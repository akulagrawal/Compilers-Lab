CXX = gcc
CXXFLAGS = -w
SRC = basic_parser.c lex.c main.c
OBJ = $(SRC:.cc=.o)
EXEC = run

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

clean:
	rm -rf $(EXEC)