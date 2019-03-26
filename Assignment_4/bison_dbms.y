%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <string.h>
  #define print(str, val) \
    printf("%s %s\n", str, val);

  // Declare stuff from Flex that Bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  extern void eat_till_semi();

  void yyerror(const char *s);
  
  extern void insert_header (FILE *filename);
  extern void insert_footer (FILE *filename);
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
%token <sval> LT_EQ
%token <sval> EQ
%token <sval> NEQ
%token <sval> LP
%token <sval> RP
%token <sval> LAB
%token <sval> RAB
%token <sval> SIC
%token <sval> DIC
%token <sval> COMMA
%token <sval> SEMI
%token <sval> NUM
%token <sval> ID
%token <sval> DOT
%token <sval> MINUS
%token <sval> ARITH_OP

%type <sval> STMT_LIST
%type <sval> STMT
%type <sval> EXPR
%type <sval> TABLE
%type <sval> CONDITION
%type <sval> CONDITION_LIST_FINAL
%type <sval> CONDITION_LIST
%type <sval> OP
%type <sval> TERM
%type <sval> ATTR_LIST
%type <sval> ATTR

%%

STMT_LIST:    STMT
    |         STMT STMT_LIST    ;

STMT:   SELECT LAB CONDITION_LIST_FINAL RAB LP TABLE RP SEMI    {
           printf("Valid Syntax \n");

           FILE *file_in = fopen("intermediate.cpp", "w+");
           insert_header(file_in);

           FILE *akul = fopen(strcat($6, ".txt"), "r");
           char line[1024];

           fgets(line, sizeof(line), akul);
           fgets(line, sizeof(line), akul);
           printf("%s\n", line);
           
           fprintf(file_in, "FILE *fp = fopen(\"input.txt\", \"w+\")\n");
           fprintf(file_in, "for(int i = 0; i < vals.size(); i++){\n");
           fprintf(file_in, "\tfor(int j = 0; j < vals[0].size(); j++){\n");
           fprintf(file_in, "m");


           insert_footer(file_in);
           fclose(file_in);
        }
    |   PROJECT LAB ATTR_LIST RAB LP TABLE RP SEMI     {
           printf("Valid Syntax \n");
        }
    |   LP TABLE RP JOIN LP TABLE RP SEMI   {
           printf("Valid Syntax \n");
        }
    |   error SEMI  {
           yyerrok;
           eat_till_semi();
        }    ;

JOIN:    CARTESIAN_PRODUCT
    |    EQUI_JOIN LAB CONDITION_LIST_EQ RAB    ;

TABLE:   ID    ;

CONDITION_LIST_FINAL:   CONDITION_LIST ;

CONDITION_LIST: CONDITION AND CONDITION_LIST     { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |           CONDITION

CONDITION:      LP CONDITION_LIST RP { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |           TERM OP EXPR  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } ;
    
CONDITION_LIST_EQ: CONDITION_EQ AND CONDITION_LIST_EQ
    |           CONDITION_EQ

CONDITION_EQ:      LP CONDITION_LIST_EQ RP
    |              ID DOT ID EQ ID DOT ID    ;

EXPR:   TERM ARITH_OP EXPR  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |   TERM MINUS EXPR  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |   TERM   ;

TERM:   LP EXPR RP { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |   NUM
    |   MINUS NUM { strcat($$, $2); }
    |   ID
    |   SIC NUM SIC  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |   SIC ID SIC { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |   DIC NUM DIC { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |   DIC ID DIC   { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } ;

OP:     EQ
    |   NEQ
    |   LAB
    |   RAB
    |   LT_EQ    ;

ATTR_LIST:    ATTR COMMA ATTR_LIST   
    |         ATTR  ;

ATTR:   ID
%%

int main(int argc, char **argv) {

    char *filename = "tests/test1.txt";
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
    while(!feof(yyin))  {
        yyparse();
    }
  
}

void yyerror(const char *s) {
  print("Invalid syntax ", s);
  // might as well halt now:
//   printf("Invalid Syntax\n");
//   exit(-1);
}

void eat_till_semi()
{
    int c;
    while((c = (char)fgetc(yyin)) != EOF && c != ';')
        printf("s");
}

void insert_header (FILE *filename) {
    char *header = "#include <bits/stdc++.h>\nusing namespace std;\n\nint main () {\n";

    fprintf(filename, "%s", header);
}

void insert_footer (FILE *filename) {
    char *header = "return 0;\n}\n";

    fprintf(filename, "%s", header);
}