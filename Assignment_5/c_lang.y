%{
    #include <bits/stdc++.h>
    #include <string>
    #define SIZE_INT 4
    #define SIZE_FLOAT 4
    #define print(str, val) \
        std::cout << str << " " <<  val << std::endl;

    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
    void yyerror(const char *s);
    using namespace std;

    struct var_record {
        string name;
        string type;
        bool is_parameter;
        int level;

        var_record(string name, string type, bool is_parameter = true, int level = 0){
            this -> name = name;
            this -> type = type;
            this -> is_parameter = is_parameter;
            this -> level = level;
        }
    };

    struct function_record {
        string function_return_type;
        list<var_record> parameters;
        list<var_record> local_variables;

        void insert_parameter(string parameter_name, string type, int level = 0){
            parameters.push_back(var_record(parameter_name, type, true, level));
        }

        void insert_variable(string var_name, string type, int level = 0){
            local_variables.push_back(var_record(var_name, type, false, level));
        }

        var_record& search_param(string parameter_name) {
            for(auto it = parameters.begin(); it != parameters.end(); ++it){
                if(it -> name == parameter_name){
                    return *it;
                }
            }
        }

        var_record& search_variable(string var_name) {
            for(auto it = local_variables.begin(); it != local_variables.end(); ++it){
                if(it -> name  == var_name){
                    return *it;
                }
            }
        }
    };

    struct symbol_table {
        unordered_map<string, function_record> entries;

        function_record* insert_function(string function_name) {
            function_record *r = new function_record();
            entries[function_name] = *r;
            return r;
        }

        bool search_function(string function_name, function_record *function) {
            // If function exists in symbol table
            if (entries.count(function_name)) {
                // Set function = pointer to function in symbol table
                // Returns true
                function = &entries[function_name];
                return true;
            }
            else {
                // If not found returns not found (i.e. false)
                return false;
            }
        }

    } symtab;

    /* Intermediate Code Generation. */
    /* Quadruples. */
    struct quadruple {
        string _operator;
        string _arg1;
        string _arg2;
        string _result;

        quadruple(string op, string arg1, string arg2, string result){
            this -> _operator = op;
            this -> _arg1 = arg1;
            this -> _arg2 = arg2;
            this -> _result = result;
        }
    };

    vector<quadruple> quadruples;

    /* Indices of associated quadruples. */
    struct indexlist {
        vector<int> indexes;
    };

    /* Temporary variables for intermediate code. */
    int curr_temp = 0;
    string get_next_temp(){
        curr_temp += 1;
        return "t" + std::to_string(curr_temp);
    }

    /* abhishek */
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

	class ab_symbol_table{
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

		void patch(char* v_type, char* s){
			vector<string> var_names = this->getvarvector(s);
			for (int i = 0; i < var_names.size(); ++i){

				for (int j = 0; j < tab.size(); ++j){
					if(tab[j].name == var_names[i]){
						tab[j].type = strdup(v_type);
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

	ab_symbol_table ab_symtab = ab_symbol_table();
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

	void checksanity(vector<string> dim)
	{
		for (int i = 0; i < dim.size(); ++i)
		{
			int index = ab_symtab.search(dim[i]);
			if(ab_symtab.tab[index].isarray)
			{
				for(int j=0;j < ab_symtab.tab[index].dimension.size();j++)
				{
					if(isNumber(ab_symtab.tab[index].dimension[j]))
						continue;
					int dim_index = ab_symtab.search(ab_symtab.tab[index].dimension[j]);

					if(dim_index<0){
						cout<<"Variable: "<<ab_symtab.tab[index].dimension[j]<<" not declared"<<endl;
					}
					else
					{
						if(ab_symtab.tab[dim_index].type != "i"){
							cout<<"Variable: "<<ab_symtab.tab[dim_index].name<<" must be of type int"<<endl;
						}
						if(ab_symtab.tab[dim_index].isarray){
							cout<<"Variable: "<<ab_symtab.tab[dim_index].name<<" is array type"<<endl;
						}
					}
				}
			}
		}
	}

    // Stores active function name
    string active_func_name;

    // Stores current level
    int level = 0;

    // Stores list of parameter of current function declaration
    list<var_record> active_func_param_list;

    // Stores list of arguments of function being called
    list<var_record> called_arg_list;

    // Stores true, If error is found while semantic checking
    bool errorFound = false;

    // Keep track of current line number
    int lineNo = 1;

    extern bool isInt(const char *type);
    extern bool isFloat(const char *type);
    extern bool isBoolean(const char *type);
    extern bool isErrorType(const char *type);
    extern bool isNoneType(const char *type);
    extern bool isMatch(const char *str1, const char *str2);
    extern void set_active_function(const char *str);

    extern bool isInt(string type);
    extern bool isFloat(string type);
    extern bool isBoolean(string type);
    extern bool isErrorType(string type);
    extern bool isNoneType(string type);
    extern bool isMatch(string str1, string str2);
    extern void set_active_function(string str);

    extern bool isInsideFunc();
    extern char* setErrorType();
    extern char* setNoErrorType();
    extern void reset_active_function();
    extern void errorLine();
%}

%union {
    struct {
        struct indexlist * indexlist;
        char* type;
        int val;
        int index;
        int len;
        char* sval;
    } type_id;
}

%expect 1       // 1. if-else

// Non Terminals
%type <type_id> statement statement_list
%type <type_id> labeled_statement compound_statement expression_statement conditional_statement loop_statement
%type <type_id> expression
%type <type_id> logical_expression relational_expression assignment_expression arithmetic_expression
%type <type_id> START

%type <type_id> function_declaration function_head
%type <type_id> param_list_declaration param_declaration
%type <type_id> function_call arg_list
%type <type_id> variable_declaration_list variable_declaration

%type <type_id> logical_operation
%type <type_id> datatype
%type <type_id> if_exp else_mark
%type <type_id> bracket_dimlist name_list id_arr
%type <type_id> term factor

// Terminals
%token <type_id> NUM IDENTIFIER
%token <type_id> TYPE VOID
%token <type_id> OR
%token <type_id> AND
%token <type_id> REL_OP
%token <type_id> IF ELSE
%token <type_id> FOR WHILE
%token <type_id> SWITCH CASE DEFAULT

// Starting Non Terminal
%start START

%%
START
	: function_declaration
    | variable_declaration_list
	| START function_declaration
    | START variable_declaration_list
	;

function_declaration
	: function_head '{' statement_list '}'
    {
        level --;
        reset_active_function();
        if (!isErrorType($1.type)) {
            if (!isNoneType($3.type)) {
                if (!(isMatch($1.type, $3.type)))
                    cout << "Type mismatch of return type between " << $$.type << " and " << $3.type << endl;
            }
        }
    }
	| function_head '{' '}'
    {
        reset_active_function();
    }
	;

function_head
    : TYPE IDENTIFIER '(' param_list_declaration ')'
    {
        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function($2.sval, r)) {
            cout << "Error : Redeclaration of function : " << $2.sval << " in line : " << lineNo << endl;
            r->function_return_type = setErrorType();
            $$.type = setErrorType();
        }
        else {
            r = symtab.insert_function($2.sval);
            r->function_return_type = $1.sval;

            // Add param_list_declaration to symbol_table corresponding to active function
            for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
                r->insert_parameter(it->name, it->type, it->level);
            }
            $$.type = strdup($1.sval);
        }

        set_active_function($2.sval);
    }
    | VOID IDENTIFIER '(' param_list_declaration ')'
    {
        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function($2.sval, r)) {
            cout << "Error : Redeclaration of function : " << $2.sval << " in line : " << lineNo << endl;
            r->function_return_type = setErrorType();
            $$.type = setErrorType();
        }
        else {
            r = symtab.insert_function($2.sval);
            r->function_return_type = $1.sval;

            // Add param_list_declaration to symbol_table corresponding to active function
            for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
                r->insert_parameter(it->name, it->type, it->level);
            }
            $$.type = strdup($1.sval);
        }

        set_active_function($2.sval);
    }
    | TYPE IDENTIFIER '(' ')'
    {
        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function($2.sval, r)) {
            cout << "Error : Redeclaration of function : " << $2.sval << " in line : " << lineNo << endl;
            $$.type = setErrorType();
        }
        else {
            r = symtab.insert_function($2.sval);
            r->function_return_type = $1.sval;
            $$.type = strdup($1.sval);
        }
        set_active_function($2.sval);
    }
    | VOID IDENTIFIER '(' ')'
    {
        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function($2.sval, r)) {
            cout << "Error : Redeclaration of function : " << $2.sval << " in line : " << lineNo << endl;
            $$.type = setErrorType();
        }
        else {
            r = symtab.insert_function($2.sval);
            r->function_return_type = $1.sval;
            $$.type = strdup($1.sval);
        }
        set_active_function($2.sval);
    }
    ;

param_list_declaration
    : param_list_declaration ',' param_declaration
    {
        bool found = false;
        // Check if variable is repeated in parameter list
        for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
            if (it -> name == $3.sval) {
                cout << "Redeclaration of parameter " << $3.sval << endl;
                $$.type = setErrorType();
                found = true;
                break;
            }
        }

        var_record param($3.sval, $3.type, /* is_parameter = */ true, level) ;
        active_func_param_list.push_back(param);
        $$.type = setNoErrorType();
        $$.len = $1.len + 1;

        if (isErrorType($1.type) || found) {
            $$.type = setErrorType();
        }
    }
    | param_declaration
    {
        active_func_param_list.clear();
        $$.len = 1;
        var_record param($1.sval, $1.type, /* is_parameter = */ true, level) ;
        active_func_param_list.push_back(param);
        $$.type = setNoErrorType();
    }
    ;

param_declaration
    : TYPE IDENTIFIER           { $$.type = $1.sval; $$.sval = $2.sval; }
    ;

function_call
    : IDENTIFIER '(' ')' ';'
    {
        function_record *r;
        string functionName = $1.sval;

        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {

                // Check if param_list_declaration is empty
                if (r->parameters.empty())  {
                    $$.type = strdup(r->function_return_type.c_str());
                }
                else {
                    // Error
                    cout << "Too many arguments to function '" << functionName << "'\n";
                    $$.type = setErrorType();
                }
            }
        }
        else {
            // Function not found
            cout << "Function " << functionName << " is not declared\n";
            $$.type = setErrorType();
        }
    }
    | IDENTIFIER '(' arg_list ')' ';'
    {
        function_record *r;
        string functionName = $1.sval;

        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {

                // Check if param_list_declaration matches with arg_list
                if (r->parameters.size() > $3.len) {
                    cout << "Too few arguments to function '" << functionName << "'\n";
                    $$.type = setErrorType();
                }
                else if (r->parameters.size() < $3.len) {
                    cout << "Too many arguments to function '" << functionName << "'\n";
                    $$.type = setErrorType();
                }
                else {
                    // Match the datatypes of param_list_declaration and arg_list
                    auto param_it = r->parameters.begin();
                    auto arg_it = called_arg_list.begin();
                    while (param_it != r->parameters.end()) {

                        if (!isMatch(param_it->type, arg_it->type)) {
                            errorLine();
                            cout << "datatype mismatch for calling function : " << functionName << "\n";
                            $$.type = setErrorType();
                            break;
                        }
                        param_it ++;
                        arg_it ++;
                    }
                }
            }
        }
        else {
            // Function not found
            errorLine();
            cout << "Function " << functionName << " is not declared\n";
            $$.type = setErrorType();
        }
    }

    | TYPE IDENTIFIER '=' IDENTIFIER '(' ')' ';'
    {
        function_record *r;
        string functionName = $4.sval;

        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {

                // Check if param_list_declaration is empty
                if (r->parameters.empty())  {
                    string return_type = r->function_return_type;
                    if ( !isMatch($1.type, return_type) ) {
                        errorLine();
                        cout << "incompatible types when initializing type " << $1.type << " using type " << return_type << endl;
                        $$.type = setErrorType();
                    }
                    else
                        $$.type = strdup(return_type.c_str());
                }
                else {
                    // Error
                    errorLine();
                    cout << "Too many arguments to function '" << functionName << "'\n";
                    $$.type = setErrorType();
                }
            }
        }
        else {
            // Function not found
            errorLine();
            cout << "Function " << functionName << " is not declared\n";
            $$.type = setErrorType();
        }
    }
    | TYPE IDENTIFIER '=' IDENTIFIER '(' arg_list ')' ';'
    {
        function_record *r;
        string functionName = $4.sval;

        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {

                // Check if param_list_declaration matches with arg_list
                if (r->parameters.size() > $6.len) {
                    cout << "Too few arguments to function '" << functionName << "'\n";
                    $$.type = setErrorType();
                }
                else if (r->parameters.size() < $6.len) {
                    cout << "Too many arguments to function '" << functionName << "'\n";
                    $$.type = setErrorType();
                }
                else {
                    // Match the datatypes of param_list_declaration and arg_list
                    auto param_it = r->parameters.begin();
                    auto arg_it = called_arg_list.begin();
                    bool matched = true;
                    while (param_it != r->parameters.end()) {

                        if (!isMatch(param_it->type, arg_it->type)) {
                            errorLine();
                            cout << "datatype mismatch for calling function : " << functionName << "\n";
                            $$.type = setErrorType();
                            matched = false;
                            break;
                        }
                        param_it ++;
                        arg_it ++;
                    }
                    if (matched) {
                        string return_type = r->function_return_type;
                        if ( !isMatch($1.type, return_type) ) {
                            errorLine();
                            cout << "incompatible types when initializing type " << $1.type << " using type " << return_type << endl;
                            $$.type = setErrorType();
                        }
                        else
                            $$.type = strdup(return_type.c_str());
                        }
                }
            }
        }
        else {
            // Function not found
            errorLine();
            cout << "Function " << functionName << " is not declared\n";
            $$.type = setErrorType();
        }
    }
    ;

arg_list
    : IDENTIFIER
    {
        called_arg_list.clear();
        $$.len = 1;

        // Search IDENTIFIER in the symbol_table
        // If found, Get the datatype of IDENTIFIER from symbol_table

        $$.type = setNoErrorType();
        string datatype = $1.type;

        var_record arg($1.sval, datatype, /* is_parameter = */ false, level) ;
        called_arg_list.push_back(arg);
    }
    | TYPE
    {
        called_arg_list.clear();
        $$.len = 1;

        $$.type = setNoErrorType();
        string datatype = $1.type;

        var_record arg($1.sval, datatype, /* is_parameter = */ false, level) ;
        called_arg_list.push_back(arg);
    }
    | arg_list ',' IDENTIFIER
    {
        // Search IDENTIFIER in the symbol_table
        // If found, Get the datatype of IDENTIFIER from symbol_table

        string datatype = $3.type;
        $$.type = setNoErrorType();

        var_record arg($3.sval, datatype, /* is_parameter = */ false, level) ;

        called_arg_list.push_back(arg);
        $$.len = $1.len + 1;

        if (isErrorType($1.type)) {
            $$.type = setErrorType();
        }
    }
    | arg_list ',' TYPE
    {
        string datatype = $3.type;
        $$.type = setNoErrorType();

        var_record arg($3.sval, datatype, /* is_parameter = */ false, level) ;

        called_arg_list.push_back(arg);
        $$.len = $1.len + 1;

        if (isErrorType($1.type)) {
            $$.type = setErrorType();
        }
    }
    ;

statement
    : conditional_statement
    | loop_statement
    | compound_statement        // Nested statement_list
    {
        $$.val = $1.val;
    }
	| expression_statement      // Expression followed by semicolon
    {
        $$.val = $1.val;
    }
    | variable_declaration_list
    | function_call
	;

conditional_statement
	: if_exp  statement
    {
        $$.val = $1.val + $2.val;
        int gotoindex = $1.index;
        quadruples[gotoindex]._result = to_string(gotoindex + $2.val + 1);
    }
    | if_exp statement else_mark statement
    {
        $$.val = $1.val + $2.val + $3.val + $4.val;
        int gotoindex1 = $1.index;
        quadruples[gotoindex1]._result = to_string(gotoindex1 + $2.val + $3.val + 1);
        int gotoindex2 = $3.index;
        quadruples[gotoindex2]._result = to_string(gotoindex2 + $4.val + 1);
    }
	| SWITCH '(' expression ')' statement
    {
        if (!isErrorType($3.type)) {
            if ( isInt($3.type) || isFloat($3.type) ) {
                $$.type = setNoErrorType();
            }
            else {
                yyerror("int expected in expression of if-else");
                $$.type = setErrorType();
            }
        }
        else
            $$.type = setErrorType();
    }
	| SWITCH '(' expression ')' labeled_statement
    {
        if (!isErrorType($3.type)) {
            if (isInt($3.type)) {
                $$.type = setNoErrorType();
            }
            else {
                yyerror("int expected in expression of switch case");
                $$.type = setErrorType();
            }
        }
        else
            $$.type = setErrorType();
    }
	;

if_exp
    :   IF '(' expression ')'
    {
        if (!isErrorType($3.type)) {
            if ( isInt($3.type) || isFloat($3.type) ) {
                $$.type = setNoErrorType();
            }
            else {
                yyerror("int expected in expression of if-else");
                $$.type = setErrorType();
            }
        }

        $$.index = quadruples.size();
        $$.val = $3.val + 1;
        quadruples.push_back(quadruple("if0", "expres", "", ""));
    }

else_mark
    : ELSE
    {
        $$.val = 1;
        $$.index = quadruples.size();
        quadruples.push_back(quadruple("go", "", "", ""));
    }

loop_statement
	: WHILE '(' expression ')' statement
    {
        if (!isErrorType($3.type)) {
            if (isInt($3.type) || isFloat($3.type)) {
                $$.type = setNoErrorType();
            }
            else {
                yyerror("int expected in expression of while statement");
                $$.type = setErrorType();
            }
        }
        else
            $$.type = setErrorType();
    }
	| FOR '(' expression_statement expression_statement ')' statement
    {
        if (!isErrorType($3.type)) {
            if (isInt($4.type) || isFloat($4.type) || isNoneType($4.type)) {
                $$.type = setNoErrorType();
            }
            else {
                yyerror("Type error in condition of for loop");
                $$.type = setErrorType();
            }
        }
        else
            $$.type = setErrorType();
    }
	| FOR '(' expression_statement expression_statement expression ')' statement
    {
        if (!isErrorType($3.type)) {
            if (isInt($4.type) || isFloat($4.type) || isNoneType($4.type)) {
                $$.type = setNoErrorType();
            }
            else {
                yyerror("Type error in condition of for loop");
                $$.type = setErrorType();
            }
        }
        else
            $$.type = setErrorType();
    }
	;

labeled_statement
	: CASE constant_expression ':' statement {
        if (!isMatch($2.type, "int")) {
            yyerror("int expected in switch case");
        }
    }
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
    {
        $$.val = 0;
    }
	| '{' statement_list '}'
    {
        $$.val = $2.val;
    }
	;

statement_list
	: statement
    {
        $$.val = $1.val;
    }
	| statement_list statement
    {
        $$.val = $1.val + $2.val;
    }
	;

expression_statement
	: ';'
    {
        $$.val = 0;
        $$.type = strdup("NoneType");
    }
	| expression ';'
    {
        $$.val = $1.val;
        $$.type = strdup($1.type);
    }
	;

/*
    Expressions.
    Expecting: Logical & Relational and Arithmetic Expressions
*/
expression
    : assignment_expression
    {
        $$.val = $1.val;
        $$.type = strdup($1.type);
    }
    | logical_expression
    {
        $$.val = $1.val;
        $$.type = strdup("int");
    }
    | relational_expression
    {
        $$.val = $1.val;
        $$.type = strdup("int");
    }
    | arithmetic_expression
    {
        $$.val = $1.val;
        $$.type = strdup("int");
    }
    ;

assignment_expression
    : IDENTIFIER '=' NUM
    {
        $$.val = 2;
        $$.type = strdup($3.type);
        quadruples.push_back(quadruple("=", string($3.sval), "", string($1.sval)));
        quadruples.push_back(quadruple("=", string($1.sval), "", "expres"));
    }
    | IDENTIFIER '=' IDENTIFIER
    {
        $$.val = 2;
        $$.type = strdup($1.type);
        quadruples.push_back(quadruple("=", string($3.sval), "", string($1.sval)));
        quadruples.push_back(quadruple("=", string($1.sval), "", "expres"));
    }
    ;

logical_expression
    : IDENTIFIER logical_operation IDENTIFIER
    {
        $$.val = 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), "expres"));
    }
    | NUM logical_operation IDENTIFIER
    {
        $$.val = 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), "expres"));
    }
    | IDENTIFIER logical_operation NUM
    {
        $$.val = 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), "expres"));
    }
    | NUM logical_operation NUM
    {
        $$.val = 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), "expres"));
    }
    ;

logical_operation
    : OR
    {
        $$.sval = strdup($1.sval);
    }
    | AND
    {
        $$.sval = strdup($1.sval);
    }
    ;

relational_expression
    : IDENTIFIER REL_OP IDENTIFIER
    {
        $$.val = 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), "expres"));
    }
    | NUM REL_OP IDENTIFIER
    {
        $$.val = 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), "expres"));
    }
    | IDENTIFIER REL_OP NUM
    {
        $$.val = 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), "expres"));
    }
    | NUM REL_OP NUM
    {
        $$.val = 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), "expres"));
    }
    ;


arithmetic_expression
    : term '+' arithmetic_expression
    {
        $$.type = strdup("num");
		//evaluvation quad factor+term and $$ = that result
		cout<<$1.sval<<" + "<<$3.sval<<endl;
	}

	| term '-' arithmetic_expression
    {
        $$.type = strdup("num");
									//evaluvation quad factor-term and $$ = that result
									cout<<$1.sval<<" - "<<$3.sval<<endl;
								}
	|		term
    {
        $$.type = strdup("num");
    }
	;

term:		factor '*' term
    {
		//evaluvation quad factor*term and $$ = that result
		cout<<$1.sval<<" * "<<$3.sval<<endl;
	}
	|		factor '/' term		{
									//evaluvation quad factor/term and $$ = that result
									cout<<$1.sval<<" / "<<$3.sval<<endl;
								}
	|		factor
	;

factor
    : '(' arithmetic_expression ')'
    {
		$$ = $2;
		//evaluvate expr first and $$ = that result
	}
	| IDENTIFIER
    | NUM
	;

/* Variable Declarations. */
datatype
    : INT                           { $$.type = strdup("int"); }
    | FLOAT                         { $$.type = strdup("float"); }
    ;

variable_declaration_list
    : datatype name_list
    {
		$$ = $1;
        ab_symtab.patch($1.sval, $2.sval);
        vector<string> dim = makedimlist($2.sval);
		checksanity(dim);
		// makecorrect(dim);
		cout<<endl;
	}
    ;

name_list
    : id_arr
	| id_arr ',' name_list
    {
        $$.sval=$1.sval;
        strcat($$.sval,",");
        strcat($$.sval,$3.sval);
	}
    ;

id_arr
    : IDENTIFIER
    {
    	//abhishek //assignment quad = 0;
    	variable v = variable($1.sval, "type", "0", false, dummy);
    	if(ab_symtab.search(v.name) == -1)
    		ab_symtab.insertintosymtab(v);
	}
	| IDENTIFIER '=' arithmetic_expression
    {
		//abhishek //assignment quad = exprvalue; //here we dump the expression as value of id
		variable v = variable($1.sval, "type", $3.sval, false, dummy);
		if(ab_symtab.search(v.name) == -1)
			ab_symtab.insertintosymtab(v);
	}
	| IDENTIFIER bracket_dimlist
    {
    	//abhishek //assignment quad = 0;
    	//here seperate values should be assigned to seperate elements
    	//not done as of now
        vector<string> dim = makedimlist($2.sval);
        variable v = variable($1.sval, "type", "0", true, dim);
    	if(ab_symtab.search(v.name) == -1)
    		ab_symtab.insertintosymtab(v);
    }
	;

bracket_dimlist
    : '[' NUM ']'
    {
	    $$=$2;
	}
	| '[' NUM ']' bracket_dimlist
    {
        $$=$2;
        strcat($$.sval,",");
        strcat($$.sval,$4.sval);
	}

%%

int main(int argc, char **argv) {

    char *filename = (char*)malloc(sizeof(char)*20);
    strcpy(filename, "input.txt");

    // Open a file handle to a particular file:
    FILE *myfile = fopen(filename, "r");
    // Make sure it is valid:
    if (!myfile) {
        print(filename, "does not exists.");
        return -1;
    }
    // Set Flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    // Parse through the input:
    while(!feof(yyin))  {
        yyparse();
    }

    cout << "Intermediate Code in Quadruple Format:" << "\n";
    for(int i = 0; i < quadruples.size(); ++i){
        quadruple quad = quadruples[i];
        cout << setw(3) << i << "      " << setw(3) << quad._operator << " | " << setw(6) << quad._arg1 << " | " << setw(6) << quad._arg2 << " | " << setw(6) << quad._result << "\n";
    }

}

void yyerror(const char *s) {
  print("", s);
//   exit(-1);
}

bool isInt(const char *type) {
    if (isMatch(type, "int"))    return true;
    else                        return false;
}
bool isFloat(const char *type) {
    if (isMatch(type, "float"))    return true;
    else                        return false;
}
bool isBoolean(const char *type) {
    if (isMatch(type, "bool"))    return true;
    else                        return false;
}
bool isErrorType(const char *type) {
    if (isMatch(type, "ErrorType"))    return true;
    else                        return false;
}
bool isNoneType(const char *type) {
    if (isMatch(type, "NoneType"))    return true;
    else                        return false;
}
bool isMatch(const char *str1, const char *str2) {
    return !strcmp(str1, str2);
}
void set_active_function(const char *str) {
    active_func_name = str;
}

bool isInt(string type) {
    if (isMatch(type, "int"))    return true;
    else                        return false;
}
bool isFloat(string type) {
    if (isMatch(type, "float"))    return true;
    else                        return false;
}
bool isBoolean(string type) {
    if (isMatch(type, "bool"))    return true;
    else                        return false;
}
bool isErrorType(string type) {
    if (isMatch(type, "ErrorType"))    return true;
    else                        return false;
}
bool isNoneType(string type) {
    if (isMatch(type, "NoneType"))    return true;
    else                        return false;
}
bool isMatch(string str1, string str2) {
    return str1 == str2;
}
void set_active_function(string str) {
    active_func_name = str;
}

char* setErrorType() {
    errorFound = true;
    return strdup("ErrorType");
}
char* setNoErrorType() {
    return strdup("NoErrorType");
}
char* setNoneType() {
    return strdup("NoneType");
}
bool isInsideFunc() {
    return !(active_func_name == "");
}
void reset_active_function() {
    active_func_name = "";
}
void errorLine() {
    cout << "Error at line " << lineNo << " : ";
}
