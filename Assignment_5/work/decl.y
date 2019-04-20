%{
	#include <bits/stdc++.h>
	#define print(str, val) \
    printf("%s %s\n", str, val);
	using namespace std;
	int yyerror(const char *s);
	int yylex(void);
	int yyparse();

	class variable{
		public:
		string name;
		string type;
		string value;

		variable(string v_name, string v_type, string v_value){
			this->name = v_name;
			this->type = v_type;
			this->value = v_value;
		}
	};

	class symbol_table{
		public:
		vector <variable> tab;

		void insertintosymtab(variable v){
			for(int i=0;i<this->tab.size();i++){
				if(this->tab[i].name == v.name){
					cout<<"Variable "<<v.name<<" already present"<<endl;
					return;
				}
			}
			tab.push_back(v);	
		}

		void printsymtab()	{
			cout<<"Symbol Table: "<<endl;
			for(int i=0;i<this->tab.size();i++){
				cout<<this->tab[i].name<<": "<<this->tab[i].value<<" ( "<<this->tab[i].type<<" )"<<endl;
			}
		}

		vector <string> getvarvector(char* s)
		{
			vector<string> ans;
			string var_name = "";
			char* itr = s;
			while(*itr){
				if(*itr == ','){
					ans.push_back(var_name);
					var_name = "";
					itr++;
					continue;
				}
				var_name += *itr;
				itr++;
			}
			if(var_name != ""){
				ans.push_back(var_name);
			}
			return ans;
		}

		void patch(char v_type, char* s){
			vector<string> var_names = this->getvarvector(s);
			for (int i = 0; i < var_names.size(); ++i){
				for (int j = 0; j < tab.size(); ++j){
					if(tab[j].name == var_names[i]){
						tab[j].type = v_type;
						break;
					}
				}
			}
		}
	};

	symbol_table symtab = symbol_table();

%}

%union 
{
    int ival;
    float fval;
    char c;
    char *sval;
    struct
    {
    	char *s;
    	char t;
    }var_at;
}

%start decl
%left SEMI
%left INT
%left FLOAT
%left COMMA
%left VAR_NAME

%token <sval> VAR_NAME
%type <var_at> name_list
%type <sval> id
%type <c> type
%type <c> one_dec

%%

decl:		decl_list SEMI {
								cout<<"Everything correct"<<endl;
								symtab.printsymtab();
						   }
			;

decl_list:	one_dec 
		|	decl_list SEMI one_dec 
			;

one_dec:	type name_list	{
								$$ = $1;
								char *itr = $<var_at.s>2;
								$<var_at.t>2 = $1;
								cout<<$1<<": ";
								while(*itr)
								{
									cout<<*itr<<" ";
									itr++;
								}
								symtab.patch($1, $<var_at.s>2);

								cout<<endl;
							}
			;

type:		INT 	{$$ = 'i';}
	|		FLOAT	{$$ = 'f';}
			;

name_list:	id 					{
									strcat($<var_at.s>$, "");
									variable v = variable($1, "type", "value");
									symtab.insertintosymtab(v);

								}
		|	name_list COMMA id 	{
									variable v = variable($3, "type", "value");
									symtab.insertintosymtab(v);
									strcat($<var_at.s>1, ",");
									strcat($<var_at.s>1, $3);
								}
			;

id:			VAR_NAME
			;

%%

int main(int argc, char **argv)
{
  if ((argc > 1) && (freopen(argv[1], "r", stdin) == NULL))
  {
    cerr << argv[0] << ": File " << argv[1] << " cannot be opened.\n";
    exit(1);
  }
  
  yyparse();

  return 0;
}

int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(const char *s)
{
  print("Invalid syntax ", s);
  return 0;
}