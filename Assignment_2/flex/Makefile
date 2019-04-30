filename=analyze_java
clean:	$(filename).yy.c $(filename).exe
	rm $(filename).yy.c
	rm $(filename).exe

build: 	$(filename).lex
	flex -o $(filename).yy.c $(filename).lex
	g++ -o $(filename).exe $(filename).yy.c

run: 	$(filename).exe
	@./$(filename).exe
