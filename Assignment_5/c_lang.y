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

    extern bool isInt(char *type);
    extern bool isFloat(char *type);
    extern bool isBoolean(char *type);
    extern bool isErrorType(char *type);
    extern bool isNoneType(char *type);
    extern char* setErrorType();
    extern char* setNoErrorType();

    /* Intermediate Code Generation. */
    /* Quadruples. */
    struct quadruple {
        string _operator;
        string _arg1;
        string _arg2;
        string _result;

        quadruple(){}

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
%}

%union {
    struct {
        struct indexlist * indexlist;
        char* type;
        int val;
        int index;
        char* sval;
    } type_id;
}

%expect 2

// Non Terminals
%type <type_id> statement statement_list
%type <type_id> labeled_statement compound_statement expression_statement conditional_statement
%type <type_id>  loop_statement loopstatement looplabeled_statement loopcompound_statement loopstatement_list loopconditional_statement
%type <type_id> expression
%type <type_id> constant_expression logical_expression relational_expression assignment_expression
%type <type_id> START
%type <type_id> logical_operation
%type <type_id> function_declaration function_head return_type func_name
%type <type_id> param_list_declaration param_declaration
%type <type_id> function_call arg_list
%type <type_id> variable_declaration_list variable_declaration
%type <type_id> datatype
%type <type_id> FOREXP WHILEEXP if_exp else_mark

// Terminals
%token <type_id> NUM IDENTIFIER
%token <type_id> INT FLOAT
%token <type_id> OR
%token <type_id> IF ELSE
%token <type_id> FOR WHILE
%token <type_id> SWITCH CASE DEFAULT
%token <type_id> BREAK CONTINUE
%token <type_id> AND
%token <type_id> REL_OP

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
	| function_head '{' '}'
	;

function_head
    : datatype func_name '(' param_list_declaration ')'
    | datatype func_name '(' ')'
    ;

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

    loopstatement
        : loopconditional_statement
        | loop_statement
        | loopcompound_statement        // Nested statement_list
        {
            $$.val = $1.val;
        }
        | expression_statement      // Expression followed by semicolon
        {
            $$.val = $1.val;
        }
        | variable_declaration_list
        | function_call
        | BREAK ';' {
            $$.index= quadruples.size();
            $$.val=1;

            quadruple temp;
            temp._operator = "jmp";
            temp._arg1 = "";
            temp._arg2 = "";
            temp._result = "";
            quadruples.push_back(temp);
        }
        |CONTINUE ';' {
            $$.val=1;
            quadruple temp;
            temp._operator = "ctn";
            temp._arg1 = "";
            temp._arg2 = "";
            temp._result = "";
            quadruples.push_back(temp);
        }
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
  	| SWITCH '(' expression ')' labeled_statement
      {
          if (strcmp($3.type, "num")) {
              yyerror("int or boolean expected in expression of switch case");
          }

      }
  	;

  loopconditional_statement
    	: if_exp  loopstatement
        {
            $$.val = $1.val + $2.val;
            int gotoindex = $1.index;
            quadruples[gotoindex]._result = to_string(gotoindex + $2.val + 1);

        }
        | if_exp loopstatement else_mark loopstatement
        {
            $$.val = $1.val + $2.val + $3.val + $4.val;
            int gotoindex1 = $1.index;
            quadruples[gotoindex1]._result = to_string(gotoindex1 + $2.val + $3.val + 1);
            int gotoindex2 = $3.index;
            quadruples[gotoindex2]._result = to_string(gotoindex2 + $4.val + 1);
        }
    	| SWITCH '(' expression ')' looplabeled_statement
        {
            if (strcmp($3.type, "num")) {
                yyerror("int or boolean expected in expression of switch case");
            }

        }
    	;

  if_exp
      :   IF '(' expression ')'
      {
          if (strcmp($3.type, "num")) {
              yyerror("int or boolean expected in expression of if-else");
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
      	: WHILEEXP loopstatement
        {

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

        }
      	| FOREXP ')' loopstatement
        {
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
        }
          | FOREXP expression ')' loopstatement
          {
            $$.val = $1.val + $2.val+$4.val;
              int gotoindex = $1.index;
              cout<<"$1.index :"<<$1.index<<" $2.val= "<<$2.val<<endl;
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
          }
      	;


  FOREXP
          : FOR '(' expression_statement expression_statement {
              if (strcmp($4.type, "num") && strcmp($4.type, "None")) {
                  yyerror("Type error in condition of for loop");
              }
              $$.index = quadruples.size();
              $$.val = $3.val+ $4.val+1;
              quadruple temp;
              temp._operator = "ifz";
              temp._arg1 = "expres";
              temp._arg2 = "";
              temp._result = "";
              quadruples.push_back(temp);
          }
          ;

  WHILEEXP
          : WHILE '(' expression ')' {
              if (strcmp($3.type, "num")) {
                  yyerror("int or boolean expected in expression of while statement");
              }
              $$.index = quadruples.size();
              $$.val = $3.val+1;
              quadruple temp;
              temp._operator = "ifz";
              temp._arg1 = "expres";
              temp._arg2 = "";
              temp._result = "";
              quadruples.push_back(temp);
          }

labeled_statement
	: CASE constant_expression ':' statement {
        if (strcmp($2.type, "int")) {
            yyerror("int expected in switch case");
        }
    }
	| DEFAULT ':' statement
	;

looplabeled_statement
  	: CASE constant_expression ':' loopstatement {
          if (strcmp($2.type, "int")) {
              yyerror("int expected in switch case");
          }
      }
  	| DEFAULT ':' loopstatement
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

  loopcompound_statement
      : '{' '}'
      {
          $$.val = 0;
      }
      | '{' loopstatement_list '}'
      {
          $$.val = $2.val;
      }
      ;

  loopstatement_list
      :   loopstatement
      {
          $$.val = $1.val;
      }
      |   loopstatement_list loopstatement
      {
          $$.val = $1.val + $2.val;
      }
      ;



expression_statement
	: ';'
    {
        $$.val = 0;
        $$.type = strdup("None");
    }
	| expression ';'
    {
        $$.val = $1.val;
        $$.type = strdup($1.type);
    }
	;

/*
 Expecting: Logical & Relational and Arithmetic expression
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
        $$.type = strdup("num");
    }
    | relational_expression
    {
        $$.val = $1.val;
        $$.type = strdup("num");
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

bool isInt(char *type) {
    if (strcmp(type, "int"))    return false;
    else                        return true;
}
bool isFloat(char *type) {
    if (strcmp(type, "float"))    return false;
    else                        return true;
}
bool isBoolean(char *type) {
    if (strcmp(type, "bool"))    return false;
    else                        return true;
}
bool isErrorType(char *type) {
    if (strcmp(type, "ErrorType"))    return false;
    else                        return true;
}
bool isNoneType(char *type) {
    if (strcmp(type, "None"))    return false;
    else                        return true;
}
char* setErrorType() {
    return strdup("ErrorType");
}
char* setNoErrorType() {
    return strdup("NoErrorType");
}
  // might as well halt now:
//   printf("Invalid Syntax\n");
//   exit(-1);
