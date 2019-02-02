#define EOI		    0	/* End of input			        */
#define SEMI		1	/* ; 				            */
#define PLUS 		2	/* + 				            */
#define TIMES		3	/* * 				            */
#define LP		    4	/* (				            */
#define RP		    5	/* )				            */
#define NUM_OR_ID	6	/* Decimal Number or Identifier */
#define MINUS       7   /* -                            */
#define DIV         8   /* /                            */

#define EQ         15   /* =                            */
#define LT         16   /* <                            */
#define GT         17   /* >                            */

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern yylineno;
