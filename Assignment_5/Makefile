CXX = g++
CPP = g++
CXXFLAG = -g -std=c++11
# DEBUG_FLAG=gdb
IC_FILE = intermediate.out


intermediate: build_bison
	./a.out > $(IC_FILE)

debug: build_bison
	$(DEBUG_FLAG) ./a.out

semantics:	build_bison
	./a.out

build_bison:	BISON FLEX
	$(CXX) $(CXXFLAG) c_lang.tab.c lex.yy.c -o a.out

FLEX:
	flex c_lang.l

BISON:	FLEX
	bison -d -v c_lang.y

clean:
	rm -rf lex.yy.c a.out *.tab*
