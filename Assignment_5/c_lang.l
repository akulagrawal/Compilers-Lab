c_lang.l
%{
  #include <bits/stdc++.h>
  #include "c_lang.tab.h"

  #define print(str, val) \
    std::cout << str << " " <<  val << std::endl;
    
  extern int yylex();
%}
%%
(if)                  { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return IF; } 
(then)                  { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return THEN; } 
(else)                 { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return ELSE; } 
(while)       { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return WHILE; } 
(do)       { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return DO; } 
(for)               { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return FOR; } 
(switch)                  { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return SWITCH; } 

\(                         { yylval.type_id.sval = strdup(yytext); return '('  ; }
\)                         { yylval.type_id.sval = strdup(yytext); return ')'  ; }
\{                         { yylval.type_id.sval = strdup(yytext); return '{'  ; }
\}                         { yylval.type_id.sval = strdup(yytext); return '}'  ; }
=                         { yylval.type_id.sval = strdup(yytext); return '='  ; }
:                         { yylval.type_id.sval = strdup(yytext); return ':'  ; } 
;                         { yylval.type_id.sval = strdup(yytext); return ';'  ; } 

([0-9]+\.[0-9]+|[0-9]+)   { yylval.type_id.val = atoi(yytext); return NUM; } 
[a-zA-Z0-9_]+              { yylval.type_id.sval = strdup(yytext); return ID; } 
.                         ;
%%

int yywrap() {}