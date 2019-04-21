#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long
#define mp make_pair
#define MAX 1000006
#define mod 1000000007
#define pb push_back
#define INF 1e18
#define pii pair<int,int>
#define OFFSET 268435455

struct quad {
	string opcode;
	string op1;
	string op2;
	string res;
};

int isfull[MAX];
int memory[MAX];
map<string, int> mapmem;

int getmem(string s) {
	if(mapmem[s])
		return mapmem[s];
	for(int i=1;i<MAX;i+=4) {
		if(!isfull[i]) {
			mapmem[s] = i;
			isfull[i] =1;
			return i;
		}
	}
	exit(1);
}

string hextoken(int x) {
	if (x % 16 < 10)
		return to_string(x % 16);
	string s;
	s.push_back('a' + x % 16 - 9);
	return s;
}

string to_hex(int y) {
	long long x = (long long)y;
	x+= OFFSET;
	string s;
	while(x) {
		s = hextoken(x % 16) + s;
		x/=16;
	}
	s = "0x" + s;
	return s;
}

int main()
{   
    freopen ("Assembly.asm","w",stdout);
	// File pointer 
	fstream fin; 
	vector<quad> quadlist;
	quad temp;

	// Open an existing file 
	fin.open("IR.csv", ios::in); 
	vector<string> row;
	string line, word; 
	vector<string> v;
	v.push_back(".data 0x10000000\n.text\n.globl main\nmain: ");

	while (fin >> line) { 
		row.clear();

		// used for breaking words 
		stringstream s(line);

		// read every column data of a row and 
		// store it in a string variable, 'word' 
		while (getline(s, word, ',')) { 
			// add all the column data 
			// of a row to a vector
			row.push_back(word); 
		}
		temp.opcode = row[0];
		temp.op1 = row[1];
		temp.op2 = row[2];
		temp.res = row[3];
		// cout << "Opcode: " << temp.opcode << "\n"; 
		// cout << "Op1   : " << temp.op1 << "\n"; 
		// cout << "Op1   : " << temp.op2 << "\n"; 
		// cout << "Res   : " << temp.res << "\n";
		if(row[0] == "assign") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = getmem(row[1]);
			v.push_back("li $t0, " + row[2]);
			v.push_back("sw $t0, " + to_hex(x) + "($0)");
		}
		if(row[0] == "+") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			if(!mapmem[row[1]] || !mapmem[row[2]]) {
				cout<<"ERROR: Variable Unassigned\n";
				exit(1);
			}
			int x = memory[mapmem[row[1]]];
			int y = memory[mapmem[row[2]]];
			v.push_back("lw $t0, " + to_hex(mapmem[row[1]]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[row[2]]) + "($0)");
			v.push_back("add $v0, $t0, $t1");
			int z = getmem(row[3]);
			v.push_back("sw $v0, " + to_hex(z) + "($0)");
		}
		/*if(row[0] == "-") {
			int x = getfree();
			int y = getfree();
			if(x < 0 || y < 0) {
				cout<<"Register overflow error\n";
				exit(1);
			}
			register[x] = stoi(row[0]);
			register[y] = stoi(row[1]);
			v.push_back("sub $v0, $t" + itos(x) + ", $t" + itos(y));
		}
		if(row[0] == "*") {
			int x = getfree();
			int y = getfree();
			if(x < 0 || y < 0) {
				cout<<"Register overflow error\n";
				exit(1);
			}
			register[x] = stoi(row[0]);
			register[y] = stoi(row[1]);
			v.push_back("mult $t" + itos(x) + ", $t" + itos(y));
			v.push_back("")
		}
		if(row[0] == "/") {
			int x = getfree();
			int y = getfree();
			if(x < 0 || y < 0) {
				cout<<"Register overflow error\n";
				exit(1);
			}
			register[x] = stoi(row[0]);
			register[y] = stoi(row[1]);
			v.push_back("sub $v0, $t" + itos(x) + ", $t" + itos(y));
			v.push_back("")
		}
		if(row[0] == "ifz") {
			cout<<"beq "<<row[1]<<", "<<row[2]<<", "<<row[3]<<endl;
		}*/


	}
	v.push_back("jr $ra");
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<endl;
	}

    return 0;
}