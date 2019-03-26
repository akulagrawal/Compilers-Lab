#include <bits/stdc++.h>
#define MAX_FILES 5

using namespace std;

vector<string> cols[MAX_FILES];
vector<vector<string> > vals[MAX_FILES];


int getcol(string name, int index)
{
	for (int i = 0; i < cols[index].size(); ++i)
	{
		if(name.compare(cols[index][i])==0)
		{
			return i;
		}
	}
	return -1;
}

void readcsv(string name, int index)
{
	char cstr[name.size() + 1];
	strcpy(cstr, name.c_str());

	FILE* stream = fopen(cstr, "r");
	char line[1024];
	int itr;
	string temp = "";
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

void query(int index)
{
	int a,b;
	cout<<"Enter entry number: ";
	cin>>a;
	while(a >= vals[index].size())
	{
		cout<<"Entry not present please reenter: "<<endl;
		cin>>a;
	}

	cout<<"Enter coloumn name: ";
	string name;
	cin>>name;

	b = getcol(name, index);
	while(b<0)
	{
		cout<<"No such coloumn please reenter: "<<endl;
		cin>>name;
		b = getcol(name, index);
	}

	cout<<"Value: "<<vals[index][a][b]<<endl;
}

int main()
{
	string filename;
	int index;
	cout<<"Enter File name: ";
	cin>>filename;
	cout<<"Enter index: ";
	cin>>index;
	readcsv(filename, index);

	for (int i = 0; i < vals[index].size(); ++i)
	{
		for (int j = 0; j< vals[index][i].size(); ++j)
		{
			cout<<vals[index][i][j]<<" ";
		}
		cout<<endl;
	}

	int a = 0;
	int t;
	while(a != -1)
	{
		cout<<"Enter index of table: ";
		cin>>a;
		if(a == -1)
		{
			return 0;
		}
		query(a);
	}

	return 0;
}