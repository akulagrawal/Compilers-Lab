%{
  #include <stdio.h>
  #include <stdlib.h>
  #define print(str, val) \
    printf("%s %s\n", str, val);

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  
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
%token <fval> NUM
%token <sval> ID
%token <sval> NEWLINE
%token <sval> DOT


%type <sval> STMT_LIST
%type <sval> STMT
%type <sval> EXPR
%type <sval> TABLE
%type <sval> CONDITION
%type <sval> COMP
%type <sval> TERM
%type <sval> ATTR

%%

STMT_LIST:
    STMT 
    |
    STMT STMT_LIST
    ;

STMT:
    SELECT LAB CONDITION RAB LP TABLE RP NEWLINE   {
        printf("Valid Syntax \n");
    }
    |
    PROJECT LAB ATTR RAB LP TABLE RP NEWLINE     {
        printf("Valid Syntax \n");
    }
    |
    LP TABLE RP EXPR NEWLINE   {
        printf("Valid Syntax \n");
    }
    |
    error NEWLINE {yyerrok;}
    ;

EXPR:
    CARTESIAN_PRODUCT LP TABLE RP  {
        // printf("bison found a EXPR: ");
    }
    |
    EQUI_JOIN LAB CONDITION RAB LP TABLE RP  {
        // printf("bison found a EXPR: ");
    }
    ;

TABLE:
    STMT {
        // printf("bison found a TABLE: ");
    }
    |
    ID  {
        // printf("bison found a TABLE: ");
    }
    ;

CONDITION:
    ID COMP AND CONDITION
    |
    ID COMP
    ;

COMP:
    EQ TERM {
        // printf("bison found a COMP: ");
    }
    |
    LAB NUM {
        // printf("bison found a COMP: ");
    }
    |
    LT_EQ NUM   {
        // printf("bison found a COMP: ");
    }
    ;

TERM:
    NUM     {
        // printf("bison found a TERM: ");
    }
    |
    S_C ID S_C  {
        // printf("bison found a TERM: ");
    }
    |
    D_C ID D_C  {
        // printf("bison found a TERM: ");
    }
    ;

ATTR:
    ID COMMA ATTR   {
        // printf("bison found a ATTR: ");
    }
    |
    ID  {
        // printf("bison found a ATTR: ");
    }
    ;
%%

int main(int argc, char **argv) {

    char *filename = "input.txt";
   
    FILE *myfile = fopen(filename, "r");
   
    if (!myfile) {
    print("I can't open ", filename);
    return -1;
    }
   
    yyin = myfile;

   do {
        yyparse();
    } while(!feof(yyin));

   // while(yyparse());
  
}

void yyerror(const char *s) {

  printf("Invalid Syntax\n");

  //  exit(-1);
}

