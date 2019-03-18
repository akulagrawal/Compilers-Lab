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
  int num_lines = 0, num_chars = 0;
  bool multilinecomment = false;
  bool singlelinecomment = false;
  bool comment = false;

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

%%
\n	   ++num_lines; ++num_chars; singlelinecomment = false;
.	   ++num_chars;
\/\*   multilinecomment = true;
\*\/   multilinecomment = false;
\/\/   singlelinecomment = true;
(class[ \t\n]+[a-zA-Z0-9_]+\{)  {
          comment = multilinecomment or singlelinecomment;
          if(!comment)
          {
            // Extract the class name from the class declaration regex.
            string classname = extract_classname(conv_string(yytext));

            // Add to a set of classnames
            classnames.insert(classname);

            cout << classname << "\n";
            cout << classnames.size() << "\n";
          }

      }
([a-zA-Z0-9_]+[ \t\n]*\(.*\)[ \t\n]*\{) {
          comment = multilinecomment or singlelinecomment;
          if(!comment)
          {
            // Extract the function name from the function declaration regex.
            string functionname = extract_functionname(conv_string(yytext));
            //cout << functionname << ": function! \n";

            // If this function shares a name with a class, it must be a constructor.
            if(classnames.count(functionname)){
              cout << functionname << ": constructor! \n";
            }
          }
      }
%%

int yywrap(){
}

int main() {
  yylex();
}
