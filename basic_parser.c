/* Basic parser, shows the structure but there's no code generation */

#include <stdio.h>
#include "lex.h"


/*
stmt → id := expr 
| if expr then stmt
| while expr do stmt
| begin opt_stmts end

opt_stmts → stmt_list |є

stmt_list → stmt_list; stmt | stmt

stmt_list -> stmt stmt_prime
stmt_prime -> ; stmt stmt_prime | epsilon
*/


statements()
{
    /*  statements -> expression SEMI
     *             |  expression SEMI statements
     */
	/*if( match( ID ) )
	{
		printf("ASSIGN");
		advance();
		if (!match( ASSI ) )
		
			//fprintf("Inserting missing assignment operator");
		expression();
	}
	else */if( match(IF))
	{
		expression();
		if(!match(THEN))
		;//	fprintf("Inserting missing then");
		//else
			statements();
	}
	else if( match( WHILE ))
	{
		expression();
		if( match(  DO ))
		{
			advance();
			statements();
		}
		//fprintf("Inserting missing DO");
	}
	else if( match( BEGIN ))
	{
		begin_prime();
	}
	
	else
	{	
    	expression();

	    if( match( SEMI ) )
		advance();
	    else
	       fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );
	
	    if( !match(EOI) )
	        statements();			/* Do another statement. */
	}	
}

begin_prime()
{
    /*  begin' -> end
     *            |  statements begin_prime
     */
	if(!match ( END ) )
	{
		statements();
		begin_prime();
	}
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
     *              | epsilon
     */

    if( match( PLUS ) || match(MINUS) )
    {
        advance();
        term();
        expr_prime();
    }
}

term()
{
    /* term -> factor term' */

    factor();
    term_prime();
}

term_prime()
{
    /* term' -> TIMES factor term'
     *       |   epsilon
     */

    if( match( TIMES ) || match(DIV))
    {
        advance();
        factor();
        term_prime();
    }
	//what if something else
}

factor()
{
    /* factor   ->    NUM_OR_ID
     *          |     LP expression RP
     */

    if( match(NUM) )
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
		printf( stderr, "%d Number or identifier expected\n", yylineno );
}
