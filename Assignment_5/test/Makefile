CC = g++

build_bison:	BISON
	$(CC) calc.tab.c lex.yy.c -lfl

FLEX:
	flex calc.lex

BISON:	FLEX
	bison -d calc.y

clean:
	rm -rf lex.yy.c a.out calc.tab*