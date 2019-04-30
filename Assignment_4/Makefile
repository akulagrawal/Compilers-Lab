CXX = gcc
CPP = g++
CXXFLAG = -g

run:	build
		./a.out

build:
		$(CPP) -std=c++11 intermediate.cpp

semantics:	build_bison
		./a.out $(file)

build_bison:	BISON FLEX
	$(CXX) $(CXXFLAG) bison_dbms.tab.c lex.yy.c -lfl

FLEX:
	flex dbms.l

BISON:	FLEX
	bison -d bison_dbms.y

clean:
	rm -rf lex.yy.c a.out bison_dbms.tab*