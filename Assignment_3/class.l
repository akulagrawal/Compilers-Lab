dbms.l
%{
  #include <iostream>
  #include <string.h>
  using namespace std;
  extern int yylex();
  int classmatch=0;
  int extmatch=0;
  int comment=0;
  int lno=1;
  
  int comment_index[1024];
  int top_comment_index;

  int class_index[1024];
  int top_class_index;

  int ext_class_index[1024];
  int top_ext_class_index;

%}

%option  yylineno

%%	
(\n)																		{
																				lno++;
																			}

(\/\/.*)                                            						{
																				//printf("Comment: %s\n", yytext);
																				//printf("Line number: %u\n", yylineno);
                                                                                int i, val = yylineno;
                                                                                for(i=0;i<1024;i++)
	                                                                          	{
	                                                                          		if(comment_index[i] == val)
	                                                                          		{
	                                                                          			break;
	                                                                          		}
	                                                                          	}
	                                                                          	if(i == 1024)
	                                                                          	{
	                                                                          		comment_index[top_comment_index++] = val++;	
	                                                                          	}
                                                                            }

(\/\*([\n]|[^\*\/])*\*\/)													{
																			  //printf("Comment: %s\n", yytext);
                                                                              //printf("Line number: %u\n", yylineno);
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
	                                                                          	f++;
	                                                                          	comment++;
	                                                                          //printf("Start =  %d\n", yylineno-f+1);
	                                                                          int i,val=yylineno-f+1;
	                                                                          while(val <= yylineno && top_comment_index < 1024)
	                                                                          {
	                                                                          	for(i=0;i<1024;i++)
	                                                                          	{
	                                                                          		if(comment_index[i] == val)
	                                                                          		{
	                                                                          			break;
	                                                                          		}
	                                                                          	}
	                                                                          	if(i == 1024)
	                                                                          	{
	                                                                          		comment_index[top_comment_index++] = val++;	
	                                                                          	}
	                                                                          }	
                                                                              //printf("Lines: %d\n", f);
                                                                            }
([ \t]*((public|private)[\n \t]+)?(final[\n \t]+)?class[\n \t]+[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*(implements[\n \t]+)?[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*\{)                  { 
                                                                              //printf("Found %s",yytext);
                                                                              //printf("Class declaration: %d\n",yylineno);
                                                                              int matchsize = strlen(yytext);
                                                                              //printf("Size of match = %d\n",matchsize);
                                                                              int it=0;
                                                                              classmatch++;

                                                                              int f=0;
                                                                              while(it!=matchsize)
                                                                              {
                                                                                if(yytext[it] == '\n')
                                                                                {
                                                                                	f++;
                                                                                  classmatch++;
                                                                                }
                                                                                it++;  
                                                                              }
                                                                              int i,j;
                                                                              int val = yylineno-f;
                                                                              for(i=0;i<=f;i++)
                                                                              {
                                                                              	for(j=0;j<1024;j++)
                                                                              	{
                                                                              		if(class_index[j]==val)
                                                                              		{
                                                                              			break;
                                                                              		}
                                                                              	}
                                                                              	if(j==1024)
                                                                              	{
                                                                              		class_index[top_class_index++] = val;
                                                                              	}
                                                                              	val++;
                                                                              }
                                                                            }
([ \t]*(public|private)?([\n \t]+)?(final)?([\n \t]+)?class[\n \t]+[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*extends[\n \t]*[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*\{)                  {

                                                                              int matchsize = strlen(yytext);
                                                                              //printf("Size of match = %d",matchsize);
                                                                              int it=0;
                                                                              extmatch++;
                                                                              classmatch++;
                                                                              int f=0;
                                                                              while(it!=matchsize)
                                                                              {
                                                                                if(yytext[it] == '\n')
                                                                                {
                                                                                	f++;
                                                                                  classmatch++;
                                                                                  extmatch++;
                                                                                }
                                                                                it++;  
                                                                              }
                                                                              int i,j;
                                                                              int val = yylineno-f;
                                                                              for(i=0;i<=f;i++)
                                                                              {
                                                                              	for(j=0;j<1024;j++)
                                                                              	{
                                                                              		if(ext_class_index[j]==val)
                                                                              		{
                                                                              			break;
                                                                              		}
                                                                              	}
                                                                              	if(j==1024)
                                                                              	{
                                                                              		ext_class_index[top_ext_class_index++] = val;
                                                                              	}

                                                                              	for(j=0;j<1024;j++)
                                                                              	{
                                                                              		if(class_index[j]==val)
                                                                              		{
                                                                              			break;
                                                                              		}
                                                                              	}
                                                                              	if(j==1024)
                                                                              	{
                                                                              		class_index[top_class_index++] = val;
                                                                              	}
                                                                              	val++;
                                                                              }
                                                                            }      
. ;
%%

int yywrap() {}
int main() {
  
  memset(comment_index, -1, 1024*sizeof(comment_index[0]));
  top_comment_index = 0;

  memset(class_index, -1, 1024*sizeof(class_index[0]));
  top_class_index = 0;

  memset(ext_class_index, -1, 1024*sizeof(ext_class_index[0]));
  top_ext_class_index = 0;

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
  int i;
  printf("Class on lines: ");
  for(i=0;i<1024;i++)
  {
  	if(class_index[i] == -1)
  	{
  		break;
  	}
  	printf("%d ", class_index[i]);
  }
  printf("\n");

  printf("Number of lines with classes: %d\n", i);

  printf("Inherited Class on lines: ");
  for(i=0;i<1024;i++)
  {
  	if(ext_class_index[i] == -1)
  	{
  		break;
  	}
  	printf("%d ", ext_class_index[i]);
  }
  printf("\n");


  printf("Number of lines with inherited classes: %d\n", i);
  
  printf("Comment on lines: ");
  for(i=0;i<1024;i++)
  {
  	if(comment_index[i] == -1)
  	{
  		break;
  	}
  	printf("%d ", comment_index[i]);
  }
  printf("\n");
  printf("Number of lines with comments: %d\n", i);
}