%{
	#include <bits/stdc++.h>
	#include <string>
	#define print(str, val) \
    printf("%s %s\n", str, val);
    #define SIZE_INT 4
    #define SIZE_FLOAT 4

	using namespace std;
	int yyerror(const char *s);
	int yylex(void);
	int yyparse();

	bool isNumber(const string &line) 
	{
		if (line[0] == '0') return true;
		return (atoi(line.c_str()));
	}

	class variable{
		public:
		string name;
		string type;
		string value;
		bool isarray;
		int startoffset;
		int endoffset;
		vector<string> dimension;

		variable(string v_name, string v_type, string v_value, bool v_isarray, vector<string> v_dimension){
			this->name = v_name;
			this->type = v_type;
			this->value = v_value;
			this->isarray = v_isarray;
			this->dimension = v_dimension;
			this->startoffset = 0;
			this->endoffset = -1;
		}

	};

	class symbol_table{
		public:
		vector <variable> tab;

		void insertintosymtab(variable v){
			
			if(tab.size() == 0)
				v.startoffset = 0;
			else
				v.startoffset = tab[tab.size()-1].endoffset;

			long long int mul = 1;
			for (int i = 0; i < v.dimension.size(); ++i){
				if(isNumber(v.dimension[i])){
					mul *= stoi(v.dimension[i]);
				}
				else{
					mul *= stoi(tab[this->search(v.dimension[i])].value);
				}
			}

			if(v.type == "i")
				mul *= SIZE_INT;
			else
				mul *= SIZE_FLOAT;

			v.endoffset = v.startoffset +mul;
			tab.push_back(v);	
		}

		void printsymtab()	{
			cout<<"Symbol Table: "<<endl;
			for(int i=0;i<this->tab.size();i++)
			{
				cout<<"Start: "<<this->tab[i].startoffset<<endl;
				cout<<this->tab[i].name<<": "<<this->tab[i].value<<" ( "<<this->tab[i].type<<" )";
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

	void makecorrect(vector<string> dim)
	{
		for (int i = 0; i < dim.size(); ++i)
		{
			if(symtab.search(dim[i]) == -1)
			{
				cout<<"not found"<<endl;
				return;
			}

			if(symtab.tab[symtab.search(dim[i])].type == "i")
			{
				string temp = symtab.tab[symtab.search(dim[i])].value;
				string temp2 = "";
				int j=0;
				while(j < temp.length() && temp[j] != '.')
				{
					temp2 += temp[j];
					j++;
				}
				symtab.tab[symtab.search(dim[i])].value = temp2;
			}
		}	
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

	string evaluvate(char* c_op1, char* c_op, char* c_op2)
	{
		string op1="", op="", op2="";

		char* itr = c_op1;
		while(*itr){
			op1 += *itr;
			itr++;
		}

		itr = c_op2;
		while(*itr){
			op2 += *itr;
			itr++;
		}

		itr = c_op;
		while(*itr){
			op += *itr;
			itr++;
		}

		float op1val, op2val;
		
		if(isNumber(op1))
			op1val = stof(op1);
		else
			op1val = stof(symtab.tab[symtab.search(op1)].value);

		if(isNumber(op2))
			op2val = stof(op2);
		else
			op2val = stof(symtab.tab[symtab.search(op2)].value);


		float ans;

		if(op == "+"){
			ans = op1val+op2val;
		}
		else if(op == "-"){
			ans = op1val-op2val;	
		}
		else if(op == "*"){
			ans = op1val*op2val;
		}
		else{
			ans = op1val/op2val;
		}
		return to_string(ans);
	}

%}

%union 
{
    int ival;
    float fval;
    char c;
    char *sval;	
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
%left EQUAL
%left OP

%token <sval> VAR_NAME
%type <sval> NUM
%type <sval> OP
%type <sval> name_list
%type <sval> id_arr
%type <sval> id
%type <sval> br_dimlist
%type <sval> expr
%type <sval> term
%type <sval> factor
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
								// makecorrect(dim);
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
										//abhishek //assignment quad = 0;
										variable v = variable($1, "type", "0", false, dummy);
										if(symtab.search(v.name) == -1)
											symtab.insertintosymtab(v);
									}

	|		id EQUAL expr			{
										//abhishek //assignment quad = exprvalue; //here we dump the expreseeion as value of id
										variable v = variable($1, "type", $3, false, dummy);
										if(symtab.search(v.name) == -1)
											symtab.insertintosymtab(v);	
									}

	|		id br_dimlist			{
										//abhishek //assignment quad = 0;
										//here seperate values should be assigned to seperate elements
										//not done as of now
										vector<string> dim = makedimlist($2);
										variable v = variable($1, "type", "0", true, dim);
										if(symtab.search(v.name) == -1)
											symtab.insertintosymtab(v);
									}
	;

expr:		term '+' expr 		{
									//evaluvation quad factor+term and $$ = that result	
									cout<<$1<<" + "<<$3<<endl;
								}

	|		term '-' expr 		{
									//evaluvation quad factor-term and $$ = that result
									cout<<$1<<" - "<<$3<<endl;
								}
	|		term
	;

term:		factor '*' term		{
									//evaluvation quad factor*term and $$ = that result	
									cout<<$1<<" * "<<$3<<endl;
								}

	|		factor '/' term		{
									//evaluvation quad factor/term and $$ = that result
									cout<<$1<<" / "<<$3<<endl;
								}
	|		factor
	;

factor:		'(' expr ')'		{
									$$ = $2;
									//evaluvate expr first and $$ = that result
								}
	|		id
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

int main()
{
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