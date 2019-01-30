#define EOI		    0	/* End of input			        */
#define SEMI		1	/* ; 				            */
#define PLUS 		2	/* + 				            */
#define TIMES		3	/* * 				            */
#define LP		    4	/* (				            */
#define RP		    5	/* )				            */
#define NUM_OR_ID	6	/* Decimal Number or Identifier */
#define MINUS       7   /* -                            */
#define DIV         8   /* /                            */

#define IF          9   /* if                           */
#define THEN       10   /* then                         */
#define WHILE      11   /* while                        */
#define DO         12   /* do                           */
#define BEGIN      13   /* begin                        */
#define END        14   /* end                          */
#define EQ         15   /* =                            */
#define LS_THAN    16   /* <                            */
#define GR_THAN    17   /* >                            */


extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern yylineno;
