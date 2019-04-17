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
        vector<var_record> parameters;
        vector<var_record> local_variables;

        void insert_parameter(string parameter_name, string type){
            parameters.push_back(var_record(parameter_name, type));
        }

        void insert_variable(string var_name, string type, int level){
            local_variables.push_back(var_record(var_name, type, false, level));
        }

        var_record& search_param(string parameter_name) {
            for(int i = 0; i < parameters.size(); ++i){
                if(parameters[i].name == parameter_name){
                    return parameters[i];
                }
            }
        }

        var_record& search_variable(string var_name) {
            for(int i = 0; i < local_variables.size(); ++i){
                if(local_variables[i].name == var_name){
                    return local_variables[i];
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

    } symtab;
%}

%union {
    struct {
        char* type;
        double val;
        char* sval;
    } type_id;
}

%expect 1

// Define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the %union:
%type <type_id> statement
%type <type_id> labeled_statement
%type <type_id> compound_statement
%type <type_id> expression_statement
%type <type_id> selection_statement
%type <type_id> iteration_statement
%type <type_id> expression
%type <type_id> constant_expression
%type <type_id> logical_expression
%type <type_id> relational_expression
%type <type_id> assignment_expression

%token <type_id> NUM
%token <type_id> IDENTIFIER

%token <type_id> OR

%token <type_id> IF
%token <type_id> ELSE

%token <type_id> FOR

%token <type_id> WHILE
%token <type_id> DO

%token <type_id> SWITCH
%token <type_id> CASE
%token <type_id> DEFAULT

%%
statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	;

selection_statement
	: IF '(' expression ')' statement 
    { 
        if (strcmp($3.type, "num")) {
            yyerror("Invalid expression type");
        }
    }
    | IF '(' expression ')' statement ELSE statement
    {
        if (strcmp($3.type, "num")) {
        yyerror("Invalid expression type");
        }
    }
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement 
    { 
        if (strcmp($3.type, "num")) {
            yyerror("Invalid expression type");
        }
    }
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

labeled_statement
	: CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

/*
 Expecting: Logical & Relational and Arithmetic expression
*/
expression
    : assignment_expression         { strcpy($$.type, $1.type); }
    | logical_expression            { $$.type = strdup("num"); }
    | relational_expression         { $$.type = strdup("num"); }
    ; 

assignment_expression
    : IDENTIFIER '=' NUM            { strcpy($$.type, $3.type); }
    | IDENTIFIER '=' IDENTIFIER     { strcpy($$.type, $1.type); }
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
    : NUM
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