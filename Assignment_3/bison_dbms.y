%{
  #include <stdio.h>
  #include <stdlib.h>
  #define print(str, val) \
    printf("%s %s\n", str, val);

  // Declare stuff from Flex that Bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
 
  void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  Initially (by default), yystype
// is merely a typedef of "int", but for non-trivial projects, tokens could
// be of any arbitrary data type.  So, to deal with that, the idea is to
// override yystype's default typedef to be a C union instead.  Unions can
// hold all of the types of tokens that Flex could return, and this this means
// we can return ints or floats or strings cleanly.  Bison implements this
// mechanism with the %union directive:
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

%type <sval> STMT_LIST
%type <sval> STMT
%type <sval> EXPR
%type <sval> TABLE
%type <sval> CONDITION
%type <sval> COMP
%type <sval> TERM
%type <sval> ATTR

%%
// This is the actual grammar that bison will parse, but for right now it's just
// something silly to echo to the screen what bison gets from flex.  We'll
// make a real one shortly:

STMT_LIST:
    STMT SEMI
    |
    STMT SEMI STMT_LIST
    ;

STMT:
    SELECT LAB CONDITION RAB LP TABLE RP     {
        printf("Valid Syntax \n");
    }
    |
    PROJECT LAB ATTR RAB LP TABLE RP      {
        printf("Valid Syntax \n");
    }
    |
    LP TABLE RP EXPR    {
        printf("Valid Syntax \n");
    }
    ;

EXPR:
    CARTESIAN_PRODUCT LP TABLE RP  {
        // printf("bison found a EXPR: ");
    }
    |
    EQUI_JOIN LP TABLE RP  {
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
    // Open a file handle to a particular file:
    FILE *myfile = fopen(filename, "r");
    // Make sure it is valid:
    if (!myfile) {
    print("I can't open ", filename);
    return -1;
    }
    // Set Flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    // Parse through the input:
    while(yyparse());
  
}

void yyerror(const char *s) {
//   print("EEK, parse error!  Message: ", s);
  // might as well halt now:
  printf("Invalid Syntax\n");
  exit(-1);
}
