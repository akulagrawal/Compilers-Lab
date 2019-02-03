#include <stdio.h>
#include "lex.h"

char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );
char    *full_expression ( void );

extern char *newname( void       );
extern void freename( char *name );

statements()
{
    /*  statements -> expression SEMI  |  expression SEMI statements  */

    char *tempvar;

    while( !match(EOI) )
    {
        if( match( IF ) )
        {
            advance();
            tempvar = full_expression();
            printf("if %s\n", tempvar);
            if( !match(THEN) )
                fprintf( stderr, "%d: Inserting missing then\n", yylineno );
            advance();
            statements();
            if( match( ENDIF ) )
                printf("endif\n");
            else
                fprintf( stderr, "%d: Inserting missing endif\n", yylineno );
        }
        if( match( ENDIF ) ) {}
        if( match( WHILE ) )
        {
            advance();
            tempvar = full_expression();
            printf("while %s\n", tempvar);
            if( !match(DO) )
                fprintf( stderr, "%d: Inserting missing do\n", yylineno );
            advance();
            statements();
            if( match( ENDWHILE ) )
                printf("endwhile\n");
            else
                fprintf( stderr, "%d: Inserting missing endwhile\n", yylineno );
        }
        if( match( ENDWHILE ) ) {}
        tempvar = full_expression();

        if( match( SEMI ) )
            advance();
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
    while( match( LT ) || match( GT ) || match( EQ ) )
    {
        char op;
        if( match( LT ) )
            op = '<';
        if( match( GT ) )
            op = '>';
        if( match( EQ ) )
            op = '=';
        advance();
        tempvar2 = expression();
        printf("    %s %c %s\n", tempvar, op, tempvar2 );
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
    char *tempvar;

    if( match(NUM_OR_ID) )
    {
	/* Print the assignment instruction. The %0.*s conversion is a form of
	 * %X.Ys, where X is the field width and Y is the maximum number of
	 * characters that will be printed (even if the string is longer). I'm
	 * using the %0.*s to print the string because it's not \0 terminated.
	 * The field has a default width of 0, but it will grow the size needed
	 * to print the string. The ".*" tells printf() to take the maximum-
	 * number-of-characters count from the next argument (yyleng).
	 */

        printf("    %s = %0.*s\n", tempvar = newname(), yyleng, yytext );
        advance();
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
