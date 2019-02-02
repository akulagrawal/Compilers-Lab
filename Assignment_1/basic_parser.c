/* Basic parser, shows the structure but there's no code generation */

#include <stdio.h>
#include "lex.h"

/*
stmt →    if comp_expr then stmt endif
		| while comp_expr do stmt endwhile
		| begin begin'
		| id := comp_expr ; 
		| comp_expr ;
		| comp_expr; stmt

begin' →  end
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
	statements →  if comp_expression then statements endif
	 *			| while comp_expression do statements endwhile
	 *			| begin begin_prime
	 *			| id COLON EQUAL comp_expression SEMI
	 *			| comp_expression SEMI
	 *			| comp_expression SEMI statements
	 */
	
	if( match( IF ) )
	{
		advance();
		comp_expression();
		if( match( THEN ) )
		{
			advance();
			statements();
		}
		else
			ERROR("Inserting missing 'then'");
		if( !match( ENDIF ) )
		{
			ERROR("Inserting missing 'endif'");
		}
		else
			advance();
	}
	else if( match( WHILE ) )
	{
		advance();
		comp_expression();
		if( match( DO ) )
		{
			advance();
			statements();
		}
		else
			ERROR("Inserting missing 'do'");
		if( !match( ENDWHILE ) )
		{
			ERROR("Inserting missing 'endwhile'");
		}
		else
			advance();
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
	       ERROR("Inserting missing semicolon");
	
	    if( !match( ENDIF ) && !match( ENDWHILE ) && !match( END ) && !match(EOI) )
	        statements();			/* Do another statement. */
	}	
}

comp_expression()
{
	/* comp_expr →  expression c_expression	*/
	expression();
	c_expression();
}

c_expression()
{
	/* c_expression  →  < expression c_expression
	 *			| > expression c_expression
	 *			| = expression c_expression
	 *			| epsilon
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
    /* begin' → end
	 *		|  statements begin_prime
     */

	if(match ( END ) )
		advance();
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
	 *				| MINUS term expression'
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
	 *		 | DIV factor term'
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
     *  	       | NUM_OR_ID
     */


    if( match( LP ) )
    {
        advance();
        expression();
        if( match(RP) )
            advance();
        else
            ERROR("Mismatched parenthesis");
    }
    else if( match( NUM ) || match ( ID ) || match( NUM_OR_ID ) )
        advance();
    else
		ERROR("Number or identifier expected");	
}
