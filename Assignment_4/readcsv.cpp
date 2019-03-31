#include <bits/stdc++.h>
using namespace std;

#define MAX_FILES 5
vector<string> cols[MAX_FILES];
vector<string> data_type[MAX_FILES];
vector<string> table_names[MAX_FILES];
vector<vector<string> > vals[MAX_FILES];


int getcol(string name, int index)
{
	for (int i = 0; i < cols[index].size(); ++i)
	{
		if(i == cols[index].size()-1)
		{
			name += "\n";
		}

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
		}	
	}
	return -1;
}

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

void printRow(int index, int row_number)
{
	if(row_number >= vals[index].size())
	{
		cout<<"Row index out of bound"<<endl;
		return;
	}
	for (int i = 0; i < vals[index][row_number].size(); ++i)
	{
		cout<<vals[index][row_number][i]<<" ";
	}
	cout<<endl;
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
		concat += vals[index][row_number][i] + spacing;
	}
	return concat;
}

void printColumnName(string table) {
	int index = getindexfortable(table);
	string spacing = "";
	int spacinglen = 0;
	for (int i = 0; i < cols[index].size(); i++) {
		spacinglen = max((14 - (int)cols[index][i].length()), 0);
		spacing = string(spacinglen, ' ');
		cout << cols[index][i] << spacing;
	}
}

void readcsv(string name, int index)
{
	string edited_name="";

	for (int i = 0; i < name.length()-4; ++i)
	{
		edited_name += name[i];
	}
	table_names[index].push_back(edited_name);

	char cstr[name.size() + 1];
	strcpy(cstr, name.c_str());

	FILE* stream = fopen(cstr, "r");
	char line[1024];
	int itr;
	string temp = "";

	//read data types
	if(fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
        int len = strlen(tmp);

        string result = "";
       	for (int i = 0; i < len-1; ++i)
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


       	for (int i = 0; i < len - 1; ++i)
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
	
	temp = "";
	while (fgets(line, 1024, stream))
	{
		char* tmp = strdup(line);
        int len = strlen(tmp);
        vector<string> storage;

       	for (int i = 0; i < len - 1; ++i)
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
