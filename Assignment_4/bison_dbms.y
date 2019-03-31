%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #define print(str, val) \
    printf("%s %s\n", str, val);

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
%type <sval> OP
%type <sval> TERM
%type <sval> ATTR_LIST
%type <sval> ATTR

%%

STMT_LIST:    STMT
    |         STMT STMT_LIST    ;

STMT:   SELECT LAB CONDITION_LIST_FINAL RAB LP TABLE RP SEMI    {

            printf("Valid Syntax \n");

            FILE *file_in = fopen("intermediate.cpp", "w+");
            insert_header(file_in);

            // Set if conditions to filter the rows
            // Get the condition
            char condition[1024];
            strcpy(condition, $3);

            // printf("Condition = %s\n", condition);

            // Open the file in which table exists
            fprintf(file_in, "\ttableName = \"%s\";\n", $6);
            fprintf(file_in, "\treadcsv(tableName+\".csv\", 0);\n");
            // fprintf(file_in, "\tprintColumnNames();\n");
            // Iterate over each row of table
            fprintf(file_in, "\tfor(int j = 0; j < getNumRows(tableName); j++) {\n");

                // Put if condition
                fprintf(file_in, "\t\tif (%s) {\n", condition);

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

            fprintf(file_in, "\tfor(int i = 0; i < getNumRows(a);i++){\n");
            fprintf(file_in, "\t\tfor(int k = 0; k < columnNames.size();k++)\n");
            fprintf(file_in, "\t\t\tcout<<getVal(0,i, columnNames[k])<<\" \";\n");
            fprintf(file_in, "\t\tcout<<\"\\n\";\n\t}\n");

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

JOIN:    CARTESIAN_PRODUCT {
            FILE *file_in = fopen("intermediate.cpp", "w+");
            insert_header(file_in);
            fprintf(file_in, "\tint r0 = getNumRows(0);\n");
            fprintf(file_in, "\tint r1 = getNumRows(1);\n");
            fprintf(file_in, "\tfor(int i = 0; i < r0;i++){\n");
            fprintf(file_in, "\t\tstring s = printRow(0, i);\n");
            fprintf(file_in, "\t\tfor(int j = 0; j < r1;j++)\n");
            fprintf(file_in, "\t\t\tcout<<s<<printRow(1, j)<<endl;\n\t}\n");

            insert_footer(file_in);
            fclose(file_in);

        }
    |    EQUI_JOIN LAB CONDITION_LIST_EQ RAB    ;

TABLE:   ID    ;

CONDITION_LIST_FINAL:   CONDITION_LIST ;

CONDITION_LIST: CONDITION AND CONDITION_LIST     { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); }
    |           CONDITION

CONDITION:      LP CONDITION_LIST RP { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); }
    |           TERM OP EXPR  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); } ;

CONDITION_LIST_EQ: CONDITION_EQ AND CONDITION_LIST_EQ
    |           CONDITION_EQ

CONDITION_EQ:      LP CONDITION_LIST_EQ RP
    |              ID DOT ID EQ ID DOT ID    ;

EXPR:   TERM ARITH_OP EXPR  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); }
    |   TERM MINUS EXPR  { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); }
    |   TERM   ;

TERM:   LP EXPR RP { strcat($$, " "); strcat($$, $2); strcat($$, " "); strcat($$, $3); }
    |   NUM
    |   MINUS NUM { strcat($$, $2); }
    |   ID {
            char columnName[30];
            strcpy(columnName, "getVal( 0, j, \"");
            strcat(columnName, $1);
            strcat(columnName, "\")");
            strcpy($$, columnName);
            }
    |   SIC NUM SIC  { strcat($$, $2); strcat($$, $3); }
    |   SIC ID SIC { strcat($$, $2); strcat($$, $3); }
    |   DIC NUM DIC { strcat($$, $2); strcat($$, $3); }
    |   DIC ID DIC   { strcat($$, $2); strcat($$, $3); } ;

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
