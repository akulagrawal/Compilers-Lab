<<<<<<< HEAD
=======
#include <bits/stdc++.h>
using namespace std;

>>>>>>> shimona
#define MAX_FILES 5
vector<string> cols[MAX_FILES];
vector<string> data_type[MAX_FILES];
vector<string> table_names[MAX_FILES];
vector<vector<string> > vals[MAX_FILES];


int getcol(string name, int index)
{
	for (int i = 0; i < cols[index].size(); ++i)
	{
<<<<<<< HEAD
		if(i == cols[index].size()-1)
		{
			name += "\n";
		}

=======
>>>>>>> shimona
		if(name.compare(cols[index][i])==0)
		{
			return i;
		}
	}
	return -1;
}

int getindexfortable(string name)
{
	for (int j = 0; j < MAX_FILES; ++j)
	{
		for (int i = 0; i < table_names[j].size(); ++i)
		{
			if(table_names[j][i] == name)
			{
				return j;
			}
<<<<<<< HEAD
		}
=======
		}	
>>>>>>> shimona
	}
	return -1;
}

<<<<<<< HEAD
int getNumRows(int index)
{
	//int index = getindexfortable(name);
=======
int getNumRows(string name)
{
	int index = getindexfortable(name);
	if(index == -1)
	{
		cout<<"No such table exists"<<endl;
		return -1;
	}
	return vals[index].size();
}

int getNumCols(string name)
{
	int index = getindexfortable(name);
	if(index == -1)
	{
		cout<<"No such table exists"<<endl;
		return -1;
	}
	return cols[index].size();
}

int getNumRowsCartesian(int index)
{
>>>>>>> shimona
	if(index == -1)
	{
		cout<<"No such table exists"<<endl;
		return -1;
	}
	return vals[index].size();
}

<<<<<<< HEAD
int getNumCols(int index)
{
	//int index = getindexfortable(name);
=======
int getNumColsCartesian(int index)
{
>>>>>>> shimona
	if(index == -1)
	{
		cout<<"No such table exists"<<endl;
		return -1;
	}
	return cols[index].size();
}

void printRow(int index, int row_number)
{
	if(row_number >= vals[index].size())
	{
		cout<<"Row index out of bound"<<endl;
		return;
	}
	for (int i = 0; i < vals[index][row_number].size(); ++i)
<<<<<<< HEAD
		cout<<setw(20)<<vals[index][row_number][i]+" ";
	return;
	//cout<<endl;
=======
	{
		cout<<setw(14)<<vals[index][row_number][i]+" ";
	}
}

string getRow(int index, int row_number) {
	
	if(row_number >= vals[index].size())
	{
		cout<<"Row index out of bound"<<endl;
		return "";
	}

	string concat = "";
	string spacing = "";
	int spacinglen = 0;
	for (int i = 0; i < vals[index][row_number].size(); ++i)
	{
		spacinglen = max((14 - (int)vals[index][row_number][i].length()), 0);
		spacing = string(spacinglen, ' ');
		concat += spacing + vals[index][row_number][i];
	}
	return concat;
}

void printColumnName(string table) {
	int index = getindexfortable(table);
	string spacing = "";
	int spacinglen = 0;
	for (int i = 0; i < cols[index].size(); i++) {
		cout<<setw(14)<<cols[index][i]+" ";
	}
>>>>>>> shimona
}

void readcsv(string name, int index)
{
	string edited_name="";

<<<<<<< HEAD
=======
	// Removing .csv
>>>>>>> shimona
	for (int i = 0; i < name.length()-4; ++i)
	{
		edited_name += name[i];
	}
	table_names[index].push_back(edited_name);

	char cstr[name.size() + 1];
	strcpy(cstr, name.c_str());

	FILE* stream = fopen(cstr, "r");
<<<<<<< HEAD
=======
	if (stream == NULL) {
		cout << "Table: " << edited_name << " does not exists\n";
		exit(0);
	}
>>>>>>> shimona
	char line[1024];
	int itr;
	string temp = "";

	//read data types
	if(fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
        int len = strlen(tmp);

        string result = "";
<<<<<<< HEAD
       	for (int i = 0; i < len; ++i)
=======
       	for (int i = 0; i < len-1; ++i)
>>>>>>> shimona
       	{
			if(line[i] == ',')
			{
				// cols[index].push_back(temp);
				if(temp[0] == 'i')
				{
					result += "i";
				}
				else
				{
					result += "s";
				}
				temp = "";
			}
			else
			{
				temp+=line[i];
			}
       	}
       	if(temp[0] == 'i')
		{
			result += "i";
		}
		else
		{
			result += "s";
		}
		temp = "";
       	data_type[index].push_back(result);
	}

	//read coloumn names
	if(fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
        int len = strlen(tmp);


<<<<<<< HEAD
       	for (int i = 0; i < len; ++i)
=======
       	for (int i = 0; i < len - 1; ++i)
>>>>>>> shimona
       	{
			if(line[i] == ',')
			{
				cols[index].push_back(temp);
				temp = "";
			}
			else
			{
				temp+=line[i];
			}
       	}
       	cols[index].push_back(temp);
	}
<<<<<<< HEAD

=======
	
>>>>>>> shimona
	temp = "";
	while (fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
        int len = strlen(tmp);
        vector<string> storage;

<<<<<<< HEAD
       	for (int i = 0; i < len; ++i)
=======
       	for (int i = 0; i < len - 1; ++i)
>>>>>>> shimona
       	{
			if(line[i] == ',')
			{
				storage.push_back(temp);
				temp = "";
			}
			else
			{
				temp+=line[i];
			}
       	}
       	storage.push_back(temp);
       	temp = "";
       	vals[index].push_back(storage);
	}
	fclose(stream);
}

//row number, coloumn name
string getVal(int index, int row_number, string coloumn)
{
	while(row_number >= vals[index].size())
	{
		cout<<"Entry not present please reenter: "<<endl;
		cin>>row_number;
	}

	int b = getcol(coloumn, index);
	while(b<0)
	{
		cout<<"No such coloumn please reenter: "<<endl;
		cin>>coloumn;
		b = getcol(coloumn, index);
	}

	return vals[index][row_number][b];
}

void query(string name)
{
	int index = getindexfortable(name);
	if(index == -1)
	{
		cout<<"No such table exists"<<endl;
		return;
	}
	else
	{
		cout<<"index: "<<index<<endl;
	}

	int a,b;
	for (int i = 0; i < data_type[index].size(); ++i)
	{
		cout<<data_type[index][i]<<endl;
	}

	cout<<"coloumn names: ";
	for (int i = 0; i < cols[index].size(); ++i)
	{
		cout<<"index: "<<i<<" "<<cols[index][i]<<" ";
	}
	cout<<endl;

	cout<<"Enter entry number: ";
	cin>>a;

	cout<<"Enter coloumn name: ";
	string col_name;
	cin>>col_name;

	cout<<"Value: "<<getVal(index, a, col_name)<<endl;
}
