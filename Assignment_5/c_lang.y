%{
    #include <bits/stdc++.h>
    #include <string>
    
    #define print(str, val) \
        std::cout << str << " " <<  val << std::endl;

    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
    void yyerror(const char *s);    
    using namespace std;
%}

%union {
    struct {
        char* type;
        double val;
        char* sval;
    } type_id;
}

// Define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the %union:
%type <type_id> IF_EXP
%type <type_id> WHILE_EXP
%type <type_id> S
%type <type_id> L
%type <type_id> E


%token <type_id> NUM
%token <type_id> ID
%token <type_id> IF
%token <type_id> THEN
%token <type_id> FOR
%token <type_id> ELSE
%token <type_id> WHILE
%token <type_id> DO
%token <type_id> SWITCH

%%

S:   IF_EXP THEN S   {  };
IF_EXP:  IF '(' E ')'    {  };

S:  WHILE_EXP '{' S '}' {  };
WHILE_EXP:  WHILE '(' E ')' {  };

S:  L ':''=' E ';'  { } ;

L:  ID { } ;
E:  NUM { } ;

%%

int main(int argc, char **argv) {

    char *filename = (char*)malloc(sizeof(char)*20);
    strcpy(filename, "input.txt");
    
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
  print("", s);
  // might as well halt now:
//   printf("Invalid Syntax\n");
//   exit(-1);
}