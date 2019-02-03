/* Basic parser, shows the structure but there's no code generation */

#include <stdio.h>
#include "lex.h"

/*
stmt →    if comp_expr then stmt
        | while comp_expr do stmt
        | begin begin'
        | id := comp_expr ; 
        | comp_expr ;
        | comp_expr; stmt

begin' →  end stmt
        | stmt begin'

comp_expr →  expr c_expr

c_expr  →  < expr c_expr
        | > expr c_expr
        | = expr c_expr
        | epsilon

expr →  term expr'

expr' →  + term expr'
        | - term expr'
        | epsilon

term →  factor term'

term' →  * factor term'
        | / factor term'
        | epsilon

factor →  ( expr )
        | num_or_id
*/


statements()
{
    /*
    statements →  if comp_expression then statements
     *          | while comp_expression do statements
     *          | begin begin_prime
     *          | id COLON EQUAL comp_expression SEMI
     *          | comp_expression SEMI
     *          | comp_expression SEMI statements
     */
    
    if( match( IF ) )
    {
        advance();
        comp_expression();
        if( !match( THEN ) )
            fprintf( stderr, "%d: Inserting missing 'then'\n", yylineno );
        else
        {
            advance();
            statements();
        }
    }
    else if( match( WHILE ) )
    {
        advance();
        comp_expression();
        if( !match( DO ) )
            fprintf( stderr, "%d: Inserting missing 'do'\n", yylineno );
        else
        {
            advance();
            statements();
        }
    }
    else if( match( BEGIN ))
    {
        advance();
        begin_prime();
    }
    else
    {   
        comp_expression();

        if( match( SEMI ) )
        advance();
        else
           fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );
    
        if( !match(EOI) )
            statements();           /* Do another statement. */
    }   
}

comp_expression()
{
    /* comp_expr →  expression c_expression */
    expression();
    c_expression();
}

c_expression()
{
    /* c_expression  →  < expression c_expression
     *          | > expression c_expression
     *          | = expression c_expression
     *          | epsilon
     */

    if ( match (LT) || match(GT) || match(EQ) )
    {
        advance();
        expression();
        c_expression();
    }
}

begin_prime()
{
    /* begin' → end statements
     *      |  statements begin_prime
     */

    if(match ( END ) )
    {
        advance();
        statements();
    }
    else
    {
        statements();
        begin_prime();
    }
}

expression()
{
    /* expression → term expression' */

    term();
    expr_prime();
}

expr_prime()
{
    /* expression' → PLUS term expression'
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
    /* term → factor term' */

    factor();
    term_prime();
}

term_prime()
{
    /* term' → TIMES factor term'
     *       | DIV factor term'
     *       |   epsilon
     */

    if( match( TIMES ) || match( DIV ) )
    {
        advance();
        factor();
        term_prime();
    }
}

factor()
{
    /* factor   →    LP expression RP
     *             | NUM_OR_ID
     */


    if( match( LP ) )
    {
        advance();
        expression();
        if( match(RP) )
            advance();
        else
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else if( match( NUM ) || match ( ID ) || match( NUM_OR_ID ) )
        advance();
    else
        printf( stderr, "%d Number or identifier expected\n", yylineno );
}
