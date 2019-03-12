dbms.l
%{
  #include <iostream>
  using namespace std;
  extern int yylex();
%}
%%
(SELECT)                  { cout << "Found a SELECT query: " << yytext << endl;}
(PROJECT)                 { cout << "Found a PROJECT query: " << yytext << endl;}
(CARTESIAN_PRODUCT)       { cout << "Found a CARTESIAN_PRODUCT query: " << yytext << endl;}
(EQUI_JOIN)               { cout << "Found a EQUI_JOIN query: " << yytext << endl;}
(AND|OR)                  { cout << "Found a boolean query: " << yytext << endl;}
((<=)|(>=))           { cout << "Found a comparator: " << yytext << endl;}
(=|(!=))                  { cout << "Found an assignment operator: " << yytext << endl;}
\(                         { cout << "Found a LP: " << yytext << endl;}
\)                         { cout << "Found a RP: " << yytext << endl;}
\<                         { cout << "Found a LAB: " << yytext << endl;}
\>                         { cout << "Found a RAB: " << yytext << endl;}
'                         { cout << "Found a S_IC: " << yytext << endl;}
\"                         { cout << "Found a D_IC: " << yytext << endl;}
;                         { cout << "Found a SEMI: " << yytext << endl;}
([0-9]+\.[0-9]+|[0-9]+)   { cout << "Found a number:" << yytext << endl; }
[a-zA-Z0-9]+              { cout << "Found a string: " << yytext << endl; }
.                         ;
%%

int yywrap() {}
int main() {
  
  char* filename = "input.txt";
  // open a file handle to a particular file:
  FILE *myfile = fopen(filename, "r");

  // make sure it's valid:
  if (!myfile) {
    cout << "I can't open " << filename << endl;
    return -1;
  }
  // set lex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  
  // lex through the input:
  while(yylex());
}