#include <stdio.h>
#include "lex.h"

char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );
char    *mul_factor ( void );

extern char *newname( void       );
extern void freename( char *name );

statements()
{
    /*  statements -> expression SEMI  |  expression SEMI statements  */

    char *tempvar;

    while( !match(EOI) )
    {
        tempvar = expression();

        if( match( SEMI ) )
            advance();
        else
            fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );

        freename( tempvar );
    }
}

char    *expression()
{
    /* expression -> term expression'
     * expression' -> PLUS term expression' | MINUS term expression' |  epsilon
     */

    char  *tempvar, *tempvar2;

    tempvar = term();
    int plus_match = 0;
    while( (plus_match = match( PLUS )) || match( MINUS ))
    {
        advance();
        tempvar2 = term();
        if (plus_match)
            printf("    %s += %s\n", tempvar, tempvar2 );
        else
            printf("    %s -= %s\n", tempvar, tempvar2 );

        freename( tempvar2 );
        
        plus_match = 0;
    }

    return tempvar;
}

char    *term()
{
    /* term -> mul_factor term'
     * term' -> TIMES mul_factor term' |  epsilon
     */

    char  *tempvar, *tempvar2 ;

    tempvar = mul_factor();
    while( match( TIMES ) )
    {
        advance();
        tempvar2 = mul_factor();
        printf("    %s *= %s\n", tempvar, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char    *mul_factor()
{
    /* mul_factor -> factor div_factor
     * div_factor -> DIV factor div_factor |  epsilon
     */

    char  *tempvar, *tempvar2 ;

    tempvar = factor();
    while( match( DIV ) )
    {
        advance();
        tempvar2 = factor();
        printf("    %s /= %s\n", tempvar, tempvar2 );
        freename( tempvar2 );
    }

    return tempvar;
}

char    *factor()
{
    /* factor -> NUM_OR_ID | LP expression RP */
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
