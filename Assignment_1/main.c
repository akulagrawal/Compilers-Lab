#include <stdio.h>

FILE *inter;

main ()
{
	inter = fopen("inter.txt", "w");
	statements ();
	fclose(inter);
}
