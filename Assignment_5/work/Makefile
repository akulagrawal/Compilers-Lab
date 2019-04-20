CC = g++

build:	BISON
	$(CC) decl.tab.c lex.yy.c -lfl

FLEX:
	flex decl.l

BISON:	FLEX
	bison -d -v decl.y

clean:
	rm -rf lex.yy.c a.out decl.tab*