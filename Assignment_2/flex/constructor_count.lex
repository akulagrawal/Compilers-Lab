/*
 Counts the number of lines in a Java source program with constructor declarations.
 */

%{
  #include <iostream>
  #include <set>
  #include <string>
  #include <cctype>

  using namespace std;

  set<string> classnames;
  set<int> startlinenums;
  bool multilinecomment = false;
  bool singlelinecomment = false;
  bool comment = false;
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
    for(int i = 5; i < s.length(); ++i)
    {
      if (isalnum(s[i]))
      {
        return s.substr(i);
      }
    }
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
.
\n
\/\*   multilinecomment = true;
\*\/   multilinecomment = false;
\/\/.*
(class[ \t\n]+[a-zA-Z0-9_]+)  {
          if(!multilinecomment)
          {
            // Extract the class name from the class declaration regex.
            string classname = extract_classname(conv_string(yytext));

            // Add to a set of classnames
            classnames.insert(classname);
          }

      }
([a-zA-Z0-9_]+[ \t\n]*\([a-zA-Z0-9_, <>]*\)[ \t\n]*\{) {
          if(!multilinecomment)
          {
            // Convert yy_text to a C++ string.
            string yy_string = conv_string(yytext);

            // Extract the function name from the function declaration regex.
            string functionname = extract_functionname(yy_string);
            cout << functionname << ": function at line number " << yylineno << "\n";

            // If this function shares a name with a class, it must be a constructor.
            if(classnames.count(functionname))
            {
              cout << functionname << ": constructor!" << "\n";
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
%%

int yywrap(){
}

int main() {
  yylex();

  cout << "\n";
  cout << "Found classes:" << "\n";
  for(set<string>::iterator it = classnames.begin(); it != classnames.end(); ++it)
  {
    cout << *it << "\n";
  }
  cout << "\n";

  cout << "Number of constructors: " << num_constructors << "\n";
  cout << "Number of constructor definition lines: " << constructor_lines << "\n";
}
