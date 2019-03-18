/*
 * Sample Scanner2:
 * Description: Count the number of characters and the number of lines
 *              from standard input
 * Usage: (1) $ flex sample2.lex
 *        (2) $ gcc lex.yy.c -lfl
 *        (3) $ ./a.out
 *            stdin> whatever you like
 *	      stdin> Ctrl-D
 * Questions: Is it ok if we do not indent the first line?
 *            What will happen if we remove the second rule?
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

  string conv_string(char * ptr) {
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
.	     ++num_chars;
\/\*   multilinecomment = true;
\*\/   multilinecomment = false;
\/\/   singlelinecomment = true;
(class[ \t\n]+[a-zA-Z0-9_]+)  {
          comment = multilinecomment or singlelinecomment;
          if(!comment)
          {
            string classname = extract_classname(conv_string(yytext));
            classnames.insert(classname);

            cout << classname << "\n";
            cout << classnames.size() << "\n";
          }

      }
([a-zA-Z0-9_]+[ \t\n]*\(.*\)[ \t\n]*\{) {
          comment = multilinecomment or singlelinecomment;
          if(!comment)
          {
            string functionname = extract_functionname(conv_string(yytext));
            //cout << functionname << ": function! \n";

            if(classnames.count(functionname)){
              cout << ": constructor! \n";
            }
          }
      }
%%

int yywrap()
{

}

int main()
{
  yylex();

}
