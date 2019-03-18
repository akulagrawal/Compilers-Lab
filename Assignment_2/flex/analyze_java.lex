/*
 Counts the number of lines in a Java source program with constructor declarations.
 */

%{
  #include <iostream>
  #include <set>
  #include <string>
  #include <cctype>

  extern int yylex();

  using namespace std;

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

  int lcount = 0;
  int count = 0;
  int flag = 0;
  int com = 0;
  int pri = 0;
  int comment_count = 0;
  int flagc = 0;

  /* Constructor Count. */
  set<string> classnames;
  set<int> startlinenums;
  bool multilinecomment = false;
  int constructor_lines = 0;
  int num_constructors = 0;

  string conv_string(char* ptr) {
    string s;
    while(*ptr)
    {
      s += *ptr;
      ++ptr;
    }

    return s;
  }

  string extract_classname(string s) {
    int start, end;
    for(int i = 0; i < s.length(); ++i)
    {
      if(s.substr(i, 5) == "class")
      {
        start = i + 5;
        break;
      }
    }

    for(int i = start; i < s.length(); ++i)
    {
      if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
      {
        start += 1;
      }
      else break;
    }

    for(int i = start; i < s.length(); ++i)
    {
      if (!isalnum(s[i]))
      {
        end = i;
        break;
      }
    }

    return s.substr(start, end - start);
  }

  string extract_functionname(string s) {
    for(int i = 0; i < s.length(); ++i)
    {
      if (!isalnum(s[i]))
      {
        return s.substr(0, i);
      }
    }
  }

%}

%option yylineno

%%
(class[ \t\n]+[a-zA-Z0-9_]+)  {
          if((com == 0) && (pri == 0))
          {
            // Extract the class name from the class declaration regex.
            string classname = extract_classname(conv_string(yytext));

            // Add to a set of classnames
            classnames.insert(classname);
          }

      }
([a-zA-Z0-9_]+[ \t\n]*\([a-zA-Z0-9_, <>]*\)[ \t\n]*\{) {
          if((com == 0) && (pri == 0))
          {
            // Convert yy_text to a C++ string.
            string yy_string = conv_string(yytext);

            // Extract the function name from the function declaration regex.
            string functionname = extract_functionname(yy_string);
            //cout << functionname << ": function at line number " << yylineno << "\n";

            // If this function shares a name with a class, it must be a constructor.
            if(classnames.count(functionname))
            {
              //cout << functionname << ": constructor!" << "\n";
              num_constructors += 1;

              if(!startlinenums.count(yylineno))
              {
                startlinenums.insert(yylineno);
                constructor_lines += 1;
                for(int i = 0; i < yy_string.length(); ++i)
                {
                  if(yy_string[i] == '\n')
                  {
                    constructor_lines += 1;
                  }
                }
              }
            }
          }
      }

([ \t]*((public|private)[\n \t]+)?(final[\n \t]+)?class[\n \t]+[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*(implements[\n \t]+)?[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*\{)	{
						if((com == 0) && (pri == 0))
						{
              // Extract the class name from the class declaration regex.
              string classname = extract_classname(conv_string(yytext));

              // Add to a set of classnames
              classnames.insert(classname);

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
          }
([ \t]*(public([\n \t]+)|private([\n \t]+))?(final([\n \t]+))?class[\n \t]+[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*extends[\n \t]*[a-zA-Z][<>a-zA-Z0-9_]*[\n \t]*\{)	{

						if((com == 0) && (pri == 0))
						{
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
          }
("/*")	{if(pri == 0) { com = 2; flagc = 1;}}
("//")  {if((pri == 0) && (com == 0)) { com = 1; flagc = 0;}}
("*/")	{if(pri == 0) { com = 0;}}
("System.out.println")  {if(com == 0) { pri = 1;}}
(")")[' ']*[;]  {if(com == 0) {pri = 0;}}
[' ';]*("abstract")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("continue")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("for")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("new")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("switch")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("assert")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("default")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("goto")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("package")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("synchronized")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("boolean")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("do")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("if")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("private")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("this")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("break")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("double")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("implements")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("protected")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("throw")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("byte")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("else")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("import")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("public")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("throws")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("case")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("enum")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("instanceof")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("return")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("transient")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("catch")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("extends")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("int")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("short")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("try")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("char")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("final")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("interface")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("static")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("void")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("class")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("finally")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("long")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("strictfp")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("volatile")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("const")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("float")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("native")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("super")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("while")[' ';]+ {if((com == 0) && (pri == 0)) {flag = 0; }}
[' ';]*("!end")[' ';]* {if((com == 0) && (pri == 0)) {return 0;}}
[' ';]*[a-zA-Z][a-zA-Z0-9_]+[' ';]+ {if((com == 0) && (pri == 0)) {if(flag == 1) lcount++; flag = 1; }}
.     {flag = 0;}
\n    {if(pri == 0) {if(com) comment_count++; else if(flagc) {comment_count++; flagc = 0;} if(lcount) count++; lcount = 0; flag = 0; if(com==1) com = 0;} }
%%

int yywrap(){
}

int main() {

  memset(comment_index, -1, 1024*sizeof(comment_index[0]));
  top_comment_index = 0;

  memset(class_index, -1, 1024*sizeof(class_index[0]));
  top_class_index = 0;

  memset(ext_class_index, -1, 1024*sizeof(ext_class_index[0]));
  top_ext_class_index = 0;

  // Explanation:
  // yywrap() - wraps the above rule section
  /* yyin - takes the file pointer
            which contains the input*/
  /* yylex() - this is the main flex function
            which runs the Rule Section*/
  // yytext is the text in the buffer

  // Uncomment the lines below
  // to take input from file
  // FILE *fp;
  // char* filename = "input.txt";
  // fp = fopen(filename,"r");
  // yyin = fp;

  yylex();

  cout << "Number of lines with object declarations: " << count << "\n";

  // cout << "Class on lines: ";
  int i;
  for(i=0;i<1024;i++)
  {
  	if(class_index[i] == -1)
  	{
  		break;
  	}
  	// printf("%d ", class_index[i]);
  }
  // printf("\n");

  cout << "Number of lines with classes: " << i << "\n";

  cout << "Number of lines with constructor definitions: " << constructor_lines << "\n";

  // printf("Inherited Class on lines: ");
  for(i=0;i<1024;i++)
  {
  	if(ext_class_index[i] == -1)
  	{
  		break;
  	}
  	// printf("%d ", ext_class_index[i]);
  }
  // printf("\n");


  cout << "Number of lines with inherited classes: " << i << "\n";

  // cout << "\n";
  // cout << "Found classes:" << "\n";
  // for(set<string>::iterator it = classnames.begin(); it != classnames.end(); ++it)
  // {
  //   cout << *it << "\n";
  // }
  // cout << "\n";
  //
  // cout << "Number of constructors: " << num_constructors << "\n";

}
