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

        function_record& insert_function(string function_name) {
            assert(!entries.count(function_name));
            return entries[function_name]; 
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

    // Stores true, If error is found while semantic checking
    bool errorFound = false;

    // Keep track of current line number
    int lineNo = 1;

    extern bool isInt(char *type);
    extern bool isFloat(char *type);
    extern bool isBoolean(char *type);
    extern bool isErrorType(char *type);
    extern bool isNoneType(char *type);
    extern bool isMatch(const char *str1, const char *str2);
    extern char* setErrorType();
    extern char* setNoErrorType();
%}

%union {
    struct {
        char* type;
        double val;
        char* sval;
    } type_id;
}

%expect 1

// Non Terminals
%type <type_id> statement statement_list
%type <type_id> labeled_statement compound_statement expression_statement conditional_statement loop_statement
%type <type_id> expression
%type <type_id> constant_expression logical_expression relational_expression assignment_expression
%type <type_id> START
%type <type_id> function_declaration function_head func_name
%type <type_id> param_list_declaration param_declaration
%type <type_id> function_call arg_list
%type <type_id> variable_declaration_list variable_declaration
%type <type_id> datatype

// Terminals
%token <type_id> NUM IDENTIFIER
%token <type_id> INT FLOAT
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
        active_func_name = "";
        if (!isErrorType($1.type)) {
            if (!(isMatch($1.type, $3.type) || isMatch($1.type, "void") && isNoneType($3.type)))
                cout << "Type mismatch of return type between " << $$.type << " and " << $3.type << endl;
        }
    }
	| function_head '{' '}'
    {
        active_func_name = "";
    }
	;

function_head
    : datatype func_name '(' param_list_declaration ')'
    {
        level ++;
        function_record r;

        // Check if function already exists
        if (symtab.search_function($2.sval, &r)) {
            cout << "Error : Redeclaration of function : " << $2.sval << " in line : " << lineNo << endl;
        }
        else {
            r = symtab.insert_function($2.sval);
            r.function_return_type = $1.sval;
            active_func_name = $2.sval;

            // Add param_list_declaration to symbol_table corresponding to active function
            if ( !isErrorType($4.type) ) {
                for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
                    r.insert_parameter(it->name, it->type, it->level);
                }
                $$.type = strdup($1.sval);
            }
        }
    }
    | datatype func_name '(' ')'
    {
        level ++;
        function_record r;

        // Check if function already exists
        if (symtab.search_function($2.sval, &r)) {
            cout << "Error : Redeclaration of function : " << $2.sval << " in line : " << lineNo << endl;
        }
        else {
            r = symtab.insert_function($2.sval);
            r.function_return_type = $1.sval;
            active_func_name = $2.sval;
            $$.type = strdup($1.sval);
        }
    }
    ;

func_name
    : IDENTIFIER                    { $$.sval = strdup($1.sval); }
    ;

param_list_declaration
    : param_list_declaration ',' param_declaration
    {
        if (!isErrorType($1.type)) {
            bool found = false;
            // Check if variable is repeated in parameter list
            for (auto it = active_func_param_list.begin(); it != active_func_param_list.end(); it++) {
                if (it -> name == $3.sval) {
                    cout << "Redeclaration of parameter " << $3.sval << endl;
                    $1.type = setErrorType();
                    $$.type = setErrorType();
                    found = true;
                    break;
                }
            }
            if (!found) {
                var_record param($3.sval, $3.type, /* is_parameter = */ true, level) ;
                active_func_param_list.push_back(param);
            }
        }
        else
            $$.type = setErrorType();
    }
    | param_declaration             
    { 
        var_record param($1.sval, $1.type, /* is_parameter = */ true, level) ;
        active_func_param_list.push_back(param);
    }
    ;

param_declaration
    : datatype IDENTIFIER           { $$.type = $1.sval; $$.sval = $2.sval; }
    ;

variable_declaration_list
    : variable_declaration
    ;

variable_declaration
    : datatype IDENTIFIER ';'       {}
    ;

datatype
    : INT                           { $$.sval = strdup("int"); }
    | FLOAT                         { $$.sval = strdup("float"); }
    ;

function_call
    : IDENTIFIER '(' ')' ';'
    | IDENTIFIER '(' arg_list ')' ';'
    | datatype IDENTIFIER '=' IDENTIFIER '(' ')' ';'
    | datatype IDENTIFIER '=' IDENTIFIER '(' arg_list ')' ';'
    ;

arg_list
    : IDENTIFIER
    | arg_list ',' IDENTIFIER
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
	: ';'                           { $$.type = strdup("None"); }
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
        print("I can't open ", filename);
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

bool isInt(char *type) {
    if (isMatch(type, "int"))    return true;
    else                        return false;
}
bool isFloat(char *type) {
    if (isMatch(type, "float"))    return true;
    else                        return false;
}
bool isBoolean(char *type) {
    if (isMatch(type, "bool"))    return true;
    else                        return false;
}
bool isErrorType(char *type) {
    if (isMatch(type, "ErrorType"))    return true;
    else                        return false;
}
bool isNoneType(char *type) {
    if (isMatch(type, "None"))    return true;
    else                        return false;
}
char* setErrorType() {
    errorFound = true;
    return strdup("ErrorType");
}
char* setNoErrorType() {
    return strdup("NoErrorType");
}
bool isMatch(const char *str1, const char *str2) {
    return !strcmp(str1, str2);
}