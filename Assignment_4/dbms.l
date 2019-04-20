dbms.l
%{
  #include <stdio.h>
  #include <string.h>
  #include "bison_dbms.tab.h"

  #define print(str, val) \
    printf("%s %s\n", str, val);
    
  extern int yylex();
%}
%%
(SELECT)                  { yylval.sval = strdup(yytext); return SELECT; } 
(PROJECT)                 { yylval.sval = strdup(yytext); return PROJECT; } 
(CARTESIAN_PRODUCT)       { yylval.sval = strdup(yytext); return CARTESIAN_PRODUCT; } 
(EQUI_JOIN)               { yylval.sval = strdup(yytext); return EQUI_JOIN; } 
(and|or)                  { yylval.sval = strdup(yytext); return AND; } 
((<=)|(>=))           { yylval.sval = strdup(yytext); return LT_EQ; } 
=                  { yylval.sval = strdup(yytext); return EQ; } 
!=                  { yylval.sval = strdup(yytext); return NEQ; } 
\(                         { yylval.sval = strdup(yytext); return LP; } 
\)                         { yylval.sval = strdup(yytext); return RP; } 
\.                         { yylval.sval = strdup(yytext); return DOT; } 
\<                         { yylval.sval = strdup(yytext); return LAB; } 
\>                         { yylval.sval = strdup(yytext); return RAB; } 
'                         { yylval.sval = strdup(yytext); return SIC; } 
\"                         { yylval.sval = strdup(yytext); return DIC; } 
,                         { yylval.sval = strdup(yytext); return COMMA; } 
;                         { yylval.sval = strdup(yytext); return SEMI; } 
[\+\*/]                         { yylval.sval = strdup(yytext); return ARITH_OP; } 
\-                         { yylval.sval = strdup(yytext); return MINUS; } 
((-[ \t\n])?[0-9]+\.[0-9]+|[0-9]+)   { yylval.sval = strdup(yytext); return NUM; } 
[a-zA-Z0-9_]+              { yylval.sval = strdup(yytext); return ID; } 
.                         ;
%%

int yywrap() {}
// int main() {
  
//   char* filename = "input.txt";
//   // open a file handle to a particular file:
//   FILE *myfile = fopen(filename, "r");

//   // make sure it's valid:
//   if (!myfile) {
//     print("I can't open ", filename);
//     return -1;
//   }
//   // set lex to read from it instead of defaulting to STDIN:
//   yyin = myfile;
  
//   // lex through the input:
//   while(yylex());
// }