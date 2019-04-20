c_lang.l
%{
  #include <bits/stdc++.h>
  #include "c_lang.tab.h"

  #define print(str, val) \
    std::cout << str << " " <<  val << std::endl;
    
  extern int yylex();
%}
%%
(if)                      { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return IF; } 
(else)                    { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return ELSE; } 
(while)                   { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return WHILE; } 
(for)                     { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return FOR; } 
(switch)                  { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return SWITCH; } 
(case)                    { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return CASE; } 
(default)                 { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return DEFAULT; }
(int)                     { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return INT; } 
(float)                   { yylval.type_id.sval = strdup(yytext); /*std::cout << yytext << std::endl;*/ return FLOAT; }
\(                        { yylval.type_id.sval = strdup(yytext); return '('  ; }
\)                        { yylval.type_id.sval = strdup(yytext); return ')'  ; }
\{                        { yylval.type_id.sval = strdup(yytext); return '{'  ; }
\}                        { yylval.type_id.sval = strdup(yytext); return '}'  ; }
=                         { yylval.type_id.sval = strdup(yytext); return '='  ; }
:                         { yylval.type_id.sval = strdup(yytext); return ':'  ; } 
;                         { yylval.type_id.sval = strdup(yytext); return ';'  ; } 
((\|\|)|or)               { yylval.type_id.sval = strdup(yytext); return OR; } 
((<=)|(>=)|<|>)           { yylval.type_id.sval = strdup(yytext); return '>'; } 
'                         { yylval.type_id.sval = strdup(yytext); return '\''; } 
\"                        { yylval.type_id.sval = strdup(yytext); return '"'; } 
,                         { yylval.type_id.sval = strdup(yytext); return ','; }
([0-9]+\.[0-9]+|[0-9]+)   { yylval.type_id.val = atoi(yytext); yylval.type_id.type = strdup("num"); return NUM; } 
[a-zA-Z0-9_]+             { yylval.type_id.sval = strdup(yytext); yylval.type_id.type = strdup("num"); return IDENTIFIER; } 
.                         ;
\n                        ;
%%

int yywrap() {}