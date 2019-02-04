#include <stdio.h>
#include "lex.h"

char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );
char    *full_expression ( void );

extern char *newname( void       );
extern void freename( char *name );

char lastid[50];
char lastreg[50];

char toassid[50];
char toassreg[50];

int flag = 0;
int c=0;

statements()
{
    /*  statements -> expression SEMI  
     *               | expression SEMI statements  
     */

    char *tempvar;
    static int countif = 0;
    static int countwhile = 0;
    static int countbegin = 0;

    while( !match(EOI) )
    {
        if( match( IF ) )
        {
            countif++;
            advance();
            tempvar = full_expression();
            printf("ifT %s\n", tempvar);
            if( !match(THEN) )
                fprintf( stderr, "%d: Inserting missing then\n", yylineno );
            advance();
            statements();
            if( match( ENDIF ) ){
                if( countif <= 0 )
                    fprintf( stderr, "%d: Unmatched endif\n", yylineno );
                else{
                    advance();
                    printf("endif\n");
                    countif--;
                }
            }
            else
                fprintf( stderr, "%d: Inserting missing endif\n", yylineno );
        }
        if( match( ENDIF ) ) {return;}
        if( match( WHILE ) )
        {
            countwhile++;
            advance();
            tempvar = full_expression();
            printf("while %s\n", tempvar);
            if( !match(DO) )
                fprintf( stderr, "%d: Inserting missing do\n", yylineno );
            advance();
            statements();
            if( match( ENDWHILE ) ){
                if( countwhile <= 0 )
                    fprintf( stderr, "%d: Unmatched endwhile\n", yylineno );
                else{
                    advance();
                    printf("endwhile\n");
                    countwhile--;
                }
            }
            else
                fprintf( stderr, "%d: Inserting missing endwhile\n", yylineno );
        }
        if( match( ENDWHILE ) ) {return;}
        if( match( BEGIN ) )
        {
            countbegin++;
            advance();
            printf("\n");
            statements();
            if( match( END ) ){
                if( countbegin <= 0 )
                    fprintf( stderr, "%d: Unmatched end\n", yylineno );
                else{
                    advance();
                    printf("\n");
                    countbegin--;
                }
            }
            else
                fprintf( stderr, "%d: Inserting missing end\n", yylineno );
        }
        if( match( END ) ) {return;}
        if( match( ENDIF ) || match( ENDWHILE ) || match( END ) ) {return;}
        if( match(EOI) )
            return;
        tempvar = full_expression();

        if( match( SEMI ) )
        {
            if(flag)
            {
                flag = 0;
                // printf("agaefa\n");
                printf("    %s = %s\n", toassid, toassreg );
            }
            advance();
        }
        else
            fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );

        freename( tempvar );
    }
}

char    *full_expression()
{
    /* full_expression -> expression full_expression'
     * full_expression' -> LT/Gt/EQ expression full_expression' |  epsilon
     */

    char  *tempvar, *tempvar2;

    tempvar = expression();
    while( match( COLON ) || match( LT ) || match( GT ) || match( EQ ) )
    {
        char *op;
        if( match( LT ) )
            op = "<";
        if( match( GT ) )
            op = ">";
        if( match( EQ ) )
            op = "==";
        if( match( COLON ) )
        {
            advance();

            flag = 1;
            char *current = lastreg;
            for(;*current; ++current)
            {
                toassreg[c++] = *current;
            }
            toassreg[c++] = '\0';

            c=0;
            current = lastid;

            for(;*current; ++current)
            {
                toassid[c++] = *current;
            }
            toassid[c++] = '\0';

            c=0;
            op = "=";
        }

        advance();
        tempvar2 = expression();
        printf("    %s %s %s\n", tempvar, op, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char    *expression()
{
    /* expression -> term expression'
     * expression' -> PLUS/MINUS term expression' |  epsilon
     */

    char  *tempvar, *tempvar2;

    tempvar = term();
    while( match( PLUS ) || match( MINUS ) )
    {
        char op;
        if( match( PLUS ) )
            op = '+';
        if( match( MINUS ) )
            op = '-';
        advance();
        tempvar2 = term();
        printf("    %s %c= %s\n", tempvar, op, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char    *term()
{
    /* term -> factor term'
     * term' -> TIMES factor term' 
     *          | DIV factor term'
     *          | epsilon
     */

    char  *tempvar, *tempvar2 ;

    tempvar = factor();
    while( match( TIMES ) || match( DIV ) )
    {
        char op;
        if( match( TIMES ) )
            op = '*';
        if( match( DIV ) )
            op = '/';
        advance();
        tempvar2 = factor();
        printf("    %s %c= %s\n", tempvar, op, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char    *factor()
{
    /* factor -> NUM_OR_ID 
     *         | LP expression RP 
     */
    char *tempvar;

    if( match(NUM) || match(ID) )
    {
    /* Print the assignment instruction. The %0.*s conversion is a form of
     * %X.Ys, where X is the field width and Y is the maximum number of
     * characters that will be printed (even if the string is longer). I'm
     * using the %0.*s to print the string because it's not \0 terminated.
     * The field has a default width of 0, but it will grow the size needed
     * to print the string. The ".*" tells printf() to take the maximum-
     * number-of-characters count from the next argument (yyleng).
     */

        char * current = yytext;
        if(*current == '1' || *current == '2' || *current == '3' || *current == '4' || *current == '5' ||
           *current == '6' || *current == '7' || *current == '8' || *current == '9' || *current == '0')
        {
            printf("    %s = %0.*s\n", tempvar = newname(), yyleng, yytext );
            advance();
        }
        else
        {
            printf("    %s = $%0.*s\n", tempvar = newname(), yyleng, yytext );
            
            char *current = tempvar;


            for(; *current; ++current)
            {
                lastreg[c++] = *current;
            }
            lastreg[c] = '\0';

            c=0;

            current = yytext;

            lastid[c++] = '$';

            while(c<=yyleng)
            {
                lastid[c++] = *current;
                current++;
            }
            lastid[c] = '\0';  
            c=0;          

            advance();
        }
        
    }
    else if( match(LP) )
    {
        advance();
        tempvar = expression();
        if( match(RP) )
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno );
    }
    else
	fprintf( stderr, "%d: Number or identifier expected\n", yylineno );

    return tempvar;
}
