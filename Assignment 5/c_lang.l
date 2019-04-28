c_lang.l
%{
  #include <iostream>
  #include <string>
  #include "c_lang.tab.h"

  #define print(str, val) \
    std::cout << str << " " <<  val << std::endl;

  extern int yylex();
%}


%%
(int)           {return INT;}
(float)           {return FLOAT;}
([0-9]+)          {return INTEGERS;}
([0-9]+\.[0-9]+)  {return FLOATS;}
([a-zA-Z0-9_]+)   {return IDENTIFIER;}
=               {return EQ;}
,               {return COMMA;}
;               {return SEMI;}

[ \t\n]
.
%%

int yywrap() {}
