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
(AND|OR)                  { yylval.sval = strdup(yytext); return AND; } 
((<=)|(>=))           { yylval.sval = strdup(yytext); return LT_EQ; } 
(=|(!=))                  { yylval.sval = strdup(yytext); return EQ; } 
\.							{ yylval.sval = strdup(yytext); return DOT; }
\(                         { yylval.sval = strdup(yytext); return LP; } 
\)                         { yylval.sval = strdup(yytext); return RP; } 
\<                         { yylval.sval = strdup(yytext); return LAB; } 
\>                         { yylval.sval = strdup(yytext); return RAB; } 
'                         { yylval.sval = strdup(yytext); return S_C; } 
\"                         { yylval.sval = strdup(yytext); return D_C; } 
,                         { yylval.sval = strdup(yytext); return COMMA; } 
[\n]						{yylval.sval =strdup(yytext); return NEWLINE; }
;                         { yylval.sval = strdup(yytext); return SEMI; } 
((-[ \t\n])?[0-9]+\.[0-9]+|[0-9]+)   { yylval.ival = atoi(yytext); return NUM; } 
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