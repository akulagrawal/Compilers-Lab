dbms.l
%{
  #include <iostream>
  #include <string.h>
  using namespace std;
  extern int yylex();
  int classmatch=0;
  int extmatch=0;
  int comment=0;
%}
%%
((\/\/.*[\n])|\/\*(.|[\n])*\*\/)                                            {
                                                                                int matchsize = strlen(yytext);
                                                                              //printf("Size of match = %d",matchsize);
                                                                              int it=0;
                                                                              int f=0;
                                                                              while(it!=matchsize)
                                                                              {
                                                                                if(yytext[it] == '\n')
                                                                                {
                                                                                  f++;
                                                                                  comment++;
                                                                                }
                                                                                it++;  
                                                                              }
                                                                              if(f>1)comment++;
                                                                            }
([ \t]*((public|private)[\n \t]+)?(final[\n \t]+)?class[\n \t]+[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*(implements[\n \t]+)?[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*\{)                  { 
                                                                              //printf("Found %s",yytext);
                                                                              int matchsize = strlen(yytext);
                                                                              //printf("Size of match = %d",matchsize);
                                                                              int it=0;
                                                                              classmatch++;
                                                                              while(it!=matchsize)
                                                                              {
                                                                                if(yytext[it] == '\n')
                                                                                {
                                                                                  classmatch++;
                                                                                }
                                                                                it++;  
                                                                              }
                                                                            }
([ \t]*(public|private)?([\n \t]+)?(final)?([\n \t]+)?class[\n \t]+[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*extends[\n \t]*[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*\{)                  {

                                                                              int matchsize = strlen(yytext);
                                                                              //printf("Size of match = %d",matchsize);
                                                                              int it=0;
                                                                              extmatch++;
                                                                              classmatch++;
                                                                              while(it!=matchsize)
                                                                              {
                                                                                if(yytext[it] == '\n')
                                                                                {
                                                                                  classmatch++;
                                                                                  extmatch++;
                                                                                }
                                                                                it++;  
                                                                              } 
                                                                            }      
. ;
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
  printf("Number of lines with classes: %d\n", classmatch);
  printf("Number of lines with inherited classes: %d\n", extmatch);
  printf("Number of lines with comments: %d\n", comment);
}