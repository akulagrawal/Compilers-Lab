%{
	#include <bits/stdc++.h>
	#include "decl.tab.h"
	using namespace std;
	int yylex(void);
	int yyparse();
%}

digit			[0-9]
int_const		[0-9.]+
alphabet		[a-zA-Z]
word			{alphabet}+
var_name		{alphabet}[a-zA-Z0-9_]*

%%

(int)			{return INT;}
(float)			{return FLOAT;}
(,)				{return COMMA;}
(])				{return RSB;}
(\[)				{return LSB;}
(;)				{return SEMI;}
(=)				{return EQUAL;}
\+				{yylval.sval = strdup(yytext);return '+';}
\-				{yylval.sval = strdup(yytext);return '-';}
\*				{yylval.sval = strdup(yytext);return '*';}
\/				{yylval.sval = strdup(yytext);return '/';}
\(              { yylval.sval = strdup(yytext); return '('  ; }
\) 				{ yylval.sval = strdup(yytext); return ')' ; }

{var_name}		{yylval.sval = strdup(yytext); return VAR_NAME;}
{int_const}		{yylval.sval = strdup(yytext); return NUM;}
[ \t]*			{}
[\n]			{yylineno++;	}
.				{cout << "Something not right"<<endl;}
%%
int yywrap() {}