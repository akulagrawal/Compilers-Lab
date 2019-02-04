#include "lex.h"

main ()
{
	while( !match( EOI ) )
		statements ();
	
	system("python3 rename_vars.py IR.txt");
	system("python3 assembler.py");
}
