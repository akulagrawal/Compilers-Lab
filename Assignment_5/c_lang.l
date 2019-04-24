c_lang.l
%{
  #include <bits/stdc++.h>
  #include "c_lang.tab.h"

  #define print(str, val) \
    std::cout << str << " " <<  val << std::endl;

  extern int yylex();
  extern int lineNo;
%}
%%
(if)                      { yylval.type_id.sval = strdup(yytext); return IF; }
(else)                    { yylval.type_id.sval = strdup(yytext); return ELSE; }
(while)                   { yylval.type_id.sval = strdup(yytext); return WHILE; }
(for)                     { yylval.type_id.sval = strdup(yytext); return FOR; }
(switch)                  { yylval.type_id.sval = strdup(yytext); return SWITCH; }
(case)                    { yylval.type_id.sval = strdup(yytext); return CASE; }
(default)                 { yylval.type_id.sval = strdup(yytext); return DEFAULT; }
(int)                     { yylval.type_id.sval = strdup(yytext); return TYPE; }
(float)                   { yylval.type_id.sval = strdup(yytext); return TYPE; }
(void)                    { yylval.type_id.sval = strdup(yytext); return VOID; }
(return)                  { yylval.type_id.sval = strdup(yytext); return RETURN; }
\(                        { yylval.type_id.sval = strdup(yytext); return '('  ; }
\)                        { yylval.type_id.sval = strdup(yytext); return ')'  ; }
\{                        { yylval.type_id.sval = strdup(yytext); return '{'  ; }
\}                        { yylval.type_id.sval = strdup(yytext); return '}'  ; }
\[                        { yylval.type_id.sval = strdup(yytext); return '['  ; }
\]                        { yylval.type_id.sval = strdup(yytext); return ']'  ; }
=                         { yylval.type_id.sval = strdup(yytext); return '='  ; }
:                         { yylval.type_id.sval = strdup(yytext); return ':'  ; }
;                         { yylval.type_id.sval = strdup(yytext); return ';'  ; }
\+                        { yylval.type_id.sval = strdup(yytext); return '+'  ; }
\-                        { yylval.type_id.sval = strdup(yytext); return '-'  ; }
\*                        { yylval.type_id.sval = strdup(yytext); return '*'  ; }
\/                        { yylval.type_id.sval = strdup(yytext); return '/'  ; }
((\|\|)|or)               { yylval.type_id.sval = strdup(yytext); return OR; }
((&&)|and)                { yylval.type_id.sval = strdup(yytext); return AND; }
((<=)|(>=)|<|>|(==))      { yylval.type_id.sval = strdup(yytext); return REL_OP; }
'                         { yylval.type_id.sval = strdup(yytext); return '\''; }
\"                        { yylval.type_id.sval = strdup(yytext); return '"'; }
,                         { yylval.type_id.sval = strdup(yytext); return ','; }
([0-9]+)                  { yylval.type_id.sval = strdup(yytext); yylval.type_id.type = strdup("int"); return NUM; }
([0-9]+\.[0-9]+)          { yylval.type_id.sval = strdup(yytext); yylval.type_id.type = strdup("float"); return NUM; }
([a-zA-Z_][a-zA-Z0-9_]*)  { yylval.type_id.sval = (char *)malloc(strlen(yytext + 2) * sizeof(char)); strcpy(yylval.type_id.sval + 1, yytext); yylval.type_id.sval[0] = '_'; return IDENTIFIER; }
.                         ;
\n                        { lineNo ++; }
%%

int yywrap() {}
