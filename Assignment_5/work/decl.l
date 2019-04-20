%{
	#include <bits/stdc++.h>
	#include "decl.tab.h"
	using namespace std;
	int yylex(void);
	int yyparse();
%}

digit			[0-9]
int_const		{digit}+
alphabet		[a-zA-Z]
word			{alphabet}+
var_name		{alphabet}[a-zA-Z0-9_]*

%%

(int)			{return INT;}
(float)			{return FLOAT;}
(,)				{return COMMA;}
(;)				{return SEMI;}
{var_name}		{yylval.sval = strdup(yytext); return VAR_NAME;}
[ \t]*			{}
[\n]			{yylineno++;	}
.				{cout << "Something not right"<<endl;}
%%
int yywrap() {}