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

    // Stores active function name
    string active_func_name;

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

        void insert_parameter(string parameter_name, string type){
            parameters.push_back(var_record(parameter_name, type));
        }

        void insert_variable(string var_name, string type, int level){
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

        bool search_function(string function_name, function_record& function) {
            // If function exists in symbol table
            if (entries.count(function_name)) {
                // Set function = pointer to function in symbol table
                // Returns true
                function = entries[function_name];
                return true;
            }
            else {
                // If not found returns not found (i.e. false)
                return false;
            }
        }

    } symtab;


    struct quadruple {
        char _operator;
        char _arg1[2];
        char _arg2[2];
        char _result[2];
        quadruple * _nextquad;

        quadruple(char op, char * arg1, char * arg2, char * result){
            this -> _operator = op;
            for(int i = 0; i < 2; ++i){
                this -> _arg1[i] = arg1[i];
                this -> _arg2[i] = arg2[i];
                this -> _result[i] = result[i];
            }
            this -> _nextquad = NULL;
        }
    };

    vector<quadruple> quadruples;

    struct indexlist {
        int a
    };
%}

%union {
    struct {
        indexlist * indexlist;
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
%type <type_id> function_declaration function_head return_type func_name
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
	: function_head '{' variable_declaration_list statement_list '}'
	;

function_head
    : return_type func_name '(' param_list_declaration ')'
    ;

return_type
    : IDENTIFIER    ;

func_name
    : IDENTIFIER
    ;

param_list_declaration
    : param_list_declaration ',' param_declaration
    | param_declaration
    ;

param_declaration
    : datatype IDENTIFIER
    ;

variable_declaration_list
    : variable_declaration
    ;

variable_declaration
    : datatype IDENTIFIER ';'       {}
    ;

datatype
    : INT                           { $$.type = strdup("int"); }
    | FLOAT                         { $$.type = strdup("float"); }
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
	| labeled_statement
	| compound_statement        // Nested statement_list
	| expression_statement      // Expression followed by semicolon
    | variable_declaration_list
    | function_call
	;

selection_statement
	:  if_exp  statement
    {
        if (strcmp($3.type, "num")) {
            yyerror("int or boolean expected in expression of if-else");
        }
    }
    | if_exp statement ELSE statement
    {
        if (strcmp($3.type, "num")) {
            yyerror("int or boolean expected in expression of if-else");
        }
    }
	| SWITCH '(' expression ')' statement
    {
        if (strcmp($3.type, "num")) {
            yyerror("int or boolean expected in expression of switch case");
        }
    }
	;

if_exp
    :   IF '(' expression ')'
    {

    }

iteration_statement
	: WHILE '(' expression ')' statement
    {
        if (strcmp($3.type, "num")) {
            yyerror("int or boolean expected in expression of while statement");
        }
    }
	| FOR '(' expression_statement expression_statement ')' statement
    {
        if (strcmp($4.type, "num") && strcmp($4.type, "None")) {
            yyerror("Type error in condition of for loop");
        }
    }
	| FOR '(' expression_statement expression_statement expression ')' statement
    {
        if (strcmp($4.type, "num") && strcmp($4.type, "None")) {
            yyerror("Type error in condition of for loop");
        }
    }
	;

labeled_statement
	: CASE constant_expression ':' statement {
        if (strcmp($2.type, "int")) {
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
    | logical_expression            { $$.type = strdup("num"); }
    | relational_expression         { $$.type = strdup("num"); }
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
  // might as well halt now:
//   printf("Invalid Syntax\n");
//   exit(-1);
}
