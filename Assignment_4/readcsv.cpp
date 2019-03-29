#include <bits/stdc++.h>
#define MAX_FILES 5

using namespace std;

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
       	for (int i = 0; i < len; ++i)
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


       	for (int i = 0; i < len; ++i)
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

       	for (int i = 0; i < len; ++i)
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

int main()
{
	string filename;
	int index;
	int choice;
	
	string a;
	int x;

	do
	{
		cout<<"1. Read a csv file."<<endl;
		cout<<"2. Query a already read table. "<<endl;
		cout<<"3. Number of rows. "<<endl;
		cout<<"4. Get Value at. "<<endl;
		cout<<"5. Print Row. "<<endl;
		cout<<"Enter Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Enter File name: ";
				cin>>filename;

				// uncomment for multiple files
				// cout<<"Enter index: ";
				// cin>>index;
				// readcsv(filename, index);
				index = 0;
				readcsv(filename, index);

				for (int i = 0; i < vals[index].size(); ++i)
				{
					for (int j = 0; j< vals[index][i].size(); ++j)
					{
						cout<<vals[index][i][j]<<" ";
					}
					cout<<endl;
				}
				break;
			case 2:
				cout<<"Enter table name: ";
				cin>>a;	
				query(a);
				break;
			case 3:
				cout<<"Enter table name: ";
				cin>>a;
				cout<<"Number of rows: "<<getNumRows(a)<<endl;
				break;
			case 4:
				cout<<"Enter index: ";
				cin>>x;
				cout<<"Enter coloumn name: ";
				cin>>a;
				cout<<"Value: "<<getVal(0,x, a)<<endl;
				break;
			case 5:
				cout<<"Enter row number: ";
				cin>>x;
				printRow(0, x);
				break;
			default:
				return 0;
		}
	}
	while(1);
	return 0;
}