%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #define print(str, val) \
    printf("%s %s\n", str, val);
    #define TRUE 1
    #define FALSE 0

    #define NUMBER 1
    #define STRING 0

    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
    extern void eat_till_semi();

    void yyerror(const char *s);

    extern void insert_header (FILE *filename);
    extern void insert_footer (FILE *filename);
    extern void extract_column ();

    char schema[1024];
    char column_str[1024];
    char column[30][30];
    int num_column = 0;
    int position = 0;
    char condition[100][50];
    int condition_ptr = 0;
    // --------------------------------------------------------------------

    #define MAX_COLS 10
    #define MAX_COL_LEN 10
    #define MAX_FILES 10
    #define MAX_FILES_LEN 10

    char data_type[MAX_FILES][MAX_COLS];
    char col_name[MAX_FILES][MAX_COLS][MAX_COL_LEN];
    char file_name[MAX_FILES][MAX_FILES_LEN];
    int num_files = 0;
    extern int gettype(char* table_name, char* col);
    extern int getcolindex(int index, char* col);
    extern int getfileindex(char* name);
    extern void readcsv(int index, char* name);
    extern int isnum(char *);
    
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  Initially (by default), yystype
// is merely a typedef of "int", but for non-trivial projects, tokens could
// be of any arbitrary data type.  So, to deal with that, the idea is to
// override yystype's default typedef to be a C union instead.  Unions can
// hold all of the types of tokens that Flex could return, and this this means
// we can return ints or floats or strings cleanly.  Bison implements this
// mechanism with the %union directive:
%union {
    int ival;
    float fval;
    char *sval;
}

// Define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the %union:
%token <sval> SELECT
%token <sval> PROJECT
%token <sval> CARTESIAN_PRODUCT
%token <sval> EQUI_JOIN
%token <sval> AND
%token <sval> LT_EQ
%token <sval> EQ
%token <sval> NEQ
%token <sval> LP
%token <sval> RP
%token <sval> LAB
%token <sval> RAB
%token <sval> SIC
%token <sval> DIC
%token <sval> COMMA
%token <sval> SEMI
%token <sval> NUM
%token <sval> ID
%token <sval> DOT
%token <sval> MINUS
%token <sval> ARITH_OP

%type <sval> STMT_LIST
%type <sval> STMT
%type <sval> EXPR
%type <sval> TABLE
%type <sval> CONDITION
%type <sval> CONDITION_LIST_FINAL
%type <sval> CONDITION_LIST
%type <sval> LOGICAL_OP
%type <sval> OP
%type <sval> ARITHMETIC
%type <sval> ATTR_LIST
%type <sval> ATTR

%%

STMT_LIST:    STMT
    |         STMT STMT_LIST    ;

STMT:   SELECT LAB CONDITION_LIST_FINAL RAB LP TABLE RP SEMI    {

            int condition_it = 0;
            // for (condition_it = 0; condition_it < condition_ptr; condition_it++) {
            //     printf("*%s*\n", condition[condition_it]);
            // }

            // Check syntax
            printf("Valid Syntax \n");

            char filename[50];
            strcpy(filename, $6);
            strcat(filename, ".csv");
            readcsv(num_files, filename);

            FILE *file_in = fopen("intermediate.cpp", "w+");
            insert_header(file_in);

            // Set if conditions to filter the rows
            // Get the condition
            char condition_str[1024];
            strcpy(condition_str, $3);

            // printf("Condition = %s\n", condition_str);

            // Open the file in which table exists
            fprintf(file_in, "\ttableName = \"%s\";\n", $6);
            fprintf(file_in, "\treadcsv(tableName+\".csv\", 0);\n");
            // fprintf(file_in, "\tprintColumnNames();\n");
            // Iterate over each row of table
            fprintf(file_in, "\tfor(int j = 0; j < getNumRows(tableName); j++) {\n");

                // Put if condition_str
                fprintf(file_in, "\t\tif (");

                // Iterate over condition and check data type with schema
                for (condition_it = 0; condition_it < condition_ptr; condition_it++) {
                    // Get column name
                    char *columnName = condition[condition_it++];
                    char *operator = condition[condition_it++];
                    char *rhs = condition[condition_it++];

                    // Both number
                    if (gettype($6, columnName) == NUMBER && isnum(rhs) == TRUE) {
                        fprintf(file_in, "stoi(getVal(0, j, \"%s\")) %s %s ", columnName, operator, rhs);
                    }
                    // Both string
                    else if (gettype($6, columnName) == STRING && isnum(rhs) == FALSE) {
                        if (!strcmp(operator, "=="))
                            fprintf(file_in, "getVal(0, j, \"%s\") %s %s ", columnName, operator, rhs);
                        else {
                            printf("Operator unsupported for condition %s %s %s", columnName, operator, rhs);
                            exit(0);
                        }    
                    }
                    else {
                        printf("gettype(%s) = %d\n", "name", gettype($6, "name"));
                        printf("Datatype mismatch in Schema for condition %s %s %s", columnName, operator, rhs);
                        exit(0);
                    }

                    if (condition_it < condition_ptr) {
                        char *and_or_op = condition[condition_it];
                        fprintf(file_in, " %s ", and_or_op);
                    }
                }
                // Put if condition_str
                fprintf(file_in, ") {\n");

                    fprintf(file_in, "\t\t\tprintRow(0, j);\n");

            fprintf(file_in, "\t\t}\n");
            fprintf(file_in, "\t}\n");

            insert_footer(file_in);
            fclose(file_in);
        }
    |   PROJECT LAB ATTR_LIST RAB LP TABLE RP SEMI     {
            printf("Valid Syntax \n");
            int i = 0;
            for (i = 0; i < position; i++) {
                printf("%s ,", column[i]);
            }

            FILE *file_in = fopen("intermediate.cpp", "w+");
            insert_header(file_in);

            // Construct vector of columnNames
            fprintf(file_in, "\tvector<string> columnNames;\n");
            
            for (i = 0; i < position; i++) {
                fprintf(file_in, "\tcolumnNames.push_back(\"%s\");\n", column[i]);
            }

            fprintf(file_in, "\tprintColumns(columnNames);\n");

            insert_footer(file_in);
            fclose(file_in);
        }
    |   LP TABLE RP JOIN LP TABLE RP SEMI   {
           printf("Valid Syntax \n");
        }
    |   error SEMI  {
           yyerrok;
           eat_till_semi();
        }    ;

JOIN:    CARTESIAN_PRODUCT
    |    EQUI_JOIN LAB CONDITION_LIST_EQ RAB    ;

TABLE:   ID    ;

CONDITION_LIST_FINAL:   CONDITION_LIST ;

CONDITION_LIST: CONDITION LOGICAL_OP CONDITION_LIST     { 
                    strcat($$, " "); 
                    strcat($$, $2); 
                    strcat($$, " "); 
                    strcat($$, $3); 
                } 
    |           CONDITION   ;

LOGICAL_OP:     AND {
                    strcpy(condition[condition_ptr++], $1);
                };
    

CONDITION:      LP CONDITION_LIST RP { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |           ID OP EXPR  { 
                    strcpy(condition[condition_ptr++], $1);
                    strcpy(condition[condition_ptr++], $2);
                    strcpy(condition[condition_ptr++], $3);
                    
                    } ;
    
CONDITION_LIST_EQ: CONDITION_EQ AND CONDITION_LIST_EQ
    |           CONDITION_EQ

CONDITION_EQ:      LP CONDITION_LIST_EQ RP
    |              ID DOT ID EQ ID DOT ID    ;

EXPR:   ARITHMETIC
    |   DIC ID DIC  { strcat($$, $2); strcat($$, $3); strcat($$, " "); } 
    |   DIC NUM DIC { strcat($$, $2); strcat($$, $3); strcat($$, " "); } ;

ARITHMETIC: NUM ARITH_OP ARITHMETIC  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |   NUM MINUS ARITHMETIC  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } 
    |   NUM  ;

OP:     EQ { strcat($$, $1); }
    |   NEQ
    |   LAB
    |   RAB
    |   LT_EQ    ;

ATTR_LIST:    ATTR COMMA ATTR_LIST   
    |         ATTR  ;

ATTR:   ID {
        strcpy(column[position], $1);
        position++;
    } ;
%%

int main(int argc, char **argv) {

    char *filename = "tests/test1.txt";
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
  print("Invalid syntax ", s);
  // might as well halt now:
//   printf("Invalid Syntax\n");
//   exit(-1);
}

void eat_till_semi()
{
    int c;
    while((c = (char)fgetc(yyin)) != EOF && c != ';')
        printf("s");
}

void insert_header (FILE *filename) {
    char *header = "#include <bits/stdc++.h>\nusing namespace std;\n\nstring tableName;\n";
    fprintf(filename, "%s", header);

    FILE *fp = fopen("readcsv.cpp", "r");
    int c;
    while((c = (char)fgetc(fp)) != EOF)
        fprintf(filename, "%c", (char)c);
    fclose(fp);

    fprintf(filename, "\nint main () {\n");
}

void insert_footer (FILE *filename) {
    char *header = "return 0;\n}\n";

    fprintf(filename, "%s", header);
}

void extract_column(char *table) {
    // Get the Schema and column name from the table
    // Assuming schema in 1st row and column name in 2nd row
    FILE *f_in = fopen(strcat(table, ".txt"), "r");

    fgets(schema, sizeof(schema), f_in);
    fgets(column_str, sizeof(column_str), f_in);
    printf("%s\n", schema);
    printf("%s\n", column_str);
    
    // Extract column name from column_str
    int i = 0;
    int begin = 0;
    int end = -1;
    int j = 0;
    int k = 0;
    for (i = 0; i < strlen(column_str); i++) {
        if (column_str[i] == ',') {
            end = i;
            for (k = begin; k < end; k++) {
                column[j][k-begin] = column_str[k];
            }
            column[j][k-begin] = '\0';
            j++;
            begin = i+1;
        }
    }
    num_column = j;
}

void readcsv(int index, char* name)
{
	//name of the file pushed
	int name_len = strlen(name);
	for (int i = 0; i < name_len-4; ++i)
	{
		file_name[index][i] = name[i];
	}

	FILE* stream = fopen(name, "r");
	char type_line[1024];
	int itr;
	
	if(fgets(type_line, 1024, stream))
	{
        int len = strlen(type_line);
   		// printf("%s\n", type_line);
   		int i=0;
	}

	char name_line[1024];
	if(fgets(name_line, 1024, stream))
	{
   		// printf("%s\n", name_line);
   		int i=0;
	}


	int top=0;
    int len = strlen(name_line);
    int j=0;
	for (int i = 0; i < len; ++i)
	{
		if(name_line[i] != ',' && name_line[i] != '\n')
		{
			col_name[index][top][j++] = name_line[i];
		}
		else
		{
			j = 0;
			top++;
		}	
	}
		
	top = 0;
    len = strlen(type_line);
    for (int i = 0; i < len; ++i)
	{
		if(type_line[i] != ',' && type_line[i] != '\n')
		{
			data_type[index][top] = type_line[i];
		}
		else
		{
			top++;
		}	
	}
	num_files++;
}

int getfileindex(char* name)
{
    // printf ("name = *%s*\n", name);
	for (int i = 0; i < MAX_FILES; ++i)
	{
		if(strcmp(file_name[i], name)==0)
		{
            // printf ("filenames = *%s*\n", file_name[i]); 
			return i;
		}
	}
	return -1;
}

int getcolindex(int index, char* col)
{
	for (int i = 0; i < MAX_COLS; ++i)
	{
		if(strcmp(col_name[index][i], col) == 0)
		{
			return i;
		}
	}
	return -1;
}

//returns 0 for string 1 for int
int gettype(char* table_name, char* col)
{
	int index = getfileindex(table_name);
	if(index == -1)
	{
		printf("No such Table loaded.\n");
		return -1;
	}

	int colindex = getcolindex(index, col);
	if(colindex == -1)
	{
        // printf("Here is the problem\n");
        printf("column name = %s\n", col);
		printf("No such column exists.\n");
		exit(0);
	}	

	if(data_type[index][colindex] == 'i')
	{
		return 1;
	}
	return 0;
}

int isnum (char *text) {
    int i = 0;
    if (text[0] == '"')
        return 0;
    else
        return 1;
}