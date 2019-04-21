CXX = g++
CPP = g++
CXXFLAG = -g -std=c++11
# DEBUG_FLAG=gdb

file=input.txt

run:	build
		./a.out

build:
		$(CPP) $(CXXFLAG) intermediate.cpp

semantics:	build_bison
		$(DEBUG_FLAG) ./a.out

build_bison:	BISON FLEX
	$(CXX) $(CXXFLAG) c_lang.tab.c lex.yy.c -lfl

FLEX:
	flex c_lang.l

BISON:	FLEX
	bison -d c_lang.y

clean:
	rm -rf lex.yy.c a.out *.tab*