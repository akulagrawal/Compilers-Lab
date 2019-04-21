CC = g++
CX = -std=c++11

build:	BISON
	$(CC) $(CX) decl.tab.c lex.yy.c -lfl

FLEX:
	flex decl.l

BISON:	FLEX
	bison -d -v decl.y

clean:
	rm -rf lex.yy.c a.out decl.tab*