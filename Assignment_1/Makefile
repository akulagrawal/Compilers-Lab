CXX = gcc
PY = python3
CXXFLAGS = -w

PARSER_SRC = basic_parser.c lex.c main.c
CODEGEN_SRC = code_gen.c lex.c name.c main.c

RENAME_VAR = rename_vars.py
ASSEMBLER = assembly.py
INPUT = IR.txt

# Parser
########################################################### 
P_OBJ = $(PARSER_SRC:.cc=.o)
P_EXEC = parser
parser: $(P_EXEC)

$(P_EXEC): $(P_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(P_OBJ)

# Codegen
###########################################################
C_OBJ = $(CODEGEN_SRC:.cc=.o)
C_EXEC = codegen
code_gen: $(C_EXEC)

$(C_EXEC): $(C_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(C_OBJ)

# Assembly
###########################################################
EXEC_CODEGEN = EXEC_CODEGEN
RUN = run
$(EXEC_CODEGEN):	$(C_EXEC)
	./$(C_EXEC) > $(INPUT)

$(RUN): $(EXEC_CODEGEN)
	$(PY) $(RENAME_VAR) $(INPUT)
	$(PY) $(ASSEMBLER)

clean:
	rm -rf $(P_EXEC) $(C_EXEC)