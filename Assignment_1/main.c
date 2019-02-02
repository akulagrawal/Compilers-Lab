#include "lex.h"

main ()
{
	while( !match( EOI ) )
		statements ();
}
