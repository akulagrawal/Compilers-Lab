CXX = gcc
CXXFLAGS = -w

PARSER_SRC = basic_parser.c lex.c main.c
CODEGEN_SRC = code_gen.c lex.c name.c main.c

P_OBJ = $(PARSER_SRC:.cc=.o)
C_OBJ = $(CODEGEN_SRC:.cc=.o)

P_EXEC = parser
C_EXEC = codegen

parser: $(P_EXEC)
code_gen: $(C_EXEC)

$(P_EXEC): $(P_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(P_OBJ)

$(C_EXEC): $(C_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(C_OBJ)

clean:
	rm -rf $(P_EXEC) $(C_EXEC)