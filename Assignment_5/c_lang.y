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

        void insert_parameter(string parameter_name, string type, int level = 1){
            parameters.push_back(var_record(parameter_name, type, true, level));
        }

        void insert_variable(string var_name, string type, int level = 2){
            local_variables.push_back(var_record(var_name, type, false, level));
        }

        bool search_param(string parameter_name, var_record *&r) {
            for(auto it = parameters.begin(); it != parameters.end(); ++it){
                if(it -> name == parameter_name){
                    r = &(*it);
                    return true;
                }
            }
            return false;
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

        void insert_function(string function_name, string datatype, list<var_record> active_func_param_list) {
            function_record * r = new function_record;
            r -> function_return_type = datatype;

            // Add param_list_declaration to symbol_table corresponding to active function
            for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
                r -> insert_parameter(it->name, it->type, it->level);
            }

            active_func_param_list.clear();
            entries[function_name] = *r;
        }

        bool search_function(string function_name, function_record *&function) {
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

        quadruple() {}

        quadruple(string op, string arg1, string arg2, string result){
            this -> _operator = op;
            this -> _arg1 = arg1;
            this -> _arg2 = arg2;
            this -> _result = result;
        }
    };

    vector<quadruple> quadruples;

    bool arraydimDefined = false;

    /* Indices of associated quadruples. */
    struct indexlist {
        vector<int> indexes;
    };

    /* Temporary variables for intermediate code. */
    int glob_temp = 0;
    map<string, int> func_temps;
    string get_next_temp(string func_name = ""){
        if(func_name == ""){
            glob_temp += 1;
            return "t" + std::to_string(glob_temp);
        } else {
            func_temps[func_name] += 1;
            return "t" + func_name + std::to_string(func_temps[func_name]);
        }
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
        string function_name;
        int level;

		bool isarray;
		int startoffset;
		int endoffset;
        int quadindex; // the quadruple for declaration
		vector<string> dimension;

		variable(string v_name, string v_type, string v_value, bool v_isarray, vector<string> v_dimension, string v_func_name = "", int v_level = 0){
			this->name = v_name;
			this->type = v_type;
			this->value = v_value;
			this->isarray = v_isarray;
			this->dimension = v_dimension;
			this->startoffset = 0;
			this->endoffset = -1;
            this->function_name = v_func_name;
            this->level = v_level;
		}

	};

	class ab_symbol_table{
		public:
		vector <variable> tab;

		void insertintosymtab(variable v, int index){

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

			v.endoffset = v.startoffset + mul;
            v.quadindex = index;
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
                        quadruples[tab[j].quadindex]._arg1 = string(tab[j].type);
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

        bool search_var(string varname, int &cur_level, string functionName, string &datatype) {
            vector<int> position;
            for (int i = 0; i < tab.size(); ++i) {
                if (tab[i].name == varname && tab[i].function_name == functionName)
                    position.push_back(i);
                else if (tab[i].name == varname && tab[i].function_name == "")
                    position.push_back(i);
            }
            if (position.empty()) {
                return false;
            }
            else {
                int pos_with_max_level = 0;
                int max_level = 0;
                for (int i = 0; i < position.size(); i++) {
                    if (tab[position[i]].level > max_level) {
                        pos_with_max_level = position[i];
                        max_level = tab[position[i]].level;
                    }
                }
                cur_level = max_level;
                datatype = tab[pos_with_max_level].type;
            }
            return true;
        }

        void delete_var_from_level(string function_name, int level) {
            for (auto it = tab.begin(); it != tab.end(); ) {
                if (it->function_name == function_name && it->level == level) {
                    it = tab.erase(it);
                }
                else
                    it++;
            }
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

    // Keep track of whether inside switch case statement
    int insideSwitchCase = 0;
    // Keep track of whether inside loops
    int insideLoop = 0;
    // Keep track whether one case conditions got matched with switch case expression
    bool matchedCaseWithExp = false;

    extern bool isInt(const char *type);
    extern bool isFloat(const char *type);
    extern bool isBoolean(const char *type);
    extern bool isErrorType(const char *type);
    extern bool isVoidType(const char *type);
    extern bool isMatch(const char *str1, const char *str2);
    extern void set_active_function(const char *str);
    extern char* setVoidType();

    extern bool isInt(string type);
    extern bool isFloat(string type);
    extern bool isBoolean(string type);
    extern bool isErrorType(string type);
    extern bool isVoidType(string type);
    extern bool isMatch(string str1, string str2);
    extern void set_active_function(string str);

    extern bool isInsideFunc();
    extern char* setErrorType();
    extern char* setIntType();
    extern char* setNoErrorType();
    extern void reset_active_function();
    extern void errorLine(string errorMsg);
    extern void warning(string warningMsg);
    extern bool isVariableInSymtab(string varname);
    extern bool checkForVariable(string var_name, string &datatype, string active_func, int cur_level, bool flag);
    extern void delete_var_list(string function_name, int level);
    extern bool isCompatible(string type1, string type2);
    extern string Variable(string str);
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

%expect 8       // 1. if-else

// Non Terminals
%type <type_id> statement statement_list
%type <type_id> labeled_statement compound_statement expression_statement conditional_statement loop_statement
%type <type_id> expression expression_cover
%type <type_id> logical_expression relational_expression assignment_expression arithmetic_expression
%type <type_id> START

%type <type_id> function_declaration function_head function_result_assignment
%type <type_id> param_list_declaration param_declaration
%type <type_id> function_call arg_list
%type <type_id> variable_declaration_statement

%type <type_id> logical_operation
%type <type_id> FOREXP WHILEEXP if_exp else_mark
%type <type_id> SWITCHEXP CASE_EXP
%type <type_id> bracket_dimlist name_list id_arr
%type <type_id> arithmetic_term arithmetic_factor

// Terminals
%token <type_id> NUM IDENTIFIER
%token <type_id> TYPE VOID
%token <type_id> OR
%token <type_id> AND
%token <type_id> REL_OP
%token <type_id> IF ELSE
%token <type_id> FOR WHILE
%token <type_id> SWITCH CASE DEFAULT
%token <type_id> BREAK CONTINUE
%token <type_id> RETURN

// Starting Non Terminal
%start START

%%
START
	: function_declaration
    | variable_declaration_statement
	| START function_declaration
    | START variable_declaration_statement
	;

function_declaration
	: function_head '{' function_result_assignment statement_list '}'
    {
        // get a variable assigned to this function to be returned.
        string temp = "t" + string($1.sval);

        // update type of this variable.
        quadruples[$3.index]._arg1 = $1.type;

        // update quads with (funcvar) which need to be filled in.
        for(int index = $3.index; index < quadruples.size(); ++index){
            if(quadruples[index]._result == "(funcvar)"){
                quadruples[index]._result = temp;
            }
        }

        quadruples.push_back(quadruple("end", string($1.sval), "", ""));

        delete_var_list(active_func_name, level);
        level --;
        reset_active_function();
        level --;
    }
	| function_head '{' '}'
    {
        delete_var_list(active_func_name, level);
        level--;
        reset_active_function();
    }
	;

function_result_assignment
    : // Assign a variable for the return value of this function.
    {
        $$.index = quadruples.size();
        quadruples.push_back(quadruple("assign", "(type)", "1", "(funcvar)"));
    }

function_head
    : TYPE IDENTIFIER '(' { level ++; } param_list_declaration ')'
    {
        quadruples.push_back(quadruple("label", string($2.sval), to_string($5.len), ""));

        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function($2.sval, r)) {
            errorLine("Redeclaration of function '" + Variable(string($2.sval)) + "'");
            r->function_return_type = setErrorType();
            $$.type = setErrorType();
        }
        else {
            symtab.insert_function($2.sval, $1.sval, active_func_param_list);
            $$.type = strdup($1.sval);
        }

        $$.sval = $2.sval;
        set_active_function($2.sval);
    }
    | VOID IDENTIFIER '(' { level ++; } param_list_declaration ')'
    {
        quadruples.push_back(quadruple("label", string($2.sval), to_string($5.len), ""));

        level ++;
        function_record *r;

        // Check if function already exists
        if (symtab.search_function($2.sval, r)) {
            errorLine("Redeclaration of function '" + Variable(string($2.sval)) + "'");
            r->function_return_type = setErrorType();
            $$.type = setErrorType();
        }
        else {
            symtab.insert_function($2.sval, $1.sval, active_func_param_list);
            $$.type = strdup($1.sval);
        }

        $$.sval = $2.sval;
        set_active_function($2.sval);
    }
    | TYPE IDENTIFIER '(' ')'
    {
        quadruples.push_back(quadruple("label", string($2.sval), to_string(0), ""));

        level += 2;
        function_record *r;

        active_func_param_list.clear();

        // Check if function already exists
        if (symtab.search_function($2.sval, r)) {
            errorLine("Redeclaration of function '" + Variable(string($2.sval)) + "'");
            $$.type = setErrorType();
        }
        else {
            symtab.insert_function($2.sval, $1.sval, active_func_param_list);
            $$.type = strdup($1.sval);
        }

        $$.sval = $2.sval;
        set_active_function($2.sval);
    }
    | VOID IDENTIFIER '(' ')'
    {
        quadruples.push_back(quadruple("label", string($2.sval), to_string(0), ""));

        level += 2;
        function_record *r;

        active_func_param_list.clear();

        // Check if function already exists
        if (symtab.search_function($2.sval, r)) {
            errorLine("Redeclaration of function '" + Variable(string($2.sval)) + "'");
            $$.type = setErrorType();
        }
        else {
            active_func_param_list.clear();
            symtab.insert_function($2.sval, $1.sval, active_func_param_list);
            $$.type = strdup($1.sval);
        }

        $$.sval = $2.sval;
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
                errorLine("Redeclaration of parameter '" + Variable(string($3.sval)) + "'");
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
    : IDENTIFIER '(' ')'
    {
        function_record *r;
        string functionName = $1.sval;
        $$.val = 0;

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
                    errorLine("Too few arguments to function '" + Variable(string(functionName)) + "'");
                    $$.type = strdup(r->function_return_type.c_str());
                }

                quadruples.push_back(quadruple("call", $1.sval, "", ""));
                $$.val += 1;
            }
            else
                $$.type = setErrorType();
        }
        else {
            // Function not found
            errorLine("Function '" + Variable(string(functionName)) + "' is not declared");
            $$.type = setErrorType();
        }
    }
    | IDENTIFIER '(' arg_list ')'
    {
        function_record *r;
        string functionName = $1.sval;
        $$.val = $3.val;

        // search for function declaration
        if (symtab.search_function(functionName, r)) {

            // If function's return type is ErrorType
            if (!isErrorType(r->function_return_type)) {

                $$.type = strdup(r->function_return_type.c_str());
                // Check if param_list_declaration matches with arg_list
                if (r->parameters.size() > $3.len) {
                    errorLine("Too few arguments to function '" + Variable(functionName) + "'");
                }
                else if (r->parameters.size() < $3.len) {
                    errorLine("Too many arguments to function '" + Variable(functionName) + "'");
                }
                else {
                    // Match the datatypes of param_list_declaration and arg_list
                    auto param_it = r->parameters.rbegin();
                    auto arg_it = called_arg_list.rbegin();
                    while (param_it != r->parameters.rend()) {

                        if (!isMatch(param_it->type, arg_it->type)) {
                            errorLine("datatype mismatch for calling function '" + Variable(functionName) + "'");
                            break;
                        }

                        quadruples.push_back(quadruple("push", arg_it -> name, $1.sval, param_it -> name));
                        $$.val += 1;

                        param_it ++;
                        arg_it ++;
                    }

                    auto delete_it = called_arg_list.begin();
                    advance(delete_it, called_arg_list.size() - $3.len);

                    called_arg_list.erase(delete_it, called_arg_list.end());

                    quadruples.push_back(quadruple("call", $1.sval, "", ""));
                    $$.val += 1;
                }
            }
            else
                $$.type = setErrorType();
        }
        else {
            // Function not found
            errorLine("Function '" + Variable(functionName) + "' is not declared");
            $$.type = setErrorType();
        }
    }
    ;

arg_list
    : arithmetic_expression
    {
        $$.len = 1;
        $$.val = $1.val;
        $$.type = setNoErrorType();
        string datatype = $1.type;

        var_record arg($1.sval, datatype, false, level) ;
        called_arg_list.push_back(arg);
    }
    | arg_list ',' arithmetic_expression
    {
        $$.val = $1.val + $3.val;
        string datatype = $3.type;
        $$.type = setNoErrorType();

        var_record arg($3.sval, datatype, /* is_parameter = */ false, level) ;

        called_arg_list.push_back(arg);
        $$.len = $1.len + 1;

        // cout << "Called args are: ";
        // for(auto it = called_arg_list.begin(); it != called_arg_list.end(); ++it){
        //     cout << it -> name << " ";
        // }
        // cout << "\n";

        if (isErrorType($1.type)) {
            $$.type = setErrorType();
        }
    }
    ;

statement
    : conditional_statement
    {
        $$.type = strdup($1.type);
    }
    | loop_statement
    {
        $$.type = strdup($1.type);
    }
    | compound_statement        // Nested statement_list
    {
        $$.type = strdup($1.type);
        $$.val = $1.val;
    }
	| expression_statement      // Expression followed by semicolon
    {
        $$.type = setVoidType();
        $$.val = $1.val;
    }
    | variable_declaration_statement
    {
        $$.type = setVoidType();
    }
    | RETURN expression_statement
    {
        if (isInsideFunc()){
            $$.type = strdup($2.type);
            $$.index = quadruples.size();
            $$.val = 1;

            function_record *func;
            symtab.search_function(active_func_name, func);

            if (!isMatch(func->function_return_type, $2.type))
                warning("'return' with a value '" + string($2.type) + "', in function returning '" + string(func->function_return_type) + "'");

            quadruples.push_back(quadruple("=", string($2.sval), "", "(funcvar)"));
        }
        else {
            errorLine("Return out of function scope");
        }
    }
    | labeled_statement
    {
        if (!insideSwitchCase)
            errorLine("Label conditions not inside switch statement");

        $$.val = $1.val;
        $$.type = strdup($1.type);
    }
    | BREAK ';'
    {
        /* Check if inside loop or switch. (to be done). */
        if (!insideLoop && !insideSwitchCase) {
            errorLine("break not inside loop or switch");
        }
        $$.index= quadruples.size();
        $$.val=1;
        quadruples.push_back(quadruple("jmp", "", "", "(loopend)"));
    }
    | CONTINUE ';'
    {
        /* Check if inside loop or switch. (to be done). */
        if (!insideLoop) {
            errorLine("continue not inside loop.");
        }
        $$.val=1;
        $$.index = quadruples.size();
        quadruples.push_back(quadruple("jmp", "", "", "(loopstart)"));
    }
	;

conditional_statement
	: if_exp statement
    {
        $$.val = $1.val + $2.val;
        int gotoindex = $1.index;
        quadruples[gotoindex]._result = to_string(gotoindex + $2.val + 1);
        $$.type = strdup($2.type);
    }
    | if_exp statement else_mark statement
    {
        $$.val = $1.val + $2.val + $3.val + $4.val;
        int gotoindex1 = $1.index;
        quadruples[gotoindex1]._result = to_string(gotoindex1 + $2.val + $3.val + 1);
        int gotoindex2 = $3.index;
        quadruples[gotoindex2]._result = to_string(gotoindex2 + $4.val + 1);

        if ( !isVoidType($2.type) )
            $$.type = strdup($2.type);
        else
            $$.type = strdup($4.type);
    }
	| SWITCHEXP statement
    {
        delete_var_list(active_func_name, level);
    	level --;

		$$.val = $1.val + $2.val;
		int startindex = $1.index;

		for (int i = startindex; i < quadruples.size(); i++) {
			if (quadruples[i]._result == "(loopend)" || quadruples[i]._result == "next_switch_case_target" + to_string(insideSwitchCase)) {
				quadruples[i]._result = to_string(startindex + $2.val + 1);
			}
		}
		$$.type = strdup($2.type);

		insideSwitchCase --;
    }
	;

SWITCHEXP
    :   SWITCH '(' expression_cover ')'
    {
        if (!isErrorType($3.type)) {
            if ( !isInt($3.type) ) {
                errorLine("int expected in expression of switch-case");
            }
        }

        $$.val = $3.val + 1;

        insideSwitchCase ++;
        level ++;

		$$.index = quadruples.size();
        string switch_result_str = "express" + to_string(insideSwitchCase);
        quadruples.push_back(quadruple("=", string($3.sval), "", switch_result_str));
    }

if_exp
    :   IF '(' expression_cover ')'
    {
        if (!isErrorType($3.type)) {
            if ( isInt($3.type) || isFloat($3.type) ) {
                $$.type = setNoErrorType();
            }
            else {
                errorLine("int expected in expression of if-else");
                $$.type = setErrorType();
            }
        }

        $$.index = quadruples.size();
        $$.val = $3.val + 1;

<<<<<<< HEAD
        quadruples.push_back(quadruple("ifF", string($3.sval), "", ""));
        // level ++;

=======
        quadruples.push_back(quadruple("=", string($3.sval), "", "expres"));
        quadruples.push_back(quadruple("ifF", "expres", "", ""));
>>>>>>> 3ce08c5540f5ea47c5d3d5ebac0b46f81482a5a7
    }

else_mark
    : ELSE
    {
        $$.val = 1;
        $$.index = quadruples.size();
        quadruples.push_back(quadruple("jmp", "", "", ""));
    }

loop_statement
    : WHILEEXP statement
    {
        delete_var_list(active_func_name, level);
        level --;

        $$.type = strdup($2.type);

        $$.val = $1.val + $2.val;
        int gotoindex = $1.index;
        //  cout<<"$1.index :"<<$1.index<<" $2.val= "<<$2.val<<endl;
        quadruples[gotoindex]._result = to_string(gotoindex + $2.val + 2);

        for(int i =gotoindex+1;i<gotoindex + $2.val + 2 && i< quadruples.size();i++ )
        {
        //string s=jmp;
        if(quadruples[i]._operator=="jmp")
        {
            quadruples[i]._result=quadruples[gotoindex]._result;
        }
        if(quadruples[i]._operator=="ctn")
        {
            quadruples[i]._result=to_string(gotoindex-1);
        }
        if((quadruples[i]._operator=="ifz"))
        {
            i=stoi(quadruples[i]._result);
        }
        }
        quadruple temp;
        temp._operator = "ljmp";
        temp._arg1 = "";
        temp._arg2 = "";
        temp._result = to_string(gotoindex-1);
        quadruples.push_back(temp);

        insideLoop --;
    }
    | FOREXP ')' statement
    {
        delete_var_list(active_func_name, level);
        level --;

        $$.type = strdup($3.type);

        $$.val = $1.val + $3.val;
        int gotoindex = $1.index;
        //  cout<<"$1.index :"<<$1.index<<" $2.val= "<<$3.val<<endl;
        quadruples[gotoindex]._result = to_string(gotoindex + $3.val + 2);

        for(int i =gotoindex+1;i<gotoindex + $3.val + 2 && i< quadruples.size();i++ )
        {
            //string s=jmp;
            if(quadruples[i]._operator=="jmp")
            {
            quadruples[i]._result=quadruples[gotoindex]._result;
            }
            if(quadruples[i]._operator=="ctn")
            {
            quadruples[i]._result=to_string(gotoindex-1);
            }
            if((quadruples[i]._operator=="ifz"))
            {
            i=stoi(quadruples[i]._result);
            }
        }
        quadruple temp;
        temp._operator = "ljmp";
        temp._arg1 = "";
        temp._arg2 = "";
        temp._result = to_string(gotoindex-1);
        quadruples.push_back(temp);

        insideLoop --;
    }
    | FOREXP expression ')' statement
    {
        delete_var_list(active_func_name, level);
        level --;

        $$.type = strdup($4.type);

        $$.val = $1.val + $2.val+$4.val;
        int gotoindex = $1.index;
        // cout<<"$1.index :"<<$1.index<<" $2.val= "<<$2.val<<endl;
        quadruples[gotoindex]._result = to_string(gotoindex + $2.val+ $4.val + 2);

        for(int i =gotoindex+1;i<gotoindex + $2.val+ $4.val + 2 && i< quadruples.size();i++ )
        {
            //string s=jmp;
            if(quadruples[i]._operator=="jmp")
            {
                quadruples[i]._result=quadruples[gotoindex]._result;
            }
            if(quadruples[i]._operator=="ctn")
            {
                quadruples[i]._result=to_string(gotoindex-1);
            }
            if((quadruples[i]._operator=="ifz"))
            {
                i=stoi(quadruples[i]._result);
            }
        }
        quadruple temp;
        temp._operator = "ljmp";
        temp._arg1 = "";
        temp._arg2 = "";
        temp._result = to_string(gotoindex-1);
        quadruples.push_back(temp);

        insideLoop --;
    }
    ;


  FOREXP
    : FOR '(' expression_statement expression_statement
    {
        insideLoop ++;

        $$.index = quadruples.size();
        $$.val = $3.val+ $4.val+1;
        quadruple temp;
        temp._operator = "ifF";
        temp._arg1 = string($4.sval);
        temp._arg2 = "";
        temp._result = "";
        quadruples.push_back(temp);
    }
    ;

  WHILEEXP
    : WHILE '(' expression_cover ')' {

        insideLoop ++;

        $$.index = quadruples.size();
        $$.val = $3.val+1;
        quadruple temp;
        temp._operator = "ifF";
        temp._arg1 = string($3.sval);
        temp._arg2 = "";
        temp._result = "";
        quadruples.push_back(temp);
        level ++;
    }
	;

labeled_statement
	: CASE_EXP statement
    {
		for (int i = $1.index; i >= 0; i--) {
			if (quadruples[i]._result == "next_switch_case_target" + to_string(insideSwitchCase)) {
				quadruples[i]._result = to_string($1.index + 1);
			}
		}
		
        $$.val = $1.val + $2.val + 1;
        int gotoindex = $1.index;
		
        quadruples[gotoindex]._result = to_string(gotoindex + $2.val + 2);
        $$.type = strdup($2.type);

        $$.index = quadruples.size();
        quadruples.push_back(quadruple("jmp", "", "", "next_switch_case_target"+to_string(insideSwitchCase)));
    }
	| DEFAULT ':' statement
    {
		for (int i = quadruples.size(); i >= 0; i--) {
			if (quadruples[i]._result == "next_switch_case_target" + to_string(insideSwitchCase)) {
				quadruples[i]._result = to_string(quadruples.size() - $3.val );
			}
		}

        $$.val = $3.val;
        $$.type = strdup($3.type);
    }
	;

CASE_EXP
    :   CASE NUM ':'
    {
        $$.index = quadruples.size() + 1;
        $$.val = $2.val + 2;

        quadruples.push_back(quadruple("==", string($2.sval), "express"+to_string(insideSwitchCase), "expres"));
        quadruples.push_back(quadruple("ifF", "expres", "", ""));

        level ++;
    }
    ;

compound_statement
	: '{' '}'
    {
        $$.val = 0;
        $$.type = setVoidType();
    }
	| '{' { level ++; } statement_list '}'
    {
        $$.val = $3.val;
        delete_var_list(active_func_name, level);
        level --;
        $$.type = strdup($3.type);
    }
	;

statement_list
	: statement
    {
        $$.val = $1.val;
        $$.type = strdup($1.type);
    }
	| statement_list statement
    {
        $$.val = $1.val + $2.val;
        if (!isVoidType($1.type))
            $$.type = strdup($1.type);
        else
            $$.type = strdup($2.type);
    }
	;

expression_statement
	: ';'
    {
        $$.val = 0;
        $$.type = setVoidType();
    }
	| expression ';'
    {
        $$.val = $1.val;
        $$.type = strdup($1.type);
    }
	;

/*
    Assignment, Logical, Relational and Arithmetic Expressions
*/
expression_cover
    : expression
    {
        $$.val = $1.val;
        $$.sval = $1.sval;
        $$.type = $1.type;
    }
    | '(' expression_cover ')'
    {
        $$.val = $2.val;
        $$.sval = $2.sval;
        $$.type = $2.type;
    }

expression
    : assignment_expression
    {
        $$.val = $1.val;
        $$.sval = $1.sval;
        $$.type = strdup($1.type);
    }
    | logical_expression
    {
        $$.val = $1.val;
        $$.sval = $1.sval;
        $$.type = setIntType();
    }
    | relational_expression
    {
        $$.val = $1.val;
        $$.sval = $1.sval;
        $$.type = setIntType();
    }
    | arithmetic_expression
    {
        $$.val = $1.val;
        $$.sval = $1.sval;
        $$.type = $1.type;
    }
    ;

assignment_expression
    : IDENTIFIER '=' arithmetic_expression
    {
        string datatype;
        bool isExists = checkForVariable($1.sval, datatype, active_func_name, level, true);

        if (!isExists) {
            errorLine("Variable '" + Variable(string($1.sval)) + "' is not declared");
            $$.type = setErrorType();
        }
        else {
            if (!isErrorType($3.type)) {

                if (isVoidType($3.type)) {
                    errorLine("void value not ignored as it ought to be");
                }
                else if (!isMatch(datatype, string($3.type))) {
                    warning("Implicit type conversion from " + string($3.type) + " to " + datatype);
                }
                $$.val = $3.val + 2;
                $$.type = strdup($3.type);
                string temp = get_next_temp();
                $$.sval = strdup(temp.c_str());
                quadruples.push_back(quadruple("=", string($3.sval), "", string($1.sval)));
                quadruples.push_back(quadruple("=", string($3.sval), "", temp));

            }
        }
    }
    | IDENTIFIER '[' NUM ']' '=' arithmetic_expression
    {
        string datatype;
        bool isExists = checkForVariable($1.sval, datatype, active_func_name, level, true);

        if (!isExists) {
            errorLine("Variable '" + Variable(string($1.sval)) + "' is not declared");
            $$.type = setErrorType();
        }
        else {
            if (!isErrorType($6.type)) {
                if (isVoidType($6.type)) {
                    errorLine("void value not ignored as it ought to be");
                }
                else if (!isMatch(datatype, string($6.type))) {
                    warning("Implicit type conversion from " + string($6.type) + " to " + datatype);
                }
                $$.val = $6.val + 2;
                $$.type = strdup($6.type);
                string temp = get_next_temp();
                $$.sval = strdup(temp.c_str());
                quadruples.push_back(quadruple("=", string($6.sval), "", string($1.sval) + "[" + string($3.sval) + "]"));
                quadruples.push_back(quadruple("=", string($6.sval), "", temp));
            }
        }
    }
    ;

logical_expression
    : expression_cover logical_operation expression_cover
    {
        $$.val = $1.val + $2.val + $3.val + 1;
        string temp = get_next_temp();
        $$.sval = strdup(temp.c_str());
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), temp));
        quadruples[$2.index]._result = to_string($2.index + $3.val + 1);
        quadruples[$2.index]._arg1 = $1.sval;
    }
    ;

logical_operation
    : OR
    {
        $$.val = 1;
        $$.index = quadruples.size();
        quadruples.push_back(quadruple("ifT", "", "", ""));
        $$.sval = strdup($1.sval);
    }
    | AND
    {
        $$.val = 1;
        $$.index = quadruples.size();
        quadruples.push_back(quadruple("ifF", "", "", ""));
        $$.sval = strdup($1.sval);
    }
    ;

relational_expression
    : expression_cover REL_OP expression_cover
    {
        $$.type = setIntType();
        $$.sval = $1.sval;
        $$.val = $1.val + $3.val + 1;
        quadruples.push_back(quadruple(string($2.sval), string($1.sval), string($3.sval), string($$.sval)));
    }
    ;

arithmetic_expression
    : arithmetic_term '+' arithmetic_expression
    {
        $$.type = $1.type;
        $$.val = $1.val + $3.val + 1;
        $$.sval = $1.sval;
        quadruples.push_back(quadruple("+", string($1.sval), string($3.sval), string($$.sval)));
    }
	| arithmetic_term '-' arithmetic_expression
    {
        $$.type = $1.type;
        $$.val = $1.val + $3.val + 1;
        $$.sval = $1.sval;
        quadruples.push_back(quadruple("-", string($1.sval), string($3.sval), string($$.sval)));
    }
	| arithmetic_term
    {
        $$.type = $1.type;
        $$.sval = $1.sval;
        $$.val = $1.val;
    }
	;

arithmetic_term
    : arithmetic_factor '*' arithmetic_term
    {
        $$.type = $1.type;
        $$.sval = $3.sval;
        $$.val = $1.val + $3.val + 1;
        quadruples.push_back(quadruple("*", string($1.sval), string($3.sval), string($$.sval)));
	}
	| arithmetic_factor '/' arithmetic_term
    {
        $$.type = $1.type;
        $$.sval = $3.sval;
        $$.val = $1.val + $3.val + 1;
        quadruples.push_back(quadruple("/", string($1.sval), string($3.sval), string($$.sval)));
    }
	| arithmetic_factor
    {
        $$.type = $1.type;
        $$.sval = $1.sval;
        $$.val = $1.val;
    }
	;

arithmetic_factor
    : '(' arithmetic_expression ')'
    {
        string temp = get_next_temp();
        $$.type = $2.type;
        $$.sval = strdup(temp.c_str());
        $$.val = $2.val + 2;
        quadruples.push_back(quadruple("assign", $$.type, "1",  temp));
        quadruples.push_back(quadruple("=", $2.sval, "",  temp));
	}
	| IDENTIFIER
    {
        string datatype;
        bool isExists = checkForVariable($1.sval, datatype, active_func_name, level, true);
        if (!isExists) {
            errorLine("Variable '" + Variable(string($1.sval)) + "' is not declared");
            $$.type = setErrorType();
        }
        else {
            $$.type = strdup(datatype.c_str());
        }

        $$.sval = $1.sval;
        $$.val = 2;

        string temp = get_next_temp();
        $$.sval = strdup(temp.c_str());

        quadruples.push_back(quadruple("assign", $$.type, "1",  temp));
        quadruples.push_back(quadruple("=", string($1.sval), "",  temp));
    }
    | NUM
    {
        $$.type = $1.type;
        $$.val = 2;

        string temp = get_next_temp();
        $$.sval = strdup(temp.c_str());

        quadruples.push_back(quadruple("assign", $$.type, "1",  temp));
        quadruples.push_back(quadruple("=", string($1.sval), "",  temp));
    }
    | function_call
    {
        $$.type = $1.type;
        string temp = get_next_temp(string($1.sval));
        $$.sval = strdup(temp.c_str());
        $$.val = $1.val + 2;

        quadruples.push_back(quadruple("assign", $$.type, "1",  temp));
        quadruples.push_back(quadruple("=", "t" + string($1.sval), "",  temp));
    }
    | IDENTIFIER '[' NUM ']'
    {
        $$.sval = $1.sval;
        $$.val = 2;

        string temp = get_next_temp();
        $$.sval = strdup(temp.c_str());

        quadruples.push_back(quadruple("assign", $$.type, "1",  temp));
        quadruples.push_back(quadruple("=", string($1.sval) + "[" + string($3.sval) + "]", "",  temp));
    }
	;

/* Variable Declarations. */
variable_declaration_statement
    : TYPE name_list ';'
    {
		$$ = $1;
        ab_symtab.patch($1.sval, $2.sval);
        vector<string> dim = makedimlist($2.sval);

        $$.val = $2.val;
        // cout << $$.val << " quads handled by declaration. \n";
	}
    ;

name_list
    : id_arr
    {
        $$.val = $1.val;
        $$.sval = $1.sval;
    }
	| id_arr ',' name_list
    {
        $$.val = $1.val;
        $$.sval=$1.sval;
        strcat($$.sval,",");
        strcat($$.sval, $3.sval);
	}
    ;

id_arr
    : IDENTIFIER
    {
        string datatype;
        bool isExists = checkForVariable($1.sval, datatype, active_func_name, level, false);
        if (!isExists) {
            variable newVar($1.sval, datatype, "0", false, dummy, active_func_name, level);
            $$.index = quadruples.size();
            $$.val = 1;
            $$.sval = $1.sval;
            quadruples.push_back(quadruple("assign", "(type)", "1", $1.sval));
            ab_symtab.insertintosymtab(newVar, $$.index);
            // cout << "Inserted into symtab : " << string($1.sval) << " ";
        }
	}
	| IDENTIFIER '=' arithmetic_expression
    {
        string datatype;
        bool isExists = checkForVariable($1.sval, datatype, active_func_name, level, false);
        if (!isExists) {
            variable newVar($1.sval, datatype, "0", false, dummy, active_func_name, level);
            $$.index = quadruples.size();
            $$.val = 2 + $3.val;
            $$.sval = $1.sval;
            quadruples.push_back(quadruple("assign", "(type)", "1", $1.sval));
            quadruples.push_back(quadruple("=", $3.sval, "", $1.sval));
            ab_symtab.insertintosymtab(newVar, $$.index);
            // cout << "Inserted into symtab : " << string($1.sval) << " ";
        }
	}
	| IDENTIFIER bracket_dimlist
    {
    	string datatype;
        vector<string> dim = makedimlist($2.sval);
        bool isExists = checkForVariable($1.sval, datatype, active_func_name, level, false);
        if (!isExists) {
            variable newVar($1.sval, datatype, "0", true, dim, active_func_name, level);
            $$.index = quadruples.size();
            $$.val = 1 + $2.val;
            $$.sval = $1.sval;
            quadruples.push_back(quadruple("assign", "(type)", "arraydim", $1.sval));
            ab_symtab.insertintosymtab(newVar, $$.index);
            // cout << "Inserted into symtab : " << string($1.sval) << " ";
        }
    }
	;

bracket_dimlist
    : '[' NUM ']'
    {
        if(string($2.type) == "float"){
            errorLine("Float cannot be passed as a dimension to an array.");
            return 1;
        }

        $$=$2;

        if(arraydimDefined){
            $$.val = 1;
            quadruples.push_back(quadruple("=", string($2.sval), "",  "arraydim"));
        } else {
            $$.val = 2;
            quadruples.push_back(quadruple("assign", "int", "1",  "arraydim"));
            quadruples.push_back(quadruple("=", string($2.sval), "",  "arraydim"));

            arraydimDefined = true;
        }

	}
	| '[' NUM ']' bracket_dimlist
    {
        if(string($2.type) == "float"){
            errorLine("Float cannot be passed as a dimension to an array.");
            return 1;
        }

        $$=$2;
        $$.val = $4.val + 1;
        $$.sval = $4.sval;

        quadruples.push_back(quadruple("*", string($2.sval), "expres", "expres"));

		strcat($$.sval,",");
		strcat($$.sval,$4.sval);
	}

%%

int main(int argc, char **argv) {

    char *filename = (char*)malloc(sizeof(char)*20);
    strcpy(filename, "input2.txt");

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

    if(!errorFound){
        cerr << "Intermediate Code in Quadruple Format:" << "\n";
        cerr << setw(3) << "" << "      " << setw(6) << "OPER" << " | " << setw(8) << "ARG1" << " | " << setw(8) << "ARG2" << " | " << setw(8) << "RESULT" << "\n";
        for(int i = 0; i < quadruples.size(); ++i){
            quadruple quad = quadruples[i];
            cerr << setw(3) << i << "      " << setw(6) << quad._operator << " | " << setw(8) << quad._arg1 << " | " << setw(8) << quad._arg2 << " | " << setw(8) << quad._result << "\n";
        }

        for(int i = 0; i < quadruples.size(); ++i){
           quadruple quad = quadruples[i];
           cout << quad._operator << "," << quad._arg1 << "," << quad._arg2 << "," << quad._result << "\n";
        }
     }

}

void yyerror(const char *s) {
    errorLine(string(s));
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
bool isVoidType(const char *type) {
    if (isMatch(type, "void"))    return true;
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
bool isVoidType(string type) {
    if (isMatch(type, "void"))    return true;
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
char* setVoidType() {
    return strdup("void");
}
char* setIntType() {
    return strdup("int");
}
bool isInsideFunc() {
    return !(active_func_name == "");
}
void reset_active_function() {
    active_func_name = "";
}
void errorLine(string errorMsg) {
    errorFound = true;
    cerr << "Error at line " << lineNo << " : " << errorMsg << endl;
}
void warning(string warningMsg) {
    cerr << "Warning at line " << lineNo << " : " << warningMsg << endl;
}
bool isVariableInSymtab(string varname) {
    if(ab_symtab.search(varname) == -1)
        return false;
    else
        return true;
}
// If flag = false : check for case like ----- int a = 3;
// If flag = true : check for case like  ----- a = 3;
// Return false if error
// else return true
bool checkForVariable(string var_name, string &datatype, string active_func, int cur_level, bool flag) {

    if (!flag) {
        function_record *r;
        bool varExists = false;

        // Check if variable is already declared
        int cur_level_of_var;
        if (ab_symtab.search_var(var_name, cur_level_of_var, active_func, datatype)) {
            if (cur_level_of_var == cur_level) {
                varExists = true;
                errorLine("Variable already declared in same scope : " + Variable(string(var_name)));
                return varExists;
            }
        }
        if (cur_level == 2) {
            function_record *func;
            var_record *r;
            if ( symtab.search_function(active_func, func) ) {
                if(func->search_param(var_name, r)) {
                    varExists = true;
                    errorLine("Redeclaration of parameter '" + Variable(string(var_name)) + "' as variable" );
                    return varExists;
                }
            }
        }

        return varExists;
    }
    else {
    // If flag = true : check for case like  ----- a = 3;
    // Variable should be declared somewhere

        function_record *r;
        bool varExists = false;
        bool found = false;

        // Check if variable is already declared as a variable (either global or local within a function)
        int cur_level_of_var;
        if (ab_symtab.search_var(var_name, cur_level_of_var, active_func, datatype)) {
            found = true;
            if (cur_level_of_var == cur_level) {
                varExists = true;
                // Variable already declared in same scope
                return varExists;
            }
        }
        if (found) {
            // If the variable is not global
            if (cur_level_of_var > 0)
                return true;
        }

        // Now, either variable is not declared, or declared in parameters or declared in global scope
        {
            function_record *func;
            var_record *r;
            if ( symtab.search_function(active_func, func) ) {
                if(func->search_param(var_name, r)) {
                    varExists = true;
                    // "Declared as parameter"
                    datatype = r->type;
                    return varExists;
                }
            }
            else if (found) {
                return true;
            }
        }

        if (!varExists) {
            // errorLine("Variable : " + var_name + " is not declared");
            return false;
        }
    }
}
void delete_var_list(string function_name, int level) {
    ab_symtab.delete_var_from_level(function_name, level);
}
bool isCompatible(string type1, string type2) {
    return true;
    cout << type1 << " " << type2 << endl;
    if (type1 == type2)
        return true;
    if ( type1 == "float" && type2 == "int" )
        return true;
    if ( type2 == "float" && type1 == "int" )
        return true;
    return false;
}
string Variable(string str) {
    if (str == "")
        return "";
    return str.substr(1);
}
