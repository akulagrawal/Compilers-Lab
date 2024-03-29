#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */

int lex(void){

   static char input_buffer[1024];
   char        *current;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */

   while(1){       /* Get the next one         */
      while(!*current ){
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         current = input_buffer;
         if(!fgets(input_buffer, sizeof(input_buffer), stdin)){
            *current = '\0' ;

            return EOI;
         }
         ++yylineno;
         while(isspace(*current))
            ++current;
      }
      for(; *current; ++current){
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         switch( *current ){
           case ';':
            return SEMI;
           case '+':
            return PLUS;
           case '-':
            return MINUS;
           case '*':
            return TIMES;
           case '/':
            return DIV;
           case '(':
            return LP;
           case ')':
            return RP;
           case '<':
            return LT;
           case '>':
            return GT;
           case '=':
            return EQ;
           case ':':
            return COLON;
           case '\n':
           case '\t':
           case ' ' :
            break;
           default:
            if(!isalnum(*current))
               fprintf(stderr, "Not alphanumeric <%c>\n", *current);
            else
            {
               while(isalnum(*current))
                  ++current;
               yyleng = current - yytext;
               char sym[yyleng+1];
               strncpy(sym, yytext, yyleng);
               sym[yyleng] = '\0';
               if( !strcmp(sym, "if") )
                  return IF;
               else if( !strcmp(sym, "then") )
                  return THEN;
               else if( !strcmp(sym, "endif") )
                  return ENDIF;
               else if( !strcmp(sym, "while") )
                  return WHILE;
               else if( !strcmp(sym, "do") )
                  return DO;
               else if( !strcmp(sym, "endwhile") )
                  return ENDWHILE;
               else if( !strcmp(sym, "begin") )
                  return BEGIN;
               else if( !strcmp(sym, "end") )
                  return END;
               else if( isalpha(*yytext) )
                  return ID;
               else
                  return NUM;
            }
            break;
         }
      }
   }
}


static int Lookahead = -1; /* Lookahead token  */

int match(int token){
   /* Return true if "token" matches the
      current lookahead symbol.                */

   if(Lookahead == -1)
      Lookahead = lex();

   return token == Lookahead;
}



void advance(void){
/* Advance the lookahead to the next
   input symbol.                               */

    Lookahead = lex();
}
