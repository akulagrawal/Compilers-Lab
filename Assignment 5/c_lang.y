%{
    #include <bits/stdc++.h>
    using namespace std;
    #define print(str, val) \
        std::cout << str << " " <<  val << std::endl;

    // Declare stuff from Flex that Bison needs to know about:
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
%token <sval> INT FLOAT SEMI EQ COMMA IDENTIFIER
%token <sval> INTEGERS FLOATS

%type <sval> DList Declare  TYPE  VARLIST RHSVAR ID_PRIME expression_statement logical_expression relational_expression assignment_expression constant_expression expression NUM

%%
DList       :      Declare DList
                  {printf("valid Syntax\n");}
                  |

                  ;

Declare     :     TYPE  VARLIST SEMI
                  {}

                  ;

VARLIST     :     VARLIST COMMA ID_PRIME
                    |
                    ID_PRIME
                    ;

ID_PRIME    :       IDENTIFIER
                    |
                    IDENTIFIER EQ RHSVAR

TYPE        :     INT
                  |
                  FLOAT
                  ;
RHSVAR      :     INTEGERS
                  |
                  FLOATS
                  |
                  IDENTIFIER
                  ;

 expression
     : assignment_expression
     | logical_expression
     | relational_expression
     ;

 assignment_expression
     : IDENTIFIER '=' NUM
     | IDENTIFIER '=' IDENTIFIER
     ;

 logical_expression
     : IDENTIFIER OR IDENTIFIER
     | NUM OR IDENTIFIER
     | IDENTIFIER OR NUM
     | NUM OR NUM

     ;

 relational_expression
     : IDENTIFIER '>' IDENTIFIER
     | NUM '>' IDENTIFIER
     | IDENTIFIER '>' NUM
     | NUM '>' NUM
     |IDENTIFIER '<' IDENTIFIER
     | NUM '<' IDENTIFIER
     | IDENTIFIER '<' NUM
     | NUM '<' NUM
     ;

 constant_expression
     : NUM

NUM : INTEGERS
      |
      FLOATS
     ;

%%

int main(int argc, char **argv) {

  //  string *filename = "test.txt";
    // Open a file handle to a particular file:
    FILE *myfile = fopen("test.txt", "r");
    // Make sure it is valid:
    if (!myfile) {
    printf("I can't open test.txt");
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

}
