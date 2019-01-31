#define EOI		0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define TIMES		3	/* * 				*/
#define LP		4	/* (				*/
#define RP		5	/* )				*/
#define NUM		6	/* Decimal Number or Identifier */
#define MINUS		7
#define DIV		8
#define EQ		9	// =
#define GT		10	// >
#define LT		11	// <
#define IF		12	
#define THEN		13
#define WHILE		14
#define DO		15
#define BEGIN		16
#define END		17
#define ID		18
#define ASSIGN		19	// :=

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern yylineno;
