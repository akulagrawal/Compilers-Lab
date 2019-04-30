## Problem Statement

Write a Java Code Analyzer Program (in any language of your choice) that determines in an input
file, the total number of lines containing each of the following categories:
1) Objects declaration
2) Class definition
3) Constructor definition
4) Inherited Class definition

Note that a single line could contain instances from more than one categories listed above, and
hence must be counted in all the categories to which it belongs. Eg an inherited class definition
would be counted in both categories 2 and 4. The program must read the input code(for counting)
from an external file (input.txt), and write the results into an output file (output.txt)
