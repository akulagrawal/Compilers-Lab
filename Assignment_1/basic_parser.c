/* Basic parser, shows the structure but there's no code generation */

#include <stdio.h>
#include "lex.h"

statements()
{
    /*  statements -> expression SEMI
     *             |  expression SEMI statements
     */

    expression();

    if( match( SEMI ) )
	    advance();
    else
        fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );

    if( !match(EOI) )
        statements();			/* Do another statement. */
}

expression()
{
    /* expression -> term expression' */

    term();
    expr_prime();
}

expr_prime()
{
    /* expression' -> PLUS term expression'
     *              | MINUS term expression'
     *              | epsilon
     */

    if( match( PLUS ) || match( MINUS ) )
    {
        advance();
        term();
        expr_prime();
    }
}

term()
{
    /* term -> mul_factor term' */

    mul_factor();
    term_prime();
}

term_prime()
{
    /* term' -> TIMES mul_factor term'
     *       |   epsilon
     */

    if( match( TIMES ) )
    {
        advance();
        mul_factor();
        term_prime();
    }
}

mul_factor()
{
    /* mul_factor -> factor div_factor */

    factor();
    div_factor();
}

div_factor()
{
    /* div_factor -> DIV factor div_factor
     *            |  epsilon
     */

    if( match( DIV ) )
    {
        advance();
        factor();
        div_factor();
    }
}

factor()
{
    /* factor   ->    NUM_OR_ID
     *          |     LP expression RP
     */

    if( match(NUM_OR_ID) )
        advance();

    else if( match(LP) )
    {
        advance();
        expression();
        if( match(RP) )
            advance();
        else
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else
	fprintf( stderr, "%d Number or identifier expected\n", yylineno );
}
