%{
  #include <stdio.h>
  #include <stdlib.h>
  #define print(str, val) \
    printf("%s %s\n", str, val);

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  extern void eat_till_semi();
  
void yyerror(const char *s);
%}


%union {
  int ival;
  float fval;
  char *sval;
}

// Define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the %union:
%token <sval> SELECT
%token <sval> PROJECT
%token <sval> CARTESIAN_PRODUCT
%token <sval> EQUI_JOIN
%token <sval> AND
%token <sval> OR
%token <sval> LT_EQ
%token <sval> EQ
%token <sval> LP
%token <sval> RP
%token <sval> LAB
%token <sval> RAB
%token <sval> S_C
%token <sval> D_C
%token <sval> COMMA
%token <sval> SEMI
%token <sval> NUM
%token <sval> STR
%token <sval> NEWLINE
%token <sval> DOT
%token <sval> PLUS
%token <sval> MINUS
%token <sval> DIV
%token <sval> MUL


%type <sval> ID
%type <sval> STMT_LIST
%type <sval> STMT
%type <sval> EXPR
%type <sval> TABLE
%type <sval> CONDITION
%type <sval> CONDITION2
%type <sval> COMP
%type <sval> TERM
%type <sval> ATTR

%type <sval> ARITH
%type <sval> EXPR_PRIME
%type <sval> TERM2
%type <sval> TERM_PRIME
%type <sval> FACTOR


%%

STMT_LIST:  STMT 
    |   STMT STMT_LIST
    ;

STMT:   SELECT LAB CONDITION RAB LP TABLE RP SEMI   {
            printf("Valid Syntax\t");
        }
    |   PROJECT LAB ATTR RAB LP TABLE RP SEMI     {
            printf("Valid Syntax\t");
        }
    |   LP TABLE RP EXPR SEMI   {
            printf("Valid Syntax\t");
        }
    |   error SEMI  {
           yyerrok;
           eat_till_semi();
        }    ;

EXPR:   CARTESIAN_PRODUCT LP TABLE RP
    |   EQUI_JOIN LAB CONDITION2 RAB LP TABLE RP ;

TABLE:  STR;

CONDITION:   ID COMP AND CONDITION
    |        ID COMP ;

CONDITION2:  STR DOT STR EQ STR DOT STR AND CONDITION2
    |        STR DOT STR EQ STR DOT STR   ;

COMP:    EQ TERM
    |    LAB NUM
    |    LT_EQ NUM  ;

TERM:    NUM
    |    S_C ID S_C
    |    D_C ID D_C ;

ATTR:
    ID COMMA ATTR
    |   ID    ;

ID: STR
    | ARITH   ;

ARITH:   TERM2 EXPR_PRIME ;

EXPR_PRIME :  PLUS TERM2 EXPR_PRIME
		| MINUS TERM2 EXPR_PRIME
		| /* epsilon */ ;

TERM2 :  FACTOR TERM_PRIME ;

TERM_PRIME :  MUL FACTOR TERM_PRIME
		| DIV FACTOR TERM_PRIME
		| /* epsilon */ ;

FACTOR :  LP ARITH RP
		| NUM
        | STR ;


%%

int main(int argc, char **argv) {

    char *filename = "input.txt";
   
    FILE *myfile = fopen(filename, "r");
   
    if (!myfile) {
    print("I can't open ", filename);
    return -1;
    }
   
    yyin = myfile;

   while(!feof(yyin)){
        yyparse();
    } 

   // while(yyparse());
  
}

void yyerror(const char *s) {

  printf("Invalid Syntax\t");

  //  exit(-1);
}

void eat_till_semi()
{
    int c;
    while((c = (char)fgetc(yyin)) != EOF && c != ';')
        printf("s");
}