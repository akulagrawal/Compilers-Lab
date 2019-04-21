%{
    #include <bits/stdc++.h>
    #include <string>
    
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
        char* type;
        int len;
        char* sval;
    } type_id;
}

%expect 1       // 1. if-else

// Non Terminals
%type <type_id> statement statement_list
%type <type_id> labeled_statement compound_statement expression_statement conditional_statement loop_statement
%type <type_id> expression
%type <type_id> constant_expression logical_expression relational_expression assignment_expression
%type <type_id> START
%type <type_id> function_declaration function_head
%type <type_id> param_list_declaration param_declaration
%type <type_id> function_call arg_list
%type <type_id> variable_declaration_list variable_declaration

// Terminals
%token <type_id> NUM IDENTIFIER
%token <type_id> TYPE VOID
%token <type_id> OR
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

variable_declaration_list
    : variable_declaration
    ;

variable_declaration
    : TYPE IDENTIFIER ';'       {}
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
	| expression_statement      // Expression followed by semicolon
    | variable_declaration_list
    | function_call
	;

conditional_statement
	: IF '(' expression ')' statement 
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
    | IF '(' expression ')' statement ELSE statement
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
	: '{' '}'                       {}
	| '{' statement_list '}'        {}
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'                           { $$.type = strdup("NoneType"); }
	| expression ';'                { $$.type = strdup($1.type); }
	;

/*
 Expecting: Logical & Relational and Arithmetic expression
*/
expression
    : assignment_expression         { $$.type = strdup($1.type); }
    | logical_expression            { $$.type = strdup("int"); }
    | relational_expression         { $$.type = strdup("int"); }
    ; 

assignment_expression
    : IDENTIFIER '=' NUM            { $$.type = strdup($3.type); }
    | IDENTIFIER '=' IDENTIFIER     { $$.type = strdup($1.type); }
    ; 

logical_expression
    : IDENTIFIER OR IDENTIFIER
    | NUM OR IDENTIFIER
    | IDENTIFIER OR NUM
    | NUM OR NUM
    ;

relational_expression
    : IDENTIFIER '>' IDENTIFIER
    | NUM '>' IDENTIFIER
    | IDENTIFIER '>' NUM
    | NUM '>' NUM
    ;

constant_expression
    : NUM                           { $$.type = strdup("num"); }
    ; 
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