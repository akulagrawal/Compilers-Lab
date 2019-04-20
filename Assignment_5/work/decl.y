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
		bool isarray;
		vector<string> dimension;

		variable(string v_name, string v_type, string v_value, bool v_isarray, vector<string> v_dimension){
			this->name = v_name;
			this->type = v_type;
			this->value = v_value;
			this->isarray = v_isarray;
			this->dimension = v_dimension;
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
			for(int i=0;i<this->tab.size();i++)
			{
				cout<<this->tab[i].name<<": "<<" ( "<<this->tab[i].type<<" )";
				if(this->tab[i].isarray)
				{
					cout<<" Dim: ";
					for (int j = 0; j < this->tab[i].dimension.size(); ++j)
					{
						cout<<", "<<this->tab[i].dimension[j];
					}
				}
				cout<<endl;
			}
		}

		vector <string> getvarvector(char* s){
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

		int search(string varname){
			for (int i = 0; i < tab.size(); ++i){
				if(tab[i].name == varname)
					return i;
			}
			return -1;
		}
	};

	symbol_table symtab = symbol_table();
	vector<string> dummy;

	vector <string> makedimlist(char* s){
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

	bool isNumber(const string &line) 
	{
		if (line[0] == '0') return true;
		return (atoi(line.c_str()));
	}

	void checksanity(vector<string> dim)
	{
		for (int i = 0; i < dim.size(); ++i)
		{
			int index = symtab.search(dim[i]);
			if(symtab.tab[index].isarray)
			{
				for(int j=0;j < symtab.tab[index].dimension.size();j++)
				{
					if(isNumber(symtab.tab[index].dimension[j]))
						continue;
					int dim_index = symtab.search(symtab.tab[index].dimension[j]);

					if(dim_index<0){
						cout<<"Variable: "<<symtab.tab[index].dimension[j]<<" not declared"<<endl;
					}
					else
					{
						if(symtab.tab[dim_index].type != "i"){
							cout<<"Variable: "<<symtab.tab[dim_index].name<<" must be of type int"<<endl;
						}
						if(symtab.tab[dim_index].isarray){
							cout<<"Variable: "<<symtab.tab[dim_index].name<<" is array type"<<endl;
						}
					}
				}
			}
		}
	}

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
%left RSB
%left LSB
%left VAR_NAME
%left NUM

%token <sval> VAR_NAME
%type <sval> name_list
%type <sval> id_arr
%type <sval> id
%type <sval> NUM
%type <sval> dimlist
%type <sval> br_dimlist
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
								symtab.patch($1, $2);
								vector<string> dim = makedimlist($2);
								checksanity(dim);
								cout<<endl;
							}
			;

type:		INT 	{$$ = 'i';}
	|		FLOAT	{$$ = 'f';}
			;


name_list:	id_arr					
		|	id_arr COMMA name_list	{
										$$=$1;
										strcat($$,",");
										strcat($$,$3);
									}
		;
id_arr:		id 						{
										variable v = variable($1, "type", "value", false, dummy);
										symtab.insertintosymtab(v);
									}

	|		id LSB dimlist RSB 		{
										vector<string> dim = makedimlist($3);
										variable v = variable($1, "type", "value", true, dim);
										symtab.insertintosymtab(v);	
									}

	|		id br_dimlist			{
										vector<string> dim = makedimlist($2);
										variable v = variable($1, "type", "value", true, dim);
										symtab.insertintosymtab(v);	
									}
	;

dimlist:	id 						

	|		id COMMA dimlist 		{
										$$=$1;
										strcat($$,",");
										strcat($$,$3);
									}
	;

br_dimlist:	LSB	id RSB				{
										$$=$2;
									}

	|		LSB id RSB br_dimlist	{
										$$=$2;
										strcat($$,",");
										strcat($$,$4);
									}
	;

id:			VAR_NAME
	|		NUM;

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