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
map<string, int> funcArgs;

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
	s.push_back('a' + x % 16 - 10);
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

int main(int argc, char **argv)
{
    freopen ("Assembly.asm","w",stdout);
	// File pointer
	fstream fin;
	vector<quad> quadlist;
	quad temp;

	// Open an existing file
	fin.open("../IR.csv", ios::in);
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
		quadlist.push_back(temp);
		// cout << "Opcode: " << temp.opcode << "\n";
		// cout << "Op1   : " << temp.op1 << "\n";
		// cout << "Op1   : " << temp.op2 << "\n";
		// cout << "Res   : " << temp.res << "\n";
	}
	map<string, int> isLabel;
	int labelidx = 1;
	for(int i=0;i<quadlist.size();i++) {
		if((quadlist[i].opcode == "ifF") || (quadlist[i].opcode == "ifT")) {
			if(!isLabel[quadlist[i].res]) {
				isLabel[quadlist[i].res] = labelidx;
				labelidx++;
			}
		}
	}
	for(int i=0;i<quadlist.size();i++) {
		string idx = to_string(i);
		if(isLabel[idx])
			v.push_back("Label" + to_string(isLabel[idx]) + ":");
		temp = quadlist[i];
		if(temp.opcode == "DECL") {
			int x = getmem(temp.op1);
			v.push_back("li $t0, 0");
			v.push_back("sw $t0, " + to_hex(x) + "($0)");
		}
		if(temp.opcode == "=") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = getmem(temp.op1);
			if(isdigit(temp.op2[0]))
				v.push_back("li $t0, " + temp.op2);
			else
				v.push_back("lw $t0, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("sw $t0, " + to_hex(x) + "($0)");
		}
		if(temp.opcode == "+") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("add $v0, $t0, $t1");
			int z = getmem(temp.res);
			v.push_back("sw $v0, " + to_hex(z) + "($0)");
		}
		if(temp.opcode == "-") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("sub $v0, $t0, $t1");
			int z = getmem(temp.res);
			v.push_back("sw $v0, " + to_hex(z) + "($0)");
		}
		if(temp.opcode == "*") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("mult $t0, $t1");
			v.push_back("mflo $v0");
			int z = getmem(temp.res);
			v.push_back("sw $v0, " + to_hex(z) + "($0)");
		}
		if(temp.opcode == "/") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("div $t0, $t1");
			v.push_back("mflo $v0");
			int z = getmem(temp.res);
			v.push_back("sw $v0, " + to_hex(z) + "($0)");
		}
		if(temp.opcode == "ifF") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("beqz $t0, Label" + to_string(isLabel[quadlist[i].res]));
		}
		if(temp.opcode == "ifT") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("bnez $t0, Label" + to_string(isLabel[quadlist[i].res]));
		}
		if(temp.opcode == "<") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("li $v0, 1");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("blt $t0, $t1, Label" + to_string(labelidx));
			v.push_back("li $v0, 0");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("Label" + to_string(labelidx) + ":");
			labelidx++;
		}
		if(temp.opcode == ">") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("li $v0, 1");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("bgt $t0, $t1, Label" + to_string(labelidx));
			v.push_back("li $v0, 0");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("Label" + to_string(labelidx) + ":");
			labelidx++;
		}
		if(temp.opcode == "<=") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("li $v0, 1");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("ble $t0, $t1, Label" + to_string(labelidx));
			v.push_back("li $v0, 0");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("Label" + to_string(labelidx) + ":");
			labelidx++;
		}
		if(temp.opcode == ">=") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("li $v0, 1");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("bge $t0, $t1, Label" + to_string(labelidx));
			v.push_back("li $v0, 0");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("Label" + to_string(labelidx) + ":");
			labelidx++;
		}
		if(temp.opcode == "==") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = memory[mapmem[temp.op1]];
			int y = memory[mapmem[temp.op2]];
			v.push_back("li $v0, 1");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("lw $t0, " + to_hex(mapmem[temp.op1]) + "($0)");
			v.push_back("lw $t1, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("beq $t0, $t1, Label" + to_string(labelidx));
			v.push_back("li $v0, 0");
			v.push_back("sw $v0, " + to_hex(mapmem[temp.res]) + "($0)");
			v.push_back("Label" + to_string(labelidx) + ":");
			labelidx++;
		}
		if(temp.opcode == "assign") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = getmem(temp.res);
			if(isdigit(temp.op2[0]))
				v.push_back("li $t0, " + temp.op2);
			else
				v.push_back("lw $t0, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("sw $t0, " + to_hex(x) + "($0)");
		}
		if(temp.opcode == "label") {
			//int x = getfree();
			//int y = getfree();
			//if(x < 0 || y < 0) {
			//	cout<<"ERROR: Register overflow\n";
			//	exit(1);
			//}
			int x = getmem(temp.res);
			if(isdigit(temp.op2[0]))
				v.push_back("li $t0, " + temp.op2);
			else
				v.push_back("lw $t0, " + to_hex(mapmem[temp.op2]) + "($0)");
			v.push_back("sw $t0, " + to_hex(x) + "($0)");
		}

		/*if(temp.opcode == "-") {
			int x = getfree();
			int y = getfree();
			if(x < 0 || y < 0) {
				cout<<"Register overflow error\n";
				exit(1);
			}
			register[x] = stoi(temp.opcode);
			register[y] = stoi(temp.op1);
			v.push_back("sub $v0, $t" + itos(x) + ", $t" + itos(y));
		}
		if(temp.opcode == "*") {
			int x = getfree();
			int y = getfree();
			if(x < 0 || y < 0) {
				cout<<"Register overflow error\n";
				exit(1);
			}
			register[x] = stoi(temp.opcode);
			register[y] = stoi(temp.op1);
			v.push_back("mult $t" + itos(x) + ", $t" + itos(y));
			v.push_back("")
		}
		if(temp.opcode == "/") {
			int x = getfree();
			int y = getfree();
			if(x < 0 || y < 0) {
				cout<<"Register overflow error\n";
				exit(1);
			}
			register[x] = stoi(temp.opcode);
			register[y] = stoi(temp.op1);
			v.push_back("sub $v0, $t" + itos(x) + ", $t" + itos(y));
			v.push_back("")
		}
		if(temp.opcode == "ifz") {
			cout<<"beq "<<temp.op1<<", "<<temp.op2<<", "<<temp.res<<endl;
		}*/


	}
	v.push_back("jr $ra");
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<endl;
	}

    return 0;
}
/* To display $t0
move $a0, $t0
li $v0, 1
syscall
*/
