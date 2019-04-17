CXX = g++
CPP = g++
CXXFLAG = -std=c++11

file=input.txt

run:	build
		./a.out

build:
		$(CPP) -std=c++11 intermediate.cpp

semantics:	build_bison
		./a.out < $(file)

build_bison:	BISON FLEX
	$(CXX) $(CXXFLAG) c_lang.tab.c lex.yy.c -lfl

FLEX:
	flex c_lang.l

BISON:	FLEX
	bison -d c_lang.y

clean:
	rm -rf lex.yy.c a.out *.tab*