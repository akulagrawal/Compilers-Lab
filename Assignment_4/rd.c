#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 10
#define MAX_COL_LEN 10
#define MAX_FILES 10
#define MAX_FILES_LEN 10


char data_type[MAX_FILES][MAX_COLS];
char col_name[MAX_FILES][MAX_COLS][MAX_COL_LEN];
char file_name[MAX_FILES][MAX_FILES_LEN];
int num_files;

void readcsv(int index, char* name)
{
	//name of the file pushed
	int name_len = strlen(name);
	for (int i = 0; i < name_len-4; ++i)
	{
		file_name[index][i] = name[i];
	}

	FILE* stream = fopen(name, "r");
	char type_line[1024];
	int itr;
	
	if(fgets(type_line, 1024, stream))
	{
        int len = strlen(type_line);
   		printf("%s\n", type_line);
   		int i=0;
	}

	char name_line[1024];
	if(fgets(name_line, 1024, stream))
	{
   		printf("%s\n", name_line);
   		int i=0;
	}


	int top=0;
    int len = strlen(name_line);
    int j=0;
	for (int i = 0; i < len; ++i)
	{
		if(name_line[i] != ',' && name_line[i] != '\n')
		{
			col_name[index][top][j++] = name_line[i];
		}
		else
		{
			j = 0;
			top++;
		}	
	}
		
	top = 0;
    len = strlen(type_line);
    for (int i = 0; i < len; ++i)
	{
		if(type_line[i] != ',' && type_line[i] != '\n')
		{
			data_type[index][top] = type_line[i];
		}
		else
		{
			top++;
		}	
	}
	num_files++;
}

int getfileindex(char* name)
{
	for (int i = 0; i < MAX_FILES; ++i)
	{
		if(strcmp(file_name[i], name)==0)
		{
			return i;
		}
	}
	return -1;
}

void p(int index)
{
	
	for (int i = 0; i < MAX_COLS; ++i)
	{
		if(strlen(col_name[index][i]) != 0)
		{
			printf("Name: %s ",col_name[index][i]);
			printf("Type: %c\n",data_type[index][i]);
		}
	}
}

int getcolindex(int index, char* col)
{
	for (int i = 0; i < MAX_COLS; ++i)
	{
		if(strcmp(col_name[index][i], col) == 0)
		{
			return i;
		}
	}
	return -1;
}

//returns 0 for string 1 for int
int gettype(char* table_name, char* col)
{
	int index = getfileindex(table_name);
	if(index == -1)
	{
		printf("Nos such Table loaded.\n");
		return -1;
	}

	int colindex = getcolindex(index, col);
	if(colindex == -1)
	{
		printf("Nos such Table loaded.\n");
		return -1;
	}	

	if(data_type[index][colindex] == 'i')
	{
		return 1;
	}
	return 0;
}

int main()
{
	num_files = 0;
	readcsv(num_files,"bc.csv");
	// p(0);
	printf("type: %d\n", gettype("bc", "qwe"));
	return 0;
}