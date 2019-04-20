CXX = gcc
CXXFLAG = -g

all:	BISON FLEX
	$(CXX) $(CXXFLAG) bison_dbms.tab.c lex.yy.c -lfl

FLEX:
	flex dbms.l

BISON:	FLEX
	bison -d bison_dbms.y

clean:
	rm -rf lex.yy.c a.out bison_dbms.tab*